#ifndef _PLANNODE_
#define _PLANNODE_

#include "SearchNode.h"

class PlannerNode {

public:

	PlannerNode() { }
	PlannerNode(float g, float h, float f, SearchNode* n, PlannerNode* p) { _hueristic = h; _node = n; _parent = p; }


	float _givenCost;
	float _hueristic;
	float _finalCost;

	SearchNode* _node;
	PlannerNode* _parent;
};
#endif