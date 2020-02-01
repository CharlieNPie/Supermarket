//
//  ShoppingItem.cpp
//  ShoppingCart
//
//  Created by Charlie Jewers on 29/01/2020.
//  Copyright © 2020 Charlie Jewers. All rights reserved.
//

#include "ShoppingItem.hpp"

#include <string>

/**
 * Constructor for shopping item.
 *
 * @param name The name of the product.
 * @param price The price of the product.
 * @param quantity The product quantity.
 */
ShoppingItem::ShoppingItem(std::string name, float price, int quantity) {
    itemName = name;
    itemPrice = price;
    itemQuantity = quantity;
    quantityDiscounted = itemQuantity / 3;
}

/**
 * Gets the name of the item.
 *
 * @return string value containing name of the item.
 */
std::string ShoppingItem::GetName() {
    return itemName;
}

/**
 * Gets the price of the item.
 *
 * @return float representing item's price.
 */
float ShoppingItem::GetPrice() {
    return itemPrice;
}

/**
 * Gets the quantity of the item.
 *
 * @return int representing the item's quantity.
 */
int ShoppingItem::GetQuantity() {
    return itemQuantity;
}

/**
 * Alters the quantity of an item.
 *
 * @param quantity The quantity to add to/subtract from the item.
 */
void ShoppingItem::EditQuantity(int quantity) {
    itemQuantity += quantity;
}

/**
 * Gets the quantity of an item that is eligible for a discount (either 3 for 2 or cheapest item free).
 *
 * @return int representing the quantity of items eligible for discount.
 */
int ShoppingItem::GetQuantityDiscounted() {
    return quantityDiscounted;
}

/**
 * Sets a new value for the itemDiscounted variable.
 *
 * @param quantityDiscounted The quantity to change quantityDiscounted to. 
 */
void ShoppingItem::SetQuantityDiscounted(int quantityDiscounted) {
    this->quantityDiscounted = quantityDiscounted;
}
