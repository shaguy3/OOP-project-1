#include "election_cycle.h"
#include <iostream>

using namespace std;

const int VOTING_AGE = 16;

void addCounty(ElectionCycle* election_cycle) {
    char* county_name = new char[30];
    cout << "Please enter the County's name: ";
    cin >> county_name;

    int number_of_electors = 0;
    cout << "Please enter the number of electors in the county: ";
    cin >> number_of_electors;

    County* new_county = new County(county_name, number_of_electors);
    election_cycle->addCounty(new_county);

    delete county_name; // TODO: delete[]

    cout << endl;
}

void addResident(ElectionCycle* election_cycle) {
    char* resident_name = new char[30];
    cout << "Please enter the Resident's name: ";
    cin >> resident_name;

    int id = 0;
    cout << "Please enter the resident's ID: ";
    do {
        cin >> id;
        if (id <= 0) {
            cout << "Non valid ID. Please enter a non negative number: ";
            id = 0;
        }

        for (int i = 0; i < election_cycle->residentslen(); i++) {
            if (id == election_cycle->getResidents()[i]->getId()) {
                cout << "This ID is already in use. Please enter a unique ID: ";
                id = 0;
            }
        }
    } while (id == 0);

    int year_of_birth = 0;
    cout << "please enter the resident's Year of birth: ";
    do {
        cin >> year_of_birth;
        if (year_of_birth > (election_cycle->getDate().getYear() - VOTING_AGE)) {
            cout << "Resident is too young to vote. Please enter a valid year of birth" << endl;
            year_of_birth = 0;
        }
    } while (year_of_birth == 0);

    int county_id = -1;
    cout << "Please enter the resident's home county: ";
    do {
        cin >> county_id;
        if (county_id < 0 || county_id >(election_cycle->countieslen() - 1)) {
            cout << "Not a valid county id. Please enter a non negative number up to " << election_cycle->countieslen() - 1 << ": ";
            county_id = -1;
        }
    } while (county_id == -1);

    Citizen* new_resident = new Citizen(resident_name, id, year_of_birth, election_cycle->getCounty(county_id));
    election_cycle->addResident(new_resident);
    election_cycle->getCounty(county_id)->addResident(new_resident);

    delete resident_name; // TODO: test delete[]
}

void addParty(ElectionCycle* election_cycle) {
    Citizen* party_leader = nullptr;
    char* party_name = new char[30];
    cout << "Please enter the party name: ";
    cin >> party_name;

    int party_leader_id = 0;
    cout << "Please enter the ID of the party's Leader: ";
    do {
        cin >> party_leader_id;
        party_leader = election_cycle->getResident(party_leader_id);
        if (!party_leader) {
            cout << "There is no resident with matching ID. Please enter an existing resident's ID: ";
            party_leader_id = 0;
        }

        if (party_leader->isRepresentative()) {
            cout << "This resident is already a representative. Please select another citizen: ";
            party_leader_id = 0;
        }
    } while (party_leader_id == 0);

    party_leader->makeRepresentative();

    Party* new_party = new Party(party_name, party_leader);
    election_cycle->addParty(new_party);

    delete party_name; // TODO: test delete[]
}

void addPartyRep(ElectionCycle* election_cycle) {
    Citizen* relavent_citizen = nullptr;
    Party* relevant_party = nullptr;
    int party_rep_id = -1;
    cout << "Please enter the ID of the party's representative: ";
    do {
        cin >> party_rep_id;
        relavent_citizen = election_cycle->getResident(party_rep_id);
        if (!relavent_citizen) {
            cout << "There is no resident with matching ID. Please enter an existing resident's ID: ";
            party_rep_id = -1;
        }

        if (relavent_citizen->isRepresentative()) {
            cout << "This resident is already a representative. Please select another citizen: ";
            party_rep_id = -1;
        }
    } while (party_rep_id == -1);

    char* party_name = new char[30];
    cout << "Please enter the name of the party representative's party: ";
    do {
        cin >> party_name;
        relevant_party = election_cycle->getParty(party_name);
        if (!relevant_party) {
            cout << "There is no party with that name. Please select an existing name: ";
        }
    } while (!relevant_party);

    relavent_citizen->makeRepresentative();
    relevant_party->addPartyRep(election_cycle->getResident(party_rep_id));

    delete party_name; // TODO: test delete[]
}

void showCouties(ElectionCycle* election_cycle) {
    cout << "County list: " << endl << endl;
    for (int i = 0; i < election_cycle->countieslen(); i++) {
        cout << i << ". " << *election_cycle->getCounties()[i] << endl;
    }

    cout << endl;
}

void showResidents(ElectionCycle* election_cycle) {
    cout << "Residents list: " << endl << endl;
    for (int i = 0; i < election_cycle->residentslen(); i++) {
        cout << i << ". " << *election_cycle->getResidents()[i] << endl;
    }

    cout << endl;
}

void showParties(ElectionCycle* election_cycle) {
    cout << "Parties list: " << endl << endl;
    for (int i = 0; i < election_cycle->partieslen(); i++) {
        cout << i << ". " << *election_cycle->getParties()[i] << endl;
    }

    cout << endl;
}

