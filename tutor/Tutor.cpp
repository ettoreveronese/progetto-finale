// autore: ettore veronese

#include "Tutor.h"
#include "Gantry.h"
#include "Vehicle.h"
#include "Passage.h"
#include "Highway.h"

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <algorithm>

void Tutor::parse_highway_data(const std::string& filename){
    std::ifstream file(filename);
    if (!file.is_open()){
        throw "invalid argument: couldn't read passages.txt";
    }
    
    double dist;
    char type;
    std::vector<double> sorted_distances;

    while (file >> dist >> type){
        if (type == "V"){
           gantries_dist.push(dist);
        } else if (type == "S"){
            continue;
        } else {
            throw "invalid argument: couldn't correctly parse highway.txt "
        }
    }

    std::sort(gantries_dist.begin(), gantries_dist.end());

    for (int i=0; i<sorted_distances.size; i++){ 
        gantries.push_back(Gantry(sorted_distances[i], i));
    }
}

// given the passages vector as reference and the path of passages.txt 
// it stores the data in passages.txt to the passages vector, sorted by time
void Tutor::parse_passages_data(const std::string& filename){
    // open file     
    std::ifstream file(filename);
    if (!file.is_open()){
        throw "invalid argument: couldn't read passages.txt";
    }
    
    int gantry_id;
    std::string plate;
    double time;
    
    // save to passages vector
    while (file >> gantry_id >> plate >> time){
        Gantry gantry(gantry_id, gantry.at(i).get_dist());
        Vehicle vehicle(plate);
        Passage p(gantry, vehicle, time);
        
        passages.push_back(p);        
    }
    
    // sort the passages by time
    std::sort( passages.begin(), passages.end(), 
        [](const Passage& a, const Passage& b){ 
            return a.get_timestamp() < b.get_timestamp();
        });
}


Tutor::Tutor(const std::string& filename) {
    interval_index = 0;

    stats.time_interval = 0.0;
    stats.sanctioned = 0;
    stats.speed_sum = 0.0;
    stats.time_interval = 0.0;
    
    parsePassagesData(filename);
}

const std::vector<Report>& Tutor::set_time(const double time_increment){
    if (time_increment<=0){   // can only add time to the interval, reset to roll back
        throw "invalid argument";
    }   
    
    // update time interval
    time_interval += time_increment;

    // clear the passaged from the previous interval
    interval_passages.clear(); 
    
    // cicle through passages within the interval
    int& i = interval_index; 
    while (p.get_timestamp() <= time_interval && i < passages.size()){
        const Passage& p = passages[i];
  
        // save passages below the gantry to stats
        GantryStats gantry_stats(p.get_gantry(), 1, 0); 
        if (!stats.gantries.insert(gantry_stats.gantry.getId(), gantry_stats).second){
            stats.gantries[gantry_stats.gantry.getId()].passage_count++;
        }

        // add passages within the interval to interval_passages
        interval_passages[p.plate].push_back(p);
        
         i++;
    }
    
    // clear reports
    reports.clear();

    // compute the violations
    for (const auto& [plate, v_passage]: interval_passages){ 
        if (v_passage.size() <= 1){
            continue;
        }

        // iterate through passages under gantries by the same vehicle
        const Passages& first = v_passages[0]; 
        for (int i=1; i<v_passages.size(); i++){
            const Passages& second = v_passages[i];
            
            double time_g2g = second.get_timestamp() - first.get_timestamp();
            double dist = second.gantry.getDist() - first.gantry.getDist();
            double avg_speed = (dist / time_g2g) * 3600;  // x3600 converts to km/h 
            
            // if speeding create a report 
            if (avg_speed > SPEED_LIMIT){   
                Report report(first, second, avg_speed);
                reports.push_back(report);

                stats.sanctioned++;
                stats.speed_sum += avg_speed;   // increment sum of all speeds
            }

            first = second;
        }
    }

    return reports;
}

const Tutor::Stats& Tutor::get_stats() const { 
    return stats;
}

void Tutor::reset() {
    interval_passages.clear();
    reports.clear();

    stats.gantries.clear();
    stats.sanctioned = 0;
    stats.speed_sum = 0.0; // ??
    stats.time_interval = 0.0;

    interval_index=0;
    time_interval=0.0;
}

void Tutor::print_reports() const {
    std::cout << "\n\nreports:\n";
    
    for (int i=0; i<reports.size(); i++){
        const Report& r = reports[i];
        
        std::cout << "license plate: " << r.first_passage.get_vehicle().get_plate() << "\n";
        std::cout << "section: " << r.first_passage.get_gantry().getId() << " - " << r.second_passage.get_gantry().getId() << "\n";
        std::cout << "time of passage: " << r.first_passage.get_timestamp() << " - " << r.second_passage.get_timestamp() << "\n";
        std::cout << "average speed: " << r.avg_speed << "\n";
    }
}

void Tutor::print_stats() const {
    std::cout << "\n\nstats: (" << timestamp/60 << " minutes\n)";
    
    for (int i=0; i<gantries.size(); i++){
        const Gantry& g = gantries[i];
        
        std::cout << "gantry id: " << g.gantry.getId() << "\n";
        std::cout << "number of passages: " << g.passage_count << "\n";
    }

    std::cout << "average speed of sanctioned vehicles: " << stats.average_speed() << "\n";
    std::cout << "n of sanctioned vehicles: " << stats.sanctioned << "\n";
}
