#ifndef KOPIECKRAWEDZI
#define KOPIECKRAWEDZI

#include <iostream>
#include <cstdlib>
#include "Krawedz.h"

using namespace std;

class Heap{
		
		
	public:
		unsigned int size;
		Edge *tab;
		void add(Edge n);
		Edge remove();
		void display();
			
		Heap();					
		~Heap();
		
	
};



#endif

