// Autore: Ettore Veronese

#include "Vehicle.h"

#include <stdexcept>
#include <random>
#include <cctype>

static bool isCapitalLetter(char c){ return c>='A' && c<='Z'; }
static bool isNumber(char c){ return c>='0' && c<='9'; }

Vehicle::Vehicle(){ plate = make_plate(); }

Vehicle::Vehicle(const std::string& p){
    if (is_valid_plate(p)){   // if given plate not valid throw an error
        plate = p;
    } else {
        throw std::invalid_argument("Invalid plate");
    }
} 

const std::string& Vehicle::get_plate() const {
    return plate;
}

std::string Vehicle::make_plate() const {
    std::string new_plate;
    
    std::random_device rd;
    std::mt19937 gen(rd());
    
    // generate random chars in the specified intervals
    std::uniform_int_distribution<> cDist('A', 'Z');
    std::uniform_int_distribution<> iDist('0', '9');

    for (int i=0; i<2; i++){ new_plate+=cDist(gen); }   // add 2 capital letters
    for (int i=0; i<3; i++){ new_plate+=iDist(gen); }   // add 3 integers
    for (int i=0; i<2; i++){ new_plate+=cDist(gen); }   // add 2 capital letters

    return new_plate;
}

static bool Vehicle::is_valid_plate(const std::string& plate) const {
    if (plate.size() != 7){ return false; }     // if size != 7 it can't be a number plate
    
    // check if the format is correct
    for (int i=0; i<2; i++){
       if (!isCapitalLetter(plate[i])){ return false; } 
    }
    for (int i=2; i<5; i++){
        if (!isNumber(plate[i])){ return false; }
    }
    for (int i=5; i<7; i++){
       if (!isCapitalLetter(plate[i])){ return false; } 
    }

    return true;
}
