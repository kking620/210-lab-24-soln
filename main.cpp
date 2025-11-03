//COMSC-210 | Lab 28 | Kristofer King
//IDE Used: VSC
#include <iostream>
#include <fstream>
#include <iomanip>
#include <list>
#include <tuple>
#include <string>
#include <random>
#include <numeric>
#include <algorithm>
#include "Goat.h"
using namespace std;

const int SZ_NAMES = 200, SZ_COLORS = 25;

//prototype functions for all of the features the user can perform by inputting the specific option
int select_goat(list<Goat> trip);
void delete_goat(list<Goat> &trip);
void add_goat(list<Goat> &trip, string [], string []);
void reverse_goat(list<Goat> &trip);
void inc_age(list<Goat> &trip);
void remove_dupes(list<Goat> &trip);
void remove_goats_young(list<Goat> &trip);
void add_all_ages(list<Goat> &trip);
void find_goat(list<Goat> &trip);
void display_trip(list<Goat> trip);
void sort_trip(list<Goat> &trip);
int main_menu();

int main() {
    srand(time(0));
    bool again;

    // read & populate arrays for names and colors
    ifstream fin("names.txt");
    string names[SZ_NAMES];
    int i = 0;
    while (fin >> names[i++]);
    fin.close();
    ifstream fin1("colors.txt");
    string colors[SZ_COLORS];
    i = 0;
    while (fin1 >> colors[i++]);
    fin1.close();

    // create & populate a trip of Goats using std::list of random size 8-15
    int tripSize = rand() % 8 + 8;
    list<Goat> trip;
    int age;
    string name, color;
    for (int i = 0; i < tripSize; i++) {
        age = rand() % MAX_AGE;  // defined in Goat.h
        name = names[rand() % SZ_NAMES];
        color = colors[rand() % SZ_COLORS];
        Goat tmp(name, age, color);
        trip.push_back(tmp);
    }
    
    // Goat Manager 3001 Engine
    int sel = main_menu();
    while (sel != 12) {
        switch (sel) {
            case 1:
                cout << "Adding a goat.\n";
                add_goat(trip, names, colors);
                break;
            case 2:    
                cout << "Removing a goat.\n";
                delete_goat(trip);
                break;
            case 3:    
                cout << "Displaying goat data.\n";
                display_trip(trip);
                break;
            //if the user inputs 4, then they will reverse the current order of the goats
            case 4:    
                cout << "Reversing the order of goats.\n";
                reverse_goat(trip);
                break;
            //if the user inputs 5, then they will increase the age of all of the goats by 1
            case 5:    
                cout << "Increasing the age of the goats by 1.\n";
                inc_age(trip);
                break;
            //if the user inputs 6, then they will remove any duplicate goats that appear on the trip
            case 6:    
                cout << "Removing duplicates.\n";
                remove_dupes(trip);
                break;
            //if the user inputs 7, then they will sort the trip in alphabetical order by name
            case 7:    
                cout << "Sorting the trip.\n";
                sort_trip(trip);
                break;
            //if the user selects 8, then they will check if any of the goats are currently the maximum age
            case 8:    
                cout << "Checking age of goats.\n";
                check_max_age(trip);
                break;
            //if the user selects 9, then they will remove any goats that don't meet the threshold age of 5 years old
            case 9:    
                cout << "Removing goats that are too young.\n";
                remove_goats_young(trip);
                break;
            //if the user inputs 10, then they will add all of the ages of the goats together
            case 10:    
                cout << "Adding all ages together.\n";
                add_all_ages(trip);
                break;
            //if the user inputs 11, then they will find a specific goat on the trip's position
            case 11:    
                cout << "Finding goat.\n";
                find_goat(trip);
                break;
            case 12:    
                cout << "Quitting.\n";
                break;
            default:
                cout << "Invalid selection.\n";
                break;
        }
        sel = main_menu();
    }
    

    return 0;
}

