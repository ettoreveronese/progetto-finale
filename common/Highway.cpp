// Autore : Paolo Gasparato

#include <fstream>
#include <stdexcept>
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
		if(type=='V'){
			gantries.push_back(Gantry(++gantry_id, km));    //inserisce nell'apposito vettore il varco (aumenta di 1 il #)
		}
		else{
			throw std::runtime_error("Error");		
		}
	}
}

void Highway::isValid(){
	
}
