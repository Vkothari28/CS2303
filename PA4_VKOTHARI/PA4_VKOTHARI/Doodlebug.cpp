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

//Delare known constants from instructions
//constant for the board dimensions of 20a20
//const int MWS = 20; //maa board size

//starting values for ants and doodlebugs

//values for returning Ants and Doodlebugs
const int DODO= 1;
const int ANT = 2;

//Values for counter when determining if ants or doodles should breed
const int ANTBREED = 3; //3 lifespans aka timesteps
const int DODOBREED = 8; //8 lifespans aka timesteps

//value for counter to determine of a doodle should starve
const int DOODIE = 3; //3 lifespans aka timesteps

/**
 * Doodlebug Construcor
 * Description: uses the default constructor from organism to create
 * a default Doodlebug. Sets moveUntilStarve to 0.
 */
Doodlebug::Doodlebug() : Organism() {
	starvemoves = 0;
}

/**
 * Overloaded constructor
 * Description: the  overloaded constructor in  organism is used to create
 * an overloaded Doodlebug. Sets starvemoves initially to 0.
 * @param board
 * @param a
 * @param b
 */
Doodlebug::Doodlebug(Board *board, int a, int b) : Organism(board, a, b) {
	starvemoves = 0;
}


/**
 * Move
 * Redefined the pure virtual function from organism to
 * reflect Doodlenbug's behavior in regards to move. First it scans up,
 * down, left, then right to look for an ant. As soon as one is found
 * the Doodlebug kills the ant (ant cell deleted) and moves to that
 * spot. moveUntilStarve resets if this happens
 */
void Doodlebug::move() {

	//if, else if statements for if the Doodlebug can eat an ant
	if ((b > 0) && (board->getfromBoard(a, b-1) != NULL) && (board->getfromBoard(a, b-1)->getType() == ANT)) {
		//delete the ant object from the board
		delete (board->printGrid[a][b-1]);
		//move "this" doodlebug to the spot the ant was in
		board->printGrid[a][b-1] = this;
		//set the spot the doodlebug just left to NULL (empty)
		board->setonBoard(a, b, NULL);
		//reset the starvemoves counter
		starvemoves = 0;
		//ensure b coordinate is decremented (moved up) changed for Doodlebug
		b--;
		return;
	}
	//similar as below for eating down, left and right
	else if ((b < WorldS-1) && (board->getfromBoard(a, b+1) != NULL) && (board->getfromBoard(a, b+1)->getType() == ANT)) {
		delete (board->printGrid[a][b+1]);
		board->printGrid[a][b+1] = this;
		board->setonBoard(a, b, NULL);
		starvemoves = 0;
		b++;
		return;
	}
	//eat left
	else if ((a > 0) && (board->getfromBoard(a-1, b) != NULL) && (board->getfromBoard(a-1, b)->getType() == ANT)) {
		delete (board->printGrid[a-1][b]);
		board->printGrid[a-1][b] = this;
		board->setonBoard(a, b, NULL);
		starvemoves = 0;
		a--;
		return;
	}
	//eat right
	else if ((a < WorldS-1) && (board->getfromBoard(a+1, b) != NULL) && (board->getfromBoard(a+1, b)->getType() == ANT)) {
		delete (board->printGrid[a+1][b]);
		board->printGrid[a+1][b] = this;
		board->setonBoard(a, b, NULL);
		starvemoves = 0;
		a++;
		return;
	}

	//Doodlebug can't eat an ant so it tries to move randomly (copied code from ant move)
	int moveDirection = rand() % 4; //values 0, 1, 2, 3

	if (moveDirection == 0) {
		if ((b > 0) && (board->getfromBoard(a, b-1) == NULL)) {
			//move the doodle to this spot
			board->setonBoard(a, b-1, board->getfromBoard(a,b));
			//set the old spot to NULL
			board->setonBoard(a, b, NULL);
			//ensure the b coordinate for object is decremented to reflect new cell
			b--;
		}
	}
	//check to move down
	else if (moveDirection==1) {
		if ((b < WorldS-1) && (board->getfromBoard(a, b+1) == NULL)) {
			board->setonBoard(a, b+1, board->getfromBoard(a, b));
			board->setonBoard(a, b, NULL);
			b++;
		}
	}
	//check to move left
	else if (moveDirection == 2) {
		if ((a > 0) && (board->getfromBoard(a-1, b) == NULL)) {
			board->setonBoard(a-1, b, board->getfromBoard(a, b));
			board->setonBoard(a, b, NULL);
			a--;
		}
	}
	//check to to move right
	else {
		if ((a < WorldS-1) && (board->getfromBoard(a+1, b) == NULL)) {
			board->setonBoard(a+1, b, board->getfromBoard(a, b));
			board->setonBoard(a, b, NULL);
			a++;
		}
	}
	//if the Doodlebug could not eat anything, increment the counter
	starvemoves++;
}

/**
 * getType
 * Redefined the pure virtual function from organism to
 * return the const integer value representing DODO.
 * @return
 */
int Doodlebug::getType() {
	return DODO;
}

/**
 * breed
 * Redefined the pure virtual function from organism to
 * create a new doodlebug if, the doodlebug in question survives 8 lifespans.
 * It won't breed if there is not an open spot. My choice to check down,
 * then up, then left, then right.
 */
void Doodlebug::breed() {

	//increase the lifespans of the Doodlebug
	lifespans++;

	//if Doodlebug has survived 8 lifespans
	if (lifespans == DODOBREED) {
		//reset the lifespan counter
		lifespans = 0;

		//above
		if ((b > 0) && (board->getfromBoard(a, b-1) == NULL)) {
			/*Doodlebug *newDoodle =*/ new Doodlebug(board, a, b-1);
			BABYDOODLE++;
		}
		//left
		else if ((b < WorldS-1) && (board->getfromBoard(a, b+1) == NULL)) {
			/*Doodlebug *newDoodle =*/ new Doodlebug(board, a, b+1);
			BABYDOODLE++;
		}
		//right
		else if ((a > 0) && (board->getfromBoard(a-1, b) == NULL)) {
			/*Doodlebug *newDoodle =*/ new Doodlebug(board, a-1, b);
			BABYDOODLE++;
		}
		//down
		else if ((a < WorldS-1) && (board->getfromBoard(a+1, b) == NULL)) {
			/*Doodlebug *newDoodle =*/ new Doodlebug(board, a+1, b);
			BABYDOODLE++;
		}
	}
}


/**
 * starve
 * Redefined the pure virtual function starve from abstract
 * class Organism to return true if a Doodlebug has not eaten in 3
 *  false if they have. Use the starvemoves
 * variable to determine this.
 */
bool Doodlebug::starve() {
	//starve
	if (starvemoves > DOODIE) {
		return true;
	}
	//survive
	else {
		return false;
	}
}
/**
 * Destructor
*/
Doodlebug::~Doodlebug(){

}
