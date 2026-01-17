#include "Tutor.h"

#include <iostream>
#include <sstream>
#include <string>

int str_to_time(const std::string& str){
    if (str.empty()){
        return 0;
    }

    int multiplier = 1;
    std::string num; 
    
    // if in minutes set multiplier to 60
    if (str[str.size()-1] == 'm'){
        num = str.substr(0, str.size()-1);
        
        if (num.empty()){
            return 0;
        } 

        multiplier = 60;
    } else {
        num = str;
    }
    
    int time = 0;

    for (char c : num){
        if (c < '0' || c > '9'){
            return 0;
        }

        time = time * 10 + (c - '0');
    }

    return time * multiplier;
}

int main() {
        Tutor tutor("./data/Highway.txt", "./data/Passages.txt");
    std::string line;
    
    while(std::getline(std::cin, line)){
        
        std::cout << "commands:\n";
        std::cout << "set_time <istante>        spostamento a un nuovo istante temporale \ne stampa eventuali violazioni tra l’istante \ncorrente e quello indicato\n";
        std::cout << "reset        resetta compleatamente il sistema\n";
        std::cout << "stats        stampa le statistiche\n";

        std::istringstream iss(line);
        std::string command;
        
        iss >> command;
        
        if(command == "set_time"){
            std::string arg;
            iss >> arg;
            int time_increment = str_to_time(arg);
            
            if (time_increment <= 0){
                std::cout << "invalid time";
                continue;
            }
            
            tutor.set_time(time_increment);
            tutor.print_reports();

        } else if(command == "stats") {
            tutor.print_stats();

        } else if(command == "reset") {
            tutor.reset();

        } else {
            std::cout << "invalid command - '" << command << "'\n";
        }
    }

    return 0;
}
