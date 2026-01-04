// Autore

#ifndef TUTOR_H
#define TUTOR_H

#include "Passage.cpp"

#include <vector>
#include <map>

class Tutor {
private: 
    std::vector<Passages> passages;     //
    std::multimap<Passages> passed_vehicles;   // v 
    double time;                        // measured in seconds

public:
    Tutor(std::string p_data_path);
    std::string setTime();     // ??
    std::string getStats() const;    // ??
    void reset();       // ??
}

#endif
