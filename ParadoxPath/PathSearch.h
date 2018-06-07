#ifndef _PATH_SEARCH_
#define _PATH_SEARCH_

#include <cmath>
#include <vector>
#include <queue>
#include <unordered_map>

#include "Grid.h"
#include "PlannerNode.h"
#include "Custom_PriorityQueue.h"
#include "BinaryHeap.h"


class PathSearch {

#pragma region Variables
	int _pathLength = 0;
	bool _foundsolution = false;

	Tile* _goal = nullptr;
	Tile* _start = nullptr;
	Grid* _myGrid = nullptr;

	//	Containers
	/*BinaryHeap<PlannerNode*> _openheap;
	DynArray<int*> openList;
	DynArray<float*> fCost;
	DynArray<int> openX;
	DynArray<int> openY;*/


	Custom_PriorityQueue<PlannerNode*> _open;
	std::vector<Tile const*> _solution;
	std::vector<SearchNode*> _searches;
	std::unordered_map<Tile*, PlannerNode*> _visited;
#pragma endregion

#pragma region Private Functions
	//	Finds neighboring tiles in the 2D Grid
	std::vector<Tile*> FindNeighbors(Grid* _grid, Tile* tile);

	//	Stores data and creates Start and Goal Data
	void Initialize(int startRow, int startColumn, int goalRow, int goalColumn);

	//	Searches for shortest path
	void Update();

	//	builds the solution path and exits
	void BuildSolution(PlannerNode* current);

	//	update successors based on heuristics
	void IdentifySuccessors(PlannerNode* current);

	//	Clean all memory
	void ShutDown();

	// Converts a 2D Index to a 1D Index
	inline size_t Index(int row, int col, int column_count) const { return row * column_count + col; };

	//	Prioritizes based on hueristic
	static bool isGreater(PlannerNode* const& lhs, PlannerNode* const& rhs) { return (lhs->_finalCost > rhs->_finalCost); }

	// Estimates a hueristic based on distance from start tile to goal tile
	inline float Estimate(Tile* node) {
		float dx1 = abs((float)node->getRow() - (float)_goal->getRow());
		float dy1 = abs((float)node->getColumn() - (float)_goal->getColumn());
		return abs(dx1 + dy1) * 1.2f;
	}
	inline float Estimate(Tile* s, Tile* e) {
		return (abs((float)s->getRow() - e->getRow()) + abs((float)s->getColumn() - e->getColumn()));
	}
#pragma endregion


public:

	// Default Constructor
	PathSearch();

	// Destructor
	~PathSearch();

	// Returns shortest path between two points in a 2-dimensional grid
	int FindPath(const int nStartX, const int nStartY,
		const int nTargetX, const int nTargetY,
		const unsigned char* pMap, const int nMapWidth, const int nMapHeight,
		int* pOutBuffer, const int nOutBufferSize);
};

#endif