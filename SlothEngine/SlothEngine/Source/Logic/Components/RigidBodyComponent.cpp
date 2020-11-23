#include "RigidBodyComponent.h"
#include <Logic/Components/TransformComponent.h>
#include <Logic/Components/SpriteComponent.h>

#include <Logic/Actor.h>
#include <Utilities/RectInt.h>

namespace slth
{
	IComponent* RigidBodyComponent::Copy(Actor* pNewOwner)
	{
		// don't actually make a copy, that causes Box2D issues
		auto newBody = new RigidBodyComponent;
		newBody->m_shape = m_shape;
		newBody->m_size = m_size;
		newBody->m_type = m_type;
		newBody->m_pOwner = pNewOwner;
		newBody->SetBody(m_pWorld);

		return newBody;

	}
	RigidBodyComponent::RigidBodyComponent()
		: m_pPhysicsBody(nullptr)
		, m_pSprite(nullptr)
		, m_pTransform(nullptr)
		, m_pWorld(nullptr)
		, m_shape(BodyShape::Box)
		, m_type(BodyType::Static)
	{
		//
	}
	RigidBodyComponent::~RigidBodyComponent()
	{

		// destroy the body
		m_pPhysicsBody->GetWorld()->DestroyBody(m_pPhysicsBody);
	}

	bool RigidBodyComponent::Init(BodyType type, BodyShape shape)
	{
		if (shape == BodyShape::Polygon)
		{
			_LOGE("You tried to create a polygon from object, that is not supported.");
			return false;
		}
		m_shape = shape;
		m_type = type;
		return true;
	}

	bool RigidBodyComponent::Init(XmlData * xmlElement)
	{
		std::string bodyType = xmlElement->Attribute("body-type");
		
		if (bodyType == "Static")
			m_type = BodyType::Static;
		else if (bodyType == "Dynamic")
			m_type = BodyType::Dynamic;
		else
			m_type = BodyType::Kinematic;

		std::string bodyShape = xmlElement->Attribute("body-shape");
		if (bodyShape == "Circle")
		{
			m_shape = BodyShape::Circle;
		}
		else if (bodyShape == "Polygon")
		{
			m_shape = BodyShape::Polygon;
			XmlData* pVertexNode = xmlElement->FirstChildElement();
			while (pVertexNode)
			{
				float vertX = pVertexNode->FloatAttribute("x") / kPixelsPerMeter;
				float vertY = pVertexNode->FloatAttribute("y") / kPixelsPerMeter;
				m_polyVertices.emplace_back(b2Vec2(vertX, vertY));
				pVertexNode = pVertexNode->NextSiblingElement();
			}
		}
		else
		{
			m_shape = BodyShape::Box;
		}
		m_offset.x = xmlElement->FloatAttribute("offset-x");
		m_offset.y = xmlElement->FloatAttribute("offset-y");
		m_size.y = xmlElement->FloatAttribute("size-y");
		m_size.x = xmlElement->FloatAttribute("size-x");
		m_bouncyness = xmlElement->FloatAttribute("bouncyness");
		m_fixedRotation = xmlElement->BoolAttribute("fixed-rotation");

		return true;
	}

