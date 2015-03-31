#ifndef EDGE_H
#define EDGE_H

#include "Util.h"

class GraphNode;

struct Edge
{
	Edge();
	~Edge();
	int mCost;
	GraphNode* mStart;
	GraphNode* mEnd;
};

#endif