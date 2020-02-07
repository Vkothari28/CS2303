using namespace std;

/*
 * Ant class represents an Ant
 */
class Ant : public Organism {

	friend class World;

public:

	//constructors
	Ant();
	Ant(Board*board, int a, int b);

	//breed, move and starve methods
	void breed();
	void move();
	bool starve();

	//function to return the type
	int getType();
	~Ant();
};
