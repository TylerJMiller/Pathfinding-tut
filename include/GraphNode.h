#ifndef GRAPHNODE_H_
#define GRAPHNODE_H_

#include <string>
#include <vector>
#include "Edge.h"

class GraphNode
{
	typedef std::vector<Edge> EdgeList;
public:
	GraphNode(int a_iNum);
	int mNodeNumber;
	bool mVisited;
	EdgeList mEdges;
};

#endif