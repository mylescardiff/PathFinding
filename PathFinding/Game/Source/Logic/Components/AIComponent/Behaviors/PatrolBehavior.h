#pragma once
/** \file PatrolBehavior.h */
// Created by Myles Cardiff
#include <Logic/Grid/GridSystem.h>

#include ".\IBehavior.h"

/// <summary>
/// Agent will walk from waypoint to waypoint
/// </summary>
class PatrolBehavior
	: public IBehavior
{
public:
	
	// --------------------------------------------------------------------- //
	// Public Member Functions
	// --------------------------------------------------------------------- //
	
	/// <summary>
	/// Default Constructor
	/// </summary>
	PatrolBehavior();

	/// <summary>
	/// Explicit Constructor for following a path
	/// </summary>
	/// <param name="path">GridPath object (vector of Vector2fs)</param>
	PatrolBehavior(slth::GridPath& path, slth::Vector2f tileOffset);

	/// <summary>
	/// Explicit Constructor
	/// </summary>
	/// <param name="singleTarget">A single waypoint to follow</param>
	/// <param name="loop"></param>
	PatrolBehavior(slth::Vector2f singleTarget);

	/// <summary>
	/// Default Destructor
	/// </summary>
	virtual ~PatrolBehavior();

	/// <summary>
	/// Update (Tick) function for the component
	/// </summary>
	/// <param name="deltaTime">Delta (frame) time</param>
	virtual void Update(float deltaTime) override;

	/// <summary>
	/// Insert a new waypoint at the end of this patrol loop
	/// </summary>
	/// <param name="waypoint"></param>
	void AddWaypoint(slth::Vector2f waypoint) { m_waypoints.emplace_back(waypoint); }

	/// <summary>
	/// Move to the next waypoint
	/// </summary>
	/// <returns></returns>
	slth::Vector2f NextWaypoint();

private:
	std::vector<slth::Vector2f> m_waypoints;
	size_t m_currentWaypointTarget;
	bool m_loop;
	bool m_slowAtWaypoints;
	float m_arriveThreshold;

	// constants
	static constexpr float kArrivalDistance = 5.f;

public:

	void SetLoop(bool loop) { m_loop = loop; }
	std::vector<slth::Vector2f>& GetWaypoints() { return m_waypoints; }
};
