// Autore : Paolo Gasparato
#include "Gantry.h"

Gantry::Gantry(const double& gantry_dist, const int& gantry_num) : gantry_dist(gantry_dist), gantry_num(gantry_num) {}

double Gantry::get_dist() const{
	return gantry_dist;                                 // fornisce la distanza in km dall'inizio
}

int Gantry::get_num() const{
	return gantry_num;                                   // fornisce il # del varco
}
