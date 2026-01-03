#ifndef SIMULATOR_H
#define SIMULATOR_H
#include <iostream>
#include <fstream>

const int Num_vehicles = 10000;   //Numero di veicoli

const int V_min = 80;            //Range di velocità
const int V_max = 190;

const int D_min = 5;             //Range durata degli intervalli
const int D_max = 15;

const double Range_min = 0.5;    //Range di tempo tra le partenze 
const double Range_max = 10.0;

const int Max_int = 50;          //Numero max di intervalli

const int Dim_plate = 7;             //Lunghezza targa

struct Interval{                //intervallo a velocità costante
  int speed;
  int duration;
};

struct Profile{                   //profilo velocità
  Interval intervals[Max_int];
  int Num_int;
};

struct Vehicle{                    //creazione veicolo
  char plate[Dim_plate];
  int Sv_in;
  int Sv_out;
  double T_in;
  Profile profile;
};

int Int_random(int min, int max);               //Genera un intero casuale
double Double_random(double min, double max);   //Genera un double casuale

void Gen_plate(char plate[]);                   //Genera targa

Interval Gen_int();                           //Genera intervallo di velocià casuale

void Gen_profile(Profile &p, double dist);      //Genera profilo di velocità per una certa distanza

double Dist(int speed, int duration);          //Calcola distanza percorsa in un intervallo

Vehicle Gen_v(double dist, int numSv, double t_start);  //Genera veicolo

void V_file(const Vehicle &v, ofstream &file);  //Scrive veicolo su file

#endif






