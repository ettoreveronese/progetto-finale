// autore: ettore veronese

#ifndef TUTOR_H
#define TUTOR_H

#include "Passage.h"
#include "Gantry.h"

#include <vector>
#include <unordered_map>
#include <string>

class Tutor {
public:
    struct GantryStats {
        Gantry gantry;
        int passage_count;
    };

    struct Stats{
        std::unordered_map<int, GantryStats> gantries;
        int sanctioned = 0;
        double speed_sum = 0.0; // sum of the speed of all speeding vehicles, to compute average
        double time_interval = 0.0;

        double average_speed() const { 
            return sanctioned > 0 ? speed_sum/sanctioned : 0.0; 
        }
    };
    
    struct Report {
        Passage first_passage;
        Passage second_passage;
        double avg_speed;
    };

    explicit Tutor(const std::string& filename);
    
    const std::vector<Report>& set_time(double time_increment);
    const Stats& get_stats() const;
    void reset();
    
    void print_reports() const;
    void print_stats() const;

private:
    static constexpr double SPEED_LIMIT = 130;  
   
    std::vector<Gantry> gantries;
    std::vector<Passage> passages;    // all the passages under the gantries, sorted by time
    std::unordered_map<std::string, std::vector<Passage>> interval_passages;    // passages in the time interval, grouped by plate
    std::vector<Report> reports;    
    Stats stats;

    int interval_index;   // index of the next passage outside the time interval    

    // methods
    void parse_highway_data(const std::string& filename);
    void parse_passages_data(const std::string& filename);
};

#endif
