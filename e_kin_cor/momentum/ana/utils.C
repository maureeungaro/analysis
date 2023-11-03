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



void print_all()
{
    activate_PRINT();

    EKinnCorrCS->show_vertex();

    PRINT = "none";
}

void print_all_message() {
    cout << " > To print all histos see README " << endl;
}
