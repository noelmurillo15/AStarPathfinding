#ifndef _GRID_
#define _GRID_

class Tile;


class Grid {

	int _rowcount;
	int _columncount;

	Tile** _tiles;

public:

	Grid();
	~Grid();

	void createTileArray(int row, int col);

	void addTile(int row, int column, unsigned char data);
	Tile* getTile(int row, int col) const;
	Tile* getTile(int index) const;

	inline int getRowCount() const 
	{
		return _rowcount;
	}
	inline int getColumnCount() const 
	{
		return _columncount;
	}
	void reset();
};

#endif