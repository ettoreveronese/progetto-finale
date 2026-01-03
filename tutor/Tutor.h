// Autore

#ifndef TUTOR_H
#define TUTOR_H

#include "Passage.cpp"

#include <iostream>
#include <vector>

class Tutor {
private: 
    std::vector<Passage> passages;

public:
    Tutor();
    void setTime();     // ??
    void getStats();    // ??
    void reset();       // ??
}

#endif
