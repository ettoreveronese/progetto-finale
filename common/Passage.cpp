// Autore : Paolo Gasparato

#include "Gantry.h"
#include "Passage.h"
#include "Vehicle.h"

//Passage::Passage(){}

Passage::Passage(const Gantry& g, const Vehicle& v, const double t) : gantry(g), vehicle(v), timestamp(t) {}

const Gantry& Passage::get_gantry() const { return gantry; }
const Vehicle& Passage::get_vehicle() const { return vehicle; }
double Passage::get_timestamp() const { return timestamp; }

std::string Passage::get_passage() const {
    return std::to_string(gantry.get_id()) + " " + vehicle.get_plate() + " " + std::to_string(timestamp);
}