//updated menu with the options the user can select from
int main_menu() {
    cout << "*** GOAT MANAGER 3001 ***\n";
    cout << "[1] Add a goat\n";
    cout << "[2] Delete a goat\n";
    cout << "[3] List goats\n";
    cout << "[4] Reverse order of goats\n";
    cout << "[5] Increase the age of the goats by 1\n";
    cout << "[6] Remove duplicates (must be sorted first)\n";
    cout << "[7] Sort the trip\n";
    cout << "[8] Check if any of the goats are max age\n";
    cout << "[9] Remove goats that are too young (under 5 years old)\n";
    cout << "[10] Calculate the total age of all goats on trip\n";
    cout << "[11] Find position of a specific goat\n";
    cout << "[12] Quit\n";
    cout << "Choice --> ";
    int choice;
    cin >> choice;
    while (choice < 1 || choice > 12) {
        cout << "Invalid, again --> ";
        cin >> choice;
    }
    return choice;
}

//void function that traverses the list using an iterator to see if the name inputted matches any of the names in the Goat class that have been stored on the list
void find_goat(list<Goat> &trip) {
    string n = "";
    cout << "Which goat would you like to find?\n";
    cin >> n;
    cin.ignore();

    auto it = find_if(trip.begin(), trip.end(), [n](const Goat& t){return t.name == n;});
    if (it != trip.end())
        cout << it->name << " found at position " << distance(trip.begin(), it) + 1 << "." << endl << endl;
    else
        cout << "Goat not found.";
}

//void function that traverses the list and adds together all of the ages that have been stored on the list
void add_all_ages(list<Goat> &trip) {
    int totalAge = accumulate(trip.begin(), trip.end(), 0, [](int sum, const Goat& t){return sum + t.age;});
    cout << "The total age of all of the goats is " << totalAge << endl;
}

//void function that traverses the list and removes any Goat class objects that do not have an age that exceeds our threshold value
void remove_goats_young(list<Goat> &trip) {
    trip.erase(remove_if(trip.begin(), trip.end(), [](const Goat& t){return t.age < 5;}), trip.end());
    display_trip(trip);
}

//void function that traverses the list and checks if any of the goats have an age equal to our max age global constant
void check_max_age(list<Goat> &trip) {
    bool isMaxAge = any_of(trip.begin(), trip.end(), [](const Goat& t){return t.age == MAX_AGE;});
    cout << "Is there a goat who is the max age? " << (isMaxAge ? "Yes":"No") << endl << endl;
}

//void function that traverses the list, which should be sorted before calling this function, and removes any Goats with a duplicate name
void remove_dupes(list<Goat> &trip) {
    trip.erase(unique(trip.begin(), trip.end(), [](const Goat& a, const Goat& b) {return a.name == b.name;}), trip.end());
    display_trip(trip);
}

//void function that sorts the list in alphabetical order by name by calling the sort() function
void sort_trip(list<Goat> &trip) {
    trip.sort();
    display_trip(trip);
}

//void function that traverses the list and increases the age of all goats on the list by 1
void inc_age(list<Goat> &trip) {
    transform(trip.begin(), trip.end(), trip.begin(), [](Goat& t) {t.age += 1; return t;});
    display_trip(trip);
}

//void function that reverses the current list by calling the reverse() function
void reverse_goat(list<Goat> &trip) {
    reverse(trip.begin(), trip.end());

    cout << "After reversing the order of our goats: \n";
    display_trip(trip);
}

void delete_goat(list<Goat> &trip) {
    cout << "DELETE A GOAT\n";
    int index = select_goat(trip);
    auto it = trip.begin();
    advance(it, (index - 1));
    trip.erase(it);
    cout << "Goat deleted. New trip size: " << trip.size() << endl;
}

void add_goat(list<Goat> &trip, string nms[], string cls[]) {
    cout << "ADD A GOAT\n";
    int age = rand() % MAX_AGE;
    string nm = nms[rand() % SZ_NAMES];
    string cl = cls[rand() % SZ_COLORS];
    Goat tmp(nm, age, cl);
    trip.push_back(tmp);
    cout << "Goat added. New trip size: " << trip.size() << endl;
}

void display_trip(list<Goat> trp) {
    int i = 1;
    for (auto gt: trp)
        cout << "\t" 
             << "[" << i++ << "] "
             << gt.get_name() 
             << " (" << gt.get_age() 
             << ", " << gt.get_color() << ")\n";
}

int select_goat(list<Goat> trp) {
    int input;
    cout << "Make a selection:\n";
    display_trip(trp);
    cout << "Choice --> ";
    cin >> input;
    while (input < 1 || input > trp.size()) {
        cout << "Invalid choice, again --> ";
        cin >> input;
    }
    return input;
}