// Autore : Paolo Gasparato
#include "Junction.h"

Junction::Junction(const double& junction_dist, const int& junction_num) : junction_dist(junction_dist), junction_num(junction_num) {}

double Junction::get_junction_dist() const{
	return junction_dist;                                 // fornisce la distanza in km dall'inizio
}

int Junction::get_junction_num() const{
	return junction_num;                                   // fornisce il # del varco
}


