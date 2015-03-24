#ifndef EDGE_H
#define EDGE_H

#include <string>
#include <vector>
#include <queue>
#include <math.h>
#include "AIE.h"
#include "Util.h"

class GraphNode;

struct Edge
{
	Edge();
	int mCost = 1;
	GraphNode* mStart;
	GraphNode* mEnd;
};

#endif