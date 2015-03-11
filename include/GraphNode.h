#ifndef GRAPHNODE_H
#define GRAPHNODE_H

#include <string>
#include <vector>
#include "Edge.h"

class GraphNode
{
public:
	GraphNode(int a_iNum);
	int m_iNodeNumber;
	typedef std::vector<Edge> EdgeList;
	EdgeList m_aEdges;
};

#endif