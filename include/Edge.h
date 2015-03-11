#ifndef EDGE_H
#define EDGE_H

#include "GraphNode.h"

struct Edge
{
	GraphNode* m_pStart, m_pEnd;
	float m_fCost;
};

#endif