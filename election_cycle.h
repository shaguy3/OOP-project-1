#pragma once
#include "date.h"
#include "citizen.h"
#include "party.h"
#include "county.h"
#include <iostream>
#include <string.h>

using namespace std;

class ElectionCycle {
    private:
        Date date_of_election;
        Citizen** residents;
        int residents_num_size;
        int residents_num_logi;
        Party** parties;
        int parties_num_size;
        int parties_num_logi;
        County** counties;
        int counties_num_size;
        int counties_num_logi;
        void resizeResidents();
        void resizeParties();
        void resizeCounties();

    public:
        /* Constructors and destructors */
        ElectionCycle(Date& _date_of_election);
        ~ElectionCycle();
        /* Getters and setters */
        Date getDate();
        Citizen** getResidents();
        Party** getParties();
        County** getCounties();
        int residentslen();
        int partieslen();
        int countieslen();
        /* Get specific items from the arrays */
        Citizen* getResident(int id);
        Party* getParty(char* party_name);
        County* getCounty(int id);
        /* Adders */
        bool addResident(Citizen* resident);
        bool addParty(Party* party);
        bool addCounty(County* county);
        /* Operators */
        friend ostream& operator<<(ostream& os, const ElectionCycle& election_cycle);
};