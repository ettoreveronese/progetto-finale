// Autore : Paolo Gasparato
// La classe rappresenta un varco

#ifndef GANTRY_H
#define GANTRY_H
class Gantry{
private:
	double gantry_dist;				// distanza (in km)
	int gantry_num;				    // # del varco
public:
	Gantry(const double& gantry_dist, const int& gantry_num);
		double get_gantry_dist() const;	
		int get_gantry_num() const;
};
#endif
