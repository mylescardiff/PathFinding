//#include <vld.h>

#include <Utilities/FileUtil.h>
#include <Logger/Logger.h>
#include <Application/ApplicationLayer.h>
#include <Application/Systems/WindowsSystem.h>
#include <Graphics/SFMLGraphics.h>
#include <Audio/SFMLAudioSystem.h>
#include <Logic/World.h>
#include <chrono>
#if _WIN64
#include <zlib.h>
#endif


slth::ApplicationLayer::ApplicationLayer()
	: m_pSystem(nullptr)
	,m_pGameLayer(nullptr)
	,m_pWindow(nullptr)
	,m_pGraphics(nullptr)
	,m_pAudio(nullptr)
	,m_pWorld(nullptr)
	,m_pKeyboard(nullptr)
	,m_pMouse(nullptr)
{
#if _WIN64
	//z_stream stream = { 0 };
	//deflateInit(&stream, Z_DEFAULT_COMPRESSION);
#endif
	
}

slth::ApplicationLayer::~ApplicationLayer()
{
	
	if (m_pGameLayer)
		delete m_pGameLayer;
	if (m_pAudio)
		delete m_pAudio;
	if (m_pGraphics)
		delete m_pGraphics;
	if (m_pWindow)
		delete m_pWindow;
	if (m_pWorld)
		delete m_pWorld;
	if (m_pMouse)
		delete m_pMouse;
	if (m_pKeyboard)
		delete m_pKeyboard;
	if (m_pSystem)
		delete m_pSystem;
}

bool slth::ApplicationLayer::Init()
{
	_LOGI("Sloth Engine Initialization Started");
	m_pSystem = ISystem::Create();
	
	m_pKeyboard = new IKeyboard;
	m_pMouse = new IMouse;

	m_pWorld = new slth::World();
	if (!m_pWorld->Init("Data\\world.xml"))
	{
		_LOGE("Error initializing world");
	}
	
	m_pWindow = new SFMLWindow();
	if (!m_pWindow->Init("Game", (u32)(m_pWorld->GetSize().x), (u32)(m_pWorld->GetSize().y), m_pKeyboard, m_pMouse))
	{
		_LOGE("Error initializing window");
		return false;
	}


	m_pGraphics = new SFMLGraphics;
	if (!m_pGraphics->Init(m_pWindow))
	{
		_LOGE("Error initializing graphics");
		return false;
	}

	
	m_pWorld->SetGraphics(m_pGraphics);

	m_pAudio = new SFMLAudioSystem;
	
	return true;
}

void slth::ApplicationLayer::Run()
{
	auto previousTime = std::chrono::high_resolution_clock::now();
	
	while (!m_pGameLayer->HasQuit())
	{
		if (!m_pWindow->ProcessEvents())
			break;

		auto time = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> deltaSeconds = time - previousTime;
		
		m_pGameLayer->Update(static_cast<float>(deltaSeconds.count()));
		m_pGameLayer->Draw();
		m_pWindow->NextFrame();

		previousTime = time;
		
	}



}

void slth::ApplicationLayer::Shutdown()
{
	m_pWindow->Close();
	_LOGI("Application Shutdown"); 
}
