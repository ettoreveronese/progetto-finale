// Autore : Paolo Gasparato

#include <fstream>
#include <stdexcept>
#include <cmath>
#include <algorithm>
#include <iostream>
#include "Highway.h"

void Highway::load_highway_data(const std::string& data_h){        // da leggere nel main
	
	std::ifstream data(data_h);

	if(!data.is_open()){                          //prova ad aprire il file
		throw std::runtime_error("Error");        //se non viene aperto lancia un errore
	}
	
	int gantry_id = 0;                          
	int junction_id = 0;        
	double km;			               // <distanza in km>
	char type;			              // <V|S per Varco o Svincolo>

	while(data >> km >> type){				// == while(data.hasNext()) ...

		if(km<0){
			throw std::runtime_error("Non valgono distanze negative");
		}
		
        std::cout << km;

		if(type=='S'){
			junctions.push_back(Junction(0, km));    //inserisce nell'apposito vettore lo svincolo (aumenta di 1 il #)
		}
		else if(type=='V'){
			gantries.push_back(Gantry(0, km));    //inserisce nell'apposito vettore il varco (aumenta di 1 il #)	
		}
		else{
			throw std::runtime_error("Errore, inserire un type valido");		
		}
	}

	std::sort(gantries.begin(), gantries.end(),			// ordina i varchi, distanza crescente
          [](const Gantry& a, const Gantry& b){				// usato anche in altre parti del progetto sotto consiglio del mio compagno Ettore, molto utile
              return a.get_dist() < b.get_dist();
          });

	std::sort(junctions.begin(), junctions.end(),   		// ordina gli svincoli, distanza crescente
          [](const Junction& a, const Junction& b){
              return a.get_dist() < b.get_dist();
          });
	
	for (int i = 0; i < gantries.size(); ++i){
    	gantries[i] = Gantry(i+1, gantries[i].get_dist());
	}

	for (int j = 0; j < junctions.size(); ++j){
   		 junctions[j] = Junction(j+1, junctions[j].get_dist());
	}

	is_valid();
}

void Highway::is_valid() const{

	if(gantries.size()<2){
		throw std::runtime_error("Errore, ci devono essere almeno 2 varchi"); 		// devono essere presenti almeno 2 varchi
	}

	
	int v = 0; 		// indice varchi
    int s = 0; 		// indice svincoli

    while (v < gantries.size() && s < junctions.size()) {
        	double abs_dist = std::abs(gantries[v].get_dist() - junctions[s].get_dist());		// posso usarlo avendo ordinato i rispettivi vettori in ordine crescente di distanza
            
            std::cout << gantries[v].get_dist() << " - " << junctions[s].get_dist() << " = " << abs_dist << "  \n";
        	if (abs_dist < 1.0) {									// distanza assoluta per evitare errori
            		throw std::runtime_error("Errore, distanza minima: 1km");				// controlla che la distanza minima tra varco e svincolo sia 1km
        	}														// (complessità temporale migliorata dopo aver ordinato i vettori)

       		if (gantries[v].get_dist() < junctions[s].get_dist()) {			// aumento del varco o svincolo di distanza minima tra i due in caso ci siano ripetizioni (ad es. 2 varchi di fila prima di uno svincolo)
            		++v;
        	} else {
            		++s;
        	}
    	}

	int num_gantry = gantries.size();
	int num_junctions = junctions.size();

	double first_gantry_dist = gantries[0].get_dist();					// grazie all'ordinamento per distanza usato precedentemente
	double first_junction_dist = junctions[0].get_dist();

	if(first_gantry_dist <= first_junction_dist){				// posso usarlo avendo ordinato i rispettivi vettori in ordine crescente di distanza
		throw std::runtime_error("Errore, ci deve essere uno svincolo prima di un varco");   			// controlla che prima di un varco ci sia uno svincolo
	}			
	
	double last_gantry_dist = gantries[num_gantry - 1].get_dist();
	double last_junction_dist = junctions[num_junctions - 1].get_dist();

	if(last_gantry_dist >= last_junction_dist){				// posso usarlo avendo ordinato i rispettivi vettori in ordine crescente di distanza
		throw std::runtime_error("Errore, dopo l'ultimo varco ci deve essere uno svincolo");   			// controlla che dopo l'ultimo varco ci sia uno svincolo
	}													
}

const std::vector<Gantry>& Highway::get_gantries() const{
	return gantries;
}

const std::vector<Junction>& Highway::get_junctions() const{
	return junctions;
}






