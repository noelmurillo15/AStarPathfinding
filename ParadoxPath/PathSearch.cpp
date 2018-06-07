#include "PathSearch.h"

#define NOPATHEXISTS -1


PathSearch::PathSearch() : _open(&isGreater) {

}


PathSearch::~PathSearch() {
	ShutDown();
}


int PathSearch::FindPath(const int nStartX, const int nStartY,
	const int nTargetX, const int nTargetY, const unsigned char* pMap,
	const int nMapWidth, const int nMapHeight, int* pOutBuffer, const int nOutBufferSize) {


	//2D Grid Setup
	_myGrid = new Grid();
	_myGrid->createTileArray(nMapHeight, nMapWidth);

	/*openList.reserve(nMapWidth * nMapHeight);
	fCost.reserve(nMapWidth * nMapHeight);*/

	// Bigger loop within smaller loop
	if (nMapHeight <= nMapWidth) {
		for (int row = 0; row < nMapHeight; row++) {
			for (int col = 0; col < nMapWidth; col++) {
				_myGrid->addTile(row, col, pMap[Index(row, col, nMapWidth)]);			
			}
		}
	}
	else {
		for (int col = 0; col < nMapWidth; col++) {
			for (int row = 0; row < nMapHeight; row++) {
				_myGrid->addTile(row, col, pMap[Index(row, col, nMapWidth)]);
			}
		}
	}

	//	Setup for the path search
	Initialize(nStartY, nStartX, nTargetY, nTargetX);


	//	if solution was found and the shortest path is not longer than nOutBufferSize
	if (_foundsolution && _pathLength > 0) {
		if (_pathLength <= nOutBufferSize) {
			unsigned int i = 0;
			for (std::vector<Tile const*>::reverse_iterator it = _solution.rbegin(); it != _solution.rend(); ++it) {
				//	Copy answer to buffer	
				pOutBuffer[i] = Index((*it)->getRow(), (*it)->getColumn(), nMapWidth);
				i++;
			}
		}
		else {	//	if pathlength is greater than buffer size
			_pathLength = NOPATHEXISTS;
		}
	}
	else {	//	if no such path exists
		_pathLength = NOPATHEXISTS;
	}
	return _pathLength;
}


#pragma region Helper Functions
std::vector<Tile*> PathSearch::FindNeighbors(Grid* _grid, Tile* tile) {

	const int _row = tile->getRow();
	const int _col = tile->getColumn();
	std::vector<Tile*> neighbors;
	neighbors.reserve(4);

	// Locations are considered to be adjacent horizontally and vertically but not diagonally
	if (_grid->getTile(_row, _col - 1) && _grid->getTile(_row, _col - 1)->getWeight() != 0) { neighbors.push_back(_grid->getTile(_row, _col - 1)); }	//	left
	if (_grid->getTile(_row, _col + 1) && _grid->getTile(_row, _col + 1)->getWeight() != 0) { neighbors.push_back(_grid->getTile(_row, _col + 1)); }	//	right
	if (_grid->getTile(_row + 1, _col) && _grid->getTile(_row + 1, _col)->getWeight() != 0) { neighbors.push_back(_grid->getTile(_row + 1, _col)); }	//	down
	if (_grid->getTile(_row - 1, _col) && _grid->getTile(_row - 1, _col)->getWeight() != 0) { neighbors.push_back(_grid->getTile(_row - 1, _col)); }	//	up

	return neighbors;
}


void PathSearch::Initialize(int startRow, int startColumn, int goalRow, int goalColumn) {
	_foundsolution = false;

	//	Determine tile that represents start and goal
	_start = _myGrid->getTile(startRow, startColumn);
	_goal = _myGrid->getTile(goalRow, goalColumn);

	//	Create SearchNode
	SearchNode* node = new SearchNode(_start);
	_searches.push_back(node);

	//	Create Planner Node
	PlannerNode* begin = new PlannerNode(0.0f, Estimate(_start), Estimate(_start), node, NULL);

	//	Add Node to open container
	_open.push(begin);

	//	Add node to Visited Map
	_visited[_start] = begin;

	//	Search for a Path
	Update();
}


void PathSearch::Update() {

	do {
		//	Denqueue the current node from open container
		PlannerNode* current = _open.front(); _open.pop();

		BuildSolution(current);

		IdentifySuccessors(current);
		
	} while (!_open.empty());
}


void PathSearch::BuildSolution(PlannerNode* current)
{
	// If this node is the goal tile, build the solution list and exit
	if (current->_node->_tile == _goal) {
		//	Don't include the start node
		while (current != NULL && current->_node->_tile != _start) {
			_solution.push_back(current->_node->_tile);
			current = current->_parent;
			_pathLength++;
		}

		// Safety check: Makes sure a path was found
		if (_pathLength > 0)
			_foundsolution = true;

		return;
	}
}


void PathSearch::IdentifySuccessors(PlannerNode* current) {
	// For each successor of the current tile
	std::vector<Tile*> children = FindNeighbors(_myGrid, current->_node->_tile);
	for (unsigned int x = 0; x < children.size(); x++) {
		SearchNode* n_successor = new SearchNode(children[x]);
		_searches.push_back(n_successor);

		//	Compute new given cost of the successor
		float gcost = Estimate(current->_node->_tile, n_successor->_tile);
		float newG = current->_givenCost + gcost;

		//	if successor is a duplicate
		if (_visited[n_successor->_tile] != NULL) {
			PlannerNode* p_node = _visited[n_successor->_tile];
			//	if newG is cheaper than given cost
			if (newG < p_node->_givenCost) {
				_open.remove(p_node);
				p_node->_givenCost = gcost;
				p_node->_finalCost = gcost + p_node->_hueristic;
				p_node->_parent = current;
				_open.push(p_node);
			}
		}
		else {	//	if successor is not a duplicate
			PlannerNode* p_node = new PlannerNode();
			p_node->_node = n_successor;
			p_node->_givenCost = gcost;
			p_node->_hueristic = Estimate(n_successor->_tile);
			p_node->_hueristic *= (1.0f + .001f);
			p_node->_finalCost = gcost + p_node->_hueristic;
			p_node->_parent = current;
			_visited[n_successor->_tile] = p_node;
			_open.push(p_node);
		}
	}
}


void PathSearch::ShutDown() {

	//	Free all the memory
	_pathLength = 0;
	_foundsolution = false;

	for (std::vector<SearchNode*>::iterator it = _searches.begin(); it != _searches.end(); it++) {
		delete (*it);
	}

	for (std::unordered_map<Tile*, PlannerNode*>::iterator it = _visited.begin(); it != _visited.end(); it++) {
		delete it->second;
	}

	_visited.clear();
	_open.clear();
	_solution.clear();

	_start = nullptr;
	_goal = nullptr;
	
	if(_myGrid != nullptr)
		delete _myGrid;
}
#pragma endregion