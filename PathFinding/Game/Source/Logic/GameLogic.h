#pragma once
/** \file GameApp.h */
// Created by Myles Cardiff

#include <Application/ApplicationLayer.h>
#include <Logic/IGameLayer.h>
#include <Logic/Actor.h>
#include <Logic/ActorFactory.h>
#include <Utilities/Rng.h>
#include <Logic/Components/TextComponent.h>

#undef _DEBUG_DRAW
#define _DEBUG_DRAW 1

/// <summary>
/// Game Logic, inherits from slth::IGameLayer, this is the primary logic file for all gameplay code. 
/// </summary>
class GameLogic
	: public slth::IGameLayer
{

public:

	/// <summary>
	/// Tile draw mode for right-click painting tiles
	/// </summary>
	enum class DrawMode
	{
		kGrass,
		kForest,
		kBridge,
		kWater
	};

	/// <summary>
	/// Default Constructor
	/// </summary>
	GameLogic();

	/// <summary>
	/// Override for setting the game name / window title 
	/// </summary>
	/// <returns>C-Style string name</returns>
	const char* GetGameName() const override{ return "GAP 321"; }
	
	/// <summary>
	/// Initialize the game logic
	/// </summary>
	/// <param name="pAppLayer"></param>
	/// <returns></returns>
	virtual bool Init(slth::ApplicationLayer* pAppLayer) override;

	/// <summary>
	/// Called when trigger distance is reached
	/// </summary>
	/// <param name="pActorA"></param>
	/// <param name="pActorB"></param>
	virtual void TriggerEnter(slth::Actor* pActorA, slth::Actor* pActorB) override;

	/// <summary>
	/// Update (Tick) function
	/// </summary>
	/// <param name="deltaTime">Frame time</param>
	virtual void Update(float deltaTime) override;


	/// <summary>
	/// Called in the middle of IGameLayer::Draw()
	/// </summary>
	virtual void PreDraw() override;

	/// <summary>
	/// If the changed tile is in the player's current path, this stops them and attempts to re-path
	/// </summary>
	void Repath(size_t changedTileIndex);
	
	/// <summary>
	/// Handles clicking to paint the tile
	/// </summary>
	/// <param name="pos"></param>
	void HandleDrawClick(slth::Vector2f pos);

	/// <summary>
	/// Initiates path-finding to the specified tile index
	/// </summary>
	/// <param name="endPoint">The desired end point of the player</param>
	void FindPlayerPath(const size_t tileIndex);

	/// <summary>
	/// Set the player on the path, once it's found using FindPlayerPath()
	/// </summary>
	/// <param name="pathFinished"></param>
	/// <param name="path"></param>
	void SetPlayerPath(bool pathFinished, slth::GridPath& path);

protected:

	slth::Actor* m_pPlayer;
	slth::GridSystem m_gridSystem;
	slth::Vector2f m_tileOffset;
	DrawMode m_drawMode;

	static constexpr long long kPathTimeAllowed = 10;
};

