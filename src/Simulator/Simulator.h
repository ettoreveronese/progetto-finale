#ifndef Simulator.h
#define Simulator.h

const int Num_veicoli = 10000;   //Numero di veicoli
                                   
const int V_min = 80;            //Range di velocità
const int V_max = 190;

const int D_min = 5;             //Range durata degli intervalli
const int D_max = 15;

const double Range_min = 0.5;    //Range di tempo tra le partenze 
const double Range_max = 10.0;

const int Max_int = 50;          //Numero max di intervalli

const Dim_targa = 7;             //Lunghezza targa
                                 
struct Intervallo{                //intervallo a velocità costante
  int velocita;
  int durata;
};

struct Profilo{                   //profilo velocità
  Intervallo intervalli[Max_int];
  int Num_int;
};
                                  
struct Veicolo{                    //creazione veicolo
  char targa[Dim_targa];
  int Sv_in;
  int Sv_out;
  double T_in;
  Profilo profilo;
};

int Int_random(int min, int max);               //Genera un intero casuale

Double Double_random(double min, double max);   //Genera un double casuale

void Gen_targa(char targa[]);                   //Genera targa
 
Intervallo Gen_int();                           //Genera intervallo di velocià casuale

void Gen_profilo(Profilo &p, double dist);      //Genera profilo di velocità per una certa distanza

double Dist(int velocita, int durata);          //Calcola distanza percorsa in un intervallo

Veicolo Gen_v(double dist, int numSv, double t_start);  //Genera veicolo

void V_file(const Veicolo &v, ofstream &file);  //Scrive veicolo su file

#endif




