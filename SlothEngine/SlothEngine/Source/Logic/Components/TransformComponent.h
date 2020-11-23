#pragma once
#include ".\IComponent.h"
#include <Utilities/Vector2f.h>
#include <functional>
#include <Utilities/RectInt.h>
#include <Utilities/RectFloat.h>
#include <Utilities/Hasher.h>

//! \namespace Sloth Engine
namespace slth
{
	class World;

/// <summary>
/// Transform component enables position, rotation, velocity (non-physics based), angular velocity (non-physics based) to an Actor.
/// </summary>
class TransformComponent
	: public IComponent
{

	Vector2f m_position;
	Vector2f m_size;
	RectFloat m_anchorRect;
	bool m_useAnchorPosition;
	RectInt m_positionRect;
	World* m_pWorld;
	float m_rotation;
	float m_angularVelocity;
	Vector2f m_velocity;
	float m_angularAcceleration;
	float m_maxVelocity;
	float m_acceleration;
public:

	/// <summary>
	/// Creates a copy of the transform component
	/// </summary>
	/// <param name="pNewOwner">The new owning actor of this component</param>
	/// <returns>A pointer to the new copy</returns>
	SLTH_API virtual IComponent* Copy(Actor* pNewOwner) override;

	/// <summary>
	/// Complie-time unique ID (int) for the component type
	/// </summary>
	SLTH_API static constexpr Id Identifier = Hasher::Hash32("Transform");

	/// <summary>
	/// Complie-time unique ID (string) for the component type
	/// </summary>
	SLTH_API inline static const char* StringId = "Transform"; 

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

	/// <summary>
	/// Initializes the transform component with supplied data for position and height
	/// </summary>
	/// <param name="x">Position X coordinate</param>
	/// <param name="y">Position Y coordinate</param>
	/// <param name="width">Width</param>
	/// <param name="height">Height</param>
	/// <param name="rotation">Intitial rotation (in degrees)</param>
	/// <returns>True if initialzation succeeds, false if it fails</returns>
	SLTH_API virtual bool Init(float x, float y, float width, float height, float rotation);

	/// <summary>
	/// Initilizes the transform component from XML node (see /data/actors.xml for syntax)
	/// </summary>
	/// <param name="xmlElement">The tinyxml node pointer contianing the data</param>
	/// <returns></returns>
	SLTH_API virtual bool Init(XmlData* xmlElement) override;


	/// <summary>
	/// Teleport the object by the specified vector
	/// </summary>
	/// <param name="amount">Vector containing the amount (X,Y) you want to change the position by</param>
	SLTH_API virtual void Move(Vector2f amount);
	
	/// <summary>
	/// Teleport the object by the specified x and y values
	/// </summary>
	/// <param name="x">Change in X position</param>
	/// <param name="y">Change in Y position</param>
	SLTH_API virtual void Move(float x, float y);

	/// <summary>
	/// Moves and rotates the actor by it's velocity and angular velocity (non-physics only)
	/// </summary>
	/// <param name="deltaTime">Delta (frame) time</param>
	SLTH_API virtual void Update(float deltaTime) override;

	/// <summary>
	/// Register the script-exposed functions for the transform component 
	/// </summary>
	/// <param name="pState">Pointer to the active Lua state</param>
	SLTH_API static void RegisterToLuaState(lua_State* pState);

	/// <summary>
	/// Change the rotation of the actor 
	/// </summary>
	/// <param name="deltaAngle">The change in angle (in degrees)</param>
	SLTH_API void Rotate(float deltaAngle) { m_rotation += deltaAngle; }

	/// <summary>
	/// Move towards the target vector using the set accelleration
	/// </summary>
	/// <param name="target">Target position vector</param>
	/// <param name="deltaTime">Delta (frame) time</param>
	SLTH_API void MoveTowards(Vector2f target, float deltaTime);

	/// <summary>
	///  Rorate towards the target vector using the set angular accelleration
	/// </summary>
	/// <param name="target">Target position vector</param>
	/// <param name="deltaTime">Delta (frame) time</param>
	SLTH_API void RotateTowards(Vector2f target, float deltaTime);

	/// <summary>
	///  Rorate towards the target angle using the set angular accelleration
	/// </summary>
	/// <param name="target">Target angle</param>
	/// <param name="deltaTime">Delta (frame) time</param>
	SLTH_API void RotateTowards(float angle, float deltaTime);

	/// <summary>
	/// Stop moving entirely
	/// </summary>
	SLTH_API void Stop();

public:
	// --------------------------------------------------------------------- //
	// Accessors & Mutators
	// --------------------------------------------------------------------- //

	SLTH_API Vector2f GetVelocity() const { return m_velocity; }
	SLTH_API void SetVelocity(Vector2f velocity) { m_velocity = velocity; }

	SLTH_API float GetAngularVelocity() const { return m_angularVelocity; }
	SLTH_API void SetAngularVelocity(float angularVelocity) { m_angularVelocity = angularVelocity; }

	SLTH_API Vector2f GetPosition() const;
	SLTH_API void SetPosition(Vector2f position);

	SLTH_API Vector2f GetSize() const { return m_size; }
	SLTH_API void SetSize(Vector2f size);

	SLTH_API float GetRotation() { return m_rotation; }
	SLTH_API void SetRotation(float rotation) { m_rotation = rotation; }

	SLTH_API RectInt GetPositionRect() const;

	SLTH_API void SetWorld(World* pWorld);
	


	/// <summary>
	/// Get the max travel speed
	/// </summary>
	/// <returns>Travel speed</returns>
	float GetTravelSpeed() { return m_maxVelocity; }

	/// <summary>
	/// Get the max acceleration
	/// </summary>
	/// <returns>Max acceleration</returns>
	float GetAcceleration() { return m_acceleration; }

};
}