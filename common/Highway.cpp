// Autore : Paolo Gasparato

#include <fstream>
#include <stdexcept>
#include <cmath>
#include "Highway.h"

void Highway::loadHighwayData(const std::string& data_h){        // da leggere nel main
	
	std::ifstream data(data_h);

	if(!data.is_open()){                          //prova ad aprire il file
		throw std::runtime_error("Error");        //se non viene aperto lancia un errore
	}
	
	int gantry_id = 0;                          
	int junction_id = 0;        
	double km;			               // <distanza in km>
	char type;			              // <V|S per Varco o Svincolo>

	while(data >> km >> type){				// == while(data.hasNext()) ...
		if(type=='S'){
			junctions.push_back(Junction(++junction_id, km));    //inserisce nell'apposito vettore lo svincolo (aumenta di 1 il #)
		}
		else if(type=='V'){
			if(junctions.size()==0){
				throw std::runtime_error("Error");	// controlla che prima del primo varco ci sia almeno uno svincolo
			} else {
			gantries.push_back(Gantry(++gantry_id, km));    //inserisce nell'apposito vettore il varco (aumenta di 1 il #)
			}
		}
		else{
			throw std::runtime_error("Error");		
		}
	}
	isValid();
}

void Highway::isValid() const{

	if(gantries.size()<2){
		throw std::runtime_error("Error"); 		// devono essere presenti almeno 2 varchi
	}

	int gantry_size = gantries.size();
	int junction_size = junctions.size();

	double lastGantryDist = gantries[gantry_size-1].getGantryDist();
	double lastJunctionDist = junctions[junction_size-1].getJunctionDist();

	if(lastGantryDist > lastJunctionDist){
		throw std::runtime_error("Error");				// controlla che l'ultimo type (per distanza) sia uno svincolo quindi che ci sia uno svincolo dopo l'ultimo varco
	}
	
	
	if(gantry_size > junction_size){
		for(int i=0; i<junction_size; ++i){
			for(int j=0; j<gantry_size; j++){	
				double temp_dist = std::abs(gantries[j].getGantryDist() - junctions[i].getJunctionDist());    	// controlla che la distanza tra varco e svincolo sia almeno 1km
				if(temp_dist < 1.0) {
					throw std::runtime_error("Error");
				}
			}
		}
	} 
	else if(junction_size > gantry_size){
		for(int i=0; i<gantry_size; ++i){
			for(int j=0; j<junction_size; j++){	
				double temp_dist = std::abs(gantries[i].getGantryDist() - junctions[j].getJunctionDist());    	// controlla che la distanza tra varco e svincolo sia almeno 1km
				if(temp_dist < 1.0) {
					throw std::runtime_error("Error");
				}
			}
		}
	}
}
