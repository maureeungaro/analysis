#include"parameters.h"


void activate_PRINT()
{
    if (is_simulation) {
        PRINT = SIM_PRINT;
    } else {
        PRINT = DATA_PRINT;
    }
    VertexCS->set_print(PRINT);
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

    VertexCS->show_vertex();
    VertexCS->show_2D_vertex();
	
	PRINT = "none";
}

void print_all_message() {
    cout << " > To print all histos see README " << endl;
}
