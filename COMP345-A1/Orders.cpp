#include "Orders.h"

//order class---------------------------------------------------------------------------

//default constructor
Order::Order() : Order("This is an order.", "This is the effect", true) {
//empty
	}

//para constructor
Order::Order(string description, string effect, bool valid) : description(new string(description)), effect(new string (effect)){
	isValid = &valid;
	}
//copy constructor
Order::Order(const Order& orderToCopy) {
	this->description = new string(*(orderToCopy.description));
	this->effect = new string(*(orderToCopy.effect));
	this->isValid = orderToCopy.isValid;
	}

//Destructor
Order::~Order() {
	delete description;
	delete effect;
	delete isValid;
	}
//to string, returns description
string Order::toString() {
	return *description;
	}
//returns effect
string Order::getEffect() {
	return *effect;
}
//stream insertion operator overload
ostream& operator<<(ostream& out, const Order& orderToStream) {
	out << *(orderToStream.description);
	return out;
	}
//stream assignment operator overload
Order& Order::operator=(const Order& orderToAssign) {
	this->description = new string(*(orderToAssign.description));
	this->isValid = orderToAssign.isValid;
	return *this;
}


//Deploy order class-------------------------------------------------------------------
//constructors
Deploy::Deploy() : Order("Deploy Order", "Deploy effect", true) {
	//empty
}
//para const
Deploy::Deploy(string description, string effect,bool valid) {
	this->description = &description;
	this->effect = &effect;
	this->isValid = &valid;
	}

//copy constructor
Deploy::Deploy(const Deploy& deployToCopy) : Order(deployToCopy) {
	//empty
}

//Destructor
Deploy::~Deploy() {
	//maybe later
}

//inherited validate, for now just checks if true
bool Deploy::validate() {
	if (this->isValid)
		return true;
	else return false;
}

//execute if validate returns true
bool Deploy::execute() {
	if (this->validate())
		return true;
	else return false;
}

// Overloads the stream insertion operator.
ostream& operator<<(ostream& out, const Deploy& deployToStream) {
	out << static_cast <const Order&>(deployToStream); // upcast to Order to call their stream insertion operator
	return out;
}

// Overloads the assignment operator.
Deploy& Deploy::operator=(const Deploy& deployToAssign) {
	Order::operator= (deployToAssign);
	return *this;
}


//Advance order class-------------------------------------------------------------------
//constructors
Advance::Advance() : Order("Advance Order", "Advance effect", true) {
	//empty
}
//para const
Advance::Advance(string description, string effect, bool valid) {
	this->description = &description;
	this->effect = &effect;
	this->isValid = &valid;
}

//copy constructor
Advance::Advance(const Advance& advanceToCopy) : Order(advanceToCopy) {
	//empty
}

//Destructor
Advance::~Advance() {
	//maybe later
}

//inherited validate, for now just checks if true
bool Advance::validate() {
	if (this->isValid)
		return true;
	else return false;
}

//execute if validate returns true
bool Advance::execute() {
	if (this->validate())
		return true;
	else return false;
}

// Overloads the stream insertion operator.
ostream& operator<<(ostream& out, const Advance& advanceToStream) {
	out << static_cast <const Order&>(advanceToStream); // upcast to Order to call their stream insertion operator
	return out;
}

// Overloads the assignment operator.
Advance& Advance::operator=(const Advance& advanceToAssign) {
	Order::operator= (advanceToAssign);
	return *this;
}

//Bomb order class-------------------------------------------------------------------
//constructors
Bomb::Bomb() : Order("Bomb Order", "Bomb effect", true) {
	//empty
}
//para const
Bomb::Bomb(string description, string effect, bool valid) {
	this->description = &description;
	this->effect = &effect;
	this->isValid = &valid;
}

//copy constructor
Bomb::Bomb(const Bomb& bombToCopy) : Order(bombToCopy) {
	//empty
}

//Destructor
Bomb::~Bomb() {
	//maybe later
}

//inherited validate, for now just checks if true
bool Bomb::validate() {
	if (this->isValid)
		return true;
	else return false;
}

//execute if validate returns true
bool Bomb::execute() {
	if (this->validate())
		return true;
	else return false;
}

// Overloads the stream insertion operator.
ostream& operator<<(ostream& out, const Bomb& bombToStream) {
	out << static_cast <const Order&>(bombToStream); // upcast to Order to call their stream insertion operator
	return out;
}

// Overloads the assignment operator.
Bomb& Bomb::operator=(const Bomb& bombToAssign) {
	Order::operator= (bombToAssign);
	return *this;
}

//Blockade order class-------------------------------------------------------------------
//constructors
Blockade::Blockade() : Order("Blockade Order", "Blockade effect", true) {
	//empty
}
//para const
Blockade::Blockade(string description, string effect,bool valid) {
	this->description = &description;
	this->effect = &effect;
	this->isValid = &valid;
}

//copy constructor
Blockade::Blockade(const Blockade& blockadeToCopy) : Order(blockadeToCopy) {
	//empty
}

//Destructor
Blockade::~Blockade() {
	//maybe later
}

//inherited validate, for now just checks if true
bool Blockade::validate() {
	if (this->isValid)
		return true;
	else return false;
}

