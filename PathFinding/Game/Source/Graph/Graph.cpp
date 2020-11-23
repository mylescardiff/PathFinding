#include "Graph.h"
#include <unordered_map>
#include <iostream>
#include <Logger/Logger.h>
#include <Graph/GraphRule.h>

Graph::Graph()
	: m_entrance(0)
	, m_exit(0)
{
	//
}

GraphNode& Graph::operator[](u64 id)
{
	return m_nodes[GetIndex(id)];
}

Graph::~Graph()
{
	Clear();
}

u64 Graph::AddNode(u32 type)
{
	u64 newId = GetFreeId();
	u64 index = GetIndex(newId);

	if (index >= m_nodes.size())
	{
		// i'm keeping the adjacency list on the node itself, so no
		// need to grow adjacency here, just creating it does that. 
		m_nodes.emplace_back(GraphNode(newId, type));
	}
	else
	{
		m_nodes[index] = GraphNode(newId, type);
	}

	return newId;
}

void Graph::ConnectNodes(u64 source, u64 destination)
{
	u64 startIndex = GetIndex(source);
	u64 endIndex = GetIndex(destination);
	m_nodes[startIndex].AddOutgoingAdjacentNode(destination);
}

void Graph::DisconnectNodes(u64 source, u64 destination)
{
	m_nodes[GetIndex(source)].RemoveIncomingAdjacentNode(destination);
	m_nodes[GetIndex(source)].RemoveOutgoingAdjacentNode(destination);
	m_nodes[GetIndex(destination)].RemoveIncomingAdjacentNode(source);
	m_nodes[GetIndex(destination)].RemoveOutgoingAdjacentNode(source);
}

void Graph::Clear()
{
	m_nodes.clear();
}

u64 Graph::AddNode(GraphNode::NodeType type)
{
	return AddNode(static_cast<u32>(type));
}

void Graph::DestroyNode(u64 id, bool toUnlink)
{
	u64 nodeIndex = GetIndex(id);
	u32 type = m_nodes[nodeIndex].GetType();
	
	m_freeIdList.push(id);

}

GraphNodePatternSet Graph::FindNodePatterns(GraphRule& rule)
{
	GraphNodePatternSet candidates;

	for (GraphNode& node : m_nodes)
	{
		if (node.GetType() == rule.GetPattern()[0])
		{
			// push a single element list into the array
			candidates.push_back(GraphNodePattern { node.GetId() }); 

			// if this is a single operation
			if (rule.GetPattern().size() == 1)
				return candidates;

			// if we get here the pattern is more complex than a single node
			GraphNodePatternSet validNodes;

			// now go through and find more...
			for (GraphNodePattern& pattern : candidates)
			{
				FindValidNodePatternsDepthLimited(pattern[0], rule.GetPattern(), validNodes);
			}
			return validNodes;
		}
	}

	return candidates;
}

