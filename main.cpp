#include <iostream>
#include <cstdlib>
#include "Macierz.h"
#include "Krawedz.h"
#include "Lista.h"
#include "funkcje.h"
using namespace std;

int main()
{
	
	GraphM graf;
	graf.fill(false);
	graf.show();
	cout<<"\nALGORYTM PRIMA\n";
	PrimsM(graf);
	cout<<"\nALGORYTM KRUSKALA\n";
	KruskalM(graf);		

	GraphL graf2;
	graf2.create(false);
	graf2.show();

	cout<<"\nALGORYTM PRIMA\n";
	PrimsL(graf2);
	cout<<"\nALGORYTM KRUSKALA\n";
	KruskalL(graf2);
	
	
	
	system("pause");
	return 0;
}
