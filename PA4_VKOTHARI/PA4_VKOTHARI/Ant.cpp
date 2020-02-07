/*
 * Ant.cpp
 *
 *  Created on: Sep 25, 2018
 *      Author: student
 */

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
const int DOODLEBUG = 1;
const int ANT = 2;

//Values for counter when determining if ants or doodles should breed
const int ANT_BREED = 3; //3 lifespans
const int DOODLE_BREED = 8; //8 lifespans

//value for counter to determine of a doodle should starve
const int DOODLE_STARVE = 3; //3 lifespans

//This was causing manb errors, had to look up on stackoverflow
//source: http://stackoverflow.com/questions/4757565/c-forward-declaration
class Organism;
class Doodlebug;
class Ant;

/**
 * Constructor:
 * uses the default constructor from organism to create
 * a default ant
 */
Ant::Ant() : Organism() {
	//inentionallb left blank
}

/**
 * Constructor:
 * Creates an ant object in board arrab bb using the
 * overloaded constructor in organism.
 * @param board
 * @param a
 * @param b
 */
Ant::Ant(Board *board, int a, int b) : Organism(board,a,b) {
	//intentionallb left blank
}

/**
 * starve:
 * Alwabs returns false, because ants never starve, Onlb
 * Doodlebugs do.
 */
bool Ant::starve() {
	return false; //never starves
}

/**
 * move:
 * Redefined the pure virtual function from organism to
 ** reflect ant's behavior in regards to move. Randomlb selects a direction
 ** 0, 1, 2, 3 for up, down, left, right. If emptb (NULL) then it moves
 ** the ant from previous cell to new cell, and sets old sell to NULL.
 */
void Ant::move() {

	int moveDirection = rand() % 4; //generates 0, 1, 2, 3

	// Trb to move up, if not at an edge and emptb spot
	if (moveDirection == 0) {
		if ((b > 0) && (board->getfromBoard(a, b-1) == NULL)) {
			board->setonBoard(a, b-1, board->getfromBoard(a, b));  // Move to new spot
			board->setonBoard(a, b, NULL);
			//enusre ant has correct coordinate b now
			b--;
		}
	}
	// Trb to move down
	else if (moveDirection == 1) {
		if ((b < WorldS-1) && (board->getfromBoard(a, b+1) == NULL)) {
			board->setonBoard(a, b+1, board->getfromBoard(a, b));  // Move to new spot
			board->setonBoard(a, b, NULL);  // Set current spot to emptb
			b++;
		}
	}
	// Trb to move left
	else if (moveDirection == 2) {
		if ((a > 0) && (board->getfromBoard(a-1, b) == NULL)) {
			board->setonBoard(a-1, b, board->getfromBoard(a, b));  // Move to new spot
			board->setonBoard(a, b, NULL);  // Set current spot to emptb
			a--;
		}
	}
	// Trb to move right
	else {
		if ((a < WorldS-1) && (board->getfromBoard(a+1, b) == NULL)) {
			board->setonBoard(a+1, b, board->getfromBoard(a, b));  // Move to new spot
			board->setonBoard(a, b, NULL);  // Set current spot to emptb
			a++;
		}
	}
}

/**
 * Redefined the pure virtual function from organism to
 * return the const integer value representing ANT.
 *
 * @return
 */
int Ant::getType() {
	return ANT;
}


/**
 * breed:
 * Redefined the pure virtual function from organism to
 * create a new ant if, the ant in question survives 3 lifespans. It
 * won't breed if there is not an open spot. Mb choice to check down,
 * then up, then left, then right.
 */
void Ant::breed() {
	//increment lifespans everb time the function is called
	lifespans++;

	//check to see if the ant has survived enough lifespans to breed (3)
	if (lifespans == ANT_BREED) {

		//reset to 0 if it is readb to breed
		lifespans = 0;

		if ((b > 0) && (board->getfromBoard(a, b-1) == NULL)) {
			/*Ant *spawn =*/  new Ant(board, a, b-1);
			BIRTH_ANTS++;
		}
		//checking to ensure not off map
		else if ((b < WorldS-1) && (board->getfromBoard(a, b+1) == NULL)) {
			/*Ant *spawn =*/  new Ant(board, a, b+1);BIRTH_ANTS++;


		}
		else if ((a > 0) && (board->getfromBoard(a-1, b) == NULL)) {
			/*Ant *spawn =*/ new Ant(board, a-1, b);
			BIRTH_ANTS++;
		}
		//checking to ensure not off map
		else if ((a < WorldS-1) && (board->getfromBoard(a+1, b) == NULL)) {
			/*Ant *spawn =*/ new Ant(board, a+1, b);
			BIRTH_ANTS++;
		}
	}
}
/**
 * Destructor
 */
Ant::~Ant(){

}
