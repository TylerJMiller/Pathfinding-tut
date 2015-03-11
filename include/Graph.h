#ifndef GRAPH_H
#define GRAPH_H

#include "GraphNode.h"

class Graph
{
	typedef std::vector<GraphNode*> NodeList;
public:
	//creates an empty graph
	Graph();
	//creates a graph with given number of nodes, random edges
	Graph(unsigned int a_uiNodeCount);

	void AddNode(GraphNode* aNode);
	void RemoveNode(GraphNode* aNode);
	void ResetVisited();

	bool SearchDFS(GraphNode* aStart, GraphNode* aEnd);

private:
	NodeList mNodes;
};


#endif