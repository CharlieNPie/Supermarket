//
//  ShoppingCart.hpp
//  ShoppingCart
//
//  Created by Charlie Jewers on 29/01/2020.
//  Copyright © 2020 Charlie Jewers. All rights reserved.
//

#ifndef ShoppingCart_hpp
#define ShoppingCart_hpp

#include <vector>
#include <string>
#include "ShoppingItem.hpp"

class ShoppingCart {
public:
    //constructor
    ShoppingCart();
    // class methods
    void AddItem(ShoppingItem);
    void RemoveItem(std::string);
    void PrintCartItems();
    void ApplyCheapestItemFree();
    float GetTotalPrice();
    std::vector<ShoppingItem> GetItems();
private:
    // class variables
    std::vector<ShoppingItem> items;
    // helper methods
    std::vector<ShoppingItem> GetDiscountableItems();
};

#endif /* ShoppingCart_hpp */
