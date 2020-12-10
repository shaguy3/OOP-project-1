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
    int current_vote_amount;        //Increases when voting 
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
    /* Getters */
    Date getDate() const { return date_of_election; }
    Citizen** getResidents() const { return residents; }
    Party** getParties() const { return parties; }
    County** getCounties() const { return counties; }
    int getVoteAmount() const { return current_vote_amount; }
    int residentslen() const { return residents_num_logi; }
    int partieslen() const { return parties_num_logi; }
    int countieslen() const { return counties_num_logi; }
    /* Get specific items from the arrays */
    Citizen* getResident(int id);
    Party* getParty(char* party_name);
    County* getCounty(int id);
    /* Adders */
    bool addVote();
    bool addResident(Citizen* resident);
    bool addParty(Party* party);
    bool addCounty(County* county);
    /* Operators */
    friend ostream& operator<<(ostream& os, const ElectionCycle& election_cycle);
};
