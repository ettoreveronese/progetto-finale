// Autore : Paolo Gasparato
// La classe rappresenta uno svincolo

#ifndef JUNCTION_H
#define JUNCTION_H
class Junction{
private:
	double dist_junction;				// distanza (in km)
	int num_junction;				    // # dello svincolo
public:
	Junction(const double& dist_junction, const int& num_junction);
		double getJunctionDist() const;	
		int getJunctionNum() const;
};
#endif
