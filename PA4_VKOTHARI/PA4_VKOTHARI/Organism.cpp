

#include "All.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <time.h>
#include <string>
#include "Board.h"
#include "Organism.h"
#include "Ant.h"
#include "Doodlebug.h"
using namespace std;

const int DOODLEBUG = 1;
const int ANT = 2;


const int ANTBREED = 3; //3 lifespans
const int DODOBREED = 8; //8 lifespans

//value for counter to determine of a doodle should starve
const int DOODIE = 3; //3 lifespans

/**
 * Constructor:
 * Creates a default organism
 */
Organism::Organism() {

	a = 0;
	b = 0;

	//empty space
	board = NULL;

	//flag for moving
	itmoved = false;
	//counter for breed/death conditions
	lifespans = 0;
}

/**
 * Constructor:
 * Creates an organism object which is in the board array
 * @param pBoard
 * @param  a
 * @param b
 */
Organism::Organism(Board *pBoard, int  a, int b) {

	this->a =  a;
	this->b = b;

	//in reference to the board object
	this->board = pBoard;
	//sets the cell in board to object
	pBoard->setonBoard(a, b, this);

	//flag for moving
	itmoved = false;
	//counter for breed/death conditions
	lifespans = 0;
}
/**
 * Destructor
 */
Organism::~Organism(){

}
