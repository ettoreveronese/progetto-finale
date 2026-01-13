// Autore : Paolo Gasparato
#include "Gantry.h"

Gantry::Gantry(const double& gantry_dist, const int& gantry_id) : gantry_dist(gantry_dist), gantry_id(gantry_id) {}

double Gantry::get_dist() const{
	return gantry_dist;                                 // fornisce la distanza in km dall'inizio
}

int Gantry::get_id() const{
	return gantry_id;                                   // fornisce il # del varco
}
