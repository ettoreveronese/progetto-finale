#include "Simulator.h"
#include <iostream>
#include <cstdlib>

using namespace std;


int Int_random(int min, int max){

	int i= min+rand() % (max-min+1);              //generazione casuale numero int
	return i;
}

int Double_random(double min, double max){         //generazione casuale numero double

	double j= min+(max-min) * ((double) rand() / RAND_MAX);
	return j;
}

void Gen_plate(char plate[]) {        //generazione targa con codice ASCII

	plate[0]= 'A' + rand()%26;
	plate[1]= 'A' + rand()%26;
	plate[2]= '0' + rand()%10;
	plate[3]= '0' + rand()%10;
	plate[4]= '0' + rand()%10;
	plate[5]= 'A' + rand()%26;
	plate[6]= 'A' + rand()%26;
}

double Dist(int speed, int duration){ //calcolo distanza con conversione di minuti in ore

	double d= speed*(duration/60);
	return d;

}

Interval Gen_int(){                   //generazione casuale intervallo di velocità

	Interval v;
	v.speed=Int_random(V_min, V_max);
	v.duration=Int_random(D_min, D_max);
	return v;
}
