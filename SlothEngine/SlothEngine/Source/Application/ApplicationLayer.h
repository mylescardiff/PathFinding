#pragma once
#include <memory>

#include <Application/Systems/ISystem.h>
#include <Audio/IAudioSystem.h>
#include <Logic/IGameLayer.h>
#include <Application/Window/SFMLWindow.h>
#include <Logic/Processes/ProcessManager.h>
#include <Logic/AnimationManager.h>
#include "../Common.h"

#include <Input/IKeyboard.h>
#include <Input/IMouse.h>

namespace slth
{
	class IGraphics;

	class ApplicationLayer
	{
	public:
		/** Default Constructor */
		SLTH_API ApplicationLayer();

		/** Default Destructor */
		SLTH_API ~ApplicationLayer();

		/** Start the engine */
		SLTH_API virtual bool Init();

		/** Runs the main loop */
		SLTH_API virtual void Run();

		/** Terminate the engine */
		SLTH_API virtual void Shutdown();

		/** Create the game layer */
		SLTH_API virtual ApplicationLayer* Create() = 0;

		
	protected: 
		
		// sub-system pointers
		ISystem* m_pSystem;
		IGameLayer* m_pGameLayer;
		IWindow* m_pWindow;
		IGraphics* m_pGraphics;
		IAudioSystem* m_pAudio;
		World* m_pWorld;
		IKeyboard* m_pKeyboard;
		IMouse* m_pMouse;

	public:
		
		// Accessors and Mutators
		IGraphics* GetGraphics() { return m_pGraphics; }
		IAudioSystem* GetAudio() { return m_pAudio; }
		IKeyboard* GetKeyboard() { return m_pKeyboard; }
		IMouse* GetMouse() { return m_pMouse; }
		World* GetWorld() { return m_pWorld; }
		ISystem* GetSystem() { return m_pSystem; }
		IWindow* GetWindow() { return m_pWindow; }
	};
}



