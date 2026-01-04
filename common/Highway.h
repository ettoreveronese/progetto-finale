// Autore : Paolo Gasparato

#ifndef HIGHWAY_H
#define HIGHWAY_H

#include <string>
#include <vector>
#include "Gantry.h"
#include "Junction.h"

class Highway{
private:
	std::vector<Gantry> gantries;				// vettore per i varchi
	std::vector<Junction> junctions;			// vettore per gli svincoli
	
	void isValid() const;			// controlla i vincoli (almeno 2 varchi, distanza minima di 1km,...)
public:
	void loadHighwayData(const std::string& h_data);      // prende i dati da Highway.txt (nel file main)
	const std::vector<Gantry>& getGantries() const;
	const std::vector<Junction>& getJunctions() const;
}
#endif

