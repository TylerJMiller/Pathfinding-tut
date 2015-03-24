#ifndef GRAPHNODE_H_
#define GRAPHNODE_H_

#include "Edge.h"

class GraphNode
{
	typedef std::vector<Edge> EdgeList;
public:
	GraphNode(int aNum, float ax, float ay);
	void AddEdgeTo(GraphNode* aEnd);
	bool mWall;
	unsigned int mNodeNumber, mState, mPath;
	float mX, mY;
	bool mVisited;
	EdgeList mEdges;
};

#endif