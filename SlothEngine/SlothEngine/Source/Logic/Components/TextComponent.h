#pragma once
/** \file TextComponent.h */
// Created by Myles Cardiff

#include ".\IDrawableComponent.h"
#include <Common.h>
#include <string>
#include <Utilities/Vector2f.h>
#include <Utilities/Color.h>

//! \namespace Sloth Engine
namespace slth
{

	class TransformComponent;

/// <summary>
///  Adds rendered text to the actor (requires Transform Component)
/// </summary>
class TextComponent
	: public IDrawableComponent
{
public:

	/// <summary>
	/// Preset types for horizontal alignment
	/// </summary>
	enum class HorizontalAlignment
	{
		Left,
		Right,
		Center
	};

	/// <summary>
	/// Preset types for vertical alignment
	/// </summary>
	enum class VerticalAlignment
	{
		Top,
		Middle,
		Bottom
	};

	/// <summary>
	/// Default Constructor
	/// </summary>
	SLTH_API TextComponent()
		: m_alignHorizontal(HorizontalAlignment::Left)
		, m_alignVertical(VerticalAlignment::Middle)
		, m_fontSize(9)
		, m_color(slth::Color::Black())
		, m_pTransformComponent(nullptr)
	{}

	/// <summary>
	/// Copy method. Creates a clone of this component under another owning actor
	/// </summary>
	/// <param name="pNewOwner">The new owning actor of the cloned component</param>
	/// <returns></returns>
	SLTH_API virtual IComponent* Copy(Actor* pNewOwner) override { return new TextComponent(*this); }

	/// <summary>
	/// Complie-time unique ID (int) for the component type
	/// </summary>
	static constexpr Id Identifier = Hasher::Hash32("Text");

	/// <summary>
	/// Complie-time unique ID (string) for the component type
	/// </summary>
	SLTH_API inline static const char* StringId = "Text";

	/// <summary>
	/// Get the unique identifier for this component
	/// </summary>
	/// <returns></returns>
	SLTH_API virtual const Id GetIdentifier() const override { return Identifier; }

	/// <summary>
	/// Get the name of this component
	/// </summary>
	/// <returns></returns>
	SLTH_API virtual const char* GetName() const override { return StringId; };

	/// <summary>
	/// Initilizes the transform component from XML node (see /data/actors.xml for syntax)
	/// </summary>
	/// <param name="xmlElement">The tinyxml node pointer contianing the data</param>
	/// <returns></returns>
	SLTH_API virtual bool Init(XmlData* xmlElement) override;

	

	/// <summary>
	/// Draw the text component on screen 
	/// </summary>
	/// <param name="pGraphics">A pointer to the graphics object contains the DrawText() function (e.g. SfmlGraphics)</param>
	SLTH_API virtual void Draw(IGraphics* pGraphics) override;

private:

	std::string m_text;
	Color m_color;
	unsigned short m_fontSize;
	HorizontalAlignment m_alignHorizontal;
	VerticalAlignment m_alignVertical;
	TransformComponent* m_pTransformComponent;
	Vector2f m_offset;

public:
	// --------------------------------------------------------------------- //
	// Accessors & Mutators
	// --------------------------------------------------------------------- //

	SLTH_API void SetText(std::string text) { m_text = text; }

};
}