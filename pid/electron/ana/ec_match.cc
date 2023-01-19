#include "ec_match.h"

// constructor using chisto and cpars
EC_Match::EC_Match(chistos *common_histo, cpars *common_pars, string P, const Color_t c[4]) {
    H = common_histo;
    Pars = common_pars;
    PRINT = P;
    for(int cc=0; cc<4; cc++) {
        colors[cc] = c[cc];
    }


}
