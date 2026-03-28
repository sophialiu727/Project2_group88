#include <string>
#include <iostream>
#include "MenuItem.h"

MenuItem::MenuItem() : restaurant(""), foodItem(""), calories(0.0) {}

MenuItem::MenuItem(const std::string& restaurant, const std::string& foodItem, double calories)
    : restaurant(restaurant), foodItem(foodItem), calories(calories) {}

std::string MenuItem::getRestaurant() const {
    return restaurant;
}

std::string MenuItem::getFoodItem() const {
    return foodItem;
}

double MenuItem::getCalories() const {
    return calories;
}
void MenuItem::printItem(){
    std::cout << restaurant << " | "
             << foodItem << " | "
             << calories << std::endl;
}