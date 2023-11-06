#include"parameters.h"

void activate_PRINT()
{
    EKinnCorrCS->set_print(DATA_PRINT);
}


void switch_print() {
    if ( PRINT == "none") {
        activate_PRINT();
    } else {
        PRINT = "none";
    }

    cout << " > PRINT set to  " << PRINT << endl;
}


void show_1d_each_sector(int what)
{
    activate_PRINT();

    for (int s = 0; s < 6; s++) {
        SECTOR = s + 1;
        EKinnCorrCS->show_1D_each_sector(SECTOR, what);
    }

    PRINT = "none";
}


void print_all()
{
    activate_PRINT();

    for (int w=0; w<4; w++) {
        show_1d_each_sector(w);
    }

    PRINT = "none";
}

void print_all_message() {
    cout << " > To print all histos see README " << endl;
}

void change_sector() {
    SECTOR++;
    if (SECTOR == 7) SECTOR = 1;

    cout << " Sector set to: " << SECTOR << endl;
}
