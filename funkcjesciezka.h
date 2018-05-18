#ifndef FUNKCJESCIEZKA_H
#define FUNKCJESCIEZKA_H

#include "Macierz.h"
#include "Lista.h"
#include "Krawedz.h"
#include <iostream>
#include <cstdlib>
#include <queue>
#include <list>
#include "Kopiec.h"
#include <stack>
#include "KrawedzMacierz.h"
#include "Wierzcholek.h"
#include <conio.h>
using namespace std;

void DijkstryL(GraphL & graf, int s, int e);
void DijkstryM(GraphM & graf, int s, int e);
void FordL(GraphL & graf, int s, int e);
void FordM(GraphM & graf, int s, int e);

#endif
