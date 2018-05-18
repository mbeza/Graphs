#ifndef LISTA_H
#define LISTA_H

#include <iostream>
#include <cstdlib>
#include <list>
#include <vector>
#include "Krawedz.h"
#include <fstream>

using namespace std;

class GraphL{

	public:
		vector<Edge> * tab;
		int size;
		int edges;
		bool direct;
		
		GraphL();
		GraphL(bool direction);
		GraphL(GraphL & ref);
		void addNode();
		void addEdge(Edge e, int pos);
		void create(bool directed, string filename);
		void createEmpty(int v, bool directed);
		void show();
		bool check(int s, int e);
};


#endif
