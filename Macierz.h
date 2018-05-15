#ifndef MACIERZ_H
#define MACIERZ_H
#include <iostream>
#include <cstdlib>
#include <iomanip>

using namespace std;

class GraphM
{

public:	
	int **Matrix;
	int *Weight;
	int nodes;
	int lines;
	bool direct;
	
	GraphM();
	void fill(bool directed); //false - nieskierowany true - skierowany
	void show();
	void showEdge(int edg);
};




#endif
