#ifndef MENUITEM_H
#define MENUITEM_H

#include <string>
using namespace std;

class MenuItem{
private:
    std::string restaurant;
    std::string foodItem;
    double calories;

public:
    MenuItem();
    MenuItem(const std::string& restaurant, const std::string& foodItem, double calories);

    std::string getRestaurant() const;
    std::string getFoodItem() const;
    double getCalories() const;

    void printItem();
};

#endif
