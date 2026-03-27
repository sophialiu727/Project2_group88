#include "MenuItem.h"

MenuItem::MenuItem(string restaurant, string foodItem, int calories){
  this->restaurant = restaurant;
  this->foodItem = foodItem;
  this->calories = calories;
}

string MenuIten::getRestaurant() const{
  return restaurant;
}

string MenuIten::getFoodItem() const{
  return foodItem;
}

string MenuIten::getCalories() const{
  return calories;
}
