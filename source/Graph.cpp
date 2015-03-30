#include "Graph.h"

Graph::Graph()
{

}

Graph::~Graph()
{
	for (int i = 0; i < mNodes.size(); i++)
		delete mNodes[i];
}

Graph::Graph(unsigned int aNodeCount, float aX, float aY, unsigned int aTileSize)
{ 
	mGridH = ceil(sqrt(aNodeCount));
	mGridW = ceil(sqrt(aNodeCount));
	mTileSize = aTileSize;
	mX = aX;
	mY = aY;
	mNodes.resize(aNodeCount);
	for (int i = 0; i < (aNodeCount); i++)
	{
		float tY = ((int)(i / ceil(sqrt((mGridH * mGridW)))) * mTileSize);
		float tX = (0 - ((((int)(i / ceil(sqrt((mGridH * mGridW)))) * ceil(sqrt((mGridH * mGridW)))) - (i))* mTileSize));
		mNodes[i] = new GraphNode(i, mX + tX, mY + tY);
	}
	EdgeMap();
}

Graph::Graph(unsigned int aGridW, unsigned int aGridH, float aX, float aY, unsigned int aTileSize)
{
	mGridH = aGridH;
	mGridW = aGridW;
	mTileSize = aTileSize;
	mX = aX;
	mY = aY;
	mNodes.resize(mGridH * mGridW);
	for (int i = 0; i < mGridH; i++)
	{
		for (int ii = 0; ii < mGridW; ii++)
		{
			mNodes[ii + (i * mGridW)] = new GraphNode(ii + (i * mGridW), mX + (ii * mTileSize), mY + (i * mTileSize));
		}
	}
	EdgeMap();
}
void Graph::AddNode(GraphNode* aNode)
{
	mNodes.push_back(aNode);
}

//void Graph::AddGridNode()
//{
//	mNodes.reserve(mNodes.size() + 1);
//	mNodes.push_back(new GraphNode(mNodes.size(),
//		mNodes[0]->mX + (0 - ((((int)((mNodes.size() - 1) / ceil(sqrt(mNodes.size()))) * ceil(sqrt(mNodes.size()))) - ((mNodes.size() - 1)))* mNodes.size())),
//		mNodes[0]->mY + ((int)((mNodes.size() - 1) / ceil(sqrt(mNodes.size()))) * mNodes.size())
//		));
//}

bool Graph::TurnWall(GraphNode* aNode)
{
	mNodes[aNode->mNodeNumber]->mEdges.resize(0);
	for (int i = 0; i < mNodes.size(); i++)
	{
		for (int ii = 0; ii < mNodes[i]->mEdges.size(); ii++)
		{
			if (mNodes[i]->mEdges[ii].mEnd == aNode)
			{
				mNodes[i]->mEdges.erase(mNodes[i]->mEdges.begin() + ii);
			}
		}
	}

	mNodes[aNode->mNodeNumber]->mWall = 1;
	mNodes[aNode->mNodeNumber]->mState = 1;
	return true;
}

void Graph::RemoveNode(GraphNode* aNode)
{
	for (int i = 0; i < mNodes.size(); i++)
	{
		for (int ii = 0; ii < mNodes[i]->mEdges.size(); ii++)
		{
			if (mNodes[i]->mEdges[ii].mEnd == aNode)
			{
				mNodes[i]->mEdges.erase(mNodes[i]->mEdges.begin() + ii);
			}
		}
	}

	mNodes.erase(mNodes.begin() + aNode->mNodeNumber);
}



void Graph::ResetVisited()
{
	for (int i = 0; i < mNodes.size(); i++)
	{
		mNodes[i]->mVisited = false;
		if (mNodes[i]->mState != 1)
			mNodes[i]->mState = 0;
	}
}

bool Graph::SearchDFS(GraphNode* aStart, GraphNode* aEnd)
{
	std::queue<GraphNode*> oNodeStack;
	aStart->mPath = 0;
	oNodeStack.push(aStart);
	while (!oNodeStack.empty())
	{
		GraphNode* pCurrent = oNodeStack.front();
		oNodeStack.pop();
		if (pCurrent->mVisited == true)
		{
			continue;
		}
		pCurrent->mState = 2;
		pCurrent->mVisited = true;
		if (pCurrent->mNodeNumber == aEnd->mNodeNumber)
		{
			pCurrent->mState = 3;
			pCurrent->mVisited = true;
			return true;
		}
		for (int i = 0; i < pCurrent->mEdges.size(); ++i)
		{
			if (!pCurrent->mEdges[i].mEnd->mVisited)
				pCurrent->mEdges[i].mEnd->mPath = pCurrent->mPath + 1;
			oNodeStack.push(pCurrent->mEdges[i].mEnd);
		}
	}
	ResetVisited();
	return false;
}

