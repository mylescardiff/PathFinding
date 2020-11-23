#include <Logic/GameLogic.h>
#include <Utilities/Rng.h>
#include <Utilities/Utilities.h>
#include <SFML/Graphics.hpp>
#include <Logic/Components/TransformComponent.h>
#include <Logic/Components/AIComponent/AIComponent.h>
#include <Logic/Components/AIComponent/Behaviors/ChaseBehavior.h>
#include <Logic/Components/AIComponent/Behaviors/IdleBehavior.h>
#include <Logic/Components/AIComponent/Behaviors/SpeakBehavior.h>
#include <Logic/Components/AIComponent/Behaviors/PatrolBehavior.h>
#include <Logic/Components/AIComponent/Behaviors/TurnBehavior.h>
#include <Logic/Components/AIComponent/Behaviors/TeleportBehavior.h>
#include <iostream>

GameLogic::GameLogic()
	: m_pPlayer(nullptr)
	, m_tileOffset({0.f, 0.f})
	, m_drawMode(DrawMode::kGrass)
{
	//
}

bool GameLogic::Init(slth::ApplicationLayer* pAppLayer)
{
	IGameLayer::Init(pAppLayer);

	pAppLayer->GetWindow()->SetTitle("GAP 321");

	// register custom components with the engine
	m_pActorFactory->RegisterComponentCreator(HASH("AI"), [](slth::Actor* pOwner) {
		return new AIComponent();
	});

	// load UI elements
	m_pActorFactory->CreateActors("Data\\ui.xml", m_uiElements, m_pGraphics, m_pWorld);

	// load starting actors
	m_pActorFactory->CreateActors("Data\\actors.xml", m_actors, m_pGraphics, m_pWorld);

	// store the IDs for the player
	m_pPlayer = FindActor("Player");

	// setup grid
	float tileSize = 25.f;
	m_gridSystem.Init("Data\\river-scene.xml");
	m_tileOffset = { tileSize / 2.f, tileSize / 2.f };

	return PostInit();
	
}

void GameLogic::TriggerEnter(slth::Actor* pActorA, slth::Actor* pActorB)
{
	//
}

void GameLogic::Update(float deltaTime)
{
	IGameLayer::Update(deltaTime);


	// check if any pathing is still pending and resume it
	if (m_gridSystem.IsPathInProgress())
	{
		slth::GridPath path;
		SetPlayerPath(m_gridSystem.Resume(path, kPathTimeAllowed), path);
	}

	slth::IMouse* pMouse = m_pAppLayer->GetMouse();
	slth::IKeyboard* pKeyboard = m_pAppLayer->GetKeyboard();

	auto mousePos = pMouse->GetPosition();

	if (pMouse->IsDoubleClicked(slth::IMouse::MouseButton::Left))
	{
		// teleport the player and cancel any paths
		m_gridSystem.Reset();
		m_pPlayer->GetComponent<slth::TextComponent>()->SetText("");
		m_pPlayer->GetComponent<AIComponent>()->SetBehavior(nullptr);
		m_pPlayer->GetComponent<slth::TransformComponent>()->SetPosition(pMouse->GetPosition().ToVector2f());
	}
	else if (pMouse->IsButtonPressed(slth::IMouse::MouseButton::Left))
	{
		// initital path finding
		slth::GridTile& clickedTile = m_gridSystem.GetTileAtScreenPosition({ (float)mousePos.x, (float)mousePos.y });
		if (clickedTile.GetType() != slth::GridTile::kInvalidTile)
		{
			FindPlayerPath(clickedTile.GetIndex());
		}
	}

	if (pMouse->IsButtonDown(slth::IMouse::MouseButton::Right))
	{
		// paint
		HandleDrawClick(slth::Vector2f((float)pMouse->GetPosition().x, (float)pMouse->GetPosition().y));
	}

	if (pKeyboard->IsKeyPressed(slth::IKeyboard::KeyCode::Tilde))
	{
		// dump grid data to the console
		m_gridSystem.OutputGridData();
	}

	// tile drawing
	if (pKeyboard->IsKeyPressed(slth::IKeyboard::KeyCode::F))
	{
		m_drawMode = DrawMode::kForest;
	}
	if (pKeyboard->IsKeyPressed(slth::IKeyboard::KeyCode::B))
	{
		m_drawMode = DrawMode::kBridge;
	}
	if (pKeyboard->IsKeyPressed(slth::IKeyboard::KeyCode::G))
	{
		m_drawMode = DrawMode::kGrass;
	}
	if (pKeyboard->IsKeyPressed(slth::IKeyboard::KeyCode::W))
	{
		m_drawMode = DrawMode::kWater;
	}
	if (pKeyboard->IsKeyPressed(slth::IKeyboard::KeyCode::R))
	{
		m_gridSystem.Reset();
	}
	if (pKeyboard->IsKeyPressed(slth::IKeyboard::KeyCode::P))
	{
		m_gridSystem.ToggleWeightMode();
		const char* onOff = m_gridSystem.GetWeightOnlyMode() ? "Off" : "On";
		_LOGW(std::string("Smoother Path Mode: ") + onOff );
	}
}

