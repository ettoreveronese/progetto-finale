// Autore : Paolo Gasparato
// La classe rappresenta un varco

#ifndef GANTRY_H
#ifndef GANTRY_H
class Gantry{
private:
	int id;				        // # of the gantry
	double dist;				// distance measured in km
public:
	Gate(const int& gantry_id, const double& dist);
	int getId() const;
	double getDist() const;
};
#endif
