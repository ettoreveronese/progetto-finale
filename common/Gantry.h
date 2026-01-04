// Autore : Paolo Gasparato
// La classe rappresenta un varco

#ifndef GANTRY_H
#ifndef GANTRY_H
class Gantry{
private:
	double dist_gantry;				// distanza (in km)
	int num_gantry;				    // # del varco
public:
	Gantry(const int& num_gantry, const double& dist_gantry);
	int getId() const;
	double getDist() const;
};
#endif
