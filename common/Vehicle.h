// autore: ettore veronese

#ifndef VEHICLE_H
#define VEHICLE_H

#include <string>

class Vehicle {
private:
    const std::string plate;

public:
    Vehicle();                                  // generate a new plate if none is given
    explicit Vehicle(const std::string& p);
    
    const std::string& get_plate() const;       // returns the plate of the current vehicle
    static std::string make_plate();     // returns a newly generated plate
    
    // returns true if the given plate is valid
    static bool is_valid_plate(const std::string& plate);    
};


#endif
