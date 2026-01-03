// Autore : Paolo Gasparato
#ifndef JUNCTION_H
#define JUNCTION_H
	
class Junction{
private: 
	int junction_id;			// # of that junction
	double dist;				  // distance measured in km
public:
	Junction(const int& junction_id, const double& dist);
	int getJunctionId() const;
	double getDist() const;
};
#endif
