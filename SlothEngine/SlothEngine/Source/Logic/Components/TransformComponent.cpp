#include "TransformComponent.h"
#include <Logic/Components/RigidBodyComponent.h>
#include <Logic/Actor.h>
#include "TransformComponent.gen.h"

using slth::TransformComponent;

slth::IComponent * slth::TransformComponent::Copy(Actor * pNewOwner)
{
	auto pTransComp = new TransformComponent(*this);
	pTransComp->m_position.x = 0;
	pTransComp->m_position.y = 0;
	pTransComp->m_acceleration = m_acceleration;
	pTransComp->m_maxVelocity = m_maxVelocity;
	return pTransComp;
}


bool slth::TransformComponent::Init(float x, float y, float width, float height, float rotation)
{
	m_size = Vector2f(width, height);
	m_position = Vector2f(x, y);
	m_rotation = rotation;
	return true;
}

bool slth::TransformComponent::Init(XmlData* pXmlNode)
{
	// transform can also take anchor positions so if you wanted the floor 
	// to always be at the bottom regardless of screen resolution, for example
	const char* testForAnchors = pXmlNode->Attribute("anchor-left");
	if (testForAnchors)
	{
		m_useAnchorPosition = true;
		m_anchorRect.left = pXmlNode->FloatAttribute("anchor-left");
		m_anchorRect.top = pXmlNode->FloatAttribute("anchor-top");
		m_anchorRect.right = pXmlNode->FloatAttribute("anchor-right");
		m_anchorRect.bottom = pXmlNode->FloatAttribute("anchor-bottom");

		m_positionRect.left = (int)pXmlNode->Int64Attribute("position-left");
		m_positionRect.top = (int)pXmlNode->Int64Attribute("position-top");
		m_positionRect.right = (int)pXmlNode->Int64Attribute("position-right");
		m_positionRect.bottom = (int)pXmlNode->Int64Attribute("position-bottom");
	}
	else
	{
		m_useAnchorPosition = false;
		this->m_position.x = pXmlNode->FloatAttribute("x");
		this->m_position.y = pXmlNode->FloatAttribute("y");
		m_size.x = pXmlNode->FloatAttribute("w");
		m_size.y = pXmlNode->FloatAttribute("h");
	}
	
	this->m_rotation = pXmlNode->FloatAttribute("rotation");
	this->m_velocity.x = pXmlNode->FloatAttribute("velocity-x");
	this->m_velocity.y = pXmlNode->FloatAttribute("velocity-y");
	this->m_angularVelocity = pXmlNode->FloatAttribute("angular-velocity");
	this->m_angularAcceleration = pXmlNode->FloatAttribute("angular-acceleration");
	m_maxVelocity = pXmlNode->FloatAttribute("speed");
	m_acceleration = pXmlNode->FloatAttribute("acceleration");

	return true;
}



void slth::TransformComponent::Move(Vector2f amount)
{
	m_position += amount;
	RigidBodyComponent* pRigidBody = m_pOwner->GetComponent<RigidBodyComponent>();
	if (pRigidBody)
	{
		pRigidBody->Move(amount);
	}
}

void slth::TransformComponent::Move(float x, float y)
{
	Vector2f v(x, y); 
	Move(v);
}

void slth::TransformComponent::Update(float deltaTime)
{
	m_position.x += m_velocity.x * deltaTime;
	m_position.y += m_velocity.y * deltaTime;

	m_rotation += m_angularVelocity * deltaTime;
}


void slth::TransformComponent::RegisterToLuaState(lua_State * pState)
{
	luaL_newmetatable(pState, StringId);				// Stack: table

	// metatable.__index = 
	luaL_getmetatable(pState, StringId);
	lua_setfield(pState, -2, "__index");
	
	// Add other functions
	lua_pushcfunction(pState, &glua::TransformComponent_Move);	// Stack: table, function
	lua_setfield(pState, -2, "move");							// Stack: table

	//
	lua_pop(pState, 1);											// Stack:
							
}

slth::Vector2f slth::TransformComponent::GetPosition() const
{
	if (m_useAnchorPosition && m_pWorld)
	{
		Vector2f anchoredPosition(
			m_pWorld->GetSize().x * (float)m_anchorRect.left + m_positionRect.left * m_pWorld->GetDPI(),
			m_pWorld->GetSize().y * (float)m_anchorRect.top + m_positionRect.top * m_pWorld->GetDPI()
		);
		return anchoredPosition;
	}
	else
	{
		return m_position;
	}
}

void slth::TransformComponent::SetPosition(Vector2f position)
{
	m_position = position; 
}

void slth::TransformComponent::SetSize(Vector2f size)
{
	m_size = size;
	
}

slth::RectInt slth::TransformComponent::GetPositionRect() const
{
	return RectInt((int)m_position.x, (int)m_position.y, (int)m_position.x + (int)m_size.x, (int)m_position.y + (int)m_size.y);
}

void slth::TransformComponent::SetWorld(World* pWorld)
{
	m_pWorld = pWorld;
	if (m_useAnchorPosition)
	{
		RectInt realPositionRect(
			(int)(m_pWorld->GetSize().x * (float)m_anchorRect.left + (float)m_positionRect.left * m_pWorld->GetDPI()),
			(int)(m_pWorld->GetSize().y * (float)m_anchorRect.top + (float)m_positionRect.top * m_pWorld->GetDPI()),
			(int)(m_pWorld->GetSize().x * (float)m_anchorRect.right + (float)m_positionRect.right * m_pWorld->GetDPI()),
			(int)(m_pWorld->GetSize().y * (float)m_anchorRect.bottom + (float)m_positionRect.bottom * m_pWorld->GetDPI())

		);
		m_size.x = (float)realPositionRect.right - (float)realPositionRect.left;
		m_size.y = (float)realPositionRect.bottom - (float)realPositionRect.top;
		m_position.x = (float)realPositionRect.left;
		m_position.y = (float)realPositionRect.top;
	}
}

void slth::TransformComponent::MoveTowards(Vector2f target, float deltaTime)
{
	// get bearing to waypoint and move towards it	
	slth::Vector2f bearing = m_position.BearingTo(target);

	// check the magnitude of the velocity vector to see how fast we're going
	float currentMagnitude = m_velocity.Magnitude();
	if (currentMagnitude < m_maxVelocity)
	{
		// accelerate up to travel speed
		currentMagnitude += m_acceleration * deltaTime;
	}

	m_velocity = bearing * currentMagnitude;


//#if _DEBUG
//	_LOGI("V: " + std::to_string(m_velocity.x) + ", " + std::to_string(m_velocity.y)
//	+ "; B: " + std::to_string(bearing.x) + ", " + std::to_string(bearing.y));
//#endif
}

void slth::TransformComponent::RotateTowards(Vector2f target, float deltaTime)
{
	float desiredAngle = Vector2f::AngleBetween(m_position, target) ;
	return RotateTowards(desiredAngle, deltaTime);
}

void slth::TransformComponent::RotateTowards(float desiredAngle, float deltaTime)
{
	float change = desiredAngle - m_rotation;

	if (change > 180.f)
	{
		change -= 360.f;
	}
	if (change < -180.f)
	{
		change += 360.f;
	}

	float dir = change / abs(change);
	if (isnan(dir))
	{
		dir = 1;
	}
	m_rotation += dir * m_angularAcceleration * deltaTime;
}

void slth::TransformComponent::Stop()
{
	m_velocity = { 0, 0 };
	m_angularVelocity = 0.f;
}




