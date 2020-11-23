#pragma once
/** \file IProcess.h */
/** Header for IProcess Class */
// Created by Myles Cardiff

#include <functional>
#include <Common.h>


//! \namespace Sloth Engine
namespace slth
{
/** \class IProcess */
/** Base class for processes*/
class IProcess
{
public:
	// --------------------------------------------------------------------- //
	// Public Member Variables
	// --------------------------------------------------------------------- //

	enum class State
	{
		kUnintialized,
		kSucceeded,
		kFailed,
		kPaused,
		kAborted,
		kRunning,
	};

	// --------------------------------------------------------------------- //
	// Public Member Functions
	// --------------------------------------------------------------------- //
	
	/** Default Constructor */
	IProcess();

	/** Default Destructor */
	virtual ~IProcess();

	virtual bool Init() { return true; }
	virtual bool Init(XmlData* pElement) { return true; }
	
	virtual void Update(float deltaTime) = 0;

	void OnSucceed()	{ if (m_onSucceed)	{ m_onSucceed(); } }
	void OnFail()		{ if (m_onFail)		{ m_onFail(); } }
	void OnAbort()		{ if (m_onAbort)	{ m_onAbort(); } }

	void AttachChildProcess(IProcess* pProcess) { m_pChild = pProcess; } 
	IProcess* RemoveChildProcess();

protected:
	// --------------------------------------------------------------------- //
	// Private Member Variables
	// --------------------------------------------------------------------- //
	State m_state;
	IProcess* m_pChild;

	using ProcessCallback = std::function<void()>;

	ProcessCallback m_onSucceed;
	ProcessCallback m_onFail;
	ProcessCallback m_onAbort;

	Id m_nextProcessId;

	// --------------------------------------------------------------------- //
	// Private Member Functions
	// --------------------------------------------------------------------- //


public:
	// --------------------------------------------------------------------- //
	// Accessors & Mutators
	// --------------------------------------------------------------------- //
	virtual void Resume()	{ m_state = State::kRunning; }
	virtual void Pause()	{ m_state = State::kPaused; }
	virtual void Abort()	{ m_state = State::kAborted; }
	virtual void Succeed()	{ m_state = State::kSucceeded; }
	virtual void Fail()		{ m_state = State::kFailed; }

	State GetState() const { return m_state; }
	bool IsAlive() const { return (m_state == State::kRunning || m_state == State::kPaused); }
	bool IsDead() const;

	void SetSucceedCallback(ProcessCallback onSucceed) { m_onSucceed = onSucceed; }
	void SetFailCallback(ProcessCallback onFail) { m_onFail = onFail; }
	void SetAbortCallback(ProcessCallback onAbort) { m_onAbort = onAbort; }

	//void SetParent(IProcess* pParent) {m_p}

	Id GetNextProcessID() { return m_nextProcessId; }
	void SetChild(IProcess* pChild) { m_pChild = pChild; }

};
} 