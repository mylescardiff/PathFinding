#pragma once
/** \file NodeGraph.h */
#include <Common.h>
#include <Utilities/RectInt.h>
#include <vector>
#include <queue>
#include <set>
#include <Graph/GraphNode.h>
#include <Utilities/Rng.h>
#include <unordered_map>
#include <Graphics\IGraphics.h>
#include <Universe/Star.h>

/** \class NodeGraph */
/** A partitioned node in our dungeon with adjacency */
class GraphRule;

// defined a bunch of these because looking them up / finding was easier
// in one or the other depending on the situation
using GraphNodePattern = std::vector<u64>;
using GraphNodePatternList = std::unordered_map<u64, GraphNodePattern>;
using GraphNodePatternSet = std::vector<GraphNodePattern>;
using GraphNodeSet = std::set<u64>;

// not my favorite method, but if the graph has more than 999 types I've got bigger problems
static constexpr u32 kInvalidNode = 999;

class Graph
{

public:

	// --------------------------------------------------------------------- //
	// Public Member Functions
	// --------------------------------------------------------------------- //
	/** Constructors */
	Graph();
	Graph(const Graph&) = delete;
	Graph(Graph&&) = default; 
	Graph& operator=(const Graph&) = delete;
	Graph& operator=(Graph&&) = default;
	GraphNode& operator[] (u64 id);

	/** Destructor */
	~Graph();

	/** Remove all nodes from the graph*/
	void Clear();

	/** Insert a node by nodetype into the graph */
	u64 AddNode(GraphNode::NodeType type);

	/** Insert a node into the graph */
	u64 AddNode(u32 type);

	/** Create directed edge between nodes */
	void ConnectNodes(u64 source, u64 destination);

	/** Remove the edges between two nodes */
	void DisconnectNodes(u64 source, u64 destination);

	/** Remove a single node */
	void DestroyNode(u64 id, bool toUnlink);

	/** Search for matching patterns for the rule in the graph */
	GraphNodePatternSet FindNodePatterns(GraphRule& rule);

	/** Splice in a subgraph at the specified position */
	void SpliceSubGraph(GraphNodePattern nodeSequenceToReplace, GraphRule& rule);

	/** Output graph to console. This will print in the array order, not necessarily the order the nodes are truly in */
	void Print();

	/** Create a graph transformation rule that makes 1 node into 2 linked nodes*/
	void AddOneToOneRule(u32 type, u32 subType, float weight, const char* name);

	/** Create a graph transformation rule that makes 1 node into 2 linked nodes*/
	void AddOneToTwoRule(u32 type, u32 subType1, u32 subType2, float weight, const char* name, bool selfDestruct = false);
	
	/** Create a complex rule where the subgraph is predefined */
	void AddComplexRule(u32 type, Graph&& subGraph, float weight, const char* name);

	/** Create a pattern-based where the subgraph is predefined */
	void AddPatternRule(GraphNodePattern pattern, Graph&& subGraph, float weight, const char* name, std::vector<size_t> nodeReplacementMap);

	/** Run a random rule on a random node */
	bool RunRandomRule(slth::Rng& rng);

	/** ID Management */
	u64 GetFreeId();
	static void IncrementRefCount(u64& id);
	static u64 GetIndex(u64 id);
	static u64 GetRefCount(u64 id);
	
	/** Drawing as a tree of squares */
	void DrawRadial(slth::IGraphics* pGraphics, slth::Vector2f centerPoint, float screenWidth);
	void DrawRadialInternal(GraphNode& currentNode, slth::IGraphics* pGraphics);

	void Reset();

private:

	// --------------------------------------------------------------------- //
	// Private Member Functions
	// --------------------------------------------------------------------- //

	void FindValidNodePatternsDepthLimited(u64 rootNodeId, const GraphNodePattern& nodePattern, GraphNodePatternSet& validNodes);

	void FindValidNodePatternsDepthLimitedInternal(u64 nodeId, GraphNodeSet& discovered, const GraphNodePattern& nodePattern, u64 nodePatternIndex,
		GraphNodePattern& workingNodeSequence, u64 workingNodeSequenceIndex, GraphNodePatternSet& validNodes);

	// --------------------------------------------------------------------- //
	// Constants 
	// --------------------------------------------------------------------- //

	static constexpr float kNodeSize = 40.f;
	static constexpr slth::Color kNodeColor = slth::Color::White();
	static constexpr slth::Color kDirectLineColor = slth::Color::Red();

	// --------------------------------------------------------------------- //
	// Private Member Variables
	// --------------------------------------------------------------------- //

	std::vector<GraphNode> m_nodes;
	std::queue<u64> m_freeIdList;

	// for faster lookup of all nodes of a specific type later
	// this gets updated when nodes are removed / added

	//NOTE: adjacency List is kept on each node node.

	u64 m_entrance;
	u64 m_exit;

	std::vector<GraphRule> m_rules;

public:

	// --------------------------------------------------------------------- //
	// Accessors & Mutators
	// --------------------------------------------------------------------- //
	std::vector<GraphNode>& GetNodes() { return m_nodes; }
	u64 GetEntrance() const { return m_entrance; }
	u64 GetExit() const { return m_exit; }
	void SetEndPoints(u64 entrance, u64 exit) { m_entrance = entrance; m_exit = exit; }

};

