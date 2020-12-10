#include "citizen.h"

Citizen::Citizen(char* _name, int _id, int _year_of_birth, County* _home_county)
    : name(new char[strlen(_name) + 1]),
    id(_id), year_of_birth(_year_of_birth),
    home_county(_home_county),
    is_representative(false),
    has_voted(nullptr)
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
    os << "Name: " << other.name << endl << "Id: " << other.id << endl \
        << "Year of birth: " << other.year_of_birth << endl;
    return os;
}

bool Citizen::makeRepresentative() {
    is_representative = true;

    return true;
}

bool Citizen::setVoted(Party* party_name) {
    has_voted = party_name;

    return true;
}
