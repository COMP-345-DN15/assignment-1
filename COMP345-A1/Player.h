
#include <iostream>
#include <vector>
#include "Cards.h"
#include "Orders.h"
#include "Map.h"

using namespace std;

class Player {

public:
	
	string playerName;
	// vectors that contain a list of Territory objects
	vector<Territory*> listOfTerritoriesOwned;
	vector<Territory*> listOfTerritoriesToAttack;
	vector<Territory*> listOfTerritoriesToDefend;

	// methods that return corresponding list
	vector<Territory*> toDefend();
	vector<Territory*> toAttack();

	// methods that create and add an order to list of orders.
	void issueOrder();


private:

	// vector that contains a list of Card objects
	vector<Hand*> listOfCards;

	// vector that contains a list of Order objects
	vector<Order*> listOfOrders;


};
class Territory {
	cout << "This is a territory";
};

