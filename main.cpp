#include <iostream>
#include <cstdlib>
#include "Macierz.h"
#include "Krawedz.h"
#include "Lista.h"
#include "funkcje.h"
#include "funkcjesciezka.h"

using namespace std;

int main()
{
/*	
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
*/	
	GraphL graf3(true);
	graf3.show();
	graf3.create(true);
	cout<<endl;
	graf3.show();
	cout<<endl;
	DijkstryL(graf3,4,5);
	
	int k;
	
	cout<<endl<<sizeof(k);
	
	
	
	system("pause");
	return 0;
}
