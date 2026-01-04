// Autore:

#include "Passage.h"

//Passage::Passage(){}

Passage::Passage(Gantry g; Vehicle v; double pt){
    gantry=g;
    vehicle=v;
    passage_time=pt;
}

std::string Print::Passage() const {
    return gantry.getId() + " " + vehicle.getPlate() + " " + passage_time;
}
