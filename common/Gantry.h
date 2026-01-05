// Autore : Paolo Gasparato
// La classe rappresenta un varco

#ifndef GANTRY_H
#define GANTRY_H
class Gantry{
private:
	double gantry_dist;				// distanza (in km)
	int gantry_id;				    // # del varco
public:
	Gantry(const double& gantry_dist, const int& gantry_id);
		double getDist() const;	
		int getId() const;
};
#endif
