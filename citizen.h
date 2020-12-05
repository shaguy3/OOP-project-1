#pragma once

#include <iostream>
//#include "county.h"
#include <string.h>
using namespace std;


class Citizen {
private:
    char* name;     
    int id;
    int year_of_birth;
    int home_county_number;

public:
    /*Constructors & Destructors*/
    Citizen(char* _name, int _id, int _year_of_birth = 0, int _home_county_number = 0);
    ~Citizen();
    /*Getters*/
    char* getName() const { return name; }
    int getId() const { return id; }
    int getYearOfBirth() const { return year_of_birth; }
    int getHomeCounty() const { return home_county_number; }
    /*Setters*/
    bool setYearOfBirth(int _year_of_birth);        //return true if citizen is eligible to vote (At least 18 years old)
    bool setCounty(int _home_county_number);        //return true if the county if valid
    /*Operators*/
    friend ostream& operator<<(ostream& os, const Citizen& other);
};
