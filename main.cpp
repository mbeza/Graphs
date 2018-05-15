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
	PrimsM(graf);
	

	GraphL graf2;
	cout<<endl<<endl;
	graf2.create(false);
	graf2.show();
	cout<<endl;
	PrimsL(graf2);
	KruskalL(graf2);
	
	
	
	system("pause");
	return 0;
}
