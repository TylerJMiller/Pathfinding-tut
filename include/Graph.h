#ifndef GRAPH_H
#define GRAPH_H

#include "GraphNode.h"

class Graph
{
	typedef std::vector<GraphNode*> NodeList;
public:
	Graph();
	Graph(unsigned int a_uiNodeCount);

	void AddNode(GraphNode* a_pNode);
	void RemoveNode(GraphNode* a_pNode);
private:
	NodeList m_aNodes;
};


#endif