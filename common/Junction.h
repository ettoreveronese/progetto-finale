// Autore : Paolo Gasparato
// La classe rappresenta uno svincolo

#ifndef JUNCTION_H
#define JUNCTION_H
class Junction{
private:
	double junction_dist;				// distanza (in km)
	int junction_num;				    // # dello svincolo
public:
	Junction(const double& junction_dist, const int& junction_num);
		double get_junction_dist() const;	
		int get_junction_num() const;
};
#endif


