#include "stdafx.h"
#include <cstdlib> 
#include <iostream>
#include "Maze.h"

// Maze constructor
Maze::Maze(){

	_verticalness = 50;
	_width = 10;
	_height = 10;

	initialise();
}

int Maze::getNeighboursWithWalls(class Cell *neighbours[], class Cell *cell){
	int count = 0;

	for (int countColumn = -1; countColumn <= 1; countColumn++){
		for (int countRow = -1; countRow <= 1; countRow++){
			if ( (cell->column() + countColumn < _width) &&
				 (cell->row() + countRow < _height) &&
				 (cell->column() + countColumn >= 0) &&
				 (cell->row() + countRow >= 0) &&
				 ((countRow == 0) || (countColumn == 0)) &&
				 (countColumn != countRow)){
					if (_cells[cell->column() + countColumn][cell->row() + countRow].hasAllWalls()){
						neighbours[count] = & _cells[cell->column() + countColumn][cell->row() + countRow];
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
			//int randomCell = int(count * (rand() / (RAND_MAX + 1.0)));
			int randomCell = getRandomCell(_currentCell, adjacentCells, count);

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

	// Open up to left cell
	_cells[0][0].setWall(TOP, FALSE);

	// Open up bottom right cell
	_cells[_width-1][_height-1].setWall(BOTTOM, FALSE);
}

// Retrieve a random cell
int Maze::getRandomCell( class Cell *currentCell, class Cell *neighbours[], int count){
	int horizontalNeighbours[2];
	int verticalNeighbours[2];

	int horizontalCount = 0;
	int verticalCount = 0;

	// Put horizontal and vertical cell indexes into 2 buckets
	for (int c = 0; c < count; c++){
		if (neighbours[c]->column() == currentCell->column()){
			verticalNeighbours[verticalCount] = c;
			verticalCount++;
		}
		else{
			horizontalNeighbours[horizontalCount] = c;
			horizontalCount++;
		}
	}

	// Decide if we're gonna go horizontal or vertical
	if (rand() % 100 >= _verticalness){
		if (horizontalCount > 0)
			return horizontalNeighbours[rand() % horizontalCount];
		else
			return verticalNeighbours[rand() % verticalCount];
	}
	else{
		if (verticalCount > 0)
			return verticalNeighbours[rand() % verticalCount];
		else
			return horizontalNeighbours[rand() % horizontalCount];
	}
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

// Set percentage of the mase being vertial
//
// 100 all vertical 
// 50  even distribution of vertical and horizontal corridoers
// 0   all horizontal 
void Maze::setVerticalness(int h){
	if (h > 100) 
		h = 100; 
	else if (h < 0) 
		h = 0;
	_verticalness = h;
}
int Maze::verticalness(){
	return _verticalness;
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