	void RigidBodyComponent::SetBody(World* pWorld)
	{
		TransformComponent* pTransform = m_pOwner->GetComponent<TransformComponent>();
		if (m_size.x == 0)
		{
			m_size.x = pTransform->GetSize().x;
			m_size.y = pTransform->GetSize().y;
		}

		// create body
		b2BodyDef bodyDef;

		if (m_type == BodyType::Static)
			bodyDef.type = b2BodyType::b2_staticBody;
		else if (m_type == BodyType::Kinematic)
			bodyDef.type = b2BodyType::b2_kinematicBody;
		else
			bodyDef.type = b2BodyType::b2_dynamicBody;

		bodyDef.userData = this;
		bodyDef.angle = pTransform->GetRotation();

		
		m_pPhysicsBody = pWorld->GetPhysicsWorld()->CreateBody(&bodyDef);
		m_pPhysicsBody->SetUserData(m_pOwner);
		if (m_shape == BodyShape::Box)
		{
			// create box
			b2PolygonShape box;
			float bWidth = (m_size.x / 2.f) / pWorld->GetPhysicsScale();
			float bHeight = (m_size.y / 2.f) / pWorld->GetPhysicsScale();
			box.SetAsBox(bWidth, bHeight);
			b2Fixture* pFixture = m_pPhysicsBody->CreateFixture(&box, 1.f);
			pFixture->SetRestitution(m_bouncyness);
			m_pPhysicsBody->SetLinearVelocity(b2Vec2(0, 0));
			
		}
		else if (m_shape == BodyShape::Circle)
		{
			b2CircleShape circle;
			circle.m_p.Set(0, 0);
			circle.m_radius = (m_size.x / 2.f) / pWorld->GetPhysicsScale();
			
			b2Fixture* pFixture = m_pPhysicsBody->CreateFixture(&circle, 1.f);
			pFixture->SetRestitution(m_bouncyness);
			pFixture->SetFriction(0.5);

		}
		else if (m_shape == BodyShape::Polygon)
		{
			b2PolygonShape polygon;
			polygon.Set(m_polyVertices.data(), (int32)m_polyVertices.size());
			
			b2Fixture* pFixture = m_pPhysicsBody->CreateFixture(&polygon, 1.f);
			pFixture->SetRestitution(m_bouncyness);
			pFixture->SetFriction(0.5);
		}

		// create fixture + transform
		Vector2f pTransPosition = pTransform->GetPosition();
		b2Vec2 physPosition =
		{
			(pTransPosition.x + (m_size.x / 2.f)) / kPixelsPerMeter + (m_offset.x / kPixelsPerMeter),
			(pTransPosition.y + (m_size.y / 2.f)) / kPixelsPerMeter + (m_offset.y / kPixelsPerMeter)
		};
	
		m_pPhysicsBody->SetTransform(physPosition, pTransform->GetRotation() * 0.0174533f);
		m_pPhysicsBody->SetLinearDamping(pWorld->GetDamping());
		m_pPhysicsBody->SetFixedRotation(m_fixedRotation);
	
		m_pWorld = pWorld;
	}

	void RigidBodyComponent::ApplyLinearImpulse(Vector2f & directionalForce)
	{
		m_pPhysicsBody->ApplyLinearImpulse(b2Vec2(directionalForce.x, directionalForce.y), m_pPhysicsBody->GetWorldCenter(), true);
	}

	void RigidBodyComponent::ApplyLinearImpulse(float x, float y)
	{
		Vector2f vec(x, y);
		ApplyLinearImpulse(vec);
	}

	void RigidBodyComponent::Move(Vector2f amount)
	{
		auto transform = m_pPhysicsBody->GetTransform();
		transform.p.x += amount.x / m_pWorld->GetPhysicsScale();
		transform.p.y += amount.y / m_pWorld->GetPhysicsScale();
		m_pPhysicsBody->SetTransform(b2Vec2(transform.p.x / kPixelsPerMeter, transform.p.y / kPixelsPerMeter), 0.f);
	}

	void RigidBodyComponent::SetPosition(Vector2f position)
	{
		auto transform = m_pPhysicsBody->GetTransform();
		transform.p.x = position.x / m_pWorld->GetPhysicsScale();
		transform.p.y = position.y / m_pWorld->GetPhysicsScale();
	}

	TransformComponent* RigidBodyComponent::GetTransform()
	{
		if (!m_pTransform)
		{
			m_pTransform = m_pOwner->GetComponent<TransformComponent>();
		}

		return m_pTransform;
	}

	SpriteComponent* RigidBodyComponent::GetSprite()
	{
		if (!m_pSprite)
		{
			m_pSprite = m_pOwner->GetComponent<SpriteComponent>();
		}

		return m_pSprite;
	}

	void slth::RigidBodyComponent::RegisterToLuaState(lua_State * pState)
	{
		luaL_newmetatable(pState, StringId);						

		// metatable.__index = 
		luaL_getmetatable(pState, StringId);
		lua_setfield(pState, -2, "__index");

		// Add other functions
		lua_pushcfunction(pState, &glua::RigidBodyComponent_ApplyLinearImpulse);	
		lua_setfield(pState, -2, "applyLinearImpulse");								

		lua_pop(pState, 1);															
	}
}

