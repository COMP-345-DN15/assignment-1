#include "Player.h"
#include "Map.h"
#include "Cards.h"
#include "Orders.h"

#include <iostream>
#include <ostream>
#include <typeinfo>
#include <cstring>
using namespace std;


//Default constructor
Player::Player()
{
	name = "";
	hand = new Hand();

}


Player() = default;
Player(std::vector<Country> countries, Hand hand, DiceFacility dice, int playerNumber, Strategy * strategy);

//Parametric construtor 
Player::Player(string pname)
{
	playerName = pname;
	listOfCards = new Hand();
}

Player::Player(std::vector<Map::Territory*>* TerritoriesOwned, Hand* Cards, vector<Map::Territory*> TerritoriesToDefend, const string name) {
	listOfTerritoriesOwned = OfTerritoriesOwned;
	listOfCards = Cards;
	listOfTerritoriesToDefend = TerritoriesToDefend;
	playerName = name;
}


// Player destructor
Player::~Player()
{
	delete listOfCards;
	listOfCards = nullptr;
}
Player::~Player()
{
	delete listOfCards;
	listOfCards = nullptr;
	delete listOfTerritoriesOwned;
	listOfTerritoriesOwned = nullptr;
	delete listOfTerritoriesToDefend;
	listOfTerritoriesToDefend = nullptr;
	delete listOfTerritoriesToAttack;
	listOfTerritoriesToAttack = nullptr;
	delete playerName;
	playerName = nullptr;
	delete listOfOrders;
	listOfOrders = nullptr;
}


//ToAttack() method return a list of territories
vector<Territory*> Player::toAttack() {
	// for now only arbitary territory list returned
	vector<Territory*> terrAttack;
	for (vector<Territory*>::iterator it = territories.begin(); it != territories.end(); ++it) {
		terrAttack.push_back(*it);
	}
	return terrAttack;
}

//ToDefend() method return a list of territories
vector<Territory*> Player::toDefend() {
	// for now only arbitary territory list returned
	vector<Territory*> terrDefend;
	for (vector<Territory*>::iterator it = territories.begin(); it != territories.end(); ++it) {
		terrDefend.push_back(*it);
	}
	return terrDefend;
}

//IssueOrder() will creat a order obj and add it to player's order list
void Player::issueOrder()
{	//every time make a new order obj there will be a printout to show it works
	Order* ord = new Order();
	listOfOrders.push_back(ord);

}


