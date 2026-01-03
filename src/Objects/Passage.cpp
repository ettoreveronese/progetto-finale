// Autore : Paolo Gasparato
#include "Gate.h"

Gate::Gate(const int& gate_id, const double& dist) : gate_id(gate_id), dist(dist) {}

int Gate::getGateId() const{
	return gate_id;
}

double Gate::getDist() const{
	return dist;
}
