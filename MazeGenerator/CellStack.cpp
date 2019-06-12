#include "stdafx.h"

#include "CellStack.h"

// Constructor
CellStack::CellStack(){
	clear();
}

// Clear the stack
void CellStack::clear(){
	_count = 0;
}

// Add a cell to the stack
void CellStack::push(class Cell* c){
	_data[_count] = c;
	_count++;
}

// Pop a cell off the the stack
Cell* CellStack::pop(){
	if (_count > 0){
		_count--;
		return (Cell*) _data[_count];
	}
	return NULL;
}