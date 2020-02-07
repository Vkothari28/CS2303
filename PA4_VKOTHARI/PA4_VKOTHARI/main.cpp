/*
 * main.cpp
 *
 *  Created on: Sep 28, 2018
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
const int DOODLEBUG = 2;
const int ANT = 1;
//Values for counter when determining if ants or doodles should breed
const int ANTBREED = 3; //3 lifespans
const int DODOBREED = 8; //8 lifespans
//value for counter to determine of a doodle should starve
const int DODODIE = 3;
string usermessage= "none yet";
class Organism;
class Doodlebug;
class Ant;

int WorldS=20;
int INITIALANTS=100;
int INITIALDOODOS=5;
int timesteps=1000;
int SEED=1;
int PAUSE= 0;
bool gg= false; // boolean for if the game is over

int BIRTH_ANTS=0;//Number of Ants reproduced
int BABYDOODLE=0;//Number of doodlebugs reproduced

//create a board object gBoard (game board) (constructs an array of pointers to organism objects)
Board gBoard;

void Output(int i){
	printf("Desired Board Size: %d\n",WorldS);
	printf("Initial number of Ants: %d\n",INITIALANTS);
	printf("Starting Number of Doodlebugs: %d\n",INITIALDOODOS);
	printf("Number of Steps: %d\n",timesteps);
	printf("Random Seed: %d\n",SEED);
	printf("PAUSE type: %d\n",PAUSE);
	printf("Steps done : %d\n",i);
	printf("Total Ants: %d\n",(INITIALANTS+BIRTH_ANTS));
	printf("Ants  remaining: %d\n", gBoard.numofants());
	printf("Total Doodlebugs: %d\n",(INITIALDOODOS+BABYDOODLE));
	printf(" Doodlebugs Remaining: %d\n",gBoard.numofdodos());
	printf("Final Grid:\n");
	gBoard.createboard();
}

int main(int argc,char *argv[]) {
	if (argc == 2){
		WorldS = atoi(argv[1]);
	}
	else if(argc == 3){
		WorldS = atoi(argv[1]);
		INITIALANTS = atoi(argv[2]);
	}
	else if(argc == 4){
		WorldS = atoi(argv[1]);
		INITIALANTS = atoi(argv[2]);
		INITIALDOODOS = atoi(argv[3]);
	}
	else if(argc == 5){
		WorldS = atoi(argv[1]);
		INITIALANTS = atoi(argv[2]);
		INITIALDOODOS = atoi(argv[3]);
		timesteps = atoi(argv[4]);
	}
	else if(argc == 6){
		WorldS = atoi(argv[1]);
		INITIALANTS = atoi(argv[2]);
		INITIALDOODOS = atoi(argv[3]);
		timesteps = atoi(argv[4]);
SEED = atoi(argv[5]);

	}
	else {}
		//seed the timer for generating random numbers
		srand(SEED);
		//directions and description
		cout << "2D predator prey simulation" << endl;
		cout << "\n";
		cout << "The rules:" << endl;
		cout << "	Time is stimulated in time steps and every step the ants and Doodlebugs " << endl;
		cout << "	The following actions can be performed :" << endl;
		cout << "		  MOVE - Eat bordering ants or randomly up, down, left, or right" << endl;
		cout << "		  STARVE - If they have not eaten an ant in 3 time steps(for doodlebug, ants don't starve" << endl;
		cout << "		  MOVE - up, down left or right accordingly" << endl;
		cout << "		  BREED -according to each species conditions " << endl;
		cout << "\n";


		//Populates World
		gBoard.input(INITIALANTS,INITIALDOODOS);
		if(PAUSE > 0){

			//keep track of number of steps
			for(int p=0; p<timesteps; p++){
				if(gBoard.blank()){
					gBoard.createboard(); //create the empty board
					gg = true;
					cout << "The Game has Ended" << endl;
					Output(p);
					return 0;
				}
				//send the board array to the console
				gBoard.createboard();
				//run 1 lifetime (1 step)
				gBoard.Playgame();

				cout << "Enter [n] to see the next generation : Any other key to exit" << endl;
				cin >> usermessage;
				if (usermessage == "n") {
					//continue playing if user enters n
					gg = false;
				}
				else {
					//exit if user does not enter n
					gg = true;
					cout << "The Game has Ended" << endl;
					Output(p);
					return 0;

				}
			}
			gg = true;
			cout << "The Game has Ended" << endl;
			Output(timesteps);
			return 0;
		}
		else{
			//print the board array to the console
			gBoard.createboard();
			for(int p=0; p<timesteps; p++){
				if(gBoard.blank()){
					gg= true;
					cout << "The Game has Ended" << endl;
					Output(p);
					return 0;
				}
				//run 1 lifetime (1 step)
				gBoard.Playgame();
				gBoard.Playgame();
			}
			gg = true;
			cout << "The Game has Ended" << endl;
			Output(timesteps);
			return 0;
		}

	return 0;
}

