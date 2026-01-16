//Autore: Polo Tommaso
#include "Simulator.h"
#include "Vehicle.h"
#include "Gantry.h"
#include "Passage.h"

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <iomanip>


using namespace std;


int int_random(int min, int max){

	int i= min+rand() % (max-min+1);              //Random int number generation
	return i;
}

double double_random(double min, double max){         //Random double number generation

	double j= min+(max-min) * ((double) rand() / RAND_MAX);
	return j;
}

double dist(int speed, int duration){           //Distance calculation with conversion of minutes to hours

	double d= speed*(duration/60.0);
	return d;

}

Interval gen_int(){                   //random speed range generation

	Interval v;
	v.speed=int_random(v_min, v_max);
	v.duration=int_random(d_min, d_max);
	return v;
}

void gen_profile(Profile &p, double dist){   //Speed profile generation

	double dist_travelled = 0.0;
	p.num_range = 0;
    
    while(dist_travelled < dist && p.num_range < max_int){    //Check the distance covered and the number of intervals allowed
    Interval h = gen_int();
    double d = dist(h.speed, h.duration);

    if(dist_travelled + d > dist){ 

    	d = dist-dist_travelled;                        //Reduces the distance to the missing value
    	h.duration = (int)((d/h.speed) * 60.0);

    }

    p.intervals[p.num_range] = h;     //Range entered in the profile
    p.num_range++;

    dist_travelled += d;

    }
}

Sim_vehicle gen_v(double dist, int num_junction, double t_start){    //Vehicle generation

	Sim_vehicle sv;
 
	sv.junction_in = int_random(0, num_junction-2);             //Entrance and exit at a random junction
	sv.junction_out = int_random(sv.junction_in +1, num_junction - 1);

	sv.time_in = t_start;

	gen_profile(sv.profile, dist);

	return sv;


}

void run(const Sim_vehicle &v, ofstream &file){        //Print generated vehicles to file

	file << "<" << v.get_plate() << "> "
	     << "<" << v.junction_in << "> "
	     << "<" << v.junction_out << "> "
	     << fixed << setprecision(2) << "<" << v.time_in << "> ";


	for(int i=0; i < v.profile.num_range; i++){

		file << "<"
	       << v.profile.intervals[i].speed << " "
		   << v.profile.intervals[i].duration << ">";


	    if(i < v.profile.num_range - 1)
	    	file << ",";
    
    }

    file << endl;
}

void passage(const Sim_vehicle &v, ofstream &file, double distTot){  //Print the crossing passages to a file

	double time = v.time_in;
	double dist_travelled = 0.0;

	int num_pass = v.junction_out - v.junction_in;

	for(int k = 1; k <= num_pass; k++){

		double dist_pass = (dist_tot / num_pass) * k;             //Total distance from start to pass k
		double dist_missed =dist_pass - dist_travelled;           //Distance missing to reach pass k

		for(int i = 0; i < v.profile.num_range; i++){

			int speed = v.profile.intervals[i].speed;
			int duration = v.profile.intervals[i].duration;


			double dist_range = (speed *duration) /60.0;

			if(dist_missed <= dist_range){                           //Check if the pass is in this range

				double delta_time = (dist_missed / speed) * 3600.0;
				double passage_time = time + delta_time;

				Gantry g(dist_pass, v.junction_in + k);
				Passage p(g, v, passage_time);

				file << p.get_passage() << endl;
				break;
			
			} else{                        //If there are no pass, the missing distance, the distance travelled and the time are updated.

				dist_missed -= dist_range;
				dist_travelled += dist_range;
				time += duration *60.0;
			} 

		}
	}	
}













