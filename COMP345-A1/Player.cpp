#include "Player.h"
#include "Map.h"
#include "Cards.h"
#include "Orders.h"

#include <iostream>
#include <ostream>
#include <typeinfo>
#include <cstring>
#include <algorithm>
using namespace std;


//Default constructor
Player::Player()
{
	name = "";
	cards = new Hand();

}

Territory::Territory(){
	cout << "This is a territory\n";
};
Cards::Cards() {
	cout << "This is a card\n";
};
Order::Order() {
	cout << "This is a order\n";
};

//Parametric construtor 
Player::Player(std::string pname)
{
	name = pname;
	cards = new Hand();
}


// Player destructor
Player::~Player()
{
	delete cards;
	cards = nullptr;
}
Player::~Player()
{
	delete cards;
	cards = nullptr;
	for (auto p : listOfTerritoriesOwned)
	{
		delete p;
	}
	listOfTerritoriesOwned.clear();

	for (auto p : listOfTerritoriesToDefend)
	{
		delete p;
	}
	listOfTerritoriesToDefend.clear();

	for (auto p : listOfTerritoriesToAttack)
	{
		delete p;
	}
	listOfTerritoriesToAttack.clear();

	for (auto p : listOfOrders)
	{
		delete p;
	}
	listOfOrders.clear();

}


//ToAttack() method return a list of territories
vector<Territory*> Player::toAttack() {
	// for now only empty territory list returned
	vector<Territory*> listOfTerritoriesToAttack;
	for (vector<Territory*>::iterator it = listOfTerritoriesToAttack.begin(); it != listOfTerritoriesToAttack.end(); ++it) {
		listOfTerritoriesToAttack.push_back(*it);
	}
	return listOfTerritoriesToAttack;
}

//ToDefend() method return a list of territories
vector<Territory*> Player::toDefend() {
	// for now only empty territory list returned
	vector<Territory*> listOfTerritoriesToDefend;
	for (vector<Territory*>::iterator it = listOfTerritoriesToDefend.begin(); it != listOfTerritoriesToDefend.end(); ++it) {
		listOfTerritoriesToDefend.push_back(*it);
	}
	return listOfTerritoriesToDefend;
}

//IssueOrder() will creat a order obj and add it to player's order list
void Player::issueOrder()
{	//every time make a new order obj there will be a printout to show it works
	//Order* ord = new Order();
	//listOfOrders.push_back(ord);

}
void  Player::print()
{
	cout << "this is player"<<name<<endl;
}

