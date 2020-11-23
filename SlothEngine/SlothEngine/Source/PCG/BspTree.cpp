#include "BspTree.h"
#include <Logger/Logger.h>

slth::BspTree::BspTree()
	: m_pRootNode(nullptr)
{
	// add some here to avoid reallocation, it might expand in really crazy maps
	for (int i = 0; i < 15; ++i)
	{
		m_nodesByDepth.emplace_back(std::queue<BspTreeNode*>());
	}
}

slth::BspTree::BspTree(slth::RectInt areaRect)
	: m_pRootNode(new BspTreeNode(nullptr, areaRect, 0))
{

	// add some here to avoid reallocation, it might expand in really crazy maps
	for (int i = 0; i < 15; ++i)
	{
		m_nodesByDepth.emplace_back(std::queue<BspTreeNode*>());
	}

}

slth::BspTree::~BspTree()
{
	// this should cascade delete all nodes
	if (m_pRootNode)
		delete m_pRootNode;
}

void slth::BspTree::Split(int minRoomSize, slth::Rng& rng)
{
	m_splitableLeafNodes.emplace_back(m_pRootNode);

	while (m_splitableLeafNodes.size() > 0)
	{

		// this should just grab the root when we start
		size_t splitLeafIndex = (size_t)rng.RandIntInRange(0, (int)m_splitableLeafNodes.size() - 1);
		BspTreeNode* pCurrentLeaf = m_splitableLeafNodes[splitLeafIndex];

		// remove the node so it can't get processed again
		m_splitableLeafNodes.erase(m_splitableLeafNodes.begin() + splitLeafIndex);

		// insert this leaf node into the depth list
		u32 currentDepth = pCurrentLeaf->GetDepth();
		if (m_nodesByDepth.size() < currentDepth)
		{
			m_nodesByDepth.emplace_back(std::queue<BspTreeNode*>());
		}

		m_nodesByDepth[currentDepth].emplace(pCurrentLeaf);

		// split the node 
		bool leafSplitResult = pCurrentLeaf->Split(minRoomSize, rng);

		// add the children to our list to get split
		if (leafSplitResult)
		{
			// it can only split two ways so it's guaranteed to have both branches
			m_splitableLeafNodes.emplace_back(pCurrentLeaf->GetLeft());
			m_splitableLeafNodes.emplace_back(pCurrentLeaf->GetRight());
		}
		

	}
}
