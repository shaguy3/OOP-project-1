#include "election_cycle.h"

ElectionCycle::ElectionCycle(Date& _date_of_election) :
    date_of_election(_date_of_election),
    current_vote_amount(0),
    residents_num_size(5),
    residents_num_logi(0),
    parties_num_size(5),
    parties_num_logi(0),
    counties_num_size(5),
    counties_num_logi(0),
    residents(new Citizen* [residents_num_size]),
    parties(new Party* [parties_num_size]),
    counties(new County* [counties_num_size])
{}

ElectionCycle::~ElectionCycle() {
    delete[] residents;
    delete[] parties;
    delete[] counties;
}

void ElectionCycle::resizeResidents() {
    residents_num_size *= 2;
    Citizen** new_arr = new Citizen * [residents_num_size];

    for (int i = 0; i < residents_num_logi; i++) {
        new_arr[i] = residents[i];
    }

    residents = new_arr;
}

void ElectionCycle::resizeParties() {
    parties_num_size *= 2;
    Party** new_arr = new Party * [parties_num_size];

    for (int i = 0; i < parties_num_logi; i++) {
        new_arr[i] = parties[i];
    }

    parties = new_arr;
}

void ElectionCycle::resizeCounties() {
    counties_num_size *= 2;
    County** new_arr = new County * [counties_num_size];

    for (int i = 0; i < counties_num_logi; i++) {
        new_arr[i] = counties[i];
    }

    counties = new_arr;
}

Citizen* ElectionCycle::getResident(int id) {
    int cur = 0;
    do {
        if (residents[cur]->getId() == id) { return residents[cur]; }
        else { cur++; }
    } while (cur < residents_num_logi);

    return nullptr;
}

Party* ElectionCycle::getParty(char* party_name) {
    for (int i = 0; i < parties_num_logi; i++) {
        if (!strcmp(parties[i]->getName(), party_name)) {
            return parties[i];
        }
    }

    return nullptr;
}

County* ElectionCycle::getCounty(int id) {
    return counties[id];
}

bool ElectionCycle::addResident(Citizen* resident) {
    if (residents_num_logi == residents_num_size) { resizeResidents(); }

    residents[residents_num_logi] = resident;
    residents_num_logi++;

    return true;
}

bool ElectionCycle::addVote() {
    current_vote_amount++;

    return true;
}

bool ElectionCycle::addParty(Party* party) {
    if (parties_num_logi == parties_num_size) { resizeParties(); }

    parties[parties_num_logi] = party;
    parties_num_logi++;

    return true;
}

bool ElectionCycle::addCounty(County* county) {
    if (counties_num_logi == counties_num_size) { resizeCounties(); }

    counties[counties_num_logi] = county;
    counties_num_logi++;

    return true;
}

ostream& operator<<(ostream& os, ElectionCycle& election_cycle) {
    os << "Election cycle of date: " << election_cycle.getDate() << endl \
        << "Residents: " << endl;

    for (int i = 0; i < election_cycle.residentslen(); i++) {
        os << *election_cycle.getResidents()[i] << endl;
    }

    os << endl << "Counties: " << endl;

    for (int i = 0; i < election_cycle.countieslen(); i++) {
        os << *election_cycle.getCounties()[i] << endl;
    }

    os << endl << "Parties: " << endl;

    for (int i = 0; i < election_cycle.partieslen(); i++) {
        os << *election_cycle.getParties()[i] << endl;
    }

    return os;
}
