// Autore : Paolo Gasparato
#ifndef GATE_H
#ifndef GATE_H

class Gate{
private:
	int gate_id;				// # of that gate
	double dist;				// distance measured in km
public:
	Gate(const int& gate_id, const double& dist);
	int getGateId() const;
	double getDist() const;
};
#endif
