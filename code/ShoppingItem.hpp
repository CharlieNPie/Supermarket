//
//  ShoppingItem.hpp
//  ShoppingCart
//
//  Created by Charlie Jewers on 29/01/2020.
//  Copyright © 2020 Charlie Jewers. All rights reserved.
//

#ifndef ShoppingItem_hpp
#define ShoppingItem_hpp

#include <string>

class ShoppingItem {
public:
    // constructor
    ShoppingItem(std::string, float, int);
    // class methods
    std::string GetName();
    float GetPrice();
    int GetQuantity();
    void EditQuantity(int);
    int GetQuantityDiscounted();
    void SetQuantityDiscounted(int);
private:
    // class variables
    std::string itemName;
    float itemPrice;
    int itemQuantity;
    int quantityDiscounted;
};

#endif /* ShoppingItem_hpp */
