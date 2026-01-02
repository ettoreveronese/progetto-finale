// Autore: Ettore Veronese

#ifndef VEHICLE_H
#define VEHICLE_H

#include <string>

class Vehicle {
private:
    const std::string plate;

public:
    Vehicle();                                          // generate a new plate if none is given
    explicit Vehicle(const std::string& p);
    
    const std::string& getPlate() const;                // returns the plate of the current vehicle
    std::string makePlate() const;                      // returns a newly generated plate
    bool isValidPlate(const std::string& plate) const;  // returns true if the given plate is valid    
};


#endif
