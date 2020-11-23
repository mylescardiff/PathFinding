#include "SpriteComponent.h"
#include <Logic/Actor.h>
#include <Logic\Components\TransformComponent.h>
#include <Logic\Components\RigidBodyComponent.h>
#include <Utilities/RectInt.h>


using slth::SpriteComponent;

SpriteComponent::SpriteComponent()
	: m_textureRect(0, 0, 0, 0)
	, m_direction(FacingDirection::kRight)
	, m_pTexture(nullptr)
{
	//
}

SpriteComponent::~SpriteComponent()
{
	if (m_pTexture)
		delete m_pTexture;
}

bool slth::SpriteComponent::Init(XmlData* xmlElement)
{
	m_path = xmlElement->Attribute("path");
	m_textureRect.left = xmlElement->IntAttribute("source-left");
	m_textureRect.right = xmlElement->IntAttribute("source-right");
	m_textureRect.top = xmlElement->IntAttribute("source-top");
	m_textureRect.bottom = xmlElement->IntAttribute("source-bottom");
	m_repeat = xmlElement->BoolAttribute("repeat");
	m_origin.x = xmlElement->FloatAttribute("origin-x");
	m_origin.y = xmlElement->FloatAttribute("origin-y");
	return true;
}

bool slth::SpriteComponent::PostInit()
{
	// check for transform component on the parent
	TransformComponent* pTransformComp = m_pOwner->GetComponent<TransformComponent>();
	if (!pTransformComp)
	{
		_LOGW("A TransformComponent was missing from an object that has a SpriteComponent.");
		return false;
	}
	
	RigidBodyComponent* pRigidBody = m_pOwner->GetComponent<RigidBodyComponent>();
	if (pRigidBody && pTransformComp)
	{
		if (pRigidBody->GetBodyShape() != RigidBodyComponent::BodyShape::Polygon)
		{
			m_origin.x = pTransformComp->GetSize().x / 2;
			m_origin.y = pTransformComp->GetSize().y / 2;
		}
	}

	return true;
}

void slth::SpriteComponent::LoadTexture(IGraphics* pGraphics)
{
	pGraphics->LoadTexture(m_path.c_str());
}


void slth::SpriteComponent::TurnAround()
{
	if (m_direction == FacingDirection::kLeft)
		m_direction = FacingDirection::kRight;
	else 
		m_direction = FacingDirection::kLeft;
}

void slth::SpriteComponent::Draw(IGraphics* pGraphics)
{
	TransformComponent* pTransformComp = m_pOwner->GetComponent<TransformComponent>();
	RectInt drawRect = pTransformComp->GetPositionRect();
	pGraphics->DrawTexture(m_path.c_str(), drawRect, m_textureRect, m_direction == FacingDirection::kLeft, pTransformComp->GetRotation(), m_origin, m_repeat, 1.f);

}

void slth::SpriteComponent::RegisterToLuaState(lua_State * pState)
{
	// ----------------------------------------------------
	// Regarding Lua for this component: there is nothing I
	// really want people accessing in here, so no functions
	// were pushed to lua intentionally, that may change in 
	// some future iteration, so I'm leaving the component 
	// registration itself in place, just not pushing any 
	// items to it for the time being.
	// ----------------------------------------------------

	luaL_newmetatable(pState, StringId);				// Stack: table

	// metatable.__index = 
	luaL_getmetatable(pState, StringId);
	lua_setfield(pState, -2, "__index");

	//
	lua_pop(pState, 1);											// Stack:
}
