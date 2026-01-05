// Autore : Paolo Gasparato
#include "Gantry.h"

Gantry::Gantry(const double& gantry_dist, const int& gantry_id) : gantry_dist(gantry_dist), gantry_id(gantry_id) {}

double Gantry::getDist() const{
	return gantry_id;                                 // fornisce la distanza in km dall'inizio
}

int Gantry::getId() const{
	return gantry_id;                                   // fornisce il # del varco
}
