#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <stdexcept>
#include <cctype>
#include "MenuItem.h"

using namespace std;

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

    while (getline(file, line)) {
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
    }

    file.close();
    return items;
}

int main() {
    string filename = "Restaurant_Item_Calories.csv";

    vector<MenuItem> items = readCSV(filename);

    cout << "Loaded " << items.size() << " menu items." << endl;
    cout << endl;

    // Print first 10 items for testing
    for (size_t i = 0; i < items.size() && i < 10; i++) {
        cout << items[i].getRestaurant() << " | "
             << items[i].getFoodItem() << " | "
             << items[i].getCalories() << endl;
    }

    return 0;
}