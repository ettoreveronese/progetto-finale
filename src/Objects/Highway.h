// Autore : Paolo Gasparato

#ifndef HIGHWAY_H
#define HIGHWAY_H

#include <string>
#include <vector>
#include "Gate.h"
#include "Junction.h"

class Highway{
private:
	std::vector<Gate> gates;
	std::vector<Junction> junctions;
	
	void isValid() const;			// check all the constraints (at least 2 junctions,#gate=#junction,...)
public:
	void loadFromFile(const std::string& file);      // take the input from the .txt file (random)
	const std::vector<Gate>& getGates() const;
	const std::vector<Gate>& getGates() const;
}
#endif

//DA FINIRE 
