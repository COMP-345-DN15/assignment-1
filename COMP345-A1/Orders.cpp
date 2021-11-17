#include "Orders.h"

//order class---------------------------------------------------------------------------

//default constructor
Order::Order() : Order("This is an order.", "This is the effect") {
	
	}

Order::Order(string name, string effect) {
	this->description = new string(name);
	this->description = new string(effect);
	this->iPlayer = nullptr;



}

//para constructor
Order::Order(string description, string effect, Player player) : description(new string(description)), effect(new string(effect)), iPlayer(new Player(player))  {
	
	}
//copy constructor
Order::Order(const Order& orderToCopy) {
	this->description = new string(*(orderToCopy.description));
	this->effect = new string(*(orderToCopy.effect));
	this->iPlayer = orderToCopy.iPlayer;
	}

//Destructor
Order::~Order() {

	}
//to string, returns description
string Order::toString() {
	return *description;
	}
//returns effect
string Order::getEffect() {
	return *effect;
}

bool Order::getValid() {
	if (*this->isValid) {
		return true;
	}
	else return false;
}
//stream insertion operator overload
ostream& operator<<(ostream& out, const Order& orderToStream) {
	out << *(orderToStream.description);
	return out;
	}
//stream assignment operator overload
Order& Order::operator=(const Order& orderToAssign) {
	this->description = new string(*(orderToAssign.description));
	*this->isValid = orderToAssign.isValid;
	return *this;
}


//Deploy order class-------------------------------------------------------------------
//constructors
Deploy::Deploy() : Order("Deploy Order", "Deploy Effect") {
	

	//empty
}
//para const
Deploy::Deploy(Player& iPlayer, Territory& targetTerr, int numArm){
	this->iPlayer = &iPlayer;
	this->targetTerr = &targetTerr;
	this->numArm = numArm;
	}

//copy constructor
Deploy::Deploy(const Deploy& deployToCopy) : Order(deployToCopy) {
	//empty
}

//Destructor
Deploy::~Deploy() {

}

//inherited validate, for now just checks if true
bool Deploy::validate() {
	if (getPlayer() != getPlayer(targetTerr))
		return false;
	else return true;

}