void addVote(ElectionCycle* election_cycle) {
    Citizen* voter = nullptr;
    int voter_id = -1;
    cout << "Please enter the ID of the voter: ";
    do {
        cin >> voter_id;
        voter = election_cycle->getResident(voter_id);
        if (!voter) {
            cout << "There is no resident with matching ID. Please enter an existing resident's ID: ";
            voter_id = -1;
        } else if (voter->hasVoted()) {
            cout << "This resident has already voted. Please select another citizen: ";
            voter_id = -1;
        }
    } while (voter_id == -1);

    Party* voted_party = nullptr;
    char* party_name = new char[30];
    cout << "Please enter the party name which the resident voted for: ";
    do {
        cin >> party_name;
        voted_party = election_cycle->getParty(party_name);
        if (!voted_party) {
            cout << "There is no party with that name. Please select an existing name: ";
        }
    } while (!voted_party);

    voter->setVoted(voted_party);
    voter->getHomeCounty()->addVote();
    election_cycle->addVote();

    delete party_name; // TODO: test delete[]
}

void electionResults(ElectionCycle* election_cycle) {
    cout << "Printing election results!" << endl;
}

void mainMenu() {
    Date date_of_election(20, 11, 2020);
    ElectionCycle* election_cycle = new ElectionCycle(date_of_election);
    int choise = 0;

    while (choise != 10) {
        cout << "Please select an option:" << endl;
        cout << "1. Add a county." << endl;
        cout << "2. Add a citizen" << endl;
        cout << "3. Add a party." << endl;
        cout << "4. Add a party representative." << endl;
        cout << "5. Show all of the counties." << endl;
        cout << "6. Show all of the Citizens." << endl;
        cout << "7. Show all of the parties." << endl;
        cout << "8. Vote." << endl;
        cout << "9. Show the election results." << endl;
        cout << "10. quit" << endl << endl;

        cin >> choise;
        cout << endl;

        if (choise > 10 || choise < 1) {
            cout << "Not a valid choise. Please choose a number between 1 and 10." << endl << endl;
            continue;
        }

        switch (choise) {
        case 1:
            addCounty(election_cycle);
            break;

        case 2:
            if (election_cycle->countieslen() == 0) {
                cout << "There are no counties! please enter a county first." << endl;
            }
            else { addResident(election_cycle); }
            break;

        case 3:
            if (election_cycle->residentslen() == 0) {
                cout << "There are no residents! Who will lead the party? (Enter a resident first)" << endl;
            }
            else {
                int non_representatives = 0;
                for (int i = 0; i < election_cycle->residentslen(); i++) {
                    if (!election_cycle->getResidents()[i]->isRepresentative()) {
                        non_representatives = 1;
                    }
                }

                if (!non_representatives) {
                    cout << "All of the existing residents are already representing existing parties. Please add more citizens." << endl;
                }
                else { addParty(election_cycle); }
            }
            break;

        case 4:
            if (election_cycle->partieslen() == 0) {
                cout << "There are no parties to add representatives to. Please add a party first." << endl;
            }
            else {
                bool non_representatives = false;
                for (int i = 0; i < election_cycle->residentslen(); i++) {
                    if (!election_cycle->getResidents()[i]->isRepresentative()) {
                        non_representatives = true;
                        break;
                    }
                }

                if (!non_representatives) {
                    cout << "All of the existing residents are already representing existing parties. Please add more citizens." << endl;
                } else { addPartyRep(election_cycle); }
            }
            break;

        case 5:
            showCouties(election_cycle);
            break;

        case 6:
            showResidents(election_cycle);
            break;

        case 7:
            showParties(election_cycle);
            break;

        case 8:
        
            if (election_cycle->partieslen() == 0) {
                cout << "There are no parties to vote to. Please add a party first." << endl;
            } else if (election_cycle->getVoteAmount() == election_cycle->residentslen()) {
                cout << "All of the existing residents have already voted! The voting is over." << endl;
            } else { addVote(election_cycle); }
            break;

        case 9:
            bool valid_reps_nums = true;
            int representatives_per_party_per_county[election_cycle->partieslen()][election_cycle->countieslen()];
            for (int i = 0; i < election_cycle->partieslen() && valid_reps_nums; i++) {
                Party* cur_party = election_cycle->getParties()[i];
                for (int j = 0; j < cur_party->partyRepsLen() && valid_reps_nums; j++) {
                    representatives_per_party_per_county[i][cur_party->getPartyReps()[j]->getHomeCounty()->getId()] += 1;
                }

                for (int k = 0; k < election_cycle->countieslen() && valid_reps_nums; k++) {
                    if (representatives_per_party_per_county[i][k] < election_cycle->getCounty(k)->getId()) {
                        cout << "Party " << i << " does not have enough representatives in county " << k << "." \
                             << " Please enter more representatives for the specified county and party." << endl;
                        valid_reps_nums = false;
                    }
                }
            }

            if (valid_reps_nums) { electionResults(election_cycle); }
            break;
        }

        cout << endl;
    }
}

int main() {

    /* Main program */
    cout << "Hello! and welcome to our computerized election system. Please read the software requirements below: " << endl \
        << "1. All of the string inputs are maxed at length of 30" << endl \
        << "2. Adding a citizen requires an existing county." << endl \
        << "3. Adding a party requires an existing non representative citizen." << endl \
        << "4. Adding a party representative requires an existing party, and a non representative citizen." << endl \
        << "5. Citizens can only represent thier home county." << endl << endl;
    mainMenu();

    return 0;
}
