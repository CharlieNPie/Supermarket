#define CATCH_CONFIG_MAIN 
#include "catch.hpp"
#include "../ShoppingCart.cpp"
#include "../ShoppingItem.cpp"

TEST_CASE("Adding items to the cart", "[shoppingcart]") {

    ShoppingCart cart;
    REQUIRE (cart.GetItems().size() == 0);

    SECTION("Adds a new item to an empty cart") {
        ShoppingItem item("itemName", 5, 1);
        cart.AddItem(item);
        REQUIRE (cart.GetItems().size() == 1);
    }

    SECTION("Adds a new item to a cart with items in it already.") {
        ShoppingItem item1("firstItem", 5, 1);
        cart.AddItem(item1);
        ShoppingItem item2("secondItem", 5, 1);
        cart.AddItem(item2);
        REQUIRE (cart.GetItems().size() == 2);
    }
    
    SECTION("Adds an item that already exists in the cart and updates its quantity") {
        ShoppingItem firstItem("firstItem", 5, 1);
        cart.AddItem(firstItem);
        ShoppingItem secondItem("firstItem", 5, 2);
        cart.AddItem(secondItem);
        REQUIRE (cart.GetItems().size() == 1);
        REQUIRE (cart.GetItems().front().GetQuantity() == 3);
    }

}

TEST_CASE ("Removing items from a cart", "[shoppingcart]") {

    ShoppingCart cart;
    ShoppingItem item("itemName", 5, 1);
    cart.AddItem(item);
    REQUIRE (cart.GetItems().size() == 1);

    SECTION("Removes an item from a cart with no other items in it") {
        cart.RemoveItem("itemName");
        REQUIRE (cart.GetItems().size() == 0);
    }

    SECTION("Removes an item from a cart with other items in it") {
        ShoppingItem item2("secondItem", 7, 2);
        cart.AddItem(item2);
        cart.RemoveItem("itemName");
        REQUIRE (cart.GetItems().size() == 1);
        REQUIRE (cart.GetItems().front().GetName() != "itemName");
    }

}

TEST_CASE ("Applying 'Cheapest Item Free' Discount") {

    ShoppingCart cart;
    ShoppingItem item1("item1", 5, 2);
    cart.AddItem(item1);
    ShoppingItem item2("item2", 4, 1);
    cart.AddItem(item2);
    ShoppingItem item3("item3", 3, 1);
    cart.AddItem(item3);

    SECTION ("If three unique items are in the basket, the cheapest one is registered as free.") {
        cart.ApplyCheapestItemFree();
        REQUIRE (cart.GetItems().at(2).GetQuantityDiscounted() == 1);
    }

}

TEST_CASE ("Calculating the total amount on the cart receipt") {
    ShoppingCart cart;

    SECTION ("Multiple items with quantity 1 add up correctly.") {
        ShoppingItem item1("item1", 5, 1);
        cart.AddItem(item1);
        ShoppingItem item2("item2", 4, 1);
        cart.AddItem(item2);
        REQUIRE (cart.GetTotalPrice() == 9);
    }

    SECTION ("Buy three unique items, get the cheapest one free") {
        ShoppingItem item1("item1", 5, 1);
        cart.AddItem(item1);
        ShoppingItem item2("item2", 6, 1);
        cart.AddItem(item2);
        ShoppingItem item3("item3", 3, 1);
        cart.AddItem(item3);
        cart.ApplyCheapestItemFree();
        REQUIRE (cart.GetTotalPrice() == 11);
    }

    SECTION ("Buy three unique items in multiple quantities, get the cheapest two free") {
        ShoppingItem item1("item1", 1, 2);
        cart.AddItem(item1);
        ShoppingItem item2("item2", 2, 2);
        cart.AddItem(item2);
        ShoppingItem item3("item3", 3, 2);
        cart.AddItem(item3);
        cart.ApplyCheapestItemFree();
        REQUIRE (cart.GetTotalPrice() == 10);
    }

    SECTION ("Buy 3 of an item, get one free") {
        ShoppingItem item1("item1", 5, 3);
        cart.AddItem(item1);
        REQUIRE (cart.GetTotalPrice() == 10);
    }

    SECTION ("Buy 9 of an item, get 3 free") {
        ShoppingItem item1("item1", 5, 9);
        cart.AddItem(item1);
        REQUIRE (cart.GetTotalPrice() == 30);
    }

    SECTION ("Buy 3 of multiple items, receive multiple discounts") {
        ShoppingItem item1("item1", 5, 3);
        cart.AddItem(item1);
        ShoppingItem item2("item2", 7, 3);
        cart.AddItem(item2);
        ShoppingItem item3("item3", 9, 3);
        cart.AddItem(item3);
        REQUIRE (cart.GetTotalPrice() == 42);
    }

}



