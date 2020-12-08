#include <string.h>
#include "party.h"

int Party::number_of_parties = 0;

Party::Party(char* _name, int _party_leader_id)
    : name(new char[strlen(_name)+ 1]),party_leader_id(_party_leader_id), id(number_of_parties), 
      party_size(5), party_size_logi(0), party_reps(new Citizen*[party_size])
    {

    int cur_char = 0;
    while (_name[cur_char] != '\0') {
        name[cur_char] = _name[cur_char];
        cur_char++;
    }
    name[cur_char] = '\0';

    number_of_parties++;
}

Party::~Party()
{
    delete name;
    delete[] party_reps;
}


bool Party::addPartyRep(Citizen* new_rep)
{
    if (party_size_logi == party_size)
        resizeParty(party_reps);

    party_reps[party_size_logi] = new_rep;
    party_size_logi++;

    return true;
}

void Party::resizeParty(Citizen** other)
{
    int i;
    party_size *= 2;
    Citizen** new_arr = new Citizen * [party_size];
    for (i = 0; i < party_size_logi; i++) {

        new_arr[i] = new Citizen(other[i]->getName(), other[i]->getId(), other[i]->getYearOfBirth(), other[i]->getHomeCounty());
    }

    for (i = 0; i < party_size_logi; i++)
    {
        delete party_reps[i];
    }
    party_reps = new_arr;
}

ostream& operator<<(ostream& os, const Party& party)
{
    os << "Party name: " << party.name << "Leader's ID: " << party.party_leader_id;

    return os;
}