#include "Player.h"
#include "Map.h"
#include "Orders.h"
#include <iostream>
#include <string>

using namespace std;

int main() {

	cout << "testing player owns--------------------------\n";
	Player* p1ayer = new Player("demo");
	p1ayer->print();

	//testing toDefend()
	cout << "testing toDefend() method--------------------------------\n";
	p1ayer->toDefend();

	//testing toAttack()
	cout << "testing toAttack() method---------------------------------\n";
	p1ayer->toAttack();


	cout << "testing issueOrder() method---------------------------------\n";
	p1ayer->issueOrder();

	//delete player that created
	delete p1ayer;

	_CrtDumpMemoryLeaks();
	return 0;
}
