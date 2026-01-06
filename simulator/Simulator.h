#ifndef SIMULATOR_H
#define SIMULATOR_H
#include <iostream>
#include <fstream>

const int Num_vehicles = 10000;   

const int V_min = 80;            //Speed range
const int V_max = 190;

const int D_min = 5;             //Interval duration range
const int D_max = 15;

const double Range_min = 0.5;    //Time range between departures
const double Range_max = 10.0;

const int Max_int = 50;          //Max number of intervals

struct Interval{                //Constant speed interval
  int speed;
  int duration;
};

struct Profile{                   //Speed profile
  Interval intervals[Max_int];
  int Num_int;
};

struct Vehicle{                    //Vehicle creation
  char plate[Dim_plate];
  int Sv_in;
  int Sv_out;
  double T_in;
  Profile profile;
};

int Int_random(int min, int max);               //Generates a random integer

double Double_random(double min, double max);   //Generates a random double

Interval Gen_int();                           //Generate random speed range

void Gen_profile(Profile &p, double dist);      //Generate speed profile for a certain distance

double Dist(int speed, int duration);          //Calculate distance traveled in an interval

Vehicle Gen_v(double dist, int numSv, double t_start);  //Generation vehicle

void Run(const Vehicle &v, ofstream &file);  //Write vehicle to file

void Passage(const Vehicle &v, ofstream &file, double distTot); //Writes passages to file

#endif







