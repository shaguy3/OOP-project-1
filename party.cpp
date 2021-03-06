#include <string.h>
#include "party.h"

int Party::number_of_parties = 0;

Party::Party(char* _name, Citizen* _party_leader)
    : name(new char[strlen(_name) + 1]), party_leader(_party_leader), id(number_of_parties),
    party_size(5), party_size_logi(0), party_reps(new Citizen* [party_size])
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
    delete[] name;
    delete[] party_reps;
}


bool Party::addPartyRep(Citizen* new_rep)
{
    if (party_size_logi == party_size)
        resizeParty();

    party_reps[party_size_logi] = new_rep;
    party_size_logi++;

    return true;
}

void Party::resizeParty()
{
    int i;
    party_size *= 2;
    Citizen** new_arr = new Citizen * [party_size];
    for (i = 0; i < party_size_logi; i++) {

        new_arr[i] = party_reps[i];
    }

    party_reps = new_arr;
}

ostream& operator<<(ostream& os, const Party& party)
{
    os << "Party name: " << party.name << ". Leader " << party.party_leader->getName() << '.' << endl;
    os << "County representatives:" << endl << endl;
    for (int i = 0; i < County::num_of_counties; i++) {
        os << "County num " << i << ":" << endl;
        for (int j = 0; j < party.party_size_logi; j++) {
            if (party.party_reps[j]->getHomeCounty()->getId() == i) {
                os << *party.party_reps[j] << endl << endl;
            }
        }
    }

    return os;
}
