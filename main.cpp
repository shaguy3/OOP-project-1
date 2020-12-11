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

    delete[] county_name; // TODO: delete[]

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

    delete[] resident_name; // TODO: test delete[]
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

        else if (party_leader->isRepresentative()) {
            cout << "This resident is already a representative. Please select another citizen: ";
            party_leader_id = 0;
        }
    } while (party_leader_id == 0);

    party_leader->makeRepresentative();

    Party* new_party = new Party(party_name, party_leader);
    election_cycle->addParty(new_party);

    delete[] party_name; // TODO: test delete[]
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

        else if (relavent_citizen->isRepresentative()) {
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

    delete[] party_name; // TODO: test delete[]
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
        }
        else if (voter->hasVoted()) {
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

    delete[] party_name; // TODO: test delete[]
}

void electionResults(ElectionCycle* election_cycle) {

    cout << "Printing election results!" << endl;

    //Need to count all of the votes in all of the counties. 2d array? 
    //Voting percentage 
    //Print all of the counties vote

    int** election_result = new int*[election_cycle->countieslen()];
    double** percentage_table = new double* [election_cycle->countieslen()];
    int** elected_reps_nums = new int* [election_cycle->countieslen()];
    Party** winner_per_county = new Party*[election_cycle->countieslen()];
    int* sorted_parties = new int[election_cycle->partieslen()];

    for (int i = 0; i < election_cycle->countieslen(); i++)     //Initilization of election_result array
    {
        election_result[i] = new int[election_cycle->partieslen()];
        for (int j = 0; j < election_cycle->partieslen(); j++)
            election_result[i][j] = 0;
    }

    for (int i = 0; i < election_cycle->countieslen(); i++)     //Initilization of percentage_table array
    {
        percentage_table[i] = new double[election_cycle->partieslen()];
        for (int j = 0; j < election_cycle->partieslen(); j++)
            percentage_table[i][j] = 0;
    }

    for (int i = 0; i < election_cycle->countieslen(); i++)     //Initilization of elected_reps_nums array
    {
        elected_reps_nums[i] = new int[election_cycle->partieslen()];
        for (int j = 0; j < election_cycle->partieslen(); j++)
            elected_reps_nums[i][j] = 0;
    }

    for (int i = 0; i < election_cycle->partieslen(); i++) {    //Initialization of sorted_parties array
        sorted_parties[i] = i;
    }

    for (int i = 0; i < election_cycle->residentslen(); i++)    //Counting the votes for each county and party
    {
        if (election_cycle->getResidents()[i]->hasVoted()) {
            int countyVote = election_cycle->getResidents()[i]->getHomeCounty()->getId();
            int partyVote = election_cycle->getResidents()[i]->hasVoted()->getId();
            election_result[countyVote][partyVote]++;
        }
    }

    for (int i = 0; i < election_cycle->countieslen(); i++)     //Counting the percentage of the votes 
    {
        for (int j = 0; j < election_cycle->partieslen(); j++)
        {
            percentage_table[i][j] = (static_cast<double>(election_result[i][j]) / static_cast<double>(election_cycle->getCounty(i)->getVoteAmount())) * 100.0;
            elected_reps_nums[i][j] = static_cast<int>(((percentage_table[i][j] / 100) * election_cycle->getCounty(i)->getNumberOfElectors()) + 0.5);
        }
    }

    for (int j = 0; j < election_cycle->partieslen(); j++) {    // Adding electors to each county 
        for (int k = 0; k < election_cycle->getParties()[j]->partyRepsLen(); k++) {
            Citizen* chosen_elector = election_cycle->getParties()[j]->getPartyReps()[k];
            int home_county_id = chosen_elector->getHomeCounty()->getId();
            if (elected_reps_nums[home_county_id][j] > 0) {
                election_cycle->getCounty(home_county_id)->addChosenElector(chosen_elector);
                elected_reps_nums[home_county_id][j] -= 1;
            }
        }
    }

    for (int i = 0; i < election_cycle->countieslen(); i++) {   
        double winner_percentage = 0.0;
        int winner_index = 0;
        for (int j = 0; j < election_cycle->partieslen(); j++) {
            if (percentage_table[i][j] > winner_percentage) {
                winner_percentage = percentage_table[i][j];
                winner_index = j;
            }
        }
        winner_per_county[i] = election_cycle->getParties()[winner_index];
    }

    int* electors_per_party = new int[election_cycle->partieslen()];
    for (int i = 0; i < election_cycle->partieslen(); i++) {    // Initializing the sum of electors per party
        electors_per_party[i] = 0;
    }

    for (int i = 0; i < election_cycle->countieslen(); i++) {   // Calculating the sum of electors per party
        electors_per_party[winner_per_county[i]->getId()] += election_cycle->getCounty(i)->getNumberOfElectors();
    }

    int max_electors = 0;
    int winner_winner_chicken_dinner = 0;
    for (int i = 0; i < election_cycle->countieslen(); i++) {
        if (electors_per_party[i] > max_electors) {
            winner_winner_chicken_dinner = i;
            max_electors = electors_per_party[i];
        }
    }

    cout << "Chosen county electors:" << endl; 
    for (int i = 0; i < election_cycle->countieslen(); i++) {
        cout << "County no'" << i << ":" << endl;
        cout << *election_cycle->getCounty(i) << endl;
        for (int j = 0; j < election_cycle->getCounty(i)->chosenElectorsLen(); j++) {
            cout << *election_cycle->getCounty(i)->getChosenElectors()[j] << endl;
        }

        cout << "County voter turnout: " << (static_cast<double>(election_cycle->getCounty(i)->getVoteAmount()) /
                                             static_cast<double>(election_cycle->getCounty(i)->residentsLen())) * 100.0 << endl;
        cout << "Winner in county: " << winner_per_county[i]->getLeader()->getName() << endl;
    }

    for (int i = 0; i < election_cycle->partieslen() - 1; i++) {
        for (int j = 0; j < election_cycle->partieslen() - i - 1; j++) {
            if (electors_per_party[j] > electors_per_party[j+1]) {
                int temp = sorted_parties[j];
                sorted_parties[j] = sorted_parties[j+1];
                sorted_parties[j+1] = i;
            }
        }
    }

    cout << "Final places:" << endl;
    for (int i = election_cycle->partieslen() - 1; i >= 0; i--) {
        cout << election_cycle->partieslen() - i << " place: " << election_cycle->getParties()[sorted_parties[i]]->getLeader()->getName() << endl;
    }
    
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
                }
                else { addPartyRep(election_cycle); }
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
            }
            else if (election_cycle->getVoteAmount() == election_cycle->residentslen()) {
                cout << "All of the existing residents have already voted! The voting is over." << endl;
            }
            else { addVote(election_cycle); }
            break;

        case 9:
            bool valid_reps_nums = true;
            int**  representatives_per_party_per_county = new int*[election_cycle->partieslen()];
            for (int x = 0; x < election_cycle->partieslen(); x++)    //Initilization of the bucket arrays(representatives_per_party_per_county)
            {
                representatives_per_party_per_county[x] = new int[election_cycle->countieslen()];
                for (int z = 0; z < election_cycle->countieslen(); z++)
                    representatives_per_party_per_county[x][z] = 0;
            }
            for (int i = 0; i < election_cycle->partieslen() && valid_reps_nums; i++) {
                Party* cur_party = election_cycle->getParties()[i];
                for (int j = 0; j < cur_party->partyRepsLen() && valid_reps_nums; j++) {
                    representatives_per_party_per_county[i][cur_party->getPartyReps()[j]->getHomeCounty()->getId()] += 1;
                }

                for (int k = 0; k < election_cycle->countieslen() && valid_reps_nums; k++) {
                    if (representatives_per_party_per_county[i][k] < election_cycle->getCounty(k)->getNumberOfElectors()) {
                        cout << "Party " << i << " does not have enough representatives in county " << k << "." \
                            << " Please enter more representatives for the specified county and party." << endl;
                        valid_reps_nums = false;
                    }
                }
            }


            if (valid_reps_nums) { electionResults(election_cycle); }

            for (int i = 0; i < election_cycle->partieslen(); i++)  //Deleting the temp array
                delete[] representatives_per_party_per_county[i];

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

    // int firstint = 3;
    // int secondint = 4;
    // double firstdouble = static_cast<double>(firstint);
    // double seconddouble = static_cast<double>(secondint); 

    // cout << firstint / secondint << endl;
    // cout << firstdouble / seconddouble * 100 << endl;

    return 0;
}
