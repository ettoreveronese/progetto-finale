// Autore : Paolo Gasparato
#include "Gantry.h"

Gantry::Gantry(const double& gantry_dist, const int& num_g) : id(gantry_id), dist(dist) {}

int Gantry::getId() const{
	return id;                                   // fornisce il # del varco
}

double Gantry::getDist() const{
	return dist;                                 // fornisce la distanza in km dall'inizio
}
