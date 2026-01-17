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

void gen_profile(Profile &p, double dist_tot){   //Speed profile generation

	double dist_travelled = 0.0;
	p.num_range = 0;
    
    while(dist_travelled < dist_tot && p.num_range < max_int){    //Check the distance covered and the number of intervals allowed
    Interval h = gen_int();
    double d = dist(h.speed, h.duration);

    if(dist_travelled + d > dist_tot){ 

    	d = dist_tot-dist_travelled;                        //Reduces the distance to the missing value
    	h.duration = (int)((d/h.speed) * 60.0);

    }

    p.intervals[p.num_range] = h;     //Range entered in the profile
    p.num_range++;

    dist_travelled += d;

    }
}

Sim_vehicle gen_v(double dist_tot, int num_junction, double t_start){    //Vehicle generation

	Sim_vehicle sv;
 
	sv.junction_in = int_random(0, num_junction-2);             //Entrance and exit at a random junction
	sv.junction_out = int_random(sv.junction_in +1, num_junction - 1);

	sv.time_in = t_start;

	gen_profile(sv.profile, dist_tot);

	return sv;


}

void run(const Sim_vehicle &v, ofstream &file){        //Print generated vehicles to file

	file << "<" << v.vehicle.get_plate() << "> "
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

void passage(const Sim_vehicle &v, const Highway& highway, ofstream &file){  //Print the crossing passages to a file

	double time = v.time_in;
	double dist_travelled = 0.0;

	const auto& gantries = highway.get_gantries();    //Tutti i varchi/svincoli nell'autostrada
	const auto& junctions = highway.get_junctions();  

	double dist_in = junctions[v.junction_in].get_dist();   //Distanza reale dell'ingresso/uscita del veicolo
	double dist_out = junctions[v.junction_out].get_dist();

	int v_range = 0;
	double dist_remaining = (v.profile.num_range > 0) ?           //Distanza mancante nell'intervallo
	                        dist(v.profile.intervals[0].speed,
	                        	 v.profile.intervals[0].duration)
	                        :0.0;

	for(const Gantry& g : gantries){         //Calcolo distanza dall'ingresso per ogni varco

		double g_dist = g.get_dist();

		
		if(g_dist <= dist_in || g_dist >= dist_out)    //Salta i varchi fuori dal percorso
			continue;

		
		double dist_to_gantry = g_dist - dist_in;


		while(dist_travelled + dist_remaining < dist_to_gantry){

			dist_travelled += dist_remaining;
			time += (dist_remaining / v.profile.intervals[v_range].speed) * 3600.0;

			v_range++;

			if(v_range >= v.profile.num_range)
				return;

			dist_remaining = (v.profile.intervals[v_range].speed *
				              v.profile.intervals[v_range].duration)
							  /60.0;
		}

		double dist_missed =dist_to_gantry - dist_travelled; 
	    double delta_time = (dist_missed / v.profile.intervals[v_range].speed) * 3600.0;
	    double passage_time = time + delta_time;

	
	    Passage p(g, v.vehicle, passage_time);
        file << p.get_passage() << endl;


     }
}


		
		




















