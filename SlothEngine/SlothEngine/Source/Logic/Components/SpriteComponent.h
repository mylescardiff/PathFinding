#pragma once
/** \file SpriteComponent.h */
// Created by Myles Cardiff

#include ".\IDrawableComponent.h"
#include <Utilities/Vector2f.h>
#include <Utilities/Color.h>
#include <functional>
#include <Graphics/IGraphics.h>
#include <Graphics/ITexture.h>

//! \namespace Sloth Engine
namespace slth
{
/// <summary>
/// Adds a renderable texture to the actor. May be a single texture or tiled to create repeating patterns and backgrounds. 
/// </summary>
class SpriteComponent
	: public IDrawableComponent
{
public:

	/// <summary>
	/// Directional data for flipping the sprite horizontally
	/// </summary>
	enum class FacingDirection
	{
		kLeft,
		kRight
	};

	// --------------------------------------------------------------------- //
	// Public Member Functions
	// --------------------------------------------------------------------- //

	/// <summary>
	/// Default constructor for the sprite component
	/// </summary>
	SLTH_API SpriteComponent();

	/// <summary>
	/// Creates a copy of the sprite component
	/// </summary>
	/// <param name="pNewOwner">The new owning actor of this component</param>
	/// <returns>A pointer to the new copy</returns>
	SLTH_API virtual IComponent* Copy(Actor* pNewOwner) override { return new SpriteComponent(*this); }

	/// <summary>
	/// Default destructor for the sprite. This will destroy the associated texture. 
	/// </summary>
	SLTH_API ~SpriteComponent();

	/// <summary>
	/// Complie-time unique ID (int) for the component type
	/// </summary>
	static constexpr Id Identifier = Hasher::Hash32("Sprite");

	/// <summary>
	/// Complie-time unique ID (string) for the component type
	/// </summary>
	SLTH_API inline static const char* StringId = "Sprite";

	/// <summary>
	/// Get the name of this component
	/// </summary>
	/// <returns></returns>
	SLTH_API virtual const char* GetName() const override { return StringId; }

	/// <summary>
	/// Get the unique identifier for this component
	/// </summary>
	/// <returns></returns>
	SLTH_API virtual const Id GetIdentifier() const override { return Identifier; }

	/** Initialization Functions */
	SLTH_API virtual bool Init(XmlData* xmlElement) override;
	SLTH_API virtual bool PostInit() override;

	/// <summary>
	/// Draw the sprite component on screen 
	/// </summary>
	/// <param name="pGraphics">A pointer to the graphics object contains the DrawTexture() function (e.g. SfmlGraphics)</param>
	SLTH_API virtual void Draw(IGraphics* pGraphics) override;

	/// <summary>
	/// Loads the texture into the graphics system for use later. 
	/// </summary>
	/// <param name="pGraphics">A pointer to the graphics object contains the LoadTexture() function (e.g. SfmlGraphics)</param>
	SLTH_API virtual void LoadTexture(IGraphics* pGraphics);
	
	/// <summary>
	/// Flips the sprite horizontally to face left / right. Don't use this with sprites with text in them, it will be backwards. 
	/// </summary>
	SLTH_API void TurnAround();

	/// <summary>
	/// Register the script-exposed functions for the sprite component 
	/// </summary>
	/// <param name="pState">Pointer to the active Lua state</param>
	SLTH_API static void RegisterToLuaState(lua_State* pState);

private:
	// --------------------------------------------------------------------- //
	// Private Member Variables
	// --------------------------------------------------------------------- //

	std::string m_path;
	ITexture* m_pTexture;
	RectInt m_textureRect;
	FacingDirection m_direction;
	Vector2f m_origin;
	bool m_repeat;

public:
	// --------------------------------------------------------------------- //
	// Accessors & Mutators
	// --------------------------------------------------------------------- //

	SLTH_API RectInt& GetTextureRect() { return m_textureRect; }
	SLTH_API void SetTextureRect(RectInt& rect) { m_textureRect = rect; }
	SLTH_API void SetDirection(FacingDirection direction) { m_direction = direction; }
	SLTH_API void SetTexturePath(std::string path) { m_path = path; }
	SLTH_API bool GetRepeat() { return m_repeat; }
	SLTH_API void SetRepeat(bool repeat) { m_repeat = repeat; }
};
}