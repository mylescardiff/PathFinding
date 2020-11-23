#include "PatrolBehavior.h"
#include <Logic/Components/AIComponent/AIComponent.h>
#include <Logic/Actor.h>

PatrolBehavior::PatrolBehavior()
	: m_loop(false)
	, m_slowAtWaypoints(false)
	, m_currentWaypointTarget(0)
	, m_arriveThreshold(kArrivalDistance)
{
	//
}

PatrolBehavior::PatrolBehavior(slth::GridPath& path, slth::Vector2f tileOffset)
	: m_loop(false)
	, m_slowAtWaypoints(false)
	, m_arriveThreshold(kArrivalDistance)
	, m_currentWaypointTarget(0)
{
	for (slth::Vector2f pathPoint : path)
	{
		m_waypoints.emplace_back(pathPoint + tileOffset);
	}
}

PatrolBehavior::PatrolBehavior(slth::Vector2f singleTarget)
	: m_loop(false)
	, m_currentWaypointTarget(0)
	, m_arriveThreshold(1.5f)
	, m_slowAtWaypoints(false)
{
	m_waypoints.emplace_back(singleTarget);
}

PatrolBehavior::~PatrolBehavior()
{
	//
}

void PatrolBehavior::Update(float deltaTime)
{
	IBehavior::Update(deltaTime);

	if (m_waypoints.empty())
		return;

	// check if we've reached the wapoint
	if (m_pTransform->GetPosition().IsApproximatleyEqualTo(m_waypoints[m_currentWaypointTarget], m_arriveThreshold))
	{
		_LOGI("Reached Waypoint " + std::to_string(m_currentWaypointTarget));
		if (m_currentWaypointTarget == m_waypoints.size() - 1 && !m_loop)
		{
			m_pTransform->Stop();
			NextBehavior();
			return;
		}

		if (m_slowAtWaypoints)
			m_pTransform->Stop(); // stop when we reach waypoint

		m_waypoints[m_currentWaypointTarget] = NextWaypoint();
	}

	m_pTransform->MoveTowards(m_waypoints[m_currentWaypointTarget], deltaTime);
	m_pTransform->RotateTowards(m_waypoints[m_currentWaypointTarget], deltaTime);
}


slth::Vector2f PatrolBehavior::NextWaypoint()
{
	++m_currentWaypointTarget;
	if (m_currentWaypointTarget == m_waypoints.size())
		m_currentWaypointTarget = 0;

	return m_waypoints[m_currentWaypointTarget];
}