#ifndef CellStack_H
#define CellStack_H

#include "Cell.h"

class CellStack{

private:
	Cell* _data[1000];
	int _count;

public:
	CellStack();

	void clear();
	void push(class Cell* c);
	Cell* pop();
};

#endif