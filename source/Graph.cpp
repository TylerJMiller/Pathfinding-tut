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
				int ia = ii + (i * mGridH) - 1;
				int ib = ii + (i * mGridH) + 1;
				int ic = ii + ((i - 1) * mGridH);
				int id = ii + ((i + 1) * mGridH);
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