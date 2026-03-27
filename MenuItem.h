#ifndef MENUITEM_H
#define MENUITEM_H

#include <string>
using namespace std;

class MenuItem{
private:
  string restaurant;
  string foodItem;
  int calories;

public: 
  MenuItem(string restaurant, string foodItem, int calories);

  string getRestaurant() const;
  string getFoodItem() const:
  int getCalories() const;
};

#endif
