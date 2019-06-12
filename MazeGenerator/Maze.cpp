#include "stdafx.h"
#include <cstdlib> 
#include <iostream>
#include "Maze.h"

#define TOP		0
#define LEFT	1
#define BOTTOM	2
#define RIGHT	3

// Maze constructor
Maze::Maze(){

	_width = 10;
	_height = 10;

	initialise();
}

int Maze::getNeighboursWithWalls(class Cell *neighbours[], class Cell *aCell){
	int count = 0;

	for (int countColumn = -1; countColumn <= 1; countColumn++){
		for (int countRow = -1; countRow <= 1; countRow++){
			if ( (aCell->column() + countColumn < _width) &&
				 (aCell->row() + countRow < _height) &&
				 (aCell->column() + countColumn >= 0) &&
				 (aCell->row() + countRow >= 0) &&
				 ((countRow == 0) || (countColumn == 0)) &&
				 (countColumn != countRow)){
					if (_cells[aCell->column() + countColumn][aCell->row() + countRow].hasAllWalls()){
						neighbours[count] = & _cells[aCell->column() + countColumn][aCell->row() + countRow];
						count++;
				}
			}
		}
	}

	return count;
}

// Initialise maze
void Maze::initialise(){

	_totalCells = _width * _height;
	for (int column = 0; column < _width; column++)
		for (int row = 0; row < _height; row++){
			_cells[column][row].setColumn(column);
			_cells[column][row].setRow(row);
		}

	_currentCell =  &_cells[0][0];
	_cellStack.clear();
}

// Generate maze
void Maze::generate(){

	int visitedCells = 1;

	class Cell* adjacentCells[4];

	while (visitedCells < _totalCells){

		// get a list of the neighboring cells with all walls intact
		int count = getNeighboursWithWalls(adjacentCells, _currentCell);

		// test if a cell like this exists
		if (count > 0){

			// yes, choose one of them, and knock down the wall between it and the current cell
			int randomCell = int(count * (rand() / (RAND_MAX + 1.0)));
			class Cell* theCell = adjacentCells[randomCell];
			_currentCell->knockDownWall(theCell);
			_cellStack.push(_currentCell); // push the current cell onto the stack
			_currentCell = theCell; // make the random neighbor the new current cell
			visitedCells++;
		}
		else {
			// No cells with walls intact, pop current cell from stack
			_currentCell = _cellStack.pop();
		}
	}

	_cells[0][0].setWall(TOP, FALSE);
	_cells[_width-1][_height-1].setWall(BOTTOM, FALSE);
}

// Width property
int Maze::width(){
	return _width;
}

void Maze::setWidth(int w){
	_width = w;
}

// Height property
void Maze::setHeight(int h){
	_height = h;
}
int Maze::height(){
	return _height;
}

// Draw Maze
void Maze::draw(HDC hdc){

	int ox = 50;
	int oy = 50;
	int size = 20;

	for (int y = 0; y < _height; y++){
		for (int x = 0; x < _width; x++) {
			if (_cells[x][y].wall(TOP)){
				MoveToEx(hdc, (x * size) + ox, (y * size) + oy, (LPPOINT) NULL); LineTo(hdc, ((x + 1) * size) + ox, (y * size) + oy);
			}
			if (_cells[x][y].wall(LEFT)){
				MoveToEx(hdc, (x * size) + ox, (y * size) + oy, (LPPOINT) NULL); LineTo(hdc, (x * size) + ox, ((y + 1) * size) + oy);
			}
			if (_cells[x][y].wall(BOTTOM)){
				MoveToEx(hdc, (x * size) + ox, ((y + 1) * size) + oy, (LPPOINT) NULL); LineTo(hdc, ((x + 1) * size) + ox, ((y + 1) * size) + oy);
			}
			if (_cells[x][y].wall(RIGHT)){
				MoveToEx(hdc, ((x + 1) * size) + ox, (y * size) + oy, (LPPOINT) NULL); LineTo(hdc, ((x + 1) * size) + ox, ((y + 1) * size) + oy);
			}
		}
	}
}