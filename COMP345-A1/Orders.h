#pragma once

#include <string>
#include <list>
#include <iostream>

class Order;
class OrdersList;

using std::cout;
using std::string;
using std::ostream;
using std::list;
using std::endl;


//order class
class Order {
public:
	//constructors
	Order(); //default
	Order(string description, string effect, bool valid); //defined
	Order(const Order& orderToCopy); //copy constructor

	//destructor
	~Order();

	//returns description
	string toString();
	//returns effect
	string getEffect();
	bool getValid();

	//validate to inherit, virtual for child classes
	virtual bool validate() = 0;

	//execute to inherit, same virtual
	virtual bool execute() = 0;
	
	//stream operator stuff
	friend ostream& operator<<(ostream& out, const Order& o);

	virtual Order& operator=(const Order& o);

	string* description;
	string* effect; 
	bool* isValid;
};

//Deploy class
class Deploy : public Order{
public:
	//Constructors
	Deploy(); //default
	Deploy(string description, string effect, bool valid); //valid for testing
	Deploy(const Deploy& DeployToCopy);
	//Destructor
	~Deploy();

	//inherited service stuff
	bool validate() override final;
	bool execute() override final;

	//stream stuff
	friend ostream& operator<<(ostream& out, const Deploy& o);

	Deploy& operator =(const Deploy& o);
};

//Advance class
class Advance : public Order {
public:
	//Constructors
	Advance(); //default
	Advance(string description, string effect, bool valid); //valid for testing
	Advance(const Advance& AdvanceToCopy);
	//Destructor
	~Advance();

	//inherited service stuff
	bool validate() override final;
	bool execute() override final;

	//stream stuff
	friend ostream& operator<<(ostream& out, const Advance& o);

	Advance& operator =(const Advance& o);
};

//Bomb class
class Bomb : public Order {
public:
	//Constructors
	Bomb(); //default
	Bomb(string description, string effect, bool valid); //valid for testing
	Bomb(const Bomb& BombToCopy);
	//Destructor
	~Bomb();

	//inherited service stuff
	bool validate() override final;
	bool execute() override final;

	//stream stuff
	friend ostream& operator<<(ostream& out, const Bomb& o);

	Bomb& operator =(const Bomb& o);
};

//Blockade class
class Blockade : public Order {
public:
	//Constructors
	Blockade(); //default
	Blockade(string description, string effect, bool valid); //valid for testing
	Blockade(const Blockade& BlockadeToCopy);
	//Destructor
	~Blockade();

	//inherited service stuff
	bool validate() override final;
	bool execute() override final;

	//stream stuff
	friend ostream& operator<<(ostream& out, const Blockade& o);

	Blockade& operator =(const Blockade& o);
};

//Airlift class
class Airlift : public Order {
public:
	//Constructors
	Airlift(); //default
	Airlift(string description, string effect, bool valid); //valid for testing
	Airlift(const Airlift& AirliftToCopy);
	//Destructor
	~Airlift();

	//inherited service stuff
	bool validate() override final;
	bool execute() override final;

	//stream stuff
	friend ostream& operator<<(ostream& out, const Airlift& o);

	Airlift& operator =(const Airlift& o);
};

//Negotiate class
class Negotiate : public Order {
public:
	//Constructors
	Negotiate(); //default
	Negotiate(string description, string effect, bool valid); //valid for testing
	Negotiate(const Negotiate& NegotiateToCopy);
	//Destructor
	~Negotiate();

	//inherited service stuff
	bool validate() override final;
	bool execute() override final;

	//stream stuff
	friend ostream& operator<<(ostream& out, const Negotiate& o);

	Negotiate& operator =(const Negotiate& o);
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