#include <string.h>
#include "party.h"

int Party::number_of_parties = 0;

Party::Party(char* _name, int _party_leader_id)
    : party_leader_id(_party_leader_id), id(number_of_parties) {
        char* name = new char[strlen(_name) + 1];
        int cur_char = 0;
        while (_name[cur_char] != '\0') {
            name[cur_char] = _name[cur_char];
            cur_char++;
        }
        name[cur_char] = '\0';
        
        number_of_parties++;

        Citizen** party_reps = new Citizen*; // TODO: Check the implementation of the
    }