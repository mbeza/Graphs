#ifndef KRAWEDZ_H
#define KRAWEDZ_H

#include <iostream>
#include <cstdlib>

using namespace std;

class Edge{
	
	public:
		int start;
		int end;
		int weight;
		void show();
		Edge();
		Edge(int s, int e, int w);
		int getW();
		
		
		
};


#endif
