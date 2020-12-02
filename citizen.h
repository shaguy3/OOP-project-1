#pragma once
#include "county.h"

class Citizen {
    private:
        char* name;
        int id;
        int year_of_birth;
        int home_county_number;
    
    public:
        Citizen(char* _name, int _id, int year_of_birth, int home_county_number);
        bool setName(char* _name);
        char* getName();
        bool setId(int _id);
        int getId();
        bool setYearOfBirth(int _year_of_birth);
        int getYearOfBirth();
        bool setHomeCounty(int _home_county_number);
        int getHomeCounty();
        ~Citizen();
};