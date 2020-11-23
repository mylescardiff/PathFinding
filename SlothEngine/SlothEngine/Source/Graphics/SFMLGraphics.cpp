#include <Graphics/IGraphics.h>
#include <Graphics/SFMLGraphics.h>
#include <Application/Window/SFMLWindow.h>
#include <Graphics/SFMLDebugDraw.h>

using slth::SFMLGraphics;

SFMLGraphics::~SFMLGraphics()
{
	for (auto e : s_textureList)
	{
		delete e.second;
	}
	s_textureList.clear();
}

bool slth::SFMLGraphics::Init(IWindow* pWindow)
{
	m_font.loadFromFile("Assets\\arial.ttf");
	m_pWindow = pWindow;
	m_pNativeWindow = reinterpret_cast<sf::RenderWindow*>(m_pWindow->GetNativeWindow());
	m_cameraView = sf::View(sf::FloatRect(0.f, 0.f, (float)m_pNativeWindow->getSize().x, (float)m_pNativeWindow->getSize().y));
	m_pNativeWindow->setView(m_cameraView);
	return true; 
}

void slth::SFMLGraphics::StartDrawing()
{	
	m_pWindow->Clear();
}

void slth::SFMLGraphics::EndDrawing()
{
	m_pWindow->Display();
}

slth::IGraphics* slth::SFMLGraphics::Create()
{
	return new SFMLGraphics;
}

void slth::SFMLGraphics::DrawTexture(const char* name, RectInt destinationRect, RectInt textureRect, bool flip, float rotation, Vector2f origin, bool repeat, float scaleFactor) const
{
	sf::RenderWindow* pWindow = reinterpret_cast<sf::RenderWindow*>(m_pWindow->GetNativeWindow());
	sf::Texture* pSfTexture = GetTextureByName(name)->GetNativeTexture();
	
	sf::Sprite sprite;
	sprite.setTexture(*pSfTexture);

	sprite.setScale(sf::Vector2f(scaleFactor, scaleFactor));
	
	sprite.setPosition((float)(destinationRect.left), (float)(destinationRect.top));
	sprite.setOrigin(origin.x, origin.y);
	sprite.setRotation(rotation);

	if (flip)
	{
		// flip the sprite horizontally
		sprite.setOrigin({ sprite.getLocalBounds().width, 0 });
		sprite.setScale({ -1, 1 });
	}
	
	if (repeat)
	{
		// figure out how many times to draw
		int xCount = destinationRect.GetWidth() / textureRect.GetWidth();
		int yCount = destinationRect.GetHeight() / textureRect.GetHeight();

		if (destinationRect.GetWidth() % textureRect.GetWidth() > 0)
			++xCount;

		if (destinationRect.GetHeight() % textureRect.GetHeight() > 0)
			++yCount;

		for (int y = 0; y < yCount; ++y)
		{
			for (int x = 0; x < xCount; ++x)
			{
				sf::IntRect thisRect = textureRect.GetSFMLRect();

				int rightDrawEdge = (x + 1) * thisRect.width;
				int bottomDrawEdge = (y + 1) * thisRect.width;

				if (rightDrawEdge > destinationRect.GetWidth())
					thisRect.width = rightDrawEdge - destinationRect.GetWidth();

				if (bottomDrawEdge > destinationRect.GetHeight())
					thisRect.height = bottomDrawEdge - destinationRect.GetHeight();
				
				sprite.setTextureRect(thisRect);
				sprite.setPosition(sf::Vector2f(
					(float)(destinationRect.left + (x * textureRect.GetWidth())), 
					(float)(destinationRect.top + (y * textureRect.GetHeight())) )
				);

				pWindow->draw(sprite);
			}
		}
	}
	else
	{
		sf::Rect sfTextRect = textureRect.GetSFMLRect();
		sprite.setTextureRect(sfTextRect);

		// just draw once and bail
		pWindow->draw(sprite);
	}
}

void slth::SFMLGraphics::DrawSfTexture(sf::Texture& texture, RectInt destinationRect, RectInt textureRect)
{
	sf::Sprite sprite;
	sprite.setTexture(texture);

	sprite.setPosition((float)(destinationRect.left), (float)(destinationRect.top));
	sprite.setOrigin(0.f, 0.f);

	sf::Rect sfTextRect = textureRect.GetSFMLRect();
	sprite.setTextureRect(sfTextRect);

	// just draw once and bail
	sf::RenderWindow* pWindow = reinterpret_cast<sf::RenderWindow*>(m_pWindow->GetNativeWindow());
	pWindow->draw(sprite);
}

