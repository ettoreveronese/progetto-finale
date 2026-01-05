// autore: ettore veronese

#include "Tutor.h"
#include "Gantry.h"
#include "Vehicle.h"
#include "Passage.h"

#include <iostream>
#include <fstream> // ifstream??
#include <stdexcept>
#include <map>

// given the passages vector as reference and the path of passages.txt 
// it stores the data in passages.txt to the passages vector, sorted by time
static void parsePassagesData(std::vector<Passages>& passages, const string p_data_path){
    // open file     
    std::ifstream p_file(p_data_path);
    if (!p_file.is_open()){
        throw "invalid argument: couldn't read passages.txt";
    }
    
    int gantry_id;
    std::string plate;
    double time;
    
    // save to passages vector
    while (p_file >> gantry_id >> plate >> time){
        Gantry gantry(gantry_id);
        Vehicle vehicle(plate);
        Passage p(gantry, vehicle, time);
        
        passages.push_back(p);        
    }
    
    // sort the passages by time
    std::sort( passags.begin(), passages.end(), 
        [](const Passage& a, const Passage& b){ 
            return a.time < b.time;
        });

}

// TODO_ 
static std::vector<Report> computeViolations(){ // unfinished
    std::vector<Report> reports; 

    for (const auto& [plate, v_passage]: interval_passages){
        if (v_passage.size() <= 1){
            continue;
        }
        
        Passages first = v_passages[0];

        for (int i=1; i<v_passages.size(); i++){
            second = v_passages[i];
            
            double time_g2g = second.passage_time - first.passage_time();
            double dist = second.gantry.getDist() - first.gantry.getDist();
            double avg_speed = (dist / time_g2g) * 3600;  // x3600 converts to km/h 
            
            if (avg_speed > SPEED_LIMIT){   // if speeding create a report
                Report report(first.vehicle, first.gantry, second.gantry, avg_speed);
                reports.push_back(report);
            }

            first = second;
        }
    }
    return reports
}


Tutor::Tutor(const std::string p_data_path) {
    interval_index = 0;
    time_interval = 0;
    parsePassagesData(passages, p_data_path);
}

std::string Tutor::setTime(const double added_time){    // unfinished
    if (added_time<=0){   // can only add time to the interval, reset to roll back
        throw "invalid argument";
    }   
    
    // update time interval
    time_interval += added_time;

    // clear the passaged from the previous interval
    interval_passages.clear;
    
    // add passages within the interval to interval_passages
    while (interval_index<passages.size()){
        if (passages[i].passage_time <= time_interval){
            if (!interval_passages.insert(passages[i].plate, passages[i]).second){
                interval_passages[passages[i].plate].push_back(passages[i]);
            }
        } else {
            break;
        }
        interval_index++;
    }

    std::string infractions;
    return infractions;
}

std::string Tutor::getStats() const {
    
}

void Tutor::reset() {
    
}