void GameLogic::PreDraw()
{
	m_gridSystem.Draw(m_pGraphics);
}

void GameLogic::Repath(size_t changedTileIndex)
{
	AIComponent* pAiComp = m_pPlayer->GetComponent<AIComponent>();

	// check if the AI is on a patrol
	PatrolBehavior* pPatrol = dynamic_cast<PatrolBehavior*>(pAiComp->CurrentBehavior());
	if (pPatrol)
	{
		for (slth::Vector2f waypoint : pPatrol->GetWaypoints())
		{
			slth::GridTile& tile = m_gridSystem.GetTileAtScreenPosition(waypoint);

			// if the tile is on the player's path, and it's an impassible tile, then attempt to repath
			// otherwise this won't care. This means putting a forest tile in the way won't stop it, but 
			// that seems reasonable, it probably wouldn't stop an enemy from murdering you in a game
			if (tile.GetIndex() == changedTileIndex && tile.GetWeight() >= slth::GridSystem::kImpassibleWeight)
			{
				slth::Vector2f pathEndPoint = pPatrol->GetWaypoints().back();
				pAiComp->SetBehavior(nullptr);

				FindPlayerPath(m_gridSystem.GetTileAtScreenPosition(pathEndPoint).GetIndex());
			}
		}
	}
}

void GameLogic::HandleDrawClick(slth::Vector2f pos)
{
	
	if (pos.x >= 0.f && pos.y >= 0.f && pos.x <= m_pWorld->GetSize().x && pos.y <= m_pWorld->GetSize().y)
	{
		slth::Color drawColor = slth::Color::Green();
		float drawWeight = 1.0;

		switch (m_drawMode)
		{
			case DrawMode::kForest:
				drawColor = slth::Color::DarkGreen();
				drawWeight = 1.5f;
				break;
			case DrawMode::kBridge:
				drawColor = slth::Color::DarkBeige();
				drawWeight = 1.0f;
				break;
			case DrawMode::kWater:
				drawColor = slth::Color::Blue();
				drawWeight = 10.f;
				break;
			default:
				break;
		}

		slth::GridTile& tile = m_gridSystem.GetTileAtScreenPosition(pos);
		tile.SetColor(drawColor);
		tile.SetWeight(drawWeight);

		// check to see if this edit screwed up the player's path
		Repath(tile.GetIndex());
		
	}
	
}

void GameLogic::FindPlayerPath(const size_t tileIndex)
{
	
	slth::GridTile& actorTile = m_gridSystem.GetTileAtScreenPosition(m_pPlayer->GetComponent<slth::TransformComponent>()->GetPosition());
	slth::GridPath shortestPath;
	SetPlayerPath(m_gridSystem.FindPathAStar(actorTile.GetIndex(), tileIndex, shortestPath, kPathTimeAllowed), shortestPath);
}

void GameLogic::SetPlayerPath(bool pathFinished, slth::GridPath& path)
{
	if (pathFinished)
	{
		if (path.size() == 0)
		{
			// negative reaction
			m_pPlayer->GetComponent<AIComponent>()->SetBehavior(new SpeakBehavior("I can't swim!", 0.75f));
		}
		else
		{
#if _DEBUG
			float totalPathDistance = 0.f;
			for (size_t i = 0; i < path.size() - 1; ++i)
			{
				totalPathDistance += path[i].DistanceTo(path[i + 1]);
			}
			_LOGI("Total Path Distance: " + std::to_string(totalPathDistance));
#endif
			m_pPlayer->GetComponent<AIComponent>()->SetBehavior(new PatrolBehavior(path, m_tileOffset));
		}
	}
}

