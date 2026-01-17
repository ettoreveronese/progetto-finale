// Autore : Paolo Gasparato
// La classe rappresenta uno svincolo

#ifndef JUNCTION_H
#define JUNCTION_H
class Junction{
private:
	double junction_dist;				// distanza (in km)
	int junction_id;				    // # dello svincolo
public:
	Junction(const int& junction_id. const double& junction_dist);
		double get_dist() const;	
		int get_id() const;
};
#endif





