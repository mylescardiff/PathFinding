#include <Graph/GraphNode.h>
#include <Graph/Graph.h>

class GraphRule
{
public:
	// --------------------------------------------------------------------- //
	// Public Member Variables
	// --------------------------------------------------------------------- //

#if _DEBUG
	std::string m_name;
#endif

	// --------------------------------------------------------------------- //
	// Public Member Functions
	// --------------------------------------------------------------------- //

	/** Constructors */
	GraphRule();
	GraphRule(const GraphRule&) = delete;
	GraphRule(GraphRule&&) = default;
	GraphRule& operator=(const GraphRule&) = delete;
	GraphRule& operator=(GraphRule&&) = default;

	/** Creates a simple 1:1 rule, e.g. Task -> Puzzle */
	GraphRule(u32 type, u32 subType, float weight, const char* name);

	/** Creates a simple 1:2 rule, e.g. Entrance -> Entrance + Treasure */
	GraphRule(u32 type, u32 subType1, u32 subType2, float weight, const char* name, bool selfDestruct);

	/** Creates a more complex rule where the sub-graph must be pre-defined */
	GraphRule(u32 type, Graph&& subGraph, float weight, const char* name);

	/** Creates a pattern-based rule where the sub-graph must be pre-defined */
	GraphRule(GraphNodePattern pattern, Graph&& subGraph, float weight, const char* name, 
		std::vector<size_t> nodeReplacementMap); 

private:
	// --------------------------------------------------------------------- //
	// Private Member Variables
	// --------------------------------------------------------------------- //

	GraphNodePattern m_pattern;
	Graph m_subGraph;
	float m_weight;
	bool m_selfDestruct; 
	GraphNodePattern m_nodeReplacementMap;

	// --------------------------------------------------------------------- //
	// Private Member Functions
	// --------------------------------------------------------------------- //

public:
	// --------------------------------------------------------------------- //
	// Accessors & Mutators
	// --------------------------------------------------------------------- //

	Graph& GetSubGraph() { return m_subGraph; }
	float GetWeight() const { return m_weight; }
	bool GetSelfDestruct() const { return m_selfDestruct; }
	void SetSelfDestruct(bool selfDestruct) { m_selfDestruct = selfDestruct; }
	const GraphNodePattern& GetPattern() const { return m_pattern; }
	const GraphNodePattern& GetReplacementMap() const { return m_nodeReplacementMap;  }

	float& Weight() { return m_weight; }
};