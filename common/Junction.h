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
		double get_junction_dist() const;	
		int get_junction_num() const;
};
#endif

