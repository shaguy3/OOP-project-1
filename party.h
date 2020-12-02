#pragma once
#include "citizen.h"

class Party {
    private:
        char* name;
        int id;
        int party_leader_id;
        Citizen** party_reps;
    public:
        static int number_of_parties;
        Party(char* _name, int _party_leader_id);
        char* getName();
        int getId();
        bool addPartyRep(const Citizen& party_rep);
        ~Party();
};