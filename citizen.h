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
    bool is_representative;
    bool has_voted;

public:
    /*Constructors & Destructors*/
    Citizen(char* _name, int _id, int _year_of_birth = 0, int _home_county_number = 0);
    ~Citizen();
    /*Getters*/
    char* getName() const { return name; }
    int getId() const { return id; }
    int getYearOfBirth() const { return year_of_birth; }
    int getHomeCounty() const { return home_county_number; }
    bool isRepresentative() const { return is_representative; }
    /*Setters*/
    bool makeRepresentative();
    bool setVoted();
    /*Operators*/
    friend ostream& operator<<(ostream& os, const Citizen& other);
};
