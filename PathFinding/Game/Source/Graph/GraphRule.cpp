#include <Graph/GraphRule.h>

GraphRule::GraphRule()
	: m_pattern({ kInvalidNode })
	, m_weight(0.f)
	, m_selfDestruct(false)
#if _DEBUG
	, m_name("")
#endif
{
	//
}

GraphRule::GraphRule(u32 type, u32 subType, float weight, const char* name)
	: m_pattern({type})
	, m_selfDestruct(false)
	, m_weight(weight)
#if _DEBUG
	, m_name(name)
#endif
{
	u64 node1Id = m_subGraph.AddNode(subType);
	m_subGraph.SetEndPoints(node1Id, node1Id);
}

GraphRule::GraphRule(u32 type, u32 subType1, u32 subType2, float weight, const char* name, bool selfDestruct)
	: m_pattern({ type })
	, m_weight(weight)
	, m_selfDestruct(selfDestruct)
#if _DEBUG
	, m_name(name)
#endif
{
	u64 node1Id = m_subGraph.AddNode(subType1);
	u64 node2Id = m_subGraph.AddNode(subType2);
	m_subGraph.ConnectNodes(node1Id, node2Id);
	m_subGraph.SetEndPoints(node1Id, node2Id);

}

// this copies the subgraph for more complex rules, I don't think there's a great way around this 
// outside using and storing the subgraph as a pointer, but i'm going for data locality here so that 
// seems bad
GraphRule::GraphRule(u32 type, Graph&& subGraph, float weight, const char* name)
	: m_pattern({ type })
	, m_weight(weight)
	, m_selfDestruct(false)
	, m_subGraph(std::move(subGraph))
#if _DEBUG
	, m_name(name)
#endif
{
	//
}

GraphRule::GraphRule(GraphNodePattern pattern, Graph&& subGraph, float weight, const char* name, std::vector<size_t> nodeReplacementMap)
	: m_pattern({ pattern })
	, m_weight(weight)
	, m_selfDestruct(false)
	, m_subGraph(std::move(subGraph))
	, m_nodeReplacementMap(nodeReplacementMap)
#if _DEBUG
	, m_name(name)
#endif
{
	//
}

