// Autore : Paolo Gasparato
#include "Gantry.h"

Gantry::Gantry(const int& gantry_id, const double& dist) : id(gantry_id), dist(dist) {}

int Gantry::getId() const{
	return id;                                   // fornisce il # del varco
}

double Gantry::getDist() const{
	return dist;                                 // fornisce la distanza in km dall'inizio
}
