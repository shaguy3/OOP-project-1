#pragma once
#include "citizen.h"
#include "county.h"
using namespace std;

class Party {
    static int number_of_parties;
private:
    char* name;                                 //name of the party
    int id;                                     //ID of the party 
    Citizen* party_leader;                      //Pointer to the party leader
    Citizen** party_reps;                       //array of party rep
    int party_size;
    int party_size_logi;
    void resizeParty();
public:
    /*Ctors & Dtors*/
    Party(char* _name, Citizen* _party_leader);
    ~Party();

    /*Getters*/
    char* getName() { return name; }
    int getId() { return id; }
    Citizen* getLeader() { return party_leader; }
    Citizen** getPartyReps() { return party_reps; }
    int partyRepsLen() const { return party_size_logi; }
    /*Methods*/
    bool addPartyRep(Citizen* citizen);         //Add the citizen as party rep
    /*Operators*/
    friend ostream& operator<<(ostream& os, const Party& party);
};
