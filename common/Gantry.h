// Autore : Paolo Gasparato
// La classe rappresenta un varco

#ifndef GANTRY_H
#ifndef GANTRY_H
class Gantry{
private:
	int id;				        // # del varco
	double dist;				// distanza (in km)
public:
	Gantry(const int& id, const double& dist);
	int getId() const;
	double getDist() const;
};
#endif
