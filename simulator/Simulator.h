#ifndef SIMULATOR.h
#define SIMULATOR.h
#include <iostream>
#include <fstream>

const int num_vehicles = 10000;   //Number of vehicles

const int v_min = 80;            //Speed ​​range
const int v_max = 190;

const int d_min = 5;             //Interval duration range
const int d_max = 15;

const double range_min = 0.5;    //Time range between departures
const double range_max = 10.0;

const int max_int = 50;          //Max number of intervals

const int dim_plate = 7;             //Plate length
                                 
struct Interval{                //Constant speed interval
  int speed;
  int duration;
};

struct Profile{                   //Speed profile
  Interval intervals[max_int];
  int num_range;
};
                                  
struct Vehicle{                    //Vehicle creation
  char plate[dim_plate];
  int junction_in;
  int junction_out;
  double time_in;
  Profile profile;
};

int int_random(int min, int max);               //Generate a random integer

double double_random(double min, double max);   //Generate a random double

Interval gen_int();                           //Generate random speed range

void gen_profile(profile &p, double dist);      //Generate speed profile for a certain distance

double dist(int speed, int duration);          //Calculate distance traveled in an interval

Vehicle gen_v(double dist, int num_junction, double t_start);  //Generate vehicle

void run(const Vehicle &v, ofstream &file);       //Write vehicle to file

void passage(const Vehicle &v, ofstream &file, double distTot);  ////Write the passed gates and at what time to the file

#endif







