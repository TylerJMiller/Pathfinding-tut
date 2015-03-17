#ifndef EDGE_H
#define EDGE_H

#include <string>
#include <vector>
#include <queue>
#include <math.h>
#include "AIE.h"

class GraphNode;

struct Edge
{
	Edge();
	GraphNode* mStart;
	GraphNode* mEnd;
};

#endif