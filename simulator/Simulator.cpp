#include "Simulator.h"
#include "Vehicle.h"

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <iomanip>


using namespace std;


int Int_random(int min, int max){

	int i= min+rand() % (max-min+1);              //Random int number generation
	return i;
}

int Double_random(double min, double max){         //Random double number generation

	double j= min+(max-min) * ((double) rand() / RAND_MAX);
	return j;
}

double Dist(int speed, int duration){ //Distance calculation with conversion of minutes to hours

	double d= speed*(duration/60);
	return d;

}

Interval Gen_int(){                   //random speed range generation

	Interval v;
	v.speed=Int_random(V_min, V_max);
	v.duration=Int_random(D_min, D_max);
	return v;
}

void Gen_profile(Profile &p, double dist){   //Speed profile generation

	double distTraveled = 0.0;
	p.num_int = 0;
    
    while(distTraveled < dist && p.num_int < Max_int){  //Check the distance covered and the number of intervals allowed
    Interval h = Gen_int();
    double d = Dist(h.speed, h.duration);

    if(distTraveled + d > dist){ 

    	d = dist-distTraveled;                        //Reduces the distance to the missing value
    	h.duration = (int)((d/h.speed) * 60.0);

    }

    p.intervals[p.Num_int] = h;     //Range entered in the profile
    p.Num_int++;

    distTraveled += d;

    }
}

Vehicle Gen_v(double dist, int numSv, double t_start){  //Vehicle generation

	Vehicle v;
	
	v.makePlate();
 
	v.Sv_in = Int_random(0, numSv-2);             //Ingresso e uscita in uno svincolo casuale
	v.Sv_out = Int_random(v.Sv_in +1, numSv - 1);

	v.T_in = t_start;

	Gen_profile(v.profile, dist);

	return v;


}

void Run(const Vehicle &v, ofstream &file){        //Print generated vehicles to file

	file << "<" << v.plate << "> "
	     << "<" << v.Sv_in << "> "
	     << "<" << v.Sv_out << "> "
	     << fixed << setprecision(2) << "<" << v.T_in << "> ";


	for(int i=0; i < v.profile.Num_int; i++){

		file << "<"
	       << v.profile.intervals[i].speed << " "
			 << v.profile.intervals[i].duration << ">";


	    if(i < v.profile.Num_int - 1)
	    	file << ",";
    
    }

    file << endl;
}
