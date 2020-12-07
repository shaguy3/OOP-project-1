#include "date.h"
#include "county.h"
#include <iostream>

using namespace std;

void add_county() {
    
}

void main_menu() {
    int choise = 0;

    while (choise != 10) {
        cout << "Hello! Please select an option:" << endl;
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
        if (choise > 10 || choise < 1) {
            cout << "Not a valid choise. Please choose a number between 1 and 10." << endl << endl;
            continue;
        }

        switch (choise) {
            case 1:
                cout << "You chose 1." << endl;
                break;

            case 2:
                cout << "You chose 2." << endl;
                break;

            case 3:
                cout << "You chose 3." << endl;
                break;
            
            case 4:
                cout << "You chose 4." << endl;
                break;

            case 5:
                cout << "You chose 5." << endl;
                break;

            case 6:
                cout << "You chose 6." << endl;
                break;

            case 7:
                cout << "You chose 7." << endl;
                break;
            
            case 8:
                cout << "You chose 8." << endl;
                break;

            case 9:
                cout << "You chose 9." << endl;
                break;
        }
    }
}

int main() {

    /* Date operator<<() testing */
    // Date my_date(1, 5, 2000);
    // cout << my_date << endl;

    /* County testing */
    // char* name = new char[30];
    // cout << "Enter the county name" << endl;
    // cin >> name;

    // County* first_county = new County(name, 5);

    /* Testing getResidents() */
    // first_county->addResident(arie);

    // Citizen** first_county_residents = first_county->getResidents();

    // cout << *first_county_residents[0] << endl;
    // cout << "num of residents " << first_county->residentsLen() << endl;

    /* Testing resizeResidents() */
    // for (int i = 0; i < 7; i++) {
    //     char* citizen_name = new char[30];
    //     cout << "Enter the citizen name" << endl;
    //     cin >> citizen_name;

    //     first_county->addResident(new Citizen(citizen_name, 101010, 1995, 0));

    // }

    // for (int i = 0; i < first_county->residentsLen(); i++) {
    //     cout << *first_county->getResidents()[i] << endl;    
    // }



    /* Main program */
    main_menu();

    return 0;
}