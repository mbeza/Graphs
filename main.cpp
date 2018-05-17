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
//	graf3.show();
	graf3.create(true);

	graf3.show();
	cout<<endl;
	DijkstryL(graf3,6,0);
	cout<<endl;
	graf3.show();
	
	
	GraphM graf4;
	graf4.fill(true);
	graf4.show();
	DijkstryM(graf4,6,5);
	
	system("pause");
	return 0;
}
