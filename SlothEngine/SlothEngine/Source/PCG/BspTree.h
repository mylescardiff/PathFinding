/** \file BspTreeNode.h */
#pragma once
#include <Common.h>
#include <vector>
#include <queue>
#include <PCG/BspTreeNode.h>
#include <Utilities/RectInt.h>

namespace slth
{
	/** \class BspTreeNode */
	/** Binary Space Partition Node */
	class BspTree
	{

	public:
		// --------------------------------------------------------------------- //
		// Public Member Functions
		// --------------------------------------------------------------------- //

		/** Default Constructor */
		SLTH_API BspTree();

		/** Explicit Constructor */
		SLTH_API BspTree(slth::RectInt areaRect);

		/** Destructor */
		SLTH_API virtual ~BspTree();

		/** Splits areas randomly in two until it can't anymore */
		SLTH_API void Split(int minRoomSize, slth::Rng& rng);

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

		SLTH_API BspTreeNode* GetRootNode() { return m_pRootNode; }
		SLTH_API std::vector<std::queue<BspTreeNode*>>& GetNodesByDepth() { return m_nodesByDepth; }

	};

}
