#include<iostream>
 #include <vector>
 #include <ctime>
 #include <stdlib.h>     /* srand, rand */
 #include "Cards.h"

 using std::cin;
 using std::cout;


 using namespace std;


 //int main(){

 //    std::cout <<"Warzome is setting up the deck"<<endl;
 //    Deck d;

 //    std::cout <<"-----------------------------------"<<endl;

 //    std::cout <<"Warzome is printing the deck..."<<endl;
 //    d.print_deck();
 //    std::cout <<"The deck has "<< d.getsize()<<" cards."<<endl;
 //    std::cout <<"-----------------------------------"<<endl;
 //   
 //    std::cout <<"-----------------------------------"<<endl;
 //    d.draw();
 //    std::cout <<"-----------------------------------"<<endl;
 //    std::cout <<"The deck has "<< d.getsize()<<" cards."<<endl;
 //    std::cout <<"-----------------------------------"<<endl;
 //    std::cout <<"Printing new Deck.........."<<endl;
 //    d.print_deck();


 //    return 0;

 //};


 void testCards() {
 
     std::cout << "Warzome is setting up the deck" << endl;
     Deck d;

     std::cout << "-----------------------------------" << endl;

     std::cout << "Warzome is printing the deck..." << endl;
     d.print_deck();
     std::cout << "The deck has " << d.getsize() << " cards." << endl;
     std::cout << "-----------------------------------" << endl;

     std::cout << "-----------------------------------" << endl;
     d.draw();
     std::cout << "-----------------------------------" << endl;
     std::cout << "The deck has " << d.getsize() << " cards." << endl;
     std::cout << "-----------------------------------" << endl;
     std::cout << "Printing new Deck.........." << endl;
     d.print_deck();

 }