class Doodlebug : public Organism {

	friend class World;

public:

	//constructors
	Doodlebug();
	Doodlebug(Board *board, int a, int b);

	//breed, move and starve methods
	void breed();
	void move();
	bool starve();


	int getType();
	virtual ~Doodlebug();

private:
 int starvemoves;
};
