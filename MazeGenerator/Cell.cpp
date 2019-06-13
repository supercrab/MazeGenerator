#include "stdafx.h"

#include "Types.h"
#include "Cell.h"
#include "Maze.h"

// Constructor - set all walls
Cell::Cell() {
	memset(_walls, 1, sizeof _walls);
}

// Cell column property
int Cell::column(){
	return _column;
}
void Cell::setColumn(int c){
	_column = c;
}

// Cell row property
int Cell::row(){
	return _row;
}
void Cell::setRow(int r){
	_row = r;
}

// Wall property
bool Cell::wall(int d){
	return _walls[d];
}

void Cell::setWall(int d, bool v){
	_walls[d] = v;
}

// Does the cell have 4 walls
bool Cell::hasAllWalls(){
	for (int i = 0; i < 4; i++){
		 if (_walls[i] == 0)
			 return false;
	}
	return true;
}

// Knock down a wall
void Cell::knockDownWall(class Cell* cell){

	// find adjacent wall
	int theWallToKnockDown = findAdjacentWall(cell);
	_walls[theWallToKnockDown] = false;
	int oppositeWall = (theWallToKnockDown + 2) % 4;
	cell->setWall(oppositeWall, false);
}

// Find the adjacent wall
int Cell::findAdjacentWall(class Cell* cell){
	if (cell->column() == _column) {
		if (cell->row() < _row)
			return TOP;
		else
			return BOTTOM;
	}
	else {
		// _rows are the same
		if (cell->column() < _column)
			return LEFT;
		else
			return RIGHT;
	}
}

// Draw cell
void Cell::draw(){

}