void slth::SFMLGraphics::DrawRect(RectInt rect, slth::Color fillColor, slth::Color outlineColor, float outlineWeight, float rotation) const
{
	sf::RectangleShape sfRect(sf::Vector2f(static_cast<float>(rect.right - rect.left), static_cast<float>(rect.bottom - rect.top)));
	float shiftX = (float)(rect.GetWidth() / 2);
	float shiftY = (float)(rect.GetHeight() / 2);
	sfRect.setPosition(sf::Vector2f(static_cast<float>(rect.left) + shiftX, static_cast<float>(rect.top) + shiftY));
	sfRect.setFillColor(sf::Color(static_cast<unsigned int>(fillColor.m_red), static_cast<unsigned int>(fillColor.m_green), static_cast<unsigned int>(fillColor.m_blue), static_cast<unsigned int>(fillColor.m_opacity)));
	sfRect.setOutlineColor(sf::Color(static_cast<unsigned int>(outlineColor.m_red), static_cast<unsigned int>(outlineColor.m_green), static_cast<unsigned int>(outlineColor.m_blue), static_cast<unsigned int>(outlineColor.m_opacity)));
	sfRect.setOutlineThickness(outlineWeight);
	sfRect.setRotation(rotation);
	sfRect.setOrigin(sf::Vector2f(static_cast<float>(rect.right - rect.left) / 2.f, static_cast<float>(rect.bottom - rect.top) / 2.f));
	sf::RenderWindow* pWindow = reinterpret_cast<sf::RenderWindow*>(m_pWindow->GetNativeWindow());
	pWindow->draw(sfRect);
}

void slth::SFMLGraphics::DrawCircle(Vector2f center, float radius, slth::Color fillColor, slth::Color outlineColor, float outlineWeight) const
{
	sf::CircleShape sfCircle(radius);
	sfCircle.setPosition(center.x, center.y);
	sfCircle.setFillColor(sf::Color(static_cast<unsigned int>(fillColor.m_red), static_cast<unsigned int>(fillColor.m_green), static_cast<unsigned int>(fillColor.m_blue), static_cast<unsigned int>(fillColor.m_opacity)));
	sfCircle.setOutlineColor(sf::Color(static_cast<unsigned int>(outlineColor.m_red), static_cast<unsigned int>(outlineColor.m_green), static_cast<unsigned int>(outlineColor.m_blue), static_cast<unsigned int>(outlineColor.m_opacity)));
	sfCircle.setOutlineThickness(outlineWeight);
	sf::RenderWindow* pWindow = reinterpret_cast<sf::RenderWindow*>(m_pWindow->GetNativeWindow());
	pWindow->draw(sfCircle);
}

void slth::SFMLGraphics::DrawPolygon(Vector2f center, std::vector<Vector2f> points, slth::Color fillColor, slth::Color outlineColor, float outlineWeight) const
{
	sf::ConvexShape polygon;
	polygon.setPointCount(points.size());
	polygon.setPosition(sf::Vector2f(center.x, center.y));
	for (size_t i = 0; i < points.size(); ++i)
	{
		polygon.setPoint(i, sf::Vector2f(points[i].x, points[i].y));
	}
	polygon.setFillColor(sf::Color(static_cast<unsigned int>(fillColor.m_red), static_cast<unsigned int>(fillColor.m_green), static_cast<unsigned int>(fillColor.m_blue), static_cast<unsigned int>(fillColor.m_opacity)));
	polygon.setOutlineColor(sf::Color(static_cast<unsigned int>(outlineColor.m_red), static_cast<unsigned int>(outlineColor.m_green), static_cast<unsigned int>(outlineColor.m_blue), static_cast<unsigned int>(outlineColor.m_opacity)));

	sf::RenderWindow* pWindow = reinterpret_cast<sf::RenderWindow*>(m_pWindow->GetNativeWindow());
	pWindow->draw(polygon);
}

