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

std::vector<Gantry> Tutor::parse_highway_data(const std::string& filename){
    std::ifstream file(filename);
    if (!file.is_open()){
        throw std::invalid_argument("couldn't read Passages.txt");
    }
    
    double dist;
    char type;
    std::vector<double> distances;  // distances of all gantries, to be sorted for ids
    
    // save the distance of gantries to distances vector
    while (file >> dist >> type){
        if (type == 'V'){
           distances.push_back(dist);
        } else if (type == 'S'){
            continue;
        } else {
            throw std::invalid_argument("couldn't correctly parse Highway.txt");
        }
    }

    std::sort(distances.begin(), distances.end());
    
    std::vector<Gantry> gantries;
    
    // create gantry objects, ids taken from index
    for (int i=0; i<distances.size(); i++){
        gantries.push_back(Gantry(distances[i], i));
    }

    return gantries;
}

// given the passages vector as reference and the path of passages.txt 
// it stores the data in passages.txt to the passages vector, sorted by time
std::vector<Passage> Tutor::parse_passages_data(const std::string& filename, const std::vector<Gantry>& gantries){
    // open file     
    std::ifstream file(filename);
    if (!file.is_open()){
        throw std::invalid_argument("couldn't read passages.txt");
    }
    
    int id;
    std::string plate;
    double time;
    std::vector<Passage> passages;

    // save to passages vector
    while (file >> id >> plate >> time){
        Passage p(gantries.at(id), Vehicle(plate), time);
        passages.push_back(p);        
    }
    
    // sort the passages by time
    std::sort( passages.begin(), passages.end(), 
        [](const Passage& a, const Passage& b){ 
            return a.get_timestamp() < b.get_timestamp();
        });
    return passages;
}


Tutor::Tutor(const std::string& highway_fn, const std::string& passages_fn) :
    gantries(parse_highway_data(highway_fn)), 
    passages(parse_passages_data(passages_fn, gantries))
{
    interval_index = 0;
   
    stats.n_passages.assign(gantries.size(), 0);
    stats.sanctioned = 0;
    stats.speed_sum = 0.0;
    stats.time_interval = 0.0;
}

const std::vector<Tutor::Report>& Tutor::set_time(const double time_increment){
    if (time_increment<=0){   // can only add time to the interval, reset to roll back
        throw std::invalid_argument("time increment must be positive");
    }   
    
    // update time interval
    stats.time_interval += time_increment;

    // clear the passaged from the previous interval
    interval_passages.clear(); 
    
    // cicle through passages within the interval
    int& i = interval_index; 
    while (i < passages.size() && passages[i].get_timestamp() <= stats.time_interval){
        const Passage& p = passages[i];
  
        // save passages below the gantry to stats
        /*GantryStats gantry_stats(p.get_gantry(), 1, 0); 
        if (!stats.gantries.insert(gantry_stats.gantry.getId(), gantry_stats).second){
            stats.gantries[gantry_stats.gantry.getId()].passage_count++;
        }*/
        stats.n_passages.at(p.get_gantry().get_id()) += 1;

        // add passages within the interval to interval_passages
        interval_passages[p.get_vehicle().get_plate()].push_back(p);
        
         i++;
    }
    
    // clear reports
    reports.clear();

    // compute the violations
    for (const auto& entry: interval_passages){ 
        const std::string& plate = entry.first;
        const auto& vehicle_passages = entry.second;
        
        if (vehicle_passages.size() <= 1){
            continue;
        }

        // iterate through passages under gantries by the same vehicle
        const Passage* first = &vehicle_passages[0]; 
        for (int i=1; i<vehicle_passages.size(); i++){
            const Passage& second = vehicle_passages[i];
            
            double time_g2g = second.get_timestamp() - first->get_timestamp();
            double dist = second.get_gantry().get_dist() - first->get_gantry().get_dist();
            
            if (time_g2g<=0 || dist<=0){
                throw "error: couldn't compute avg_speed";
            }

            double avg_speed = (dist / time_g2g) * 3600;  // x3600 converts to km/h 
            
            // if speeding create a report 
            if (avg_speed > SPEED_LIMIT){   
                Report report(*first, second, avg_speed);
                reports.push_back(report);

                stats.sanctioned++;
                stats.speed_sum += avg_speed;   // increment sum of all speeds
            }

            first = &second;
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

    std::fill(stats.n_passages.begin(), stats.n_passages.end(), 0);

    stats.sanctioned = 0;
    stats.speed_sum = 0.0; // ??
    stats.time_interval = 0.0;

    interval_index=0;
}

void Tutor::print_reports() const {
    std::cout << "\n\nreports:\n";
    
    for (int i=0; i<reports.size(); i++){
        const Report& r = reports[i];
        
        std::cout << "license plate: " << r.first_passage.get_vehicle().get_plate() << "\n";
        std::cout << "section: " << r.first_passage.get_gantry().get_id() << " - " << r.second_passage.get_gantry().get_id() << "\n";
        std::cout << "time of passage: " << r.first_passage.get_timestamp() << " - " << r.second_passage.get_timestamp() << "\n";
        std::cout << "average speed: " << r.avg_speed << "\n";
    }
}

void Tutor::print_stats() const {
    std::cout << "\n\nstats: (" << stats.time_interval/60 << " minutes\n)";
    
    for (int i=0; i<gantries.size(); i++){
        std::cout << "gantry id: " << gantries[i].get_id() << "\n";
        std::cout << "number of passages: " << stats.n_passages[i] << "\n";
    }

    std::cout << "average speed of sanctioned vehicles: " << stats.average_speed() << "\n";
    std::cout << "n of sanctioned vehicles: " << stats.sanctioned << "\n";
}
