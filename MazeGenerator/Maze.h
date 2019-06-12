#ifndef Maze_H
#define Maze_H

#include "Cell.h"
#include "CellStack.h"

enum direction { 
	TOP, 
	LEFT, 
	BOTTOM, 
	RIGHT 
};

class Maze {

private:
	int _width;
	int _height;

	Cell _cells[100][100];
	CellStack _cellStack;

	int _totalCells;

	class Cell* _currentCell;

public:
	Maze();

	void initialise();
	void generate();
	void draw(HDC hdc);

	int width();
	int height();

	void setWidth(int w);
	void setHeight(int h);

	int getNeighboursWithWalls(Cell *neighbours[], Cell* aCell);
};

#endif