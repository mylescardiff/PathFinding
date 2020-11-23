/** \file BspTreeNode.h */
#pragma once
#include <Common.h>
#include <Utilities/Vector2.h>
#include <Utilities/RectInt.h>
#include <Utilities/Rng.h>


/** \class BspTreeNode */
/** Binary Space Partition Node */
class BspTreeNode
{
	
public:
	// --------------------------------------------------------------------- //
	// Public Member Functions
	// --------------------------------------------------------------------- //
	/** Explicit Constructor */
	BspTreeNode(BspTreeNode* pParent, slth::RectInt area, u32 depth);

	/** Destructor */
	virtual ~BspTreeNode();

	/** Split the node into left and right nodes (areas)*/
	bool Split(int minSize, slth::Rng& rng);

private:
	// --------------------------------------------------------------------- //
	// Private Member Variables
	// --------------------------------------------------------------------- //

	BspTreeNode* m_pParent;
	BspTreeNode* m_pLeft;
	BspTreeNode* m_pRight;

	slth::RectInt m_areaRect;
	slth::RectInt m_roomRect;
	u32 m_depth;
	bool m_processed;
	bool m_splitHorizontally; 


public:

	// --------------------------------------------------------------------- //
	// Accessors & Mutators
	// --------------------------------------------------------------------- //

	slth::RectInt GetRect() { return m_areaRect; }
	BspTreeNode* GetLeft() { return m_pLeft; }
	BspTreeNode* GetRight() { return m_pRight; }
	bool SplitHorizontally() { return m_splitHorizontally; }
	BspTreeNode* GetSibling();
	u32 GetDepth() { return m_depth; }
	bool IsLeaf() { return (!m_pLeft && !m_pRight); }
	void SetRoomRect(slth::RectInt roomRect) { m_roomRect = roomRect; }
	slth::RectInt GetRoomRect() { return m_roomRect; }
	void SetProcessed(bool processed) { m_processed = processed; }
	bool IsProcessed() { return m_processed; }
};	
