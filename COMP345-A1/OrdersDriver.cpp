#include "Orders.h"
#include <string>
#include <iostream>

using namespace std;

//  Orders Driver

//Will create orders list, add list of orders to list, 
void OrdersTest() {
	//create test list
	OrdersList test;

	//create different orders, first all true, then all false 
	Deploy deployTest;
	test.add(&deployTest);

	Advance advanceTest;
	test.add(&advanceTest);

	Bomb bombTest;
	test.add(&bombTest);

	Blockade blockadeTest;
	test.add(&blockadeTest);

	Airlift airliftTest;
	test.add(&airliftTest);

	Negotiate negotiateTest;
	test.add(&negotiateTest);


	//false orders
	Deploy deployTestFalse("Deploy Order", "Deploy effect", false);
	test.add(&deployTestFalse);


	Advance advanceTestFalse("Advance Order", "Advance effect", false);
	test.add(&advanceTestFalse);

	Bomb bombTestFalse("Bomb Order", "Bomb effect", false);
	test.add(&bombTestFalse);

	Blockade blockadeTestFalse("Blockade Order", "Blockade effect", false);
	test.add(&blockadeTestFalse);

	Airlift airliftTestFalse("Airlift Order", "Airlift order", false);
	test.add(&airliftTestFalse);

	Negotiate negotiateTestFalse("Negotiate Order", "Negotiate effect", false);
	test.add(&negotiateTestFalse);

	

	cout << "Will print effect when order is valid and executed, iterates over entire orderslist." << endl;
	//testing execute for the orderslist, will return true for first half then false second half, since if validate() returns true, execute returns true
	for (auto ordersIterator = test.orders.begin(); ordersIterator != test.orders.end(); ordersIterator++) {
		//iterates through list, will print effect if executed. 
		(*ordersIterator)->execute();
	}

	cout << " " << endl;
	cout << "Move function test"<< endl;
	//move function tester
	cout << test << endl;
	cout << "Move happens here" << endl;
	test.move(1, 6);
	cout << test << endl;


	cout << " " << endl;
	cout << "Remove Function test" << endl;
	//remove function tester
	cout << test << endl;
	cout << "Remove happens here" << endl;
	test.remove(1);
	cout << test << endl;


}
