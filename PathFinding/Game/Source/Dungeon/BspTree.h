/** \file BspTreeNode.h */
#pragma once
#include <Common.h>
#include <vector>
#include <queue>
#include <Dungeon/BspTreeNode.h>
#include <Utilities/RectInt.h>


/** \class BspTreeNode */
/** Binary Space Partition Node */
class BspTree
{
	
public:
	// --------------------------------------------------------------------- //
	// Public Member Functions
	// --------------------------------------------------------------------- //

	/** Default Constructor */
	BspTree();

	/** Explicit Constructor */
	BspTree(slth::RectInt areaRect);

	/** Destructor */
	virtual ~BspTree();

	/** Splits areas randomly in two until it can't anymore */
	void Split(int minRoomSize, slth::Rng& rng);

private:
	// --------------------------------------------------------------------- //
	// Private Member Variables
	// --------------------------------------------------------------------- //

	BspTreeNode* m_pRootNode;
	std::vector<std::queue<BspTreeNode*>> m_nodesByDepth;
	std::vector<BspTreeNode*> m_splitableLeafNodes;

public:

	// --------------------------------------------------------------------- //
	// Accessors & Mutators
	// --------------------------------------------------------------------- //

	BspTreeNode* GetRootNode() { return m_pRootNode; }
	std::vector<std::queue<BspTreeNode*>> GetNodesByDepth() { return m_nodesByDepth; }

};	
