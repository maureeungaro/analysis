#ifndef VERTEX_PARAMETERS_LOADED
#define VERTEX_PARAMETERS_LOADED

// histos and parameters
#include "../src/common_info.h"

// root
#include "TGraphErrors.h"

class Vertex_CS {

public:

    Vertex_CS();

    ~Vertex_CS();


    // constructor using chisto and cpars
    Vertex_CS(chistos *common_histo, cpars *common_pars, string P, bool is_sim) {


        H = common_histo;
        Pars = common_pars;
        PRINT = P;
        is_simulation = is_sim;

    }

    // set print
    void set_print(string P) { PRINT = P; }

    void show_vertex();

    void show_2D_vertex();


private:

    chistos *H;
    cpars *Pars;
    string PRINT;
    bool is_simulation = false;

    const int csize = 1200; // common canvas size


};

#endif