void Graph::Dijkstra(GraphNode* aStart, GraphNode* aEnd)
{
	GraphNode* pCurrent = aEnd;
	for (int j = 0; j < pCurrent->mEdges.size(); j++)
	{
		if (pCurrent->mEdges[j].mEnd->mPath == pCurrent->mPath - 1)
		{
			if (pCurrent->mPath == 1)
				return;
			pCurrent->mEdges[j].mEnd->mState = 3;
			pCurrent = pCurrent->mEdges[j].mEnd;
			j = -1;
		}
	}
}

void Graph::SearchSTAR(GraphNode* aStart, GraphNode* aEnd)
{
	std::vector<GraphNode*> NodeStack;
	aStart->mPath = 0;
	NodeStack.push_back(aStart);
	while (!NodeStack.empty())
	{
		GraphNode* Current = NodeStack.back();
		NodeStack.pop_back();
		if (Current->mVisited)
		{
			continue;
		}
		Current->mVisited = true;
		if (Current->mNodeNumber == aEnd->mNodeNumber)
			return;
		switch (Current->mEdges.size())
		{
		case 0:
			break;
		case 1:
			NodeStack.push_back(Current->mEdges[0].mEnd);
			Current->mEdges[0].mEnd->mState = 2;
			break;
		case 2:
			NodeStack.push_back(Closest(Current->mEdges[0].mEnd, Current->mEdges[1].mEnd, aEnd));
			Closest(Current->mEdges[0].mEnd, Current->mEdges[1].mEnd, aEnd)->mState = 2;
			break;
		case 3:
			NodeStack.push_back(Closest(Current->mEdges[0].mEnd, Current->mEdges[1].mEnd, Current->mEdges[2].mEnd, aEnd));
			Closest(Current->mEdges[0].mEnd, Current->mEdges[1].mEnd, Current->mEdges[2].mEnd, aEnd)->mState = 2;
			break;
		case 4:
			NodeStack.push_back(Closest(Current->mEdges[0].mEnd, Current->mEdges[1].mEnd, Current->mEdges[2].mEnd, Current->mEdges[3].mEnd, aEnd));
			Closest(Current->mEdges[0].mEnd, Current->mEdges[1].mEnd, Current->mEdges[2].mEnd, Current->mEdges[3].mEnd, aEnd)->mState = 2;
			break;

		};
	}
}

//void Graph::SearchSTAR(GraphNode* aStart, GraphNode* aEnd)
//{
//	std::vector<GraphNode*> oNodeStack;
//	aStart->mPath = 0;
//	oNodeStack.push_back(aStart);
//	while (!oNodeStack.empty())
//	{
//		GraphNode* pCurrent = oNodeStack.back();
//		oNodeStack.pop_back();
//		if (pCurrent->mVisited == true)
//		{
//			continue;
//		}
//		pCurrent->mState = 2;
//
//		pCurrent->mVisited = true;
//
//		if (pCurrent->mNodeNumber == aEnd->mNodeNumber)
//		{
//			pCurrent->mState = 3;
//			pCurrent->mVisited = true;
//			return;
//		}
//		if (pCurrent->mEdges.size() == 1)
//		{
//			if (!pCurrent->mEdges[0].mEnd->mVisited)
//				pCurrent->mEdges[0].mEnd->mPath = pCurrent->mPath + 1;
//			oNodeStack.push_back(pCurrent->mEdges[0].mEnd);
//		}
//		else
//		{
//			float edgeSize = oNodeStack.size();
//			for (int i = 0; i < pCurrent->mEdges.size(); ++i)
//			{
//				if (DistanceTo(pCurrent, aEnd) > DistanceTo(pCurrent->mEdges[i].mEnd, aEnd))
//				{
//					if (!pCurrent->mEdges[i].mEnd->mVisited)
//						pCurrent->mEdges[i].mEnd->mPath = pCurrent->mPath + 1;
//					oNodeStack.push_back(pCurrent->mEdges[i].mEnd);
//				}
//			}
//			if (edgeSize == oNodeStack.size())
//			{
//				for (int i = 0; i < pCurrent->mEdges.size(); ++i)
//				{
//					if (!pCurrent->mEdges[i].mEnd->mVisited)
//						pCurrent->mEdges[i].mEnd->mPath = pCurrent->mPath + 1;
//					oNodeStack.push_back(pCurrent->mEdges[i].mEnd);
//				}
//			}
//		}
//	}
//	ResetVisited();
//	return;
//}

