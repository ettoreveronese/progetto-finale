// Autore : Paolo Gasparato
#include "Junction.h"

Junction::Junction(const double& dist_junction, const int& num_junction) : dist_junction(dist_junction), num_junction(num_junction) {}

double Junction::get_junction_dist() const{
	return dist_junction;                                 // fornisce la distanza in km dall'inizio
}

int Junction::get_junction_num() const{
	return num_junction;                                   // fornisce il # del varco
}

