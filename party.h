#pragma once
#include "citizen.h"
#include "county.h"
using namespace std;

class Party {
    static int number_of_parties;
private:
    char* name;                                 //name of the party
    int id;                                     //ID of the party 
    int party_leader_id;                        //ID of the party leader
    Citizen** party_reps;                       //array of party rep
    int party_size;
    int party_size_logi;
    void resizeParty();
public:
    /*Ctors & Dtors*/
    Party(char* _name, int _party_leader_id);
    ~Party();

    /*Getters*/
    char* getName() { return name; }
    int getId() { return id; }
    int getLeaderId() { return party_leader_id; }
    /*Methods*/
    bool addPartyRep(Citizen* citizen);         //Add the citizen as party rep
    /*Operators*/
    friend ostream& operator<<(ostream& os, const Party& party);
};