#include "market.h"
#include <iostream>
#include <limits>

int main() {
    Market market;
    market.setUserBudget(200.00); 

    cout << " Initial Market Inventory " << endl;
    market.printAvailableProducts();

    market.addToCart("Milk", 2);       
    market.addToCart("Book", 1);       
    market.addToCart("Sausages", 3);   
    market.printCart();
    market.checkOut();

    market.addToCart("Expired Yoghurt", 1);
    market.printCart();
    market.checkOut(); //this should fail

    market.addToCart("Laptop", 1); //this will likely exceed the remaining budget
    market.printCart();
    market.checkOut();

    cout << "\n Final Market Inventory " << endl;
    market.printAvailableProducts();
    
    cout << "\n\nPress Enter to exit the application...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
    cin.get();

    return 0;
}