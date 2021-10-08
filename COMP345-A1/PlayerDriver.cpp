
#include <iostream>
#include <string>
#include "Player.h"

using namespace std;

int main() {

	cout << "testing player owns--------------------------\n";
	Player* player = new Player("demo");
	player->print();

	Territory* landToDefend = new Territory;
	player->listOfTerritoriesToDefend.push_back(landToDefend);

	//testing toDefend()
	cout << "testing toDefend() method--------------------------------\n";
	player->toDefend();

	Territory* landToAttack = new Territory;
	player->listOfTerritoriesToDefend.push_back(landToAttack);

	//testing toAttack()
	cout << "testing toAttack() method---------------------------------\n";
	player->toAttack();


	cout << "testing issueOrder() method---------------------------------\n";
	player->issueOrder();

	//delete player that created
	delete player;

	_CrtDumpMemoryLeaks();
	return 0;
}