void Graph::SpliceSubGraph(GraphNodePattern nodeSequenceToReplace, GraphRule& rule)
{
	// copying these 
	size_t entranceIndex = GetIndex(nodeSequenceToReplace[0]);
	std::vector<u64> entranceEdges = m_nodes[entranceIndex].IncomingAdjacentNodes(); 
	size_t exitIndex = GetIndex(nodeSequenceToReplace.back());
	std::vector<u64> exitEdges = m_nodes[exitIndex].OutgoingAdjacentNodes();
	
	GraphNodePatternSet incomingEdges;
	GraphNodePatternSet outgoingEdges;

	for (int i = 0; i < nodeSequenceToReplace.size(); ++i)
	{
		u64 nodeId = nodeSequenceToReplace[i];

		if (i != 0)
		{
			// incoming edges that aren't coming into the entrance node
			for (u64 incomingNeighborId : m_nodes[GetIndex(nodeId)].IncomingAdjacentNodes())
			{
				// check to see if the incoming neighbor is NOT in the nodeSequenceToReplace
				if (std::find(nodeSequenceToReplace.begin(), nodeSequenceToReplace.end(), incomingNeighborId) == nodeSequenceToReplace.end())
				{
					incomingEdges[i].push_back(incomingNeighborId); 
				}
			}
		}

		// outgoing edges that aren't going out of the exit node.
		if (i != nodeSequenceToReplace.size() - 1)
		{
			for (u64 outgoingNeighborId : m_nodes[GetIndex(nodeId)].OutgoingAdjacentNodes())
			{
				// This was removed because the outgoing node from Entrance to Boss was not picked up,
				// that might have been an unrelated error below where ReplaceMentMap is null
				//// check to see if the outgoing neighbor is NOT in the nodeSequenceToReplace
				if (std::find(nodeSequenceToReplace.begin(), nodeSequenceToReplace.end(), outgoingNeighborId) == nodeSequenceToReplace.end())
				{
					outgoingEdges[i].push_back(outgoingNeighborId);
				}
			}
		}

		DestroyNode(nodeId, true);
	}

	// clone the nodes, and store them in a node map so we can reconnect them later
	std::unordered_map<u64, u64> nodeMap;
	for (GraphNode& node : rule.GetSubGraph().GetNodes())
	{
		u64 newId = AddNode(node.GetType());
		nodeMap.emplace(node.GetId(), newId);
	}

	// clone each edge
	for (GraphNode& node : rule.GetSubGraph().GetNodes())
	{
		for (u64 targetNode : node.OutgoingAdjacentNodes())
		{
			u64 newFrom = nodeMap[node.GetId()];
			u64 newTo = nodeMap[targetNode];
			ConnectNodes(newFrom, newTo);
		}
	}

	// connect the new island to the existing graph, not including the entrance and exit nodes. 
	for (int i = 0; i < rule.GetReplacementMap().size(); ++i)
	{
		u64 replacingSubGraphId = rule.GetSubGraph().GetNodes()[rule.GetReplacementMap()[i]].GetId();
		u64 replacingLevelGraphId = nodeMap[replacingSubGraphId];

		if (replacingSubGraphId != rule.GetSubGraph().GetEntrance())
		{
			for (u64 neighborId : incomingEdges[i])
			{
				ConnectNodes(neighborId, replacingLevelGraphId);
			}
		}

		if (replacingSubGraphId != rule.GetSubGraph().GetExit())
		{
			for (u64 neighborId : outgoingEdges[i])
			{
				ConnectNodes(replacingLevelGraphId, neighborId);
			}
		}
	}

	// link the incoming entrance nodes
	u64 entranceId = nodeMap[rule.GetSubGraph().GetEntrance()];
	for (u64 neighborId : entranceEdges)
	{
		ConnectNodes(neighborId, entranceId);
	}

	// link the outgoing exit ids
	u64 exitId = nodeMap[rule.GetSubGraph().GetExit()];
	for (u64 neighborId : exitEdges)
	{
		ConnectNodes(exitId, neighborId);
	}
}

u64 Graph::GetFreeId()
{
	u64 newId = 0;
	if (m_freeIdList.empty())
	{
		newId = m_nodes.size();
	}
	else
	{
		newId = m_freeIdList.front();
		m_freeIdList.pop();
	}

	IncrementRefCount(newId);
	return newId;
}

void Graph::IncrementRefCount(u64& id)
{
	u64 refCount = GetRefCount(id);
	++refCount;

	id &= 0x00000000ffffffff;
	id |= (refCount << 32);
}

u64 Graph::GetIndex(u64 id)
{
	return id & 0x00000000ffffffff;
}

u64 Graph::GetRefCount(u64 id)
{
	return id >> 32;
}



void Graph::Reset()
{
	for (GraphNode& node : m_nodes)
	{
		node.SetDiscovered(false);
	}
}

void Graph::DrawRadial(slth::IGraphics* pGraphics, slth::Vector2f centerPoint, float screenWidth)
{

	Reset();

 	float sepDegrees = 360.f / (float)m_nodes.size();
	float distance = 300.f;
	slth::Vector2f textOffset = { -kNodeSize / 2.f, -kNodeSize / 2.f };

	slth::Vector2f currentPos = { centerPoint.x, centerPoint.y - distance };
	for (GraphNode& node : m_nodes)
	{
		currentPos = currentPos.Rotate(sepDegrees, centerPoint);
		pGraphics->DrawCircle(currentPos, kNodeSize, kNodeColor, kNodeColor, 0.f);
		pGraphics->DrawText(GraphNode::kNodeNames[node.GetType()], node.GetTileArea().GetCenter() + textOffset, 12, slth::Color::Black());
		node.SetTileArea({ (int)currentPos.x, (int)currentPos.y, (int)currentPos.x + (int)kNodeSize * 2, (int)currentPos.y + (int)kNodeSize * 2 });
		
	}

	if (m_nodes.size() > 0)
		DrawRadialInternal(m_nodes[0], pGraphics);
}

void Graph::DrawRadialInternal(GraphNode& currentNode, slth::IGraphics* pGraphics)
{
	currentNode.SetDiscovered(true);
	std::vector<u64>& neighbors = currentNode.OutgoingAdjacentNodes();
	
	for (u64 neighborId : neighbors)
	{
		GraphNode& neighborNode = m_nodes[GetIndex(neighborId)];
		if (!neighborNode.IsDiscovered())
		{
			// draw connection
			pGraphics->DrawLine(currentNode.GetTileArea().GetCenter(), neighborNode.GetTileArea().GetCenter(), kDirectLineColor);

			// go deeper
			DrawRadialInternal(neighborNode, pGraphics);
		}
		else
		{
			// just draw connection to existing node
			pGraphics->DrawLine(currentNode.GetTileArea().GetCenter(), neighborNode.GetTileArea().GetCenter(), kDirectLineColor);
		}
	}
}



