#ifndef _TILE_
#define _TILE_


class Tile {

	int _row;
	int _column;
	unsigned char _weight;


public:

	Tile(int r, int c, unsigned char w);
	~Tile();

	inline int getRow() const 
	{
		return _row;
	}
	inline int getColumn() const 
	{
		return _column;
	}

	inline unsigned char getWeight() const 
	{
		return _weight;
	}
};

#endif