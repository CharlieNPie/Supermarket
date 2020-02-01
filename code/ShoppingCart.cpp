//
//  ShoppingCart.cpp
//  ShoppingCart
//
//  Created by Charlie Jewers on 29/01/2020.
//  Copyright © 2020 Charlie Jewers. All rights reserved.
//

#include "ShoppingCart.hpp"
#include "ShoppingItem.hpp"

#include <iostream>
#include <string>

/**
 * Empty constructor.
 */
ShoppingCart::ShoppingCart() {
    
}

/**
 * Gives the items in a cart.
 * 
 * @return Vector of ShoppingItem objects in the cart.
 */
std::vector<ShoppingItem> ShoppingCart::GetItems() {
    return items;
}

/**
 * Comparator function for AddItem().
 *
 * Checks if a supplied item name already exists in the cart.
 *
 * @param item A given item in the cart.
 * @param name Name value to check against the name of item.
 *
 * @return True if the supplied name matches the item name, false if not. 
 */
bool checkItemAlreadyExists(ShoppingItem item, std::string name) {
    if (item.GetName() == name)
        return true;
    else
        return false;
}

/**
 * Adds an item to the shopping cart.
 *
 * If an item with the same name already exists, updates the item's quantity and applies a discount if necessary.
 *
 * @param item The item to add to the cart.
 */
void ShoppingCart::AddItem(ShoppingItem item) {
    std::vector<ShoppingItem>::iterator it;
    it = std::find_if(items.begin(), items.end(), std::bind(checkItemAlreadyExists, std::placeholders::_1, item.GetName()));
    if(it != items.end()) {
        it->EditQuantity(item.GetQuantity());
        it->SetQuantityDiscounted(it->GetQuantity() / 3);
    }
    else
        items.push_back(item);
    std::cout << "Added " << item.GetName() << "!\n\n";
}

/**
 * Removes an item from the shopping cart, specified by the item name.
 *
 * @param itemName The name of the item to remove.
 */
void ShoppingCart::RemoveItem(std::string itemName) {
    std::vector<ShoppingItem>::iterator it = find_if(items.begin(), items.end(), [&itemName](ShoppingItem obj) {
        return obj.GetName() == itemName;
    });
    if (it != items.end()) {
        items.erase(it);
        std::cout << itemName << " removed from cart.\n";
    }
    else
        std::cout << itemName << " is not in the cart.\n";
}

/**
 * Gets a vector of items that qualify for the 'Cheapest Item Free' discount.
 * 
 * Helper function for ApplyCheapestItemFree().
 * 
 * @return A vector of ShoppingItems eligible for discount.
 */
std::vector<ShoppingItem> ShoppingCart::GetDiscountableItems() {
    std::vector<ShoppingItem> discountableItems;
    std::copy_if (items.begin(), items.end(), std::back_inserter(discountableItems), [](ShoppingItem item){
        return (item.GetQuantity() - item.GetQuantityDiscounted() > 0);
    });
    return discountableItems;
}

/**
 * Compares 2 items in a cart to see which is the cheapest.
 * 
 * Helper function for ApplyCheapestItemFree().
 *
 * @param x A shopping item from a cart.
 * @param y A shopping item from the same cart.
 * @return Boolean that states whether item x is more expensive than item y.
 */
bool compareItemPrices(ShoppingItem x, ShoppingItem y)
{
    return x.GetPrice() > y.GetPrice();
}

/**
 * If there are 3 unique types of item in the cart, discounts the cheapest one. Repeats until no sets of 3 unique items left.
 */
void ShoppingCart::ApplyCheapestItemFree() {
    // sub-vector of items (where itemQuantity > quantityDiscounted)
    std::vector<ShoppingItem> discountableItems = this->GetDiscountableItems();
    if (discountableItems.size() >= 3) {
        // gets cheapest item from sub-vector
        std::vector<ShoppingItem>::iterator cheapestItem = std::max_element(discountableItems.begin(), discountableItems.end(), compareItemPrices);
        // name is needed to find corresponding item in full items vector
        std::string cheapestItemName = cheapestItem->GetName(); 
        // searched full items vector for cheapest item and discounts it by one
        std::vector<ShoppingItem>::iterator it = find_if(items.begin(), items.end(), [&cheapestItemName](ShoppingItem obj) {return obj.GetName() == cheapestItemName;});
        if( it != items.end() )
        {
            long index = std::distance(items.begin(), it);
            items.at(index).SetQuantityDiscounted(items.at(index).GetQuantityDiscounted() + 1);
            std::cout << "CHEAPEST ITEM FREE DEAL: " << items.at(index).GetName() << "\n";
        }
        this->ApplyCheapestItemFree();
    }
}

/**
 * Prints the items in a shopping cart, indicating any free items.
 */
void ShoppingCart::PrintCartItems() {
    std::cout << "\nITEMS:\n";
    this->ApplyCheapestItemFree();
    for(int i = 0; i < items.size(); i++) {
        ShoppingItem itemToPrint = items.at(i);
        std::string name = itemToPrint.GetName();
        float price = itemToPrint.GetPrice();
        int quantity = itemToPrint.GetQuantity();
        int discounted = itemToPrint.GetQuantityDiscounted();
        std::cout << name << " x" << quantity << " (" << discounted << " free) @ £" << price << "\n";
    }
}

/**
 * Calculates the total price of the items in a shopping cart, taking into account any free items from deals.
 *
 * @return float value representing the cumulative price of all items in cart.
 */
float ShoppingCart::GetTotalPrice() {
    float total = 0;
    for(int i = 0; i < items.size(); i++) {
        ShoppingItem item = items.at(i);
        float price = item.GetPrice();
        int quantity = item.GetQuantity();
        int discounted = item.GetQuantityDiscounted();
        total += (price * (quantity - discounted));
    }
    return total;
}


