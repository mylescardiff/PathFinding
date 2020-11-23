#pragma once
/** \file Actor.h */

// Created by Myles Cardiff

#include <memory>
#include <unordered_map>
#include <Common.h>
#include <Logic/Components/IComponent.h>
#include <Logger/Logger.h>
#include <Utilities/Vector2f.h>

//! \namespace Sloth Engine
namespace slth
{

/** \class Actor */

class Actor
{
public:
	// --------------------------------------------------------------------- //
	// Public Member Variables
	// --------------------------------------------------------------------- //


	// --------------------------------------------------------------------- //
	// Public Member Functions
	// --------------------------------------------------------------------- //
	/** Default Constructor */
	SLTH_API Actor(Id32 id);

	/** Copy Constructor */
	SLTH_API Actor(const Actor& otherActor, const Vector2f position, u32 id);
		
	/** Default Destructor */
	SLTH_API ~Actor();

	SLTH_API bool Init(XmlData* pData); // this will probably be the XML element from tinyxml
	SLTH_API bool PostInit();

	SLTH_API void AddComponent(IComponent* pComponent);
	SLTH_API IComponent* GetComponent(Id id);
	SLTH_API IComponent* GetComponent(std::string& name);

	template<typename Component>
	Component* GetComponent();
	
	template<typename Component>
	Component* AddComponent();

	//SLTH_API void CreateComponent(XmlData* xmlNode);
	SLTH_API Id32 GetId() { return m_id; }

	// putting this here becuase i've got some learning to do with Lua tables
	SLTH_API void ApplyLinearImpulse(float x, float y);
	
private:

	// --------------------------------------------------------------------- //
	// Private Member Variables
	// --------------------------------------------------------------------- //
	Id32 m_id;
	std::string m_name;
	std::string m_tag;
	bool m_hidden;
	// --------------------------------------------------------------------- //
	// Private Member Functions
	// --------------------------------------------------------------------- //

	using ComponentMap = std::unordered_map<size_t, IComponent*>;
	ComponentMap m_components;

public:

	// --------------------------------------------------------------------- //
	// Accessors & Mutators
	// --------------------------------------------------------------------- //

	SLTH_API ComponentMap& GetComponents() { return m_components; }
	SLTH_API std::string& GetName() { return m_name; }
	SLTH_API std::string& GetTag() { return m_tag; }
	SLTH_API void SetTag(const char* tag) { m_tag = std::string(tag); }
	SLTH_API bool IsHidden() { return m_hidden; }
	SLTH_API void Show() { m_hidden = false; }
	SLTH_API void Hide() { m_hidden = true; }
	SLTH_API void SetVisible(bool visible) { m_hidden = !visible; }
};

template<typename Component>
inline Component* Actor::GetComponent()
{
	Id id = Component::Identifier;
	auto result = m_components.find(id);
	if (result != m_components.end())
		return static_cast<Component*>(result->second);

	return nullptr;
}

template<typename Component>
inline Component* Actor::AddComponent()
{
	auto result = m_components.find(Component::Identifier);

	// didn't find one, add it
	if (result == m_components.end())
		return static_cast<Component*>(m_components.emplace(std::make_pair(Component::Identifier, new Component)).first->second);

	// return the existing component
	return static_cast<Component*>(result->second);
	
}
}

