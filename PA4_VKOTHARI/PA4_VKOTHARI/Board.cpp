




#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <time.h>
#include <string>
#include "Board.h"
#include "All.h"
#include "Organism.h"
#include "Ant.h"
#include "Doodlebug.h"

using namespace std;
const int SEED=1;
//values for returning Ants and Doodlebugs
const int DODO = 1;
const int ANT = 2;

//Values for counter when determining if ants or doodles should breed
const int ANTBREED = 3; //3 lifespans
const int DOODLEBREED = 8; //8 lifespans

//the counter to determine if a doodle should starve
const int DOODIE = 3; //3 lifespans

class Organism;
class Doodlebug;
class Ant;


/**
 * Constructor:
 * fills organism array of (NULL) values
 */
Board::Board() {
	//fill the word with null objects (empty spaces)
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			printGrid[i][j] = NULL; //fills organism array (in board class) with null values
		}
	}
}


/**
 * input:
 * Initializes the board with Ants and Doodlebugs at a random location
 * @param INITIALANTS
 * @param INITIALDODOS
 */
void Board::input(int INITIALANTS,int INITIALDODOS){
	//integers for initial values of ants and doodlebugs for random filling of board
	int numberOfAnts = 0;
	int numberOfDoodles = 0;

	//inputting the board with ants
	while (numberOfAnts < INITIALANTS) {

		//generate a random  coordinate
		int a = rand() % WorldS;
		int b = rand() % WorldS;

		//if a certain coordinate is empty
		if (this->getfromBoard(a,b) == NULL) {
			//increase the counter
			numberOfAnts++;

			//create a pointer to Ant object
			new Ant(this, a, b);
		}
	}

	while (numberOfDoodles < INITIALDODOS) {
		//generate a random  coordinate within desired board size
		int a = rand()%WorldS;
		int b = rand()%WorldS;

		//for if the desired coordinate is empty
		if (this->getfromBoard(a,b) == NULL) {
			//increase the counter
			numberOfDoodles++;
			//create a pointer to Doodle object
			new Doodlebug(this, a, b);
		}
	}
}


/**
 * getfromBoard:
 * returns the organism that is stored in the cell
 * at coordinates a, b in the array.
 * @param a
 * @param b
 * @return
 */
Organism* Board::getfromBoard(int a, int b) {
	//check to make sure in the bounds of the board
	if ((a >= 0) && (a < WorldS) && ( b >= 0) && (b < WorldS)) {
		return printGrid[a][b];
	}
	return NULL;
}

/**
 * setonBoard:
 * Fills the cell at coordinates a and b with an object
 * (pointer) from the organism (derived) class
 * @param a
 * @param b
 * @param Orgo
 */
void Board::setonBoard(int a, int b, Organism *Orgo) {
	//check to make sure in the bounds of the board
	if ((a >= 0) && (a < WorldS) && (b >= 0) && (b < WorldS)) {
		printGrid[a][b] = Orgo;
	}
}

/**
 * createBoard:
 *  Prints the board to the console using O for ants and
 *  X for doodlebugs.
 */
void Board::createboard() {
	//free up some space between generations
	cout << "\n";

	//print the array
	for (int i = 0; i < WorldS; i++) {
		for (int j = 0; j < WorldS; j++) {
			//if no object is present a blank space will be given
			if(j==0){
				cout << "|";
			}
			if (printGrid[i][j] == NULL) {
				cout << " " << "|"; // | for formatting purposes, as it helps see cells more easily
				}
			//if a doodlebug output an X
			else if (printGrid[i][j]->getType() == DODO) {
				cout << "X" << "|";
			}
			else {
				cout << "O" << "|"; //for ants output O
			}
		}
		cout << "\n"; //a break is given  after each row
	}
}

/**
 * Playgame
 *  Resets all organism so itmoved is false in the
 * board , Loop through the board and move the Doodlebugs and set
 * them as  itmoved true,  if they did move Same step for ants
 *  Check for starving doodlebugs and delete them off the board
 *  check the bool for breeding and breed if any possibilities occur. itmoved variable ensures
 * that one organism doesnt move multiple times in one turn. Once it
 * gets its bool changed it can't moved again the same turn
 */
