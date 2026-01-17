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

std::vector<Gantry> Tutor::gantries_from_highway(const std::string& filename){
    Highway hw;
    hw.load_highway_data(filename);
    return hw.get_gantries();
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
    gantries(gantries_from_highway(highway_fn)), 
    passages(parse_passages_data(passages_fn, gantries))
{
    interval_index = 0;
   
    stats.n_passages.assign(gantries.size(), 0);
    stats.n_measures = 0;
    stats.speed_sum = 0.0;
    stats.time_interval = 0.0;
}

const std::vector<Tutor::Report>& Tutor::set_time(const double time_increment){
    if (time_increment<=0){   // can only add time to the interval, reset to roll back
        throw std::invalid_argument("time increment must be positive");
    }   
    
    // update time interval
    stats.time_interval += time_increment;

    // clear reports from last interval
    reports.clear();
    
    // cicle through passages within the interval
    int& i = interval_index; 
    while (i < passages.size() && passages[i].get_timestamp() <= stats.time_interval){
        const Passage& p2 = passages[i];
        const std::string& plate = p2.get_vehicle().get_plate();
  
        // update gantry stats
        stats.n_passages.at(p2.get_gantry().get_id()) += 1;
         
        // if possible compute average speed between 2 gantries
        if (last_passages.find(plate) != last_passages.end()){
            const Passage& p1 = last_passages.at(plate);

            double time_gtg = p2.get_timestamp() - p1.get_timestamp();
            double dist = p2.get_gantry().get_dist() - p1.get_gantry().get_dist();

            if (time_gtg<=0 || dist<=0){
                throw std::runtime_error("couldn't compute avg_speed");
            }

            double avg_speed = (dist / time_gtg) * 3600;  // x3600 converts to km/h 
            
            // if speeding create a report 
            if (avg_speed > SPEED_LIMIT){   
                Report report(p1, p2, avg_speed);
                reports.push_back(report);

                stats.sanctioned_set.insert(p2.get_vehicle().get_plate());
            }
            
            // update stats
            stats.n_measures += 1;
            stats.speed_sum += avg_speed;

            // insert latest passage in last_passages
            last_passages.at(plate) = p2;
        } else {
            last_passages.insert({plate, p2}); 
        }

        i++;
    }
    
    return reports;
}

const Tutor::Stats& Tutor::get_stats() const { 
    return stats;
}

void Tutor::reset() {
    // reset interval
    interval_index = 0;
    last_passages.clear(); 
    reports.clear();
    
    // reset stats
    std::fill(stats.n_passages.begin(), stats.n_passages.end(), 0); 
    stats.sanctioned_set.clear();
    stats.n_measures = 0;
    stats.speed_sum = 0.0; // ??
    stats.time_interval = 0.0; 
}

void Tutor::print_reports() const {
    std::cout << "\n\nREPORTS:\n";
    
    for (int i=0; i<reports.size(); i++){
        const Report& r = reports[i];
        
        std::cout << "\nlicense plate: " << r.first_passage.get_vehicle().get_plate() << "\n";
        std::cout << "section: " << r.first_passage.get_gantry().get_id() << " - " << r.second_passage.get_gantry().get_id() << "\n";
        std::cout << "time of passage: " << r.first_passage.get_timestamp() << " - " << r.second_passage.get_timestamp() << "\n";
        std::cout << "average speed: " << r.avg_speed << "\n";
    }
    
    std::cout << "\n\n";
}

void Tutor::print_stats() const {
    std::cout << "\n\nSTATS: (" << stats.time_interval/60 << " minutes)\n";
    
    for (int i=0; i<gantries.size(); i++){
        std::cout << "\ngantry id: " << gantries[i].get_id() << "\n";
        std::cout << "number of passages: " << stats.n_passages[i] << "\n";
        std::cout << "passages per minute: " << stats.gantry_passages_min(i) << "\n";
    }
    std::cout << "\n\n";
    std::cout << "average speed of all vehicles: " << stats.avg_speed() << "\n";
    std::cout << "n of sanctioned vehicles: " << stats.sanctioned() << "\n";
    std::cout << "\n\n";
}
