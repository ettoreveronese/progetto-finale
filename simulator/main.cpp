//Autore: Polo Tommaso
#include <iostream>
#include <ctime>
#include <fstream>

#include "Simulator.h"
#include "Vehicle.h"
#include "Highway.h"
#include "Junction.h"

using namespace std;

int main(){

	srand(time(NULL));

	const double dist_tot = 130;

	Highway highway;
	
	try{
		highway.load_highway_data("Data/highway.txt");
	
	}catch (runtime_error &e){

		cout << "Errore caricamento highway: " << e.what << endl;
		return 1;
	}

    Vehicle vehicles[num_vehicles];
	
	ofstream run_file("Data/Runs.txt");

	if(!run_file.in_open()){

		cout<< "Errore apertura file Runs.txt" << endl;
		return 1;
	
	 }

	double current_time = 0.0;
	
	for (int i = 0; i < num_vehicles; i++){

		vehicles[i] = gen_v(0.0, num_junctions, current_time);

		int in = vehicles[i].junction_in;
		int out = vehicles[i].junction_out;

		double dist_tot = highway.get_junctions() [out].get_dist() - highway.get_junctions() [in].get_dist()

		gen_profile(vehicles[i].profile, dist_tot);

		run(vehicles[i], run_file);
		
		current_time += double_random(range_min, range_max);

	}

	run_file.close();
	
	ofstream pass_file("Data/Passages.txt");
	
	if(!pass_file.is_open()){
		cout<< "Errore apertura file Passages.txt" << endl;
		return 1;
	}

	for(int i = 0; i < num_vehicles; i++){
		passage(vehicles[i], pass_file, dist_tot);
	}
	
	pass_file.close();
	
	cout<< "Simulazione completata!"  << endl;
	return 0;

}








