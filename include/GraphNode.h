#ifndef GRAPHNODE_H_
#define GRAPHNODE_H_

#include "Edge.h"

class GraphNode
{
	typedef std::vector<Edge> EdgeList;
public:
	GraphNode(int aNum, float ax, float ay);
	~GraphNode();
	void AddEdgeTo(GraphNode* aEnd);
	bool mWall;
	unsigned int mNodeNumber, mState;
	int mPathScore;
	float mX, mY;
	bool mVisited;
	GraphNode* mParent;
	EdgeList mEdges;
};

#endif