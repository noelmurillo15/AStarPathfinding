#ifndef _NODE_
#define _NODE_

#include "Tile.h"
#include <vector>


class SearchNode {

public:

	SearchNode(Tile* _t) { _tile = _t; }
	std::vector<Tile*> _edges;
	Tile* _tile;
};
#endif