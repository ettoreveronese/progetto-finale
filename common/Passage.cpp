// Autore:

#include "Passage.h"

//Passage::Passage(){}

Passage::Passage(Gantry g; Vehicle v; Double pt){
    gantry=g;
    vehicle=v;
    passage_time=pt;
}

String Print::Passage() const {
    return gantry.getId() + " " + vehicle.getPlate() + " " + passage_time;
}
