// Autore : Paolo Gasparato

#ifndef VEHICLE_H
#define VEHICLE_H

#include <string>

class Vehicle {
private:
    std::string plate;

public:
    Vehicle();                                  // crea una nuova targa (se non ne esiste una)
    explicit Vehicle(const std::string& p);
    
    const std::string& get_plate() const;       // restituisce la targa
    static std::string make_plate();     // restituisce una nuova targa
    
    static bool is_valid_plate(const std::string& plate);    // controllo validità della targa
};
#endif
