#include"parameters.h"

void activate_PRINT()
{
    if (is_simulation) {
        PRINT = SIM_PRINT;
    } else {
        PRINT = DATA_PRINT;
    }
    Fiducial->set_print(PRINT);
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

void change_mom()
{
    MOM++;
    if(MOM == chistos::NDIV_P+1) MOM = 1;

    cout << " Momentum Bin set to: " << MOM << endl;
}

void change_plane()
{
    PLANE++;
    if(PLANE == 6) PLANE = 1;

    cout << " Plane set to: " << PLANE << endl;
}

void switch_logz()
{
    if(LOGZ==0) LOGZ = 1;
    else        LOGZ = 0;
}


void print_phi_theta()
{
    activate_PRINT();

    for(int s=0; s<6; s++) {
        SECTOR = s+1;
        for(int p=0; p<chistos::NDIV_P; p++) {
            MOM = p+1;
            Fiducial->show_phi_theta(SECTOR, MOM);
        }
        Fiducial->show_phi_thetas(SECTOR, 0);
        Fiducial->show_phi_thetas(SECTOR, 3);
    }

}

void print_phis()
{
    activate_PRINT();

    for(int s=0; s<6; s++) {
        SECTOR = s+1;
        for(int p=0; p<chistos::NDIV_P; p++) {
            MOM = p+1;
            Fiducial->show_phis(SECTOR, MOM, PLANE);
        }
        Fiducial->show_phi_thetas(SECTOR, 0);
        Fiducial->show_phi_thetas(SECTOR, 3);
    }

}


//{
//	for(int s=0; s<6; s++)
//	{
//		SECTOR = s+1;
//		for(int p=0; p<chistos::NDIV_P; p++)
//		{
//			MOM = p+1;
////
////			for(int pl=1; pl<6; pl++)
////			{
////				if(pl == 4) continue;
////				PLANE = pl;
////				show_plane();
////			}
//		}
////		for(int pl=1; pl<6; pl++)
////		{
////			if(pl == 4) continue;
////			PLANE = pl;
////			show_planes();
////			show_integrated_plane();
///*			for(int y=2; y<12; y++)
//			{
//				DrawFit(s, pl-1, y);
//			}*/
////		}
//	}



void print_all()
{
    cout << " > Printing all histograms " << endl;

    print_phi_theta();
    print_phis();

    PRINT = "none";
}





