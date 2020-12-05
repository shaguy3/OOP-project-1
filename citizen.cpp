#include "citizen.h"

Citizen::Citizen(char* _name, int _id, int _year_of_birth, int _home_county_number)
	: name(new char[strlen(_name) + 1]), id(_id), year_of_birth(_year_of_birth), home_county_number(_home_county_number)
{
    int cur_char = 0;
    while (_name[cur_char] != '\0') {
        name[cur_char] = _name[cur_char];
        cur_char++;
    }
    name[cur_char] = '\0';
}

Citizen::~Citizen()
{
    delete[] name;
}

std::ostream& operator<<(std::ostream& os, const Citizen& other)
{
    os << "Name: " << other.name << '\n' << "Id: " << other.id << '\n' 
        << "Year of birth: " << other.year_of_birth << '\n' << "County: " << other.home_county_number;
    return os;
}

bool Citizen::setYearOfBirth(int _year_of_birth)        //TODO:How to access date from the date class? 
{
    int currentYear = 2020;

    year_of_birth = _year_of_birth;
    if (currentYear - _year_of_birth >= 18)         
        return true;

    return false;
}

bool Citizen::setCounty(int _home_county_number)       //TODO:Do you have to check if the county is valid? 
{
    home_county_number = _home_county_number;
    return true;
}
