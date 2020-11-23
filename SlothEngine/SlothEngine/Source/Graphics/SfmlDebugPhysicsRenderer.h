#pragma once

#include <Box2D.h>
#include <SFML/Graphics.hpp>
#include <Common.h>



// this file is from Dylan, just using it to fix my polygon woes

namespace slth
{
	class SfmlGraphics;
	class IGraphics;
	
	class SfmlDebugPhysicsRenderer : public b2Draw
	{
	private:
		sf::RenderWindow* m_pTarget;

	public:
		SLTH_API bool Init(IGraphics* pGraphics);

		// Inherited via DebugPhysicsRenderer
		virtual void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) final override;
		virtual void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) final override;
		virtual void DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color) final override;
		virtual void DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color) final override;
		virtual void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color) final override;
		virtual void DrawTransform(const b2Transform& xf) final override;
		virtual void DrawPoint(const b2Vec2& p, float32 size, const b2Color& color) final override;
	};
}