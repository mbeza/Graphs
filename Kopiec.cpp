#include "Kopiec.h"

Heap::Heap()
{
	size=0;
	tab= new Edge[1];
}

Heap::~Heap()
{	
	delete [] tab;	
}

void Heap::add(Edge n)
{	
	Edge *tmp = new Edge[size+1]; //deklarujemy wskaznik na tablice o 1 miejsce wieksza
	
	for(int i=0; i<size; i++)
	{ 
		tmp[i]=tab[i];			//kopiujemy ze starej do nowej
	}
	
	tmp[size]=n;				//na koniec nowej dodajemy wartosc przekazana w funkcji
	
	delete tab;					//zwalniamy pamiec tam gdzie byla poprzednia tablica
	tab=tmp;					//aktualizujemy wskaznik na tablice
	
	int iterator=size;				//tworzymy zmienna pomocnicza, ktora bedzie iteratorem dodanego elementu
	
	while(iterator>0)
	{
		if(tab[(iterator-1)/2].weight>tab[iterator].weight)
		{
			Edge tmp2=tab[(iterator-1)/2];
			tab[(iterator-1)/2]=tab[iterator];	//zamiana ojca z synem jesli ojciec jest mniejszy niz rozpatrywany syn
			tab[iterator--]=tmp2;			//postdekrementacja, bo trzeba odjac 1 i dopiero podzielic przez 2
			iterator/=2;
		}
		else break;
	}
	
	size++;						//zwiekszamy rozmiar	
	
}


Edge Heap::remove()
{
	Edge root=tab[0];				//gdyby by³a potrzebne wykorzystanie tego elementu
	if(size!=0)
	{
		tab[0]=tab[--size];				//zamiana korzenia z ostatnim elementem kopca, przy okazji zmniejszenie rozmiaru kopca
		
		Edge *tmp = new Edge[size];		//nowa tablica o mniejszym rozmiarze
	
		for(int i=0; i<size; i++)
		{ 
			tmp[i]=tab[i];			//kopiujemy ze starej do nowej
		}	
	
		delete tab;					//zwalniamy pamiec tam gdzie byla poprzednia tablica
		tab=tmp;					//aktualizujemy wskaznik na tablice
		
	
		int iter=0;					//zmienna pomocnicza do poruszania sie po kopcu. iter=0 oznacza, ze zaczynamy od korzenia
		
		while((2*iter+1)<size)		
		{
			if((2*iter+2<size) && tab[2*iter+1].weight>tab[2*iter+2].weight)		//jesli istnieje prawy syn i jest mniejszy od lewego 
			{
				if(tab[2*iter+2].weight<tab[iter].weight)								//jesli prawy syn wezla ktory rozpatrujemy jest od niego mniejszy
				{				
					Edge tmp2=tab[2*iter+2];
					tab[2*iter+2]=tab[iter];								//zamien rodzica z prawym synem
					tab[iter]=tmp2;
	
					iter=2*iter+2;											//przesun iterator na wezel ktory zamieniono
				}
				else break;												//jesli prawy syn nie jest wiekszy, to koniec algorytmu
			}
			else													// jesli lewy syn jest wiekszy, lub nie istnieje prawy
			{
				if(tab[2*iter+1].weight<tab[iter].weight)								//sprawdzamy czy lewy syn wezla ktory rozpatrujemy jest od niego mniejszy
				{
					Edge tmp2=tab[2*iter+1];
					tab[2*iter+1]=tab[iter];								//zamien rodzica z lewym synem
					tab[iter]=tmp2;	
					iter=2*iter+1;											//przesun iterator na wezel ktory zamieniono
					
				}
				else break;
			}
		}	
	}
	else system("pause");	
	return root;					//zwracamy korzen
}

int potega (int podst, int wykl)
{
	int wynik=podst;
	while(wykl>1)
	{
		wynik*=podst;
		wykl--;
	}
	return wynik;
}


void Heap::display()
{
	int level=1;					//wyswietlanie poziomami 
	for(int i=0; i<size; i++)
	{
		cout<<tab[i].start<<"-"<<tab[i].end<<"|"<<tab[i].weight<<" ";
		if(potega(2,level)-2==i)		//jesli numer wezla jest ostatnim w danym poziomie
		{
			cout<<endl;				//to przejdz do nowej linii 
			level++;
		}
	}
		
	cout<<endl;
}






















