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

int select_goat(list<Goat> trip);
void delete_goat(list<Goat> &trip);
void add_goat(list<Goat> &trip, string [], string []);
void reverse_goat(list<Goat> &trip);
void inc_age(list<Goat> &trip);
void remove_dupes(list<Goat> &trip);
void remove_goats_young(list<Goat> &trip);
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
    while (sel != 10) {
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
            case 4:    
                cout << "Reversing the order of goats.\n";
                reverse_goat(trip);
                break;
            case 5:    
                cout << "Increasing the age of the goats by 1.\n";
                inc_age(trip);
                break;
            case 6:    
                cout << "Removing duplicates.\n";
                remove_dupes(trip);
                break;
            case 7:    
                cout << "Sorting the trip.\n";
                sort_trip(trip);
                break;
            case 8:    
                cout << "Checking age of goats.\n";
                check_max_age(trip);
                break;
            case 9:    
                cout << "Removing goats that are too young.\n";
                remove_goats_young(trip);
                break;
            case 10:    
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
    cout << "[10] Quit\n";
    cout << "Choice --> ";
    int choice;
    cin >> choice;
    while (choice < 1 || choice > 10) {
        cout << "Invalid, again --> ";
        cin >> choice;
    }
    return choice;
}

void remove_goats_young(list<Goat> &trip) {
    trip.erase(remove_if(trip.begin(), trip.end(), [](const Goat& t){return t.age < 5;}), trip.end());
    display_trip(trip);
}

void check_max_age(list<Goat> &trip) {
    bool isMaxAge = any_of(trip.begin(), trip.end(), [](const Goat& t){return t.age == MAX_AGE;});
    cout << "Is there a goat who is the max age? " << (isMaxAge ? "Yes":"No") << endl << endl;
}

void remove_dupes(list<Goat> &trip) {
    trip.erase(unique(trip.begin(), trip.end(), [](const Goat& a, const Goat& b) {return a.name == b.name;}), trip.end());
    display_trip(trip);
}

void sort_trip(list<Goat> &trip) {
    trip.sort();
    display_trip(trip);
}

void inc_age(list<Goat> &trip) {
    transform(trip.begin(), trip.end(), trip.begin(), [](Goat& t) {t.age += 1; return t;});
    display_trip(trip);
}

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