void Graph::FindValidNodePatternsDepthLimited(u64 rootNodeId, const GraphNodePattern& nodePattern, GraphNodePatternSet& validNodes)
{
	GraphNodeSet discovered;
	GraphNodePattern workingNodeSequence;
	workingNodeSequence.resize(nodePattern.size());
	FindValidNodePatternsDepthLimitedInternal(rootNodeId, discovered, nodePattern, 0, workingNodeSequence, 0, validNodes);
}

void Graph::FindValidNodePatternsDepthLimitedInternal(u64 nodeId, GraphNodeSet& discovered, const GraphNodePattern& nodePattern, u64 nodePatternIndex,
											  GraphNodePattern& workingNodeSequence, u64 workingNodeSequenceIndex, GraphNodePatternSet& validNodes)
{
	discovered.emplace(nodeId);

	// check for matching pattern , if yes add to candiate list and keep going
	if (m_nodes[GetIndex(nodeId)].GetType() == nodePattern[nodePatternIndex])
	{
		workingNodeSequence[workingNodeSequenceIndex] = nodeId;
		 
		// are we done and succesful?
		if (workingNodeSequenceIndex == nodePattern.size() - 1)
		{
			validNodes.push_back(workingNodeSequence); 
			workingNodeSequence[workingNodeSequenceIndex] = kInvalidNode;
			return; 
		}

		// we're not done, go deeper
		for (u64 neighborId : m_nodes[GetIndex(nodeId)].OutgoingAdjacentNodes())
		{
			if (discovered.find(neighborId) == discovered.end())
			{
				FindValidNodePatternsDepthLimitedInternal(neighborId, discovered, nodePattern, nodePatternIndex + 1, workingNodeSequence, workingNodeSequenceIndex + 1, validNodes);
			}
		}
	}
	else
	{
		workingNodeSequence[workingNodeSequenceIndex] = kInvalidNode;
		
	}
}

void Graph::Print()
{
	for (GraphNode& node : m_nodes)
	{
		u64 nodeIndex = GetIndex(node.GetId());
		u32 nodeType = m_nodes[nodeIndex].GetType();
		_LOGS("[Node "  + std::to_string(nodeIndex) + " : " + GraphNode::kNodeNames[nodeType] + "]");
		for (u64 adjId : node.OutgoingAdjacentNodes())
		{
			u64 adjNodeIndex = GetIndex(adjId);
			u32 adjNodeType = m_nodes[adjNodeIndex].GetType();
			_LOGS("\t --> [ Node " + std::to_string(adjNodeIndex) + " : " + GraphNode::kNodeNames[adjNodeType] + "]");
		}
	}
}

void Graph::AddOneToOneRule(u32 type, u32 subType, float weight, const char* name)
{
	m_rules.emplace_back(GraphRule(type, subType, weight, name));
}

void Graph::AddOneToTwoRule(u32 type, u32 subType1, u32 subType2, float weight, const char* name, bool selfDestruct)
{
	m_rules.emplace_back(GraphRule(type, subType1, subType2, weight, name, selfDestruct));
}

void Graph::AddComplexRule(u32 type, Graph&& subGraph, float weight, const char* name)
{
	m_rules.emplace_back(GraphRule(type, std::move(subGraph), weight, name));
}

void Graph::AddPatternRule(GraphNodePattern pattern, Graph&& subGraph, float weight, const char* name, std::vector<size_t> nodeReplacementMap)
{
	m_rules.emplace_back(GraphRule(pattern, std::move(subGraph), weight, name, nodeReplacementMap));
}

bool Graph::RunRandomRule(slth::Rng& rng)
{
	// weight calculation 
	float totalWeight = 0.f;
	for (GraphRule& rule : m_rules)
	{
		totalWeight += rule.GetWeight();
	}

	if (totalWeight == 0.f)
	{
		// there are no rules on this type
		_LOGS("There were no valid rules to apply on this node");
		return false;
	}

	size_t ruleChoice = (size_t)rng.RandIntInRange(0, (int)m_rules.size() - 1);
	float randChoice = rng.RandFloat();
	for (GraphRule& rule : m_rules)
	{
		randChoice -= rule.GetWeight();
		if (randChoice <= 0.f)
		{

#if _DEBUG
			_LOGS("Applied Rule: " + std::string(rule.m_name));
#endif
		
			GraphNodePatternSet validNodes = FindNodePatterns(rule);

			if (validNodes.size() == 0)
			{
				_LOGS("There were no valid rules to apply on this node");
				return false;
			}
			else
			{
 				SpliceSubGraph(validNodes[0], rule);
			
				rule.Weight() = std::clamp(rule.Weight() - 0.1f , 0.f, 1.0f);
			}

			return true;
		}

	}

	return false;
}
