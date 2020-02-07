#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <time.h>
#include <string>
using namespace std;
class Organism;
class Doodlebug;
class Ant;
const int size = 1000;

class Board {
	//these friend classes can set cells in the world
	friend class Organism;
	friend class Doodlebug;
	friend class Ant;

public:
	//constructor
	Board();
	//function for printing the world to the console
	void createboard();
	void Playgame();

	bool blank();// to check if board is empty
	//functions for setting and getting organism in the array
	Organism* getfromBoard(int a, int b);	//
	void setonBoard(int x, int b, Organism *Orgo);
	void input(int INITIALANTS ,int INITIALDODS);
	int numofants();
	int numofdodos();
	~Board();
private:

	Organism* printGrid[size][size]; // a 2d array of pointers towards the class of the oragnism
};
