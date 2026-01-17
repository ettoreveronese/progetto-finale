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
     
    std::cout << "\nCOMMANDS:\n\n";
    std::cout << "set_time <istante>\t\t\tpostamento a un nuovo istante temporale \n\t\t\t\t\te stampa eventuali violazioni tra l’istante \n\t\t\t\t\tcorrente e quello indicato\n\n";
    std::cout << "reset\t\t\t\t\tresetta compleatamente il sistema\n\n";
    std::cout << "stats\t\t\t\t\tstampa le statistiche\n";
    std::cout << "\n> ";

    while(std::getline(std::cin, line)){    

        std::istringstream iss(line);
        std::string command;
        
        iss >> command;
        
        if(command == "set_time"){
            std::string arg;
            iss >> arg;
            int time_increment = str_to_time(arg);
            
            if (time_increment <= 0){
                std::cout << "invalid time\n>";
                continue;
            }
            
            tutor.set_time(time_increment);
            tutor.print_reports();

        } else if(command == "stats") {
            tutor.print_stats();

        } else if(command == "reset") {
            tutor.reset();

        } else {
            std::cout << "invalid command - '" << command << "'\n>";
            continue;
        }

        std::cout << "\n> ";
    }

    return 0;
}
