// Autore

#include "Tutor.h"
#include "Gantry.h"
#include "Vehicle.h"
#include "passages.h"

#include <iostream>
#include <fstream>
#include <stdexcept>

static void parsePassagesData(std::stack<Passages> passages, string p_file_path){
    std::ifstream p_file(p_file_path);
    if (!p_file.is_open()){
        throw "invalid argument: couldn't read passages.txt";
    }
    
    int gantry_id;
    std::string plate;
    double time;
    
    while (p_file >> gantry_id >> plate >> time){
        Gantry gantry(gantry_id);
        Vehicle vehicle(plate);
        Passage p(gantry, vehicle, time);
        passages.push(p);
    }
}

Tutor::Tutor(std::string p_data_path) time(0){
    parsePassagesData(passages, p_data_path);
}

std::string Tutor::setTime(double time_interval){
    if (time<=0){
        throw "invalid argument";
    }
    
    time += time_interval;
    
    std::string infractions;

    return infractions;
}



