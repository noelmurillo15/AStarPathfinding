#include "Grid.h"
#include "Tile.h"


Grid::Grid()
	: _rowcount(0), _columncount(0), _tiles(0){
}


Grid::~Grid() {
	reset();
}

void Grid::createTileArray(int row, int col) {
	reset();
	_rowcount = row;
	_columncount = col;
	_tiles = new Tile*[_rowcount * _columncount];
}

void Grid::addTile(int row, int col, unsigned char data) {
	_tiles[row * _columncount + col] = new Tile(row, col, data);
}

Tile* Grid::getTile(int row, int col) const {
	if ((0 <= row) && (0 <= col) && (row < _rowcount) && (col < _columncount))
		return _tiles[row * _columncount + col];
	else
		return 0;
}

Tile* Grid::getTile(int i) const {
	return _tiles[i];
}

void Grid::reset() {

	if (_tiles)
	{
		int n = _rowcount * _columncount;
		_rowcount = _columncount = 0;

		while (n)
		{
			delete _tiles[--n];
			_tiles[n] = 0;
		}

		delete[] _tiles;
		_tiles = 0;
	}
}