
class Organism {

	//Since we need to allow the board to interact with organism, make it a friend
	friend class Board;

public:

	//constructors
	Organism();
	Organism(Board *board, int  a, int b);

	//virtual functions for breed, move and starve
	virtual void breed() = 0;
	virtual void move() = 0;
	virtual bool starve() = 0;

	//virtual function for checking if an object is an ant or doodle
	virtual int getType() = 0;
	virtual ~Organism();
protected:

	//for coordinates in the board
	int a;
	int b;


	bool itmoved;


	int lifespans;

	//pointer to the board
	Board *board;

};
