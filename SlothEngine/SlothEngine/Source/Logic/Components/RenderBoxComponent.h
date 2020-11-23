#pragma once
/** \file RenderBoxComponent.h */

// Created by Myles Cardiff

#include ".\IDrawableComponent.h"
#include <Utilities/Vector2f.h>
#include <Utilities/Color.h>
#include <functional>
#include <Graphics/IGraphics.h>


//! \namespace Sloth Engine
/** Adds a renderable rectangle to the actor (requires Transform) */
namespace slth
{

	class TransformComponent;
	class SpriteComponent;
	/** \class RenderBoxComponent */
class RenderBoxComponent
	: public IDrawableComponent
{
	

public:
	// --------------------------------------------------------------------- //
	// Public Member Variables
	// --------------------------------------------------------------------- //

	// --------------------------------------------------------------------- //
	// Public Member Functions
	// --------------------------------------------------------------------- //
	/** Default Constructor */
	SLTH_API RenderBoxComponent()
		: m_pSprite(nullptr)
		, m_pTransform(nullptr)
		
	{};

	/** Copy Method */
	SLTH_API virtual IComponent* Copy(Actor* pNewOwner) override { return new RenderBoxComponent(*this); }


	/** Default Destructor */
	SLTH_API ~RenderBoxComponent();

	/** Ideintifier Functions */
	static constexpr Id Identifier = Hasher::Hash32("RenderBox");
	SLTH_API virtual const Id GetIdentifier() const override { return Identifier; }
	SLTH_API virtual const char* GetName() const override { return "RenderBox"; };

	/** Initialization Functions*/
	SLTH_API virtual bool Init(XmlData* xmlElement) override;
	SLTH_API virtual bool Init(Vector2f size, float r, float g, float b);

	SLTH_API virtual bool PostInit() override;

	/** Draw the box on screen */
	SLTH_API virtual void Draw(IGraphics* pGraphics) override;

private:
	// --------------------------------------------------------------------- //
	// Private Member Variables
	// --------------------------------------------------------------------- //

	TransformComponent* m_pTransform;
	SpriteComponent* m_pSprite;

	Vector2f m_size;
	Color m_color;

	// --------------------------------------------------------------------- //
	// Private Member Functions
	// --------------------------------------------------------------------- //

	TransformComponent* GetTransform();
	SpriteComponent* GetSprite();

public:
	// --------------------------------------------------------------------- //
	// Accessors & Mutators
	// --------------------------------------------------------------------- //

	SLTH_API Vector2f GetSize() { return m_size; }
	SLTH_API Color GetColor() { return m_color; }
	SLTH_API void SetColor(Color color) { m_color = color; }

};
}