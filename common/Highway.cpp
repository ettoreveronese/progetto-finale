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

	std::vector<double> gantry_dist;		// vettore con le distanze dei varchi
	std::vector<double> junction_dist;		// vettore con le distanze degli svincoli
	double km;			               // <distanza in km>
	char type;			              // <V|S per Varco o Svincolo>

	while(data >> km >> type){				// == while(data.hasNext()) ...

		if(km<0){
			throw std::runtime_error("Non valgono distanze negative");
		}
		
		if(type=='S'){
			junction_dist.push_back(km);    //inserisce nel vettore delle distanze dei varchi
		}
		else if(type=='V'){
			gantry_dist.push_back(km);    //inserisce nel vettore delle distanze degli svincoli
		}
		else{
			throw std::runtime_error("Errore, inserire un type valido");		
		}
	}

	std::sort(gantry_dist.begin(),gantry_dist.end());		// ordina il vettore delle distanze dei varchi
	std::sort(junction_dist.begin(),junction_dist.end());		// ordina il vettore delle distanze degli svincoli
	//ordinamento consigliato da Ettore

	for (int i = 0; i < gantry_dist.size(); ++i)
    	gantries.push_back(Gantry(i+1,gantry_dist[i]));

	for (int j = 0; j < junction_dist.size(); ++j)
    	junctions.push_back(Junction(j+1,junction_dist[j]));
	
	is_valid();
}

void Highway::is_valid() const{

    for (int i=0; i<gantries.size(); i++){
        std::cout << gantries[i].get_dist() << " ";
    }
    std::cout << "\n";
    for (int i=0; i<junctions.size(); i++){
        std::cout << junctions[i].get_dist() << " ";
    }

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


