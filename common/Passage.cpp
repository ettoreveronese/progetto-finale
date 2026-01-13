// autore: ettore veronese

#include "Passage.h"
#include "Vehicle.h"

//Passage::Passage(){}

Passage::Passage(const Gantry& g; const Vehicle& v; const double& t) : gantry(g), vehicle(v), timestamp(t) {}

const Gantry& Passage::get_gantry(){ return gantry; }
const Vehicle& Passage::get_vehicle(){ return vehicle; }
double get_timestamp(){ return timestamp; }

std::string Print::Passage() const {
    return gantry.get_id() + " " + vehicle.get_plate() + " " + passage_time;
}
