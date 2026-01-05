// Autore : Paolo Gasparato

#include <fstream>
#include <stdexcept>
#include <cmath>
#include <algorithm>
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

	std::sort(gantries.begin(), gantries.end(),			// ordina i varchi, distanza crescente
          [](const Gantry& a, const Gantry& b){				// usato anche in altre parti del progetto sotto consiglio del mio compagno Ettore, molto utile
              return a.getGantryDist() < b.getGantryDist();
          });

	std::sort(junctions.begin(), junctions.end(),   		// ordina gli svincoli, distanza crescente
          [](const Junction& a, const Junction& b){
              return a.getJunctionDist() < b.getJunctionDist();
          });

	isValid();
}

void Highway::isValid() const{

	if(gantries.size()<2){
		throw std::runtime_error("Error"); 		// devono essere presenti almeno 2 varchi
	}

	int num_gantry = gantries.size();
	int num_junctions = junctions.size();

	double lastGantryDist = gantries[num_gantry - 1].getGantryDist();
	double lastJunctionDist = junctions[num_junction- 1].getJunctionDist();

	if(lastGantryDist > lastJunctionDist){				// posso usarlo avendo ordinato i rispettivi vettori in ordine crescente di distanza
		throw std::runtime_error("Error");   			// controlla che dopo l'ultimo varco ci sia uno svincolo
	}													

	int v = 0; 		// indice varchi
    int s = 0; 		// indice svincoli

    while (v < gantries.size() && s < junctions.size()) {
        	double abs_dist = std::abs(gantries[v].getGantryDist() - junctions[s].getJunctionDist());		// posso usarlo avendo ordinato i rispettivi vettori in ordine crescente di distanza

        	if (abs_dist < 1.0) {									// distanza assoluta per evitare errori
            		throw std::runtime_error("Error");				// controlla che la distanza minima tra varco e svincolo sia 1km
        	}														// (complessità temporale migliorata dopo aver ordinato i vettori)

       		if (gantries[v].getGantryDist() < junctions[s].getJunctionDist()) {			// aumento del varco o svincolo di distanza minima tra i due in caso ci siano ripetizioni (ad es. 2 varchi di fila prima di uno svincolo)
            		++v;
        	} else {
            		++s;
        	}
    	}
}


