#pragma once

#include <string>
#include <list>
#include <iostream>
#include "Map.h"
#include "Player.h"
#include "GameEngine.h"

class Order;
class OrdersList;

using std::cout;
using std::string;
using std::ostream;
using std::list;
using std::endl;
using std::find;



//order class
class Order {
public:
	//constructors
	Order(); //default
	Order(string name, string effect);
	Order(string description, string effect, Player player); //defined
	Order(const Order& orderToCopy); //copy constructor

	//destructor
	~Order();

	//returns description
	string toString();
	//returns effect
	string getEffect();
	bool getValid();

	//inline declarations to return the pointer to the player for comparison purposes
	Player* getPlayer(Territory* t);
	Player* getPlayer() {this->iPlayer;}

	//validate to inherit, virtual for child classes
	virtual bool validate() = 0;

	//execute to inherit, same virtual
	virtual void execute() = 0;
	
	//stream operator stuff
	friend ostream& operator<<(ostream& out, const Order& o);

	virtual Order& operator=(const Order& o);

	string* description;
	string* effect; 
	Player* iPlayer;
	GameEngine* gameEngine;
	bool* isValid;
};

//Deploy class
class Deploy : public Order{
public:
	//Constructors
	Deploy(); //default
	Deploy(Player& iPlayer, Territory& targetTerr, int numArm, GameEngine* gameEngine); //valid for testing
	Deploy(const Deploy& DeployToCopy);
	//Destructor
	~Deploy();

	//inherited service stuff
	bool validate() override final;
	void execute() override final;

	//stream stuff
	friend ostream& operator<<(ostream& out, const Deploy& o);

	Deploy& operator =(const Deploy& o);
	Territory* targetTerr;
	int numArm{0};


};

//Advance class
class Advance : public Order {
public:
	//Constructors
	Advance(); //default
	Advance(Player& iPlayer, Territory& sourceTerr, Territory& targetTerr, int numArm, GameEngine* gameEngine); //valid for testing
	Advance(const Advance& AdvanceToCopy);
	//Destructor
	~Advance();

	//inherited service stuff
	bool validate() override final;
	void execute() override final;

	//stream stuff
	friend ostream& operator<<(ostream& out, const Advance& o);

	Advance& operator =(const Advance& o);

	Territory* sourceTerr{ nullptr };
	Territory* targetTerr{ nullptr };
	int numArm{ 0 };

};

//Bomb class
class Bomb : public Order {
public:
	//Constructors
	Bomb(); //default
	Bomb(Territory& target, Player& player, GameEngine* gameEngine); //valid for testing
	Bomb(const Bomb& BombToCopy);
	//Destructor
	~Bomb();

	//inherited service stuff
	bool validate() override final;
	void execute() override final;

	//stream stuff
	friend ostream& operator<<(ostream& out, const Bomb& o);

	Bomb& operator =(const Bomb& o);

	Territory* target;

};

//Blockade class
class Blockade : public Order {
public:
	//Constructors
	Blockade(); //default
	Blockade(Player& player, Territory& target, GameEngine* gameEngine); //valid for testing
	Blockade(const Blockade& BlockadeToCopy);
	//Destructor
	~Blockade();

	//inherited service stuff
	bool validate() override final;
	void execute() override final;

	//stream stuff
	friend ostream& operator<<(ostream& out, const Blockade& o);

	Blockade& operator =(const Blockade& o);
	Territory* target;

};

//Airlift class
class Airlift : public Order {
public:
	//Constructors
	Airlift(); //default
	Airlift(Player& player, Territory& source, Territory& target, int armCount, GameEngine* gameEngine); //valid for testing
	Airlift(const Airlift& AirliftToCopy);
	//Destructor
	~Airlift();

	//inherited service stuff
	bool validate() override final;
	void execute() override final;

	//stream stuff
	friend ostream& operator<<(ostream& out, const Airlift& o);

	Airlift& operator =(const Airlift& o);
	
	Territory* targetTerr;
	Territory* source;
	int numArm{0};
};

//Negotiate class
class Negotiate : public Order {
public:
	//Constructors
	Negotiate(); //default
	Negotiate(Player& iPlayer, Player& targetPlayer); //valid for testing
	Negotiate(const Negotiate& NegotiateToCopy);
	//Destructor
	~Negotiate();

	//inherited service stuff
	bool validate() override final;
	void execute() override final;

	//stream stuff
	friend ostream& operator<<(ostream& out, const Negotiate& o);

	Negotiate& operator =(const Negotiate& o);

	Player* targetPlayer;

};

class OrdersList {
public: 
	//Constructors
	OrdersList();
	OrdersList(const OrdersList& ordersListToCopy);
	//Destructor
	~OrdersList();
	//required services for list operations
	void add(Order* orderToAdd); //adds order to the end 
	void move(int oldIndex, int newIndex); //moves order based on pos index
	
	void remove(int pos); //removes at pos index
	string toString();
	//stream stuff
	friend ostream& operator<<(ostream& out, const OrdersList& ordersListToStream);
	OrdersList& operator=(OrdersList& ordersListToAssign);
	list<Order*> orders;
};