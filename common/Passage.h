// Autore:

#ifndef PASSAGE_H
#define PASSAGE_H

#include "Gantry.h"
#include "Vehicle.h"

class Passage {
private:
    Gantry gantry;
    Vehicle vehicle;    
    Double passage_time;

public:
    //Passage();
    Passage(Gantry g; Vehicle v; Double pt);
    String getPassage() const;
};

#endif
