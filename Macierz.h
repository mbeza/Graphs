#ifndef MACIERZ_H
#define MACIERZ_H
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <stack>

using namespace std;

class GraphM
{

public:	
	int **Matrix;
	int *Weight;
	int nodes;
	int lines;
	bool direct;
	bool connectivity;
	
	GraphM();
	void create(bool directed, string filename); //false - nieskierowany true - skierowany
	void show();
	void showEdge(int s, int e);
	void addEdge(int s, int e, int w);
	void addNode();
	void createEmpty(int v, bool directed,int edg=0);
	int findStartEdge(int edg);
	int findEndEdge(int edg, int strt=0);
	void deleteEdge();
	bool check(int s, int e);
	void editEdge(int s, int e, int w);
	void checkConnectivity();
	
};




#endif
