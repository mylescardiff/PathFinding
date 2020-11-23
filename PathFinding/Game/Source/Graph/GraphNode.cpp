#include "GraphNode.h"

GraphNode::GraphNode(u64 nodeId, u32 type)
	: m_nodeId(nodeId)
	, m_tileArea({ 0, 0, 0, 0 })
	, m_nodeType(type)
	, m_distanceFromEnd(0)
	, m_discovered(false)
	, m_starID(0)
{
	//
}
GraphNode::GraphNode(u64 nodeId, u32 type, u32 starID)
	: m_nodeId(nodeId)
	, m_tileArea({ 0, 0, 0, 0 })
	, m_nodeType(type)
	, m_distanceFromEnd(0)
	, m_discovered(false)
	, m_starID(starID)
{
	//
}



void GraphNode::AddOutgoingAdjacentNode(u64 node)
{
	m_outgoingAdjacentNodes.push_back(node);
}

void GraphNode::RemoveOutgoingAdjacentNode(u64 id)
{
	for (size_t i = 0; i < m_outgoingAdjacentNodes.size(); ++i)
	{
		if (id == m_outgoingAdjacentNodes[i])
		{
			m_outgoingAdjacentNodes.erase(m_outgoingAdjacentNodes.begin() + i);
		}
	}
}

void GraphNode::AddIncomingAdjacentNode(u64 node)
{
	m_incomingAdjacentNodes.push_back(node);
}

void GraphNode::RemoveIncomingAdjacentNode(u64 id)
{
	for (size_t i = 0; i < m_incomingAdjacentNodes.size(); ++i)
	{
		if (id == m_incomingAdjacentNodes[i])
		{
			m_incomingAdjacentNodes.erase(m_incomingAdjacentNodes.begin() + i);
		}
	}
}
