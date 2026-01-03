// Autore : Paolo Gasparato
#include "Junction.h"

Junction::Junction(const int& junction_id, const double& dist) : junction_id(junction_id), dist(dist) {}

int Junction::getId() const{
	return junction_id;
}

double Junction::getDist() const{
	return dist;
}
