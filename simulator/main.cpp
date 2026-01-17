//Autore: Polo Tommaso
#include <iostream>
#include <ctime>
#include <fstream>

#include "Simulator.h"
#include "Vehicle.h"
#include "Highway.h"

using namespace std;

int main(){

	srand(time(NULL));

	Highway highway;

	try{
		highway.load_highway_data("./data/Highway.txt");          //Validity check of passages and junctions
	
	}catch (runtime_error &e){

		cout << "Errore caricamento highway: " << e.what() << endl;
		return 1;
	}

	int num_junctions = highway.get_junctions().size();

    Sim_vehicle vehicles[num_vehicles];
	
	ofstream run_file("./data/Runs.txt");

	if(!run_file.is_open()){                                      //Check opening file

		cout<< "Errore apertura file Runs.txt" << endl;
		return 1;
	
	 }

	double current_time = 0.0;
	
	for (int i = 0; i < num_vehicles; i++){              //Vehicle generation

		vehicles[i] = gen_v(0.0, num_junctions, current_time);

		int in = vehicles[i].junction_in;
		int out = vehicles[i].junction_out;

		double dist_tot = highway.get_junctions() [out].get_dist() - highway.get_junctions() [in].get_dist();   //Calculate the distance the vehicle will travel

		gen_profile(vehicles[i].profile, dist_tot);

		run(vehicles[i], run_file);               //Writes the requested information to the Runs.txt file
		
		current_time += double_random(range_min, range_max);

	}

	run_file.close();
	
	ofstream pass_file("./data/Passages.txt");
	
	if(!pass_file.is_open()){                                    //Check opening file
		cout<< "Errore apertura file Passages.txt" << endl;
		return 1;
	}

	for(int i = 0; i < num_vehicles; i++){
		
		passage(vehicles[i], highway, pass_file);       //Writes to the Passages.txt file the passages crossed by each vehicle
	}
	
	pass_file.close();
	
	cout<< "Simulazione completata!"  << endl;
	return 0;

}
