//execute if validate returns true
void Deploy::execute() {
	if (validate()) {
		(*targetTerr).armyCount += numArm;
		cout << "added" << numArm ;
	}
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
Advance::Advance() : Order("Advance Order", "Advance effect") {
	//empty
}
//para const
Advance::Advance(Player& iPlayer, Territory& sourceTerr, Territory& targetTerr, int numArm) {
	this->iPlayer = &iPlayer;
	this->sourceTerr = &sourceTerr;
	this->targetTerr = &targetTerr;
	this->numArm = numArm;

}

//copy constructor
Advance::Advance(const Advance& advanceToCopy) : Order(advanceToCopy) {
	//empty
}

//Destructor
Advance::~Advance() {

}

//inherited validate, for now just checks if true
bool Advance::validate() {
	vector<Territory*> listOwned = iPlayer->listOfTerritoriesOwned;
	vector<int> adjList = sourceTerr->borders;

	if (numArm >= 0) {
		if (find(iPlayer->contractsWith.begin(), iPlayer->contractsWith.end(), getPlayer(targetTerr)) != iPlayer->contractsWith.end())
			return false;

		if (find(listOwned.begin(), listOwned.end(), sourceTerr) != listOwned.end()) {
			if (find(adjList.begin(), adjList.end(), targetTerr) != adjList.end()) {
				return true;
			}
			else return false;
		}
		else return false;
	}
	else return false;
}

//execute if validate returns true
void Advance::execute() {
	

	if (validate()) {



		//if target unowned
		if (getPlayer(targetTerr) == nullptr) {
			targetTerr->armyCount += numArm;
			targetTerr->player = iPlayer;
		}

		//if same player
		if (getPlayer() == getPlayer(targetTerr)) {
			targetTerr->armyCount += numArm;
			sourceTerr->armyCount -= numArm;
			}

		//if different players BATTLE!
		else {
			int atkCount = numArm;
			int defCount = targetTerr->armyCount;

			while (atkCount != 0 && defCount != 0) {
				int atkRand = rand() % 100 + 1;
				int defRand = rand() % 100 + 1;
				
				if (atkRand <= 60)
					defCount--;

				if (defRand <= 70)
					atkCount--;
			}

			if (atkCount == 0)
				targetTerr->armyCount = defCount;
				
			if (defCount == 0) {
				targetTerr->armyCount = atkCount;
				targetTerr->player = iPlayer;
			}
		}

		
	}

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
Bomb::Bomb() : Order("Bomb Order", "Bomb effect") {
	//empty
}
//para const
Bomb::Bomb(Territory& target, Player& player) {
	this->iPlayer = &player;
	this->target = &target;

}

//copy constructor
Bomb::Bomb(const Bomb& bombToCopy) : Order(bombToCopy) {
	//empty
}

//Destructor
Bomb::~Bomb() {
}

//inherited validate, for now just checks if true
bool Bomb::validate() {
	vector<Territory*> listOwned = iPlayer->listOfTerritoriesOwned;
	if (getPlayer(target) == nullptr)
		return true;

	if (getPlayer() == getPlayer(target))
		return false;

	if (find(iPlayer->contractsWith.begin(), iPlayer->contractsWith.end(), getPlayer(target)) != iPlayer->contractsWith.end())
		return false;


	else return true;

}

//execute if validate returns true
void Bomb::execute() {
	if (validate()) {
		int half = target->armyCount / 2;
		target->armyCount = half;

	}
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
Blockade::Blockade() : Order("Blockade Order", "Blockade effect") {
	//empty
}
//para const
Blockade::Blockade(Player& player, Territory& target) {
	this->iPlayer = &player;
	this->target = &target;

	
}

//copy constructor
Blockade::Blockade(const Blockade& blockadeToCopy) : Order(blockadeToCopy) {
	//empty
}

//Destructor
Blockade::~Blockade() {

}

//inherited validate, for now just checks if true
bool Blockade::validate() {
	if (getPlayer(target) == iPlayer)
		return true;
	else return false;
}

//execute if validate returns true
void Blockade::execute() {
	if (validate()) {
		int doubleArm = target->armyCount * 2;
		target->armyCount = doubleArm;
		target->player = nullptr;
	}
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
Airlift::Airlift() : Order("Airlift Order", "Airlift order") {
	//empty
}
//para const
Airlift::Airlift(Player& player, Territory& source, Territory& targetTerr, int numArm) {
	this->iPlayer = &player;
	this->targetTerr = &targetTerr;
	this->numArm = numArm;

}

//copy constructor
Airlift::Airlift(const Airlift& airliftToCopy) : Order(airliftToCopy) {
	//empty
}

//Destructor
Airlift::~Airlift() {

}

//inherited validate, for now just checks if true
bool Airlift::validate() {
	if (iPlayer != (getPlayer(targetTerr)) || iPlayer != (getPlayer(source))) {
		return false;
	}
	if (numArm <= 0)
		return false;

	if (find(iPlayer->contractsWith.begin(), iPlayer->contractsWith.end(), getPlayer(targetTerr)) != iPlayer->contractsWith.end())
		return false;
	
	else return true;
}

//execute if validate returns true
void Airlift::execute() {
	if (validate()) {

		//if same player
		if (getPlayer() == getPlayer(targetTerr)) {
			targetTerr->armyCount += numArm;
			source->armyCount -= numArm;
		}

		//if different players BATTLE!
		else {
			int atkCount = numArm;
			int defCount = targetTerr->armyCount;

			while (atkCount != 0 && defCount != 0) {
				int atkRand = rand() % 100 + 1;
				int defRand = rand() % 100 + 1;

				if (atkRand <= 60)
					defCount--;

				if (defRand <= 70)
					atkCount--;
			}

			if (atkCount == 0)
				targetTerr->armyCount = defCount;

			if (defCount == 0) {
				targetTerr->armyCount = atkCount;
				targetTerr->player = iPlayer;
			}
		}


	}

	
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
Negotiate::Negotiate() : Order("Negotiate Order", "Negotiate effect") {
	//empty
}
//para const
Negotiate::Negotiate(Player& iPlayer, Player& targetPlayer) {
	this->iPlayer = &iPlayer;
	this->targetPlayer = &targetPlayer;

}

//copy constructor
Negotiate::Negotiate(const Negotiate& negotiateToCopy) : Order(negotiateToCopy) {
	//empty
}

//Destructor
Negotiate::~Negotiate() {

}

//inherited validate, for now just checks if true
bool Negotiate::validate() {
	if (iPlayer == targetPlayer || nullptr)
		return false;
	if (targetPlayer == nullptr)
		return false;
	if (find(iPlayer->contractsWith.begin(), iPlayer->contractsWith.end(), targetPlayer) != iPlayer->contractsWith.end())
		return false;

	else return true;


}

//execute if validate returns true
void Negotiate::execute() {
	if (validate()) {
		cout << this->getEffect() << endl;
	}
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
	list<Order*> orders;

}

//copy constructor
OrdersList::OrdersList(const OrdersList &ordersListToCopy) {
	for (auto ordersIterator = ordersListToCopy.orders.begin(); ordersIterator != ordersListToCopy.orders.end(); ordersIterator++) {
		orders.push_back(*ordersIterator);
	}
}

//Destructor
OrdersList::~OrdersList() {
	
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