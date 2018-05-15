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
	

	GraphL graf2;
	cout<<endl<<endl;
	graf2.create(false);
	graf2.show();
	cout<<endl;
	Prims(graf2);
	
	
	system("pause");
	return 0;
}
