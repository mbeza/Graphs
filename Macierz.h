#ifndef MACIERZ_H
#define MACIERZ_H
#include <iostream>
#include <cstdlib>
#include <iomanip>

using namespace std;

class GraphM
{
	
	int **Matrix;
	int *Weight;
	int nodes;
	int lines;
	bool direct;
	
	public:
	GraphM();
	void fill(bool directed); //false - nieskierowany true - skierowany
	void show();
};




#endif
