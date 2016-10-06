void change_sector()
{
	SECTOR ++;
	if(SECTOR == 7) SECTOR = 1;
	
	cout << " Sector set to: " << SECTOR << endl;
}



void print_all()
{
	PRINT = "jpg";
	
	show_vertex();
	show_2D_vertex();
	
	PRINT = "";
}

