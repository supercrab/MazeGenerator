#ifndef Maze_H
#define Maze_H

#include "Types.h"
#include "Cell.h"
#include "CellStack.h"

class Maze {

private:
	Cell _cells[100][100];
	CellStack _cellStack;

	int _verticalness;
	int _width;
	int _height;
	int _totalCells;

	class Cell* _currentCell;

public:
	Maze();

	void initialise();
	void generate();
	void draw(HDC hdc);

	int width();
	int height();
	int verticalness();
	
	void setWidth(int w);
	void setHeight(int h);
	void setVerticalness(int v);

	int getNeighboursWithWalls(Cell *neighbours[], Cell* cell);
	int getRandomCell(Cell* cell, Cell *neighbours[], int count);
};

#endif