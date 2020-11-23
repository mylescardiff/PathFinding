/** \file BspTreeNode.h */
#pragma once
#include <Common.h>
#include <Utilities/Vector2f.h>
#include <Utilities/RectInt.h>
#include <Utilities/Rng.h>

namespace slth
{

	/** \class BspTreeNode */
	/** Binary Space Partition Node */
	class BspTreeNode
	{

	public:
		// --------------------------------------------------------------------- //
		// Public Member Functions
		// --------------------------------------------------------------------- //
		/** Explicit Constructor */
		SLTH_API BspTreeNode(BspTreeNode* pParent, slth::RectInt area, u32 depth);

		/** Destructor */
		SLTH_API virtual ~BspTreeNode();

		/** Split the node into left and right nodes (areas)*/
		SLTH_API bool Split(int minSize, slth::Rng& rng);

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

		SLTH_API slth::RectInt GetRect() { return m_areaRect; }
		SLTH_API BspTreeNode* GetLeft() { return m_pLeft; }
		SLTH_API BspTreeNode* GetRight() { return m_pRight; }
		SLTH_API bool SplitHorizontally() { return m_splitHorizontally; }
		SLTH_API BspTreeNode* GetSibling();
		SLTH_API u32 GetDepth() const { return m_depth; }
		SLTH_API bool IsLeaf() { return (!m_pLeft && !m_pRight); }
		SLTH_API void SetRoomRect(slth::RectInt roomRect) { m_roomRect = roomRect; }
		SLTH_API slth::RectInt GetRoomRect() { return m_roomRect; }
		SLTH_API void SetProcessed(bool processed) { m_processed = processed; }
		SLTH_API bool IsProcessed() { return m_processed; }
	};

}
