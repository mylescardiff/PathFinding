#include "SFMLWindow.h"
#include <chrono>
#include <thread>
using slth::SFMLWindow;

SFMLWindow::SFMLWindow()
	:m_pWindow(nullptr)
{
	//
}

SFMLWindow::~SFMLWindow()
{
	delete m_pWindow;
}

bool slth::SFMLWindow::Init(const char* title, u32 width, uint32_t height, IKeyboard* pKeyboard, IMouse* pMouse)
{
	// create the window
	m_pWindow = new sf::RenderWindow(sf::VideoMode(width, height), title);
	m_pWindow->setKeyRepeatEnabled(false);
	m_pWindow->clear();

	// get keyboard & Mouse
	m_pKeyboard = pKeyboard;
	m_pMouse = pMouse;

	return true;
}


bool slth::SFMLWindow::ProcessEvents() const
{
	sf::Event event;
	while (m_pWindow->pollEvent(event)) 
	{
		// declared here because it doesn't like being declared in the case statement
		sf::Vector2i mousePositionInWindow = sf::Mouse::getPosition(*m_pWindow);
		m_pMouse->SetPosition(mousePositionInWindow.x, mousePositionInWindow.y);

		IMouse::MouseButton button = IMouse::MouseButton::kNumButtons;
		if (event.mouseButton.button == sf::Mouse::Button::Left)
		{
			button = IMouse::MouseButton::Left;
		}
		else if (event.mouseButton.button == sf::Mouse::Button::Right)
		{
			button = IMouse::MouseButton::Right;
		}

		switch (event.type)
		{
			case sf::Event::Closed:
				m_pWindow->close();
				return false;
				break;

			case sf::Event::KeyPressed: 
				m_pKeyboard->SetKey((IKeyboard::KeyCode)event.key.code, true);
				break;

			case sf::Event::KeyReleased: 
				m_pKeyboard->SetKey((IKeyboard::KeyCode)event.key.code, false);
				break;
		
			case sf::Event::MouseButtonPressed:
				m_pMouse->SetButton(button, true);
				break;

			case sf::Event::MouseButtonReleased:
				m_pMouse->SetButton(button, false);
				break;
		}
		
	}
	return true;

}

void slth::SFMLWindow::NextFrame() const
{
	m_pKeyboard->ClearAllKeys();
	m_pMouse->ClearAllButtons();
}

bool slth::SFMLWindow::IsOpen()
{
	if (!m_pWindow)
		return false;

	return m_pWindow->isOpen();
}

void slth::SFMLWindow::Clear()
{
	m_pWindow->clear(sf::Color(0, 0, 0));
}

void slth::SFMLWindow::Display()
{
	m_pWindow->display();
}

void slth::SFMLWindow::Close()
{
	m_pWindow->close();
}


void slth::SFMLWindow::SetTitle(const char* title)
{
	m_pWindow->setTitle(title);
}
