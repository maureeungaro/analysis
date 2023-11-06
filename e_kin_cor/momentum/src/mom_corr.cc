// MU includes
#include "mom_corr.h"

// C++ includes
#include <sstream>
#include <fstream>
#include <cstdlib>

V4 mom_corr::m_corr(V4 x) {
    // DO NOT PERFORM CORRECTION IF OUTSIDE 14-30 DEGREES
    if (x.theta() / degree < 14 || x.theta() / degree > 30) return x;

    V4 y;
    double corr;
    double a, b, c, d;
    double theta = x.theta() / degree;
    double phi = loc_phi(x) / degree;
    int s = sector(x) - 1;

    a = b = c = d = 0;

    for (int p = 0; p < 10; p++) a = a + par_par_phi[s][0][p] * pow(theta, p);
    for (int p = 0; p < 10; p++) b = b + par_par_phi[s][1][p] * pow(theta, p);
    for (int p = 0; p < 10; p++) c = c + par_par_phi[s][2][p] * pow(theta, p);
    for (int p = 0; p < 10; p++) d = d + par_par_phi[s][3][p] * pow(theta, p);

    corr = (a + b * phi + c * phi * phi + d * phi * phi * phi) * GeV;

    y.x = (x.mod() + corr) * sin(x.theta()) * cos(x.phi());
    y.y = (x.mod() + corr) * sin(x.theta()) * sin(x.phi());
    y.z = (x.mod() + corr) * cos(x.theta());
    y.t = sqrt(y.mod() * y.mod() + electron_mass * electron_mass);

//	 cout << s+1 << " " << theta << " " << phi << "   a " <<  a << "     b " << b << "    c " << c << "     d " << d << "  COR " << corr << endl;

    return y;
}
