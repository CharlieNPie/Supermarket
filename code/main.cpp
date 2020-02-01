//
//  main.cpp
//  ShoppingCart
//
//  Created by Charlie Jewers on 29/01/2020.
//  Copyright © 2020 Charlie Jewers. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>

#include "ShoppingCart.hpp"
#include "ShoppingItem.hpp"

/**
 * Asks the user to input item details to be added to a shopping cart.
 *
 * User input is then passed to AddItem, located within the ShoppingCart class.
 *
 * @param cart A shopping cart.
 */
void AddToCart(ShoppingCart& cart) {
    std::string itemName;
    float itemPrice;
    int itemQuantity;
    
    std::cout << "Enter item name: ";
    std::getline(std::cin, itemName);
    
    std::cout << "Enter price: ";
    std::cin >> itemPrice;
    if(!std::cin) { 
        std::cin.clear(); // prevents crash if non-numeric input is given
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
    }
    
    std::cout << "Enter quantity: ";
    std::cin >> itemQuantity;
    if(!std::cin) {
        std::cin.clear(); 
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
    }

    ShoppingItem item(itemName, itemPrice, itemQuantity);
    cart.AddItem(item);
}

/**
 * Asks user to input name of item to remove from a shopping cart.
 *
 * @param cart A shopping cart.
 */
void RemoveFromCart(ShoppingCart& cart) {
    std::string itemName;
    std::cout << "Enter name of item to remove: ";
    std::getline(std::cin, itemName);
    
    cart.RemoveItem(itemName);
}

/**
 * Prints the contents of a shopping cart, including the total price.
 *
 * @param cart A shopping cart.
 */
void PrintReceipt(ShoppingCart cart) {
    cart.PrintCartItems();
    std::cout << "TOTAL PRICE: £" << cart.GetTotalPrice() << "\n\n";
}

/**
 * Main method. Prints menu options to console and handles corresponding user input.
 */
int main() {
    ShoppingCart cart;
    std::string action;
    do {
        std::cout << "SHOP MENU:\n"
        "a: Add item\n"
        "r: Remove item\n"
        "p: Print receipt\n"
        "q: Quit\n\n"
        "Select option: ";
                
        std::getline(std::cin, action);
        
        if (action == "a")
            AddToCart(cart);
        else if (action == "r")
            RemoveFromCart(cart);
        else if (action == "p")
            PrintReceipt(cart);
        else if (action == "q")
            std::cout << "Bye!\n";
    }
    while (action != "q");
    
    return 0;
}


