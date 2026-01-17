// Autore : Paolo Gasparato
#include "Junction.h"

Junction::Junction(const int& junction_id, const double& junction_dist) : junction_id(junction_id), junction_dist(junction_dist) {}

double Junction::get_dist() const{
	return junction_dist;                                 // fornisce la distanza in km dall'inizio
}

int Junction::get_id() const{
	return junction_id;                                   // fornisce il # del varco
}





