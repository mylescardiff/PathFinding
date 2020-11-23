#include "BspTreeNode.h"
#include <Logger/Logger.h>

BspTreeNode::BspTreeNode(BspTreeNode* pParent, slth::RectInt areaRect, u32 depth)
	: m_pParent(pParent)
	, m_pLeft(nullptr)
	, m_pRight(nullptr)
	, m_depth(depth)
	, m_areaRect(areaRect)
	, m_splitHorizontally(false)
	, m_processed(false)
{
	//
}

BspTreeNode::~BspTreeNode()
{
	if (m_pLeft)
		delete m_pLeft;

	if (m_pRight)
		delete m_pRight;
}

bool BspTreeNode::Split(int minSize, slth::Rng& rng)
{
	m_splitHorizontally = rng.RandBool();
	if (m_splitHorizontally)
	{
		// horizontal split 
		int low = m_areaRect.top + minSize;
		int high = m_areaRect.bottom - minSize;
		
		//BUG: if this fails, then it fails to split vercially, records that it split vertically but that's actually not ture
		if (high < low)
			m_splitHorizontally = false; // not splitable, switch to vertical and try below
			
		if (m_splitHorizontally)
		{
			// create the rectangles
			int splitY = rng.RandIntInRange(low, high);
			slth::RectInt topArea(m_areaRect.left, m_areaRect.top, m_areaRect.right, splitY);
			slth::RectInt bottomArea(m_areaRect.left, splitY + 1, m_areaRect.right, m_areaRect.bottom);

			// log
			_LOGI("SPLITTING: " + m_areaRect.ToString());
			_LOGI("--TOP: " + topArea.ToString());
			_LOGI("--BOTTOM: " + bottomArea.ToString());

			// create the children
			m_pLeft = new BspTreeNode(this, topArea, m_depth + 1);
			m_pRight = new BspTreeNode(this, bottomArea, m_depth + 1);

			return true;
		}
		
	}
	
	// this isn't an else case because the above can fail and change the type
	if (!m_splitHorizontally)
	{
		// vertical split
		int low = m_areaRect.left + minSize;
		int high = m_areaRect.right - minSize;

		if (high < low)
			return false; // not splitable

		// create the rectangles
		int splitX = rng.RandIntInRange(low, high);
		slth::RectInt leftArea(m_areaRect.left, m_areaRect.top, splitX, m_areaRect.bottom);
		slth::RectInt rightArea(splitX + 1, m_areaRect.top, m_areaRect.right, m_areaRect.bottom);

		// log
		_LOGI("SPLITTING: " + m_areaRect.ToString());
		_LOGI("--LEFT: " + leftArea.ToString());
		_LOGI("--RIGHT: " + rightArea.ToString());

		// create the children
		m_pLeft = new BspTreeNode(this, leftArea, m_depth + 1);
		m_pRight = new BspTreeNode(this, rightArea, m_depth + 1);

		return true;

	}
	return false;
}

BspTreeNode* BspTreeNode::GetSibling()
{
	BspTreeNode* pSibling = m_pParent->GetLeft();
	if (pSibling != this)
		return pSibling;

	return m_pParent->GetRight();
}
