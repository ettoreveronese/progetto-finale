// Autore : Paolo Gasparato
#ifndef JUNCTION_H
#define JUNCTION_H
	
class Junction{
private: 
	int junction_id;			  // # dello svincolo
	double dist;				  // distanza (in km)
public:
	Junction(const int& junction_id, const double& dist);
	int getJunctionId() const;
	double getDist() const;
};
#endif

