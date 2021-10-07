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
	listOfTerritoriesOwned = Territory owned[5];
	listOfTerritoriesToDefend = Territory toDefend[5];
	listOfTerritoriesToAttack = Territory toAttack[5];
}

Player::Player(std::vector<Map::Territory*>* TerritoriesOwned, Hand* Cards, vector<Map::Territory*> TerritoriesToDefend, vector<Map::Territory*> TerritoriesToAttack, const string name) {
	listOfTerritoriesOwned = OfTerritoriesOwned;
	listOfCards = Cards;
	listOfTerritoriesToDefend = TerritoriesToDefend;
	listOfTerritoriesToAttack = TerritoriesToAttack;
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
	// for now only empty territory list returned
	vector<Territory*> listOfTerritoriesToAttack;
	for (vector<Territory*>::iterator it = territories.begin(); it != territories.end(); ++it) {
		listOfTerritoriesToAttack.push_back(*it);
	}
	return listOfTerritoriesToAttack;
}

//ToDefend() method return a list of territories
vector<Territory*> Player::toDefend() {
	// for now only empty territory list returned
	vector<Territory*> listOfTerritoriesToDefend;
	for (vector<Territory*>::iterator it = territories.begin(); it != territories.end(); ++it) {
		listOfTerritoriesToDefend.push_back(*it);
	}
	return listOfTerritoriesToDefend;
}

//IssueOrder() will creat a order obj and add it to player's order list
void Player::issueOrder()
{	//every time make a new order obj there will be a printout to show it works
	Order* ord = new Order();
	listOfOrders.push_back(ord);

}


