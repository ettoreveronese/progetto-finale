// autore: ettore veronese

#ifndef PASSAGE_H
#define PASSAGE_H

#include "Gantry.h"
#include "Vehicle.h"

class Passage {
private:
    Gantry gantry;
    Vehicle vehicle;    
    double timestamp;

public: 
    //Passage();
    Passage(const Gantry& g, const Vehicle& v, const double t);
    
    const Gantry& get_gantry() const;
    const Vehicle& get_vehicle() const;
    double get_timestamp() const;
    
    std::string get_passage() const;
};

#endif
