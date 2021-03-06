#pragma once

#include <iostream>
#include "county.h"
#include <string.h>

using namespace std;
class County;
class Party;

class Citizen {
private:
    char* name;
    int id;
    int year_of_birth;
    County* home_county;
    Party* is_representative;
    Party* has_voted;

public:
    /*Constructors & Destructors*/
    Citizen(char* _name, int _id, int _year_of_birth, County* _home_county);
    ~Citizen();
    /*Getters*/
    char* getName() const { return name; }
    int getId() const { return id; }
    int getYearOfBirth() const { return year_of_birth; }
    County* getHomeCounty() const { return home_county; }
    Party* hasVoted() const { return has_voted; }
    Party* isRepresentative() const { return is_representative; }
    /*Setters*/
    bool makeRepresentative(Party* party_name);
    bool setVoted(Party* party_name);
    /*Operators*/
    friend ostream& operator<<(ostream& os, const Citizen& other);
};
