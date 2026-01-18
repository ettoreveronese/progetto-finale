// Autore : Paolo Gasparato
// La classe rappresenta un varco

#ifndef GANTRY_H
#define GANTRY_H
class Gantry{
private:
	double gantry_dist;				// distanza (in km)
	int gantry_id;				    // # del varco

public:
	Gantry(const int& gantry_id, const double& gantry_dist);
	double get_dist() const;	
	int get_id() const;
};
#endif
