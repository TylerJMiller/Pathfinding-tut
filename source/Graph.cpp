#include "Graph.h"

Graph::Graph()
{};

Graph::Graph(unsigned int aNodeCount)
{ 
	mNodes.resize(aNodeCount);
}

void Graph::AddNode(GraphNode* aNode)
{
	mNodes.push_back(aNode);
}

void Graph::RemoveNode(GraphNode* aNode)
{
	for (int i = 0; i < mNodes.size(); i++)
	{
		for (std::vector<Edge>::iterator it = mNodes[i]->mEdges.begin(); it != mNodes[i]->mEdges.end(); it++)
		{
			if (&(*it->mEnd) == aNode)
			{
				mNodes[i]->mEdges.erase(it);
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
	std::stack<GraphNode*> oNodeStack;
	oNodeStack.push(aStart);
	return false;
}