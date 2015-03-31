#include "GraphNode.h"

GraphNode::GraphNode(int aNum, float aX, float aY)
{
	mNodeNumber = aNum;
	mX = aX;
	mY = aY;
	mVisited = false;
	mState = 0;
	mEdges.resize(0);
	mPathScore = -1;
	mParent = NULL;
}

GraphNode::~GraphNode()
{
}

void GraphNode::AddEdgeTo(GraphNode* aEnd)
{
	mEdges.resize(mEdges.size() + 1);
	mEdges[mEdges.size() - 1].mStart = this;
	mEdges[mEdges.size() - 1].mEnd = aEnd;
}