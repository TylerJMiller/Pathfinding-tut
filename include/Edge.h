#ifndef EDGE_H
#define EDGE_H

#include <string>
#include <vector>
#include <stack>

class GraphNode;

struct Edge
{
	Edge();
	GraphNode* mStart;
	GraphNode* mEnd;
	float mCost;
};

#endif