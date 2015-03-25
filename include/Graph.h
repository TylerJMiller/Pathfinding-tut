#ifndef GRAPH_H
#define GRAPH_H

#include "GraphNode.h"

class Graph
{
	typedef std::vector<GraphNode*> NodeList;
public:
	//creates an empty graph
	Graph();
	~Graph();
	//creates a grid with gridsize, x start, y start, tile size
	Graph(unsigned int a_uiNodeCount, float aX, float Ay, unsigned int aTileSize);
	Graph(unsigned int aGridW, unsigned int aGridH, float aX, float aY, unsigned int aTileSize);
	//adds node to the end
	void AddNode(GraphNode* aNode);
	
	//turns given node into wall and removes edges
	bool TurnWall(GraphNode* aNode);

	//removes specified node
	void RemoveNode(GraphNode* aNode);

	//outputs neighbor nodes
	void PrintNeighbors(GraphNode* aNode);
	void ResetVisited();
	void Draw();
	void IsKill();
	//RETURNS TRUE IF astart CAN FIND aend
	bool SearchDFS(GraphNode* aStart, GraphNode* aEnd);
	//STAR SEARCH
	void SearchSTAR(GraphNode* aStart, GraphNode* aEnd);
	//DIJKSTRA SEARCH
	void Dijkstra(GraphNode* aStart, GraphNode* aEnd);
	unsigned int mGridW, mGridH, mCurNode;

	float DistanceTo(GraphNode* aStart, GraphNode* aEnd);

	float mTileSize, mX, mY;
	NodeList mNodes;
private:
	void EdgeMap();
};


#endif