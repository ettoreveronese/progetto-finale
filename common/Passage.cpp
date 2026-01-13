// autore: ettore veronese

#include "Passage.h"

//Passage::Passage(){}

Passage::Passage(const Gantry& g; const Vehicle& v; const double& t) : gantry(g), vehicle(v), timestamp(t) {}

const Gantry& Passage::get_gantry(){ return gantry; }
const Vehicle& Passage::get_vehicle(){ return vehicle; }
double get_timestamp(){ return timestamp; }

std::string Passage::Passage() const {
    return gantry.getId() + " " + vehicle.get_plate() + " " + get_timestamp();
}