void slth::SFMLGraphics::DrawPoint(Vector2f center, slth::Color color)
{
	RectInt rect = RectInt(static_cast<int>(center.x), static_cast<int>(center.y), static_cast<int>(center.x) + 1, static_cast<int>(center.y) + 1);
	DrawRect(rect, color, color, 0.f, 0.f);
}

void slth::SFMLGraphics::DrawText(const char* text, slth::Vector2f position, int size, slth::Color color) const
{
	sf::Text sfText;
	sfText.setString(text);
	sfText.setFillColor(sf::Color((u8)color.m_red, (u8)color.m_green, (u8)color.m_blue, (u8)color.m_opacity));
	sfText.setPosition(position.x, position.y);
	sfText.setCharacterSize(size);
	sfText.setFont(m_font);
	sf::RenderWindow* pWindow = reinterpret_cast<sf::RenderWindow*>(m_pWindow->GetNativeWindow());
	pWindow->draw(sfText);
}

void slth::SFMLGraphics::DrawLine(slth::Vector2f pointA, slth::Vector2f pointB, slth::Color color)
{
	sf::Vertex line[2];
	line[0].position = sf::Vector2f(pointA.x, pointA.y);
	line[0].color = sf::Color((u8)color.m_red, (u8)color.m_green, (u8)color.m_blue, (u8)color.m_opacity);
	line[1].position = sf::Vector2f(pointB.x, pointB.y);
	line[1].color = sf::Color((u8)color.m_red, (u8)color.m_green, (u8)color.m_blue, (u8)color.m_opacity);

	sf::RenderWindow* pWindow = reinterpret_cast<sf::RenderWindow*>(m_pWindow->GetNativeWindow());
	pWindow->draw(line, 2, sf::Lines);
}

void slth::SFMLGraphics::SetCameraPosition(float x, float y)
{
	m_cameraView = m_pNativeWindow->getView();
	m_cameraView.setCenter(x, y);
	m_pNativeWindow->setView(m_cameraView);
}

void slth::SFMLGraphics::SetCameraZoom(float level)
{
	m_cameraView = m_pNativeWindow->getView();
	m_cameraView.zoom(level);
	m_pNativeWindow->setView(m_cameraView);
}

void slth::SFMLGraphics::SetCameraSize(slth::Vector2f size)
{
	m_cameraView = m_pNativeWindow->getView();
	m_cameraView.setSize(sf::Vector2f(size.x, size.y));
	m_pNativeWindow->setView(m_cameraView);
}
void slth::SFMLGraphics::SetCameraViewport(slth::RectFloat rect)
{
	m_cameraView = m_pNativeWindow->getView();
	m_cameraView.setViewport(sf::FloatRect(rect.left, rect.top, rect.right, rect.bottom));
	m_pNativeWindow->setView(m_cameraView);
}
void slth::SFMLGraphics::SetCameraDefault()
{
	m_pNativeWindow->setView(m_pNativeWindow->getDefaultView());
}

void slth::SFMLGraphics::LoadTexture(const char* filename)
{
	// check if the texture name already exists, so we don't load it more than once to GPU
	auto foundIt = s_textureList.find(HASH(filename));
	if (foundIt != s_textureList.end())
		return;

	sf::Texture* pTexture = new sf::Texture;
	if (pTexture->loadFromFile(filename))
	{
		SFMLTexture* pSfTexture = new SFMLTexture();
		pSfTexture->Init(pTexture);
		s_textureList.insert(std::make_pair(HASH(filename), pSfTexture));
	}

}

void slth::SFMLGraphics::LoadTexture(sf::Image& image, const char* name)
{
	// check if the texture name already exists, so we don't load it more than once to GPU
	auto foundIt = s_textureList.find(HASH(name));
	if (foundIt != s_textureList.end())
		return;

	sf::Texture* pTexture = new sf::Texture;
	if (pTexture->loadFromImage(image))
	{
		SFMLTexture* pSfTexture = new SFMLTexture();
		pSfTexture->Init(pTexture);
		s_textureList.insert(std::make_pair(HASH(name), pSfTexture));
	}

}

slth::SFMLTexture* slth::SFMLGraphics::GetTextureByName(const char* name) const
{
	auto it = s_textureList.find(HASH(name));

	if (it != s_textureList.end())
	{
		return it->second;
	}
	return nullptr;
}



