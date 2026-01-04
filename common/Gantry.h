// Autore : Paolo Gasparato
// La classe rappresenta un varco

#ifndef GANTRY_H
#define GANTRY_H
class Gantry{
private:
	double dist_gantry;				// distanza (in km)
	int num_gantry;				    // # del varco
public:
	Gantry(const double& dist_gantry, const int& num_gantry);
		double getDist() const;	
		int getNum() const;
};
#endif