void Graph::Draw()
{
	for (int i = 0; i < mNodes.size(); i++)
	{
		MoveSprite(mNodes[i]->mState, mNodes[i]->mX, mNodes[i]->mY);
		DrawSprite(mNodes[i]->mState);
	}
}

void Graph::IsKill()
{
	if (mNodes.size() != 0)
		RemoveNode(mNodes[mNodes.size() - 1]);
}

void Graph::EdgeMap()
{
	if (mGridH * mGridW != mNodes.size())
	{
		//for (int i = 0; i < mGridW; i++)
		//{
		//	for (int ii = 0; ii < mGridH; ii++)
		//	{
		//		if (ii > 0)
		//			mNodes[ii + (i * mGridH)]->AddEdgeTo(mNodes[ii + (i * mGridH) - 1]);
		//		if (ii < mGridH - 1)
		//			mNodes[ii + (i * mGridH)]->AddEdgeTo(mNodes[ii + (i * mGridH) + 1]);
		//		if (i > 0)
		//			mNodes[ii + (i * mGridH)]->AddEdgeTo(mNodes[ii + (i * mGridH) - 1]);
		//		if (i < mGridW - 1)
		//			mNodes[ii + (i * mGridH)]->AddEdgeTo(mNodes[ii + (i * mGridH) + 1]);

		//	}
		//}
	}
	else
	{
		for (int i = 0; i < mGridW; i++)
		{
			for (int ii = 0; ii < mGridH; ii++)
			{
				//int ia = ii + (i * mGridH) - 1;
				//int ib = ii + (i * mGridH) + 1;
				//int ic = ii + ((i - 1) * mGridH);
				//int id = ii + ((i + 1) * mGridH);
				if (ii > 0 )
					mNodes[ii + (i * mGridH)]->AddEdgeTo(mNodes[ii + (i * mGridH) - 1]);
				if (ii < mGridH - 1)
					mNodes[ii + (i * mGridH)]->AddEdgeTo(mNodes[ii + (i * mGridH) + 1]);
				if (i > 0)
					mNodes[ii + (i * mGridH)]->AddEdgeTo(mNodes[ii + ((i - 1) * mGridH)]);
				if (i < mGridW - 1)
					mNodes[ii + (i * mGridH)]->AddEdgeTo(mNodes[ii + ((i + 1) * mGridH)]);
			}
		}
	}
}

GraphNode* Graph::Closest(GraphNode* aGN, GraphNode* bGN, GraphNode* aEnd)
{
	if (DistanceTo(bGN, aEnd) < DistanceTo(aGN, aEnd))
		return aGN;
	return bGN;
}

GraphNode* Graph::Closest(GraphNode* aGN, GraphNode* bGN, GraphNode* cGN, GraphNode* aEnd)
{
	if (DistanceTo(bGN, aEnd) < DistanceTo(aGN, aEnd))
	{
		if (DistanceTo(cGN, aEnd) < DistanceTo(bGN, aEnd))
			return cGN;
		return bGN;
	}
	if (DistanceTo(aGN, aEnd) < DistanceTo(cGN, aEnd))
		return aGN;
	return cGN;
}

GraphNode* Graph::Closest(GraphNode* aGN, GraphNode* bGN, GraphNode* cGN, GraphNode* dGN, GraphNode* aEnd)
{
	if (DistanceTo(bGN, aEnd) < DistanceTo(aGN, aEnd))
	{
		if (DistanceTo(cGN, aEnd) < DistanceTo(bGN, aEnd))
		{
			if (DistanceTo(cGN, aEnd) < DistanceTo(dGN, aEnd))
				return cGN;
			return dGN;
		}
		if (DistanceTo(bGN, aEnd) < DistanceTo(dGN, aEnd))
			return bGN;
		return dGN;
	}
	if (DistanceTo(aGN, aEnd) < DistanceTo(cGN, aEnd))
	{
		if (DistanceTo(aGN, aEnd) < DistanceTo(dGN, aEnd))
			return aGN;
		return dGN;
	}
	if (DistanceTo(cGN, aEnd) < DistanceTo(dGN, aEnd))
		return cGN;
	return dGN;
}

float Graph::DistanceTo(GraphNode* aStart, GraphNode* aEnd)
{
	return sqrt(((aEnd->mX - aStart->mX) * (aEnd->mX - aStart->mX)) + ((aEnd->mY - aStart->mY) * (aEnd->mY - aStart->mY)));
}
