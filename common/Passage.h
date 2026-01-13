// Autore:

#ifndef PASSAGE_H
#define PASSAGE_H

#include "Gantry.h"
#include "Vehicle.h"

class Passage {
private:
    Gantry gantry;
    Vehicle vehicle;    
    double passage_time;

public:
    //Passage();
    Passage(Gantry g; Vehicle v; Double pt);
    std::string get_passage() const;
};

#endif
