// autore: ettore veronese

#ifndef TUTOR_H
#define TUTOR_H

#include "Passage.cpp"
#include "Gantry.cpp"

#include <vector>
#include <map>

class Tutor {
private:
    struct GantryData {
        Gantry gantry;
        int n_of_passages;
        double avg_passages_min;
    };

    struct Report {
        Vehicle vehicle;
        Gantry first_gantry;
        Gantry second_gantry;
        double avg_speed;
    }

    std::vector<Passage> passages;  // all the passages under the gantries, sorted by time
    std::unordered_map<std::string, std::vector<Passage>> interval_passages;    // passages in the time interval, grouped by plate
    std::unordered_map<gantryData> gantries_data;
   
    int interval_index;   // index of the next passage outside the time interval
    
    /*struct {
        double t1;
        double t2;
    } time_interval;*/    // in seconds 
    double time_interval;

    const double SPEED_LIMIT = 130;

public:
    Tutor(const std::string p_data_path);
    std::string setTime();     // ??
    std::string getStats() const;    // ??
    void reset();       // ??
}

#endif
