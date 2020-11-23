#pragma once
/** \file NodeGraph.h */
#include <Common.h>
#include <Utilities/RectInt.h>
#include <vector>
#include <map>
#include <set>

/** \class NodeGraph */
/** a generic node in out graph */


class GraphNode
{
public:

	enum class NodeType
	{
		kStart,
		kTalk,
		kItem,
		kLock,
		kFinish,
		kNone
	};

	static constexpr const char* kNodeNames[] = { "Start", "Talk", "Item", "Lock", "Finish" };

	// --------------------------------------------------------------------- //
	// Public Member Functions
	// --------------------------------------------------------------------- //
	
	/** Constructors */
	GraphNode(u64 nodeId, u32 type);
	GraphNode(u64 nodeId, u32 type, u32 starID);
	GraphNode(const GraphNode&) = delete;
	GraphNode(GraphNode&&) = default;
	GraphNode& operator=(const GraphNode&) = delete;
	GraphNode& operator=(GraphNode&&) = default;

private:
	// --------------------------------------------------------------------- //
	// Private Member Variables
	// --------------------------------------------------------------------- //

	u64 m_nodeId;
	slth::RectInt m_tileArea;
	u32 m_nodeType;
	u32 m_distanceFromEnd;
	bool m_discovered;
	u32 m_starID;

	std::vector<u64> m_incomingAdjacentNodes;
	std::vector<u64> m_outgoingAdjacentNodes;

public:

	// --------------------------------------------------------------------- //
	// Accessors & Mutators
	// --------------------------------------------------------------------- //

	u64 GetId() const { return m_nodeId; }

	slth::RectInt GetTileArea() { return m_tileArea; }
	void SetTileArea(slth::RectInt tileArea) { m_tileArea = tileArea; }

	u32 GetType() const { return m_nodeType; }
	void SetType(u32 type) { m_nodeType = type; }

	void SetDistance(u32 distance) { m_distanceFromEnd = distance; }
	int GetDistance() const { return m_distanceFromEnd;  }

	std::vector<u64>& OutgoingAdjacentNodes() { return m_outgoingAdjacentNodes; }
	std::vector<u64>& IncomingAdjacentNodes() { return m_incomingAdjacentNodes; }

	void AddOutgoingAdjacentNode(u64 id);
	void RemoveOutgoingAdjacentNode(u64 id);

	void AddIncomingAdjacentNode(u64 id);
	void RemoveIncomingAdjacentNode(u64 id);

	bool IsTerminal() const { 
		return false; // this needs to be generic 
	}

	void SetDiscovered(bool discovered) { m_discovered = discovered; }
	bool IsDiscovered() const { return m_discovered; }

	u32 GetStar() { return m_starID; }
	void SetStar(u32 starID) { 
		m_starID = starID; 
	}
};

