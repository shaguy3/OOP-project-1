#pragma once
#include "citizen.h"

class County {
    private:
        char* name;
        int id;
        Citizen* residents;
        const int number_of_electors;
        Citizen* chosen_electors;
    
    public:
        County(char* _name, int _number_of_electors);
        bool setName(char* _name);
        char* getName();
        bool setId(int _id);
        int getId();
        bool addResident(const Citizen& new_resident);
        Citizen* getResidents(); // TODO: Check if the main can get to the residents.
        int getNumberOfElectors();
        bool addChosenElector(const Citizen& chosen_elector);
        ~County();
};