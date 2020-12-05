#include <iostream>
#include <string.h>
#include "county.h"

using namespace std;

int County::num_of_counties = 0;

void County::resizeResidents() {

    residents_num_size *= 2;
    Citizen** new_arr = new Citizen*[residents_num_size];

    for (int i = 0; i < residents_num_logi; i++) {
        new_arr[i] = residents[i];
    }

    delete[] residents; // TODO: May cause trouble by deleting the citizens. Initial testing is promising.

    residents = new_arr;
}

void County::resizeChosenElectors() {
    chosen_electors_size *= 2;
    Citizen** new_arr = new Citizen*[chosen_electors_size];

    for (int i = 0; i < chosen_electors_logi; i++) {
        new_arr[i] = chosen_electors[i];
    }

    delete[] chosen_electors; // TODO: May cause trouble by deleting the citizens. Initial testing is promising.

    chosen_electors = new_arr;
}

County::County(char* _name, int _number_of_electors) :
    name(new char[strlen(_name) + 1]),
    id(County::num_of_counties),    
    number_of_electors(_number_of_electors),
    residents_num_logi(0),
    chosen_electors_logi(0), 
    residents_num_size(5),
    chosen_electors_size(5),
    residents(new Citizen*[residents_num_size]),
    chosen_electors(new Citizen*[chosen_electors_size]) {

    int cur_char = 0;
    while (_name[cur_char] != '\0') {
        name[cur_char] = _name[cur_char];
        cur_char++;
    }
    name[cur_char] = '\0';

    County::num_of_counties++;
}

char* County::getName() {
    return name;
}

int County::getId() {
    return id;
}

int County::getNumberOfElectors() {
    return number_of_electors;
}

bool County::addResident(Citizen* new_resident) {
    if (residents_num_logi == residents_num_size) { resizeResidents(); }

    residents[residents_num_logi] = new_resident;
    residents_num_logi++;

    return true;
}

Citizen** County::getResidents() {
    return residents;
}

int County::residentsLen() {
    return residents_num_logi;
}

bool County::addChosenElector(Citizen* chosen_elector) {
    if (chosen_electors_logi == chosen_electors_size) { resizeChosenElectors(); }

    residents[chosen_electors_logi] = chosen_elector;
    chosen_electors_logi++;

    return true;
}

Citizen** County::getChosenElectors() {
    return chosen_electors;
}

int County::chosenElectorsLen() {
    return chosen_electors_logi;
}

ostream& operator<<(ostream& os, const County& county) {
    os << "ID: " << county.id << " Name: " << county.name;

    return os;
}

County::~County() {
    delete name;
    delete[] residents;
    delete[] chosen_electors;
}