#include <Graphics/SfmlDebugPhysicsRenderer.h>

#include <Graphics/SfmlGraphics.h>
#include <Graphics/IGraphics.h>
#include <SFML/Graphics.hpp>
#include <Logic/World.h>


namespace slth
{
	bool SfmlDebugPhysicsRenderer::Init(IGraphics* pGraphics)
	{
		m_pTarget = reinterpret_cast<sf::RenderWindow*>(dynamic_cast<SFMLGraphics*>(pGraphics)->GetWindow()->GetNativeWindow());

		return true;
	}

	void SfmlDebugPhysicsRenderer::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
	{
		sf::ConvexShape polygon(vertexCount);
		sf::Vector2f center;
		for (int i = 0; i < vertexCount; i++)
		{
			polygon.setPoint(i, sf::Vector2f(std::floor(vertices[i].x *kPixelsPerMeter), std::floor(vertices[i].y *kPixelsPerMeter)));
		}																							
		polygon.setOutlineThickness(-1.f);
		polygon.setFillColor(sf::Color::Transparent);
		polygon.setOutlineColor(sf::Color((u32)(255.f * color.r), (u32)(255.f * color.g), (u32)(255.f * color.b), (u32)(255.f * color.a)));

		m_pTarget->draw(polygon);
	}

	void SfmlDebugPhysicsRenderer::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
	{
		sf::ConvexShape polygon(vertexCount);
		for (int i = 0; i < vertexCount; i++)
		{
			polygon.setPoint(i, sf::Vector2f(std::floor(vertices[i].x *kPixelsPerMeter), std::floor(vertices[i].y *kPixelsPerMeter)));
		}
		polygon.setOutlineThickness(-1.f);
		polygon.setFillColor(sf::Color((u32)(255.f * color.r), (u32)(255.f * color.g), (u32)(255.f * color.b), 60));
		polygon.setOutlineColor(sf::Color((u32)(255.f * color.r), (u32)(255.f * color.g), (u32)(255.f * color.b), (u32)(255.f * color.a)));

		m_pTarget->draw(polygon);
	}

	void SfmlDebugPhysicsRenderer::DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color)
	{
		sf::CircleShape circle(radius *kPixelsPerMeter);
		circle.setOrigin(radius *kPixelsPerMeter, radius *kPixelsPerMeter);
		circle.setPosition(center.x *kPixelsPerMeter, center.y *kPixelsPerMeter);
		circle.setFillColor(sf::Color::Transparent);
		circle.setOutlineThickness(-1.f);
		circle.setOutlineColor(sf::Color((u32)(255.f * color.r), (u32)(255.f * color.g), (u32)(255.f * color.b), (u32)(255.f * color.a)));

		m_pTarget->draw(circle);
	}

	void SfmlDebugPhysicsRenderer::DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color)
	{
		sf::Color sfColor((u32)(255.f * color.r), (u32)(255.f * color.g), (u32)(255.f * color.b), (u32)(255.f * color.a));

		sf::CircleShape circle(radius *kPixelsPerMeter);
		circle.setOrigin(radius *kPixelsPerMeter, radius *kPixelsPerMeter);
		circle.setPosition(center.x *kPixelsPerMeter, center.y *kPixelsPerMeter);
		circle.setOutlineThickness(1.f);
		circle.setFillColor(sf::Color(sfColor.r, sfColor.g, sfColor.b, 60));
		circle.setOutlineColor(sfColor);

		b2Vec2 endPoint = center + radius * axis;
		sf::Vertex line[2] =
		{
			sf::Vertex(sf::Vector2f(center.x *kPixelsPerMeter, center.y *kPixelsPerMeter), sfColor),
			sf::Vertex(sf::Vector2f(endPoint.x *kPixelsPerMeter, endPoint.y *kPixelsPerMeter), sfColor),
		};

		m_pTarget->draw(circle);
		m_pTarget->draw(line, 2, sf::Lines);
	}

	void SfmlDebugPhysicsRenderer::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
	{
		sf::Color sfColor((u32)(255.f * color.r), (u32)(255.f * color.g), (u32)(255.f * color.b), (u32)(255.f * color.a));

		sf::Vertex line[] =
		{
			sf::Vertex(sf::Vector2f(p1.x *kPixelsPerMeter, p1.y *kPixelsPerMeter), sfColor),
			sf::Vertex(sf::Vector2f(p2.x *kPixelsPerMeter, p2.y *kPixelsPerMeter), sfColor),
		};

		m_pTarget->draw(line, 2, sf::Lines);
	}

	void SfmlDebugPhysicsRenderer::DrawTransform(const b2Transform& xf)
	{
		const float kLineLength = 0.4f;

		/*b2Vec2 xAxis(b2Vec2(xf.p.x + (lineLength * xf.q.c), xf.p.y + (lineLength * xf.q.s)));*/
		b2Vec2 xAxis = xf.p + kLineLength * xf.q.GetXAxis();
		sf::Vertex redLine[] =
		{
			sf::Vertex(sf::Vector2f(xf.p.x * kPixelsPerMeter, xf.p.y * kPixelsPerMeter), sf::Color::Red),
			sf::Vertex(sf::Vector2f(xAxis.x * kPixelsPerMeter, xAxis.y * kPixelsPerMeter), sf::Color::Red)
		};

		// You might notice that the ordinate(Y axis) points downward unlike the one in Box2D testbed
		// That's because the ordinate in SFML coordinate system points downward while the OpenGL(testbed) points upward
		/*b2Vec2 yAxis(b2Vec2(xf.p.x + (lineLength * -xf.q.s), xf.p.y + (lineLength * xf.q.c)));*/
		b2Vec2 yAxis = xf.p + kLineLength * xf.q.GetYAxis();
		sf::Vertex greenLine[] =
		{
			sf::Vertex(sf::Vector2f(xf.p.x *kPixelsPerMeter, xf.p.y *kPixelsPerMeter), sf::Color::Green),
			sf::Vertex(sf::Vector2f(xAxis.x *kPixelsPerMeter, xAxis.y *kPixelsPerMeter), sf::Color::Green)
		};

		m_pTarget->draw(redLine, 2, sf::Lines);
		m_pTarget->draw(greenLine, 2, sf::Lines);
	}

	void SfmlDebugPhysicsRenderer::DrawPoint(const b2Vec2& p, float32 size, const b2Color& color)
	{
		sf::RectangleShape rect;
		rect.setOrigin(size *kPixelsPerMeter, size *kPixelsPerMeter);
		rect.setPosition(p.x *kPixelsPerMeter, p.y *kPixelsPerMeter);
		rect.setFillColor(sf::Color((u32)(255.f * color.r), (u32)(255.f * color.g), (u32)(255.f * color.b), (u32)(255.f * color.a)));

		m_pTarget->draw(rect);
	}

}

