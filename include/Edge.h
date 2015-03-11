#ifndef EDGE_H
#define EDGE_H

class GraphNode;

struct Edge
{
	Edge();
	GraphNode* mStart;
	GraphNode* mEnd;
	float mCost;
};

#endif