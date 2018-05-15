#ifndef FUNKCJEGRAFOWE_H
#define FUNKCJEGRAFOWE_H

#include "Macierz.h"
#include "Lista.h"
#include "Krawedz.h"
#include <iostream>
#include <cstdlib>
#include <queue>
#include <list>
#include "Kopiec.h"
#include <stack>

using namespace std;

void PrimsL(GraphL & graf);
void PrimsM(GraphM & graf);
void KruskalL(GraphL & graf);
bool cycle(GraphL &graf, int v, int w, stack<int> &S, bool * visited);



#endif






	
