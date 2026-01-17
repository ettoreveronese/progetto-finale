// autore: ettore veronese

#ifndef TUTOR_H
#define TUTOR_H

#include "Passage.h"
#include "Gantry.h"

#include <vector>
#include <unordered_map>
#include <string>
#include <set>

class Tutor {
public:
    struct Stats{
        std::vector<int> n_passages;    // passages under each gantry  
        std::set<std::string> sanctioned_set;   // set of all sanctioned vehicles 
        
        // used to compute average speed of all vehicles
        int n_measures = 0;     // total number of measures between 2 gantries
        double speed_sum = 0.0;     // sum of all measured speeds
 
        double time_interval = 0.0;     // the timestamp up to which the stats are updated

        double avg_speed() const { 
            return n_measures > 0 ? speed_sum/n_measures : 0.0; 
        }
        
        double gantry_passages_min(int i) const {  // passages per min below a gantry
            if (time_interval == 0) { return 0.0; }
            return n_passages.at(i) / (time_interval / 60);
        }

        int sanctioned() const {
            return sanctioned_set.size();
        }
    };
    
    struct Report {
        Passage first_passage;
        Passage second_passage;
        double avg_speed;

        Report(const Passage& first, const Passage& second, double speed) : 
            first_passage(first), second_passage(second), avg_speed(speed) {}
    };
    
    // constructor
    explicit Tutor(const std::string& highway_fn, const std::string& passages_fn);
    
    // set a new time interval, update stats, 
    // save and return reports in the time interval
    const std::vector<Report>& set_time(const double time_increment);

    // returns stats struct, updated up to latest time interval
    const Stats& get_stats() const;         
    
    // reset time interval and associated attributes to initial state
    void reset();       

    void print_reports() const;     // print latest reports
    void print_stats() const;

private:
    static constexpr double SPEED_LIMIT = 130;  
   
    const std::vector<Gantry> gantries;     // gantries sorted by id, taken from Highway.txt
    const std::vector<Passage> passages;    // all the passages under the gantries, sorted by time
    
    std::unordered_map<std::string, Passage> last_passages;    // passages in the time interval, grouped by plate
    std::vector<Report> reports;    
    Stats stats;

    int interval_index;   // index of the next passage outside the time interval    

    // methods
    static std::vector<Gantry> gantries_from_highway(const std::string& filename);
    static std::vector<Passage> parse_passages_data(const std::string& filename, const std::vector<Gantry>& gantries);
};

#endif