void Board::Playgame() {

	//create a new vector and fill it with 0 - 399, each number corresponds to a cell in the board
	vector <int> randomTable;
	for(int i = 0; i < (WorldS*WorldS); i++) {
		randomTable.push_back(i);
	}
	//Shuffle the vector so its in a random order
	random_shuffle(randomTable.begin(), randomTable.end());
	//(1) First reset all organisms so none of them have moved
	for (int i = 0; i < WorldS; i++) {
		for (int j = 0; j < WorldS; j++) {
			if (printGrid[i][j] != NULL) {
				printGrid[i][j]->itmoved = false;
			}
		}
	}

	//random selection to move any ant or doodlebug

	for(vector<int>::iterator r = randomTable.begin(); r != randomTable.end(); r++) {
		int i = *r / WorldS; //for row
		int j = *r % WorldS; //for column

		//For Moving Doodlebugs
		if ((printGrid[i][j] != NULL) && (printGrid[i][j]->getType() == DODO)) {
			if (printGrid[i][j]->itmoved == false) { //if they haven't moved
				printGrid[i][j]->itmoved = true; // change the itmoved factor to true to mark as moved
				printGrid[i][j]->move(); // doodlebugs eat
			}
		}

		//For Moving Ants
		if ((printGrid[i][j] != NULL) && (printGrid[i][j]->getType() == ANT)) {
			if (printGrid[i][j]->itmoved == false) {
				printGrid[i][j]->itmoved = true; // Mark as itmoved
				printGrid[i][j]->move();
			}
		}
	}


	// Loop through the board to check for starving doodlebugs
	for (int i = 0; i < WorldS; ++i) {
		for (int j = 0; j < WorldS; ++j) {
			if ((printGrid[i][j] != NULL) && (printGrid[i][j]->getType() == DODO)) { //if doodlebug
				if (printGrid[i][j]->starve()) { //if starving
					delete (printGrid[i][j]); //then delete(kill digitally) of that doodlebug
					printGrid[i][j] = NULL; //and then the space it died is replaced with an empty space
				}
			}
		}
	}

	// check for possible breeding
	for (int i = 0; i < WorldS; ++i) {
		for (int j = 0; j < WorldS; ++j) {
			//make sure the organism moved
			if ((printGrid[i][j] != NULL) && (printGrid[i][j]->itmoved == true)) {
				printGrid[i][j]->breed(); //breed that organism (if it can)
			}
		}
	}

}



/**
 * blank:
 * returns a bool true if all cells on the board are null
 * @return
 */
bool Board::blank(){
	//Loop through the board and check for any null pointers present
		for (int i = 0; i < WorldS; ++i) {
			for (int j = 0; j < WorldS; ++j) {

				//checking if board space is empty
				if ((printGrid[i][j] != NULL)) {
					return false; 				}
			}
		}
		return true; //There is nothing on the board
}
/**
 * numofAnts
 * Loops the board and returns the number of Ants on the board
 * @return
 */
int Board::numofants(){
	int numA =0;
	//check for starving doodlebugs
		for (int i = 0; i < WorldS; ++i) {
			for (int j = 0; j < WorldS; ++j) {
				if ((printGrid[i][j] != NULL) && (printGrid[i][j]->getType() == ANT)) { //if doodlebug
					numA++;
				}
			}
		}
		return numA;
}
/**
 * numofdodos:
 * Loops through the board and returns the number of Doodlebugs in the board
 * @return
 */
int Board::numofdodos(){
	int numD =0;
	// check for starving doodlebugs
	for (int i = 0; i < WorldS; ++i) {
			for (int j = 0; j < WorldS; ++j) {
				if ((printGrid[i][j] != NULL) && (printGrid[i][j]->getType() == DODO)) { //if doodlebug
					numD++;
				}
			}
		}
		return numD;
}

Board::~Board(){

}
