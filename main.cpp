#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <stdexcept>
#include <cctype>
#include "MenuItem.h"
#include "btree.cpp"
#include "redblack.cpp"

using namespace std;

struct stringdata {
	std::string key;
	MenuItem data;

    void printItem(){
        cout << data.getRestaurant() << " | "
             << data.getFoodItem() << " | "
             << data.getCalories() << endl;
    }
};

string trim(const string& s) {
    size_t start = 0;
    while (start < s.size() && isspace(static_cast<unsigned char>(s[start]))) {
        start++;
    }

    size_t end = s.size();
    while (end > start && isspace(static_cast<unsigned char>(s[end - 1]))) {
        end--;
    }

    return s.substr(start, end - start);
}

vector<string> parseCSVLine(const string& line) {
    vector<string> fields;
    string current;
    bool inQuotes = false;

    for (size_t i = 0; i < line.size(); i++) {
        char c = line[i];

        if (c == '"') {
            // Handle escaped double quotes inside a quoted field
            if (inQuotes && i + 1 < line.size() && line[i + 1] == '"') {
                current += '"';
                i++;
            } else {
                inQuotes = !inQuotes;
            }
        }
        else if (c == ',' && !inQuotes) {
            fields.push_back(trim(current));
            current.clear();
        }
        else if (c != '\r') {
            current += c;
        }
    }

    fields.push_back(trim(current));
    return fields;
}

vector<MenuItem> readCSV(const string& filename) {
    vector<MenuItem> items;
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Error: could not open file " << filename << endl;
        return items;
    }

    string line;

    // Skip header row
    getline(file, line);

    int i = 0;
    while (getline(file, line) && i < 100) {
        if (trim(line).empty()) {
            continue;
        }

        vector<string> fields = parseCSVLine(line);

        if (fields.size() != 3) {
            cerr << "Skipping malformed row: " << line << endl;
            continue;
        }

        string restaurant = fields[0];
        string foodItem = fields[1];
        string calorieStr = fields[2];

        try {
            double calories = stod(calorieStr);
            items.push_back(MenuItem(restaurant, foodItem, calories));
        }
        catch (const exception&) {
            cerr << "Skipping row with invalid calorie value: " << line << endl;
        }

        i++;
    }

    file.close();
    return items;
}

void interface(BTree<stringdata> btree_restaurant, BTree<stringdata> btree_item, RedBlackTree rbtree){
    int choice = -1;
    int searchType = 0;
    while(choice != 0){
        cout << "\n===== MENU =====\n";
        cout << "1. Search B-Tree\n";
        cout << "2. Search Red-Black Tree\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1 || choice == 2) {
            cout << "\nSearch by:\n";
            cout << "1. Restaurant name\n";
            cout << "2. Item name\n";
            cout << "Enter choice: ";
            cin >> searchType;
            cin.ignore();
        }

        string key;
        if(choice == 1 || choice == 2){
            cout << "What would you like to search for?";
            getline(cin, key);
            cout << "\nItems Found: \n";
        }
        
        if(choice == 1){
            if(searchType == 1){
                auto results = btree_restaurant.search(key);
                for(int i = 0 ; i < results.size() ; ++i){
                    results[i] -> printItem();
                }
            }
            if(searchType == 2){
                auto results = btree_item.searchContains(key);
                for(int i = 0 ; i < results.size() ; ++i){
                    results[i] -> printItem();
                }
            }
        }
        if(choice == 2){
            if(searchType == 1){
                auto results = rbtree.search(key);
                for(int i = 0 ; i < results.size() ; ++i){
                    results[i].printItem();
                }
            }
            if(searchType == 2){
                auto results = rbtree.searchContains(key);
                for(int i = 0 ; i < results.size() ; ++i){
                    results[i].printItem();
                }
            }
        }
    }
}

int main() {
    string filename = "Restaurant_Item_Calories.csv";

    vector<MenuItem> items = readCSV(filename);

    cout << "Loaded " << items.size() << " menu items." << endl;
    cout << endl;

    // Print first 10 items for testing
    cout << "Preview of the first 10 elements" << endl;
    for (size_t i = 0; i < items.size() && i < 10; i++) {
        cout << items[i].getRestaurant() << " | "
             << items[i].getFoodItem() << " | "
             << items[i].getCalories() << endl;
    }

    //creates btree
    BTree<stringdata> btree_restaurant(items.size());
    for(int i = 0 ; i < items.size() ; ++i){
        stringdata* d = new stringdata;
        d -> key = items[i].getRestaurant();
        d -> data = items[i];
        btree_restaurant.insert(d);
    }

    BTree<stringdata> btree_item(items.size());
    for(int i = 0 ; i < items.size() ; ++i){
        stringdata* d = new stringdata;
        d -> key = items[i].getFoodItem();
        d -> data = items[i];
        btree_item.insert(d);
    }

     RedBlackTree rbtree;
    for(int i = 0 ; i < items.size() ; ++i){
        rbtree.insert(items[i]);
    }

    //  auto seven_eleven = btree_restaurant.search("7 Eleven");
    // for(int i = 0 ; i < seven_eleven.size() ; ++i){
    //     cout << seven_eleven[i] -> key << endl;
    // }

    // auto apple_pie = btree_item.searchContains("Bacon");
    // for(int i = 0 ; i < apple_pie.size() ; ++i){
    //     apple_pie[i] -> printItem();
    // }

    // auto rbtree_7eleven = rbtree.search("7 Eleven");
    // for(int i = 0 ; i < rbtree_7eleven.size() ; ++i){
    //     rbtree_7eleven[i].printItem();
    // }

    // auto rbtree_bacon = rbtree.searchContains("Bacon");
    // for(int i = 0 ; i < rbtree_bacon.size() ; ++i){
    //     rbtree_bacon[i].printItem();
    // }

    interface(btree_restaurant, btree_item, rbtree);

    return 0;
}