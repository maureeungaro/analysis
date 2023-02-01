#include"parameters.h"

void activate_PRINT()
{
    if (is_simulation) {
        PRINT = SIM_PRINT;
    } else {
        PRINT = DATA_PRINT;
    }
    TOFMatch->set_print(PRINT);
}


void switch_print() {
    if ( PRINT == "none") {
        activate_PRINT();
    } else {
        PRINT = "none";
    }

    cout << " > PRINT set to  " << PRINT << endl;
}


void change_sector()
{
    SECTOR++;
    if(SECTOR == 7) SECTOR = 1;

    cout << " Sector set to: " << SECTOR << endl;
}


void print_dt_vs_mom() {

    activate_PRINT();

    for (int s = 0; s < 6; s++) {
        SECTOR = s + 1;
        TOFMatch->fit_and_calculate_pars(H->dt_momz[SECTOR-1], H->dt_mom[SECTOR-1], SECTOR);
        TOFMatch->show_dt_vs_mom(SECTOR);

        // dt slices
        for (int b = 0; b < TOF_Match::NDIV; b++) {
            TOFMatch->DrawFit(s, b);
        }
    }

    TOFMatch->show_dt_vs_mom_all_sectors();

}

void print_mass_and_beta() {

    activate_PRINT();

    for (int s = 0; s < 6; s++) {
        SECTOR = s + 1;
        TOFMatch->show_mass_and_beta(SECTOR);
    }

    TOFMatch->show_mass_and_beta_all_sectors();

}

void print_all()
{

//    print_dt_vs_mom();
    print_mass_and_beta();
	
	PRINT = "none";

}