//execute if validate returns true
bool Blockade::execute() {
	if (this->validate())
		return true;
	else return false;
}

// Overloads the stream insertion operator.
ostream& operator<<(ostream& out, const Blockade& blockadeToStream) {
	out << static_cast <const Order&>(blockadeToStream); // upcast to Order to call their stream insertion operator
	return out;
}

// Overloads the assignment operator.
Blockade& Blockade::operator=(const Blockade& blockadeToAssign) {
	Order::operator= (blockadeToAssign);
	return *this;
}

//Airlift order class-------------------------------------------------------------------
//constructors
Airlift::Airlift() : Order("Airlift Order", "Airlift order", true) {
	//empty
}
//para const
Airlift::Airlift(string description, string effect, bool valid) {
	this->description = &description;
	this->effect = &effect;
	this->isValid = &valid;
}

//copy constructor
Airlift::Airlift(const Airlift& airliftToCopy) : Order(airliftToCopy) {
	//empty
}

//Destructor
Airlift::~Airlift() {
	//maybe later
}

//inherited validate, for now just checks if true
bool Airlift::validate() {
	if (this->isValid)
		return true;
	else return false;
}

//execute if validate returns true
bool Airlift::execute() {
	if (this->validate())
		return true;
	else return false;
}

// Overloads the stream insertion operator.
ostream& operator<<(ostream& out, const Airlift& airliftToStream) {
	out << static_cast <const Order&>(airliftToStream); // upcast to Order to call their stream insertion operator
	return out;
}

// Overloads the assignment operator.
Airlift& Airlift::operator=(const Airlift& airliftToAssign) {
	Order::operator= (airliftToAssign);
	return *this;
}

//Negotiate order class-------------------------------------------------------------------
//constructors
Negotiate::Negotiate() : Order("Negotiate Order", "Negotiate effect", true) {
	//empty
}
//para const
Negotiate::Negotiate(string description, string effect, bool valid) {
	this->description = &description;
	this->effect = &effect;
	this->isValid = &valid;
}

//copy constructor
Negotiate::Negotiate(const Negotiate& negotiateToCopy) : Order(negotiateToCopy) {
	//empty
}

//Destructor
Negotiate::~Negotiate() {
	//maybe later
}

//inherited validate, for now just checks if true
bool Negotiate::validate() {
	if (this->isValid)
		return true;
	else return false;
}

//execute if validate returns true
bool Negotiate::execute() {
	if (this->validate())
		return true;
	else return false;
}

// Overloads the stream insertion operator.
ostream& operator<<(ostream& out, const Negotiate& negotiateToStream) {
	out << static_cast <const Order&>(negotiateToStream); // upcast to Order to call their stream insertion operator
	return out;
}

// Overloads the assignment operator.
Negotiate& Negotiate::operator=(const Negotiate& negotiateToAssign) {
	Order::operator= (negotiateToAssign);
	return *this;
}

//OrdersList class-------------------------------------------------------------------
//consructors
//default
OrdersList::OrdersList() {
	orders;

}

//copy constructor
OrdersList::OrdersList(const OrdersList &ordersListToCopy) {
	for (auto ordersIterator = ordersListToCopy.orders.begin(); ordersIterator != ordersListToCopy.orders.end(); ordersIterator++) {
		orders.push_back(*ordersIterator);
	}
}

//Destructor
OrdersList::~OrdersList() {
	for (Order* order : orders) {
		delete order;

	}
	orders.clear();
}

//service funcs for lists
//add to the list, adds to end 
void OrdersList::add(Order* orderToAdd) {
	orders.push_back(orderToAdd);

}

//move func, takes old index and moves to new index uses iterators to get to the respective orders, then splices to get the right order
void OrdersList::move(int oldIndex, int newIndex) {
	auto oldPosition = orders.begin();
	advance(oldPosition, oldIndex);
	auto newPosition = orders.begin();
	advance(newPosition, newIndex);
	orders.splice(newPosition, orders, oldPosition);
}


//remove an entry. uses iterator to find the correct index then erases entry 
void OrdersList::remove(int index) {
	int pos = 0;
	for (auto ordersIterator = orders.begin(); ordersIterator != orders.end(); ordersIterator++) {
		if (pos == index) {
			orders.erase(ordersIterator);
			return;
		}
		pos++;
	}
}

string OrdersList::toString() {
	string out = "";
	for (auto ordersIterator : orders) {
		out += ordersIterator->toString() + " ";
		}
	return out;
}

// Overloads the stream insertion operator
ostream& operator<<(ostream& out, const OrdersList& ordersListToStream) {
	for (auto ordersIterator = ordersListToStream.orders.begin(); ordersIterator != ordersListToStream.orders.end(); ordersIterator++) {
		out << **ordersIterator << " ";
	}
	out << endl;
	return out;
}

// Overloads the assignment operator
OrdersList& OrdersList::operator=(OrdersList& ordersListToAssign) {
	for (auto ordersIterator = ordersListToAssign.orders.begin(); ordersIterator != ordersListToAssign.orders.end(); ordersIterator++) {
		orders.push_back(*ordersIterator);
	}
	return *this;
}