// Autore : Paolo Gasparato
#include "Gantry.h"

Gantry::Gantry(const double& dist_gantry, const int& num_gantry) : dist_gantry(dist_gantry), num_gantry(num_gantry) {}

double Gantry::getDist() const{
	return dist_gantry;                                 // fornisce la distanza in km dall'inizio
}

int Gantry::getNum() const{
	return num_gantry;                                   // fornisce il # del varco
}
