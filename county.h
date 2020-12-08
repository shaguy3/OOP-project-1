#pragma once
#include "citizen.h"

class County {

    private:
        char* name;
        int id;
        int number_of_electors;
        Citizen** residents;
        int residents_num_size;
        int residents_num_logi;
        Citizen** chosen_electors;
        int chosen_electors_size;
        int chosen_electors_logi;
        void resizeResidents();
        void resizeChosenElectors();
    
    public:
        static int num_of_counties;
        County(char* _name, int _number_of_electors);
        char* getName();
        int getId();
        int getNumberOfElectors();
        bool addResident(Citizen* new_resident);
        Citizen** getResidents();
        int residentsLen();
        bool addChosenElector(Citizen* chosen_elector);
        Citizen** getChosenElectors();
        int chosenElectorsLen();
        friend ostream& operator<<(ostream& os, const County& county);
        ~County();
};