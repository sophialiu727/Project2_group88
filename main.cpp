#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <stdexcept>
#include "MenuItem.h"

using namespace std;

//CSV fields
vector<string> parseCSVLine(const string& line) {
  vector<string> field;
  string current;
  bool inQuotes = false;

  for (size_t i = 0; i < line.size(); i++) {
    char c = line[i];

    if (c == '"') {
      inQuotes == !inQuotes;
    } else if (c == ',' && !inQuotes) {
        fields.push_back(current);
        current.clear();
    } else {
        current += c;
    }
  }

  fields.push_back(current);
  return fields;
}

vector<MenuItem> readCSV(const string& filename) {
    vector<MenuItem> items;
    ifstream file (filename);

    if (!file.is_open()) {
          cerr << "Error -- Could not open (LOL) file: " << filename << endl;
          return items;
    }

    string line;

// skip first row of csv file
    getline(file, line);

    while (getline(file, line)) {
        if (line.empty()) {
            continue;
        }

        vector<string> fields = parseCSVLine(line);

        if (fields.size() !=3) {
              cerr << "Skipping improperly formatted row: " << line << endl;
              continue;
        }

        string restaurant = fields[0];
        string foodItem = fields [1];
        int calories = 0;

        try {
            calories = stoi(fields[2]);
        } catch (const exception&) {
            cerr << "Skipping row with invalid caloric value: " << line << endl;
            continue;
        }

        items.push_back(MenuItem(restaurant, foodItem, calories));
    }
    file.close();
    return items;
}

int main() {
    string filename = "Restaurant_Item_Calories.csv";
    vector<MenuItem> items = readCSV(filename);

    cout << "Loaded " << items.size() << " menu items." << endl;


// Test Print of first 10 items in csv
    for (size_t i=0; i < items.size() && i < 10; i++) {
        cout << items[i].getRestaurant() << " | "
             << items[i].getFoodItem() << " | "
             << items[i].getCalories() << " Cal" << endl;
    }

    return 0;
}
