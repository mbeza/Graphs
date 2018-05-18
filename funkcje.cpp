#include "funkcje.h"

struct compareEdge
{
	bool operator ()( EdgM & e1, EdgM & e2 )
    {
        //kolejnoœæ - rosn¹co
        if( e1.weight > e2.weight ) return true;
       
        if( e1.weight < e2.weight ) return false;
       
        return false;
    }
};

void PrimsL(GraphL & graf)
{
	
	Heap priority;				//kolejka priorytetowa na bazie kopca
	
	int nodes = graf.size;		
	bool visited [nodes]; 		//tablica odwiedzonych wierzcholkow
	
	for(int i=0; i<nodes; i++)	//uzupelniamy tablice odwiedzonych wierzcholkow wartosciami false
	{
		visited[i]=false;
	}
	
	GraphL wynikowy;
	wynikowy.createEmpty(nodes,false);
	
	int iter=0;					//zaczynamy od wierzcholka o numerze 0
	visited[iter] = true;		//oznaczamy go jako odwiedzony	
	
	for(int i = 0; i<nodes-1; i++)	//petla do poruszania sie po wierzcholkach
	{
		int vecsize = graf.tab[iter].size();	//kazdy wierzcholek, to element tablicy zawierajacy liste sasiadow. Aby poruszac sie po sasiadach musimy wiedziec ilu ich ma
		
		for(int j=0; j<vecsize; j++)		//przechodzimy przez kazdego sasiada
		{
			if (!visited[graf.tab[iter][j].end])	//jesli sasiedni wierzcholek jest oznaczony jako nieodwiedzony
			{
				priority.add(graf.tab[iter][j]);	//to wrzucamy krawedz do tego wierzcholka do kolejki priorytetowej
			}
		}
	
		Edge k;	//zmienna pomocnicza
		
		do
		{
			k=priority.remove();	//sciagamy krawedz o najmniejszej wadze...		
		}while(visited[k.end]);		//...tak dlugo, az napotkamy taka krawedz, ktorej koniec jest jeszcze nieodwiedzonym wierzocholkiem
		
		
		wynikowy.addEdge(k,k.start);
		Edge l;
		l.start=k.end;
		l.end=k.start;
		l.weight=k.weight;
		wynikowy.addEdge(l,l.start);
		visited[k.end]=true;		//wierzcholek na drugim koncu krawedzi oznaczamy jako odwiedzony
		iter=k.end;					//i przechodzimy do niego kontynuujac petle
	}

	cout<<endl;
	wynikowy.show();	
}

void PrimsM(GraphM & graf)
{
	Heap priority;				//kolejka priorytetowa na bazie kopca
	
	int nodes = graf.nodes;
	bool visited [nodes]; 		//tablica odwiedzonych wierzcholkow
	
	for(int i=0; i<nodes; i++)
	{
		visited[i]=false;		//uzupelniamy tablice odwiedzonych wierzcholkow wartosciami false
	}
	
	GraphM wynikowy;
	wynikowy.createEmpty(nodes,false);
	
	
	int iter=0;					//zaczynamy od wierzcholka o numerze 0
	visited[iter] = true;		//oznaczamy go jako odwiedzony
	
	for(int i = 0; i<nodes-1; i++)	//przechodzimy przez wierzcholki
	{
		int edgs = graf.lines;		//w macierzy incydencji kolumny to krawedzie, wiec potrzebujemy liczbe krawedzi
		for(int j=0; j<edgs; j++)	//sprawdzamy czy wierzcholek nalezy do konkretnej krawedzi, przechodzac poziomo po macierzy
		{
			int endnode=0;		//iterator pomocniczy do szukania konca krawedzi
			if(graf.Matrix[iter][j]==1)	//jesli napotkamy jedynke, oznacza, ze wierzcholek nalezy do krawedzi
			{
				while(endnode<nodes)	//szukamy konca krawedzi, czyli wierzcholka z ktorym jest polaczony za pomoce tej krawedzi
				{
					if (endnode==iter)	//jesli nasz iterator jest poczatkiem krawedzi
					{
						endnode++;	//to szukamy dalej
						continue;
					}
					if(graf.Matrix[endnode][j]==1)	//jesli napotkamy jedynke, ktora nie jest poczatkiem krawedzi, czyli bedzie rozna niz iter, to oznacza ze znalezlismy koniec krawedzi
					{
						break;	//wiec koniec
					}
					endnode++;		//gdy zaden z warunkow to inkrementujemy i szukamy dalej w petli
				}
			}

			if (!visited[endnode])		//sprawdzamy czy koniec krawedzi jest juz odwiedzony
			{
				Edge l;				//jesli nie, to tworzymy krawedz
				l.start=iter;		
				l.end=endnode;
				l.weight=graf.Weight[j];
				priority.add(l);			//i dodajemy ja do kolejki priorytetowej
			}
		}
	
		Edge k;
		
		do
		{
			k=priority.remove();			
		}while(visited[k.end]);
		
		wynikowy.addEdge(k.start,k.end,k.weight);
		visited[k.end]=true;
		iter=k.end;	
	}

	wynikowy.show();
	
}

bool cycle(GraphL & graf, int v, int w, stack<int> &S, bool * visited2)
{
	int u;
	visited2[w]=true;
	int nbr=graf.tab[w].size();
	while(nbr>0)
	{
		u=graf.tab[w][nbr-1].end;
		if (!S.empty())
		{
			if(u==S.top())
			{
				nbr--;
				continue;
			}		
		}
		S.push(w);
		if(u==v) return true;
		if(visited2[u]==false && cycle(graf,v,u,S,visited2)==true) return true;
		S.pop();
		nbr--;
	}
	return false;	
}

void KruskalL(GraphL & graf)
{
	Heap lista;
	int nodes=graf.size;
	bool visited[nodes];
	
	for(int i=0; i<nodes; i++)
		visited[i]=false;
	
	int licznik=0;
	for(int i = 0; i<nodes; i++)	//petla do poruszania sie po wierzcholkach
	{
		int vecsize = graf.tab[i].size();	//kazdy wierzcholek, to element tablicy zawierajacy liste sasiadow. Aby poruszac sie po sasiadach musimy wiedziec ilu ich ma
		
		for(int j=0; j<vecsize; j++)		//przechodzimy przez kazdego sasiada
		{
			lista.add(graf.tab[i][j]);
			licznik++;
		}
	}
	
	GraphL tree;
	tree.createEmpty(nodes,false);
	stack <int> stosik;
		
	
//				if(cycle(graf,5,5,stosik,visited)) cout<<"\njest cykl\n";
	//		else cout<<"\nnie ma\n";
	
	while (lista.size!=0)
	{
		stack <int> stos;
		for (int i=0; i<nodes; i++)
			visited[i]=false;
		
		Edge candidate = lista.remove();
		//candidate.show();
/*		if(tree.edges==0)
		{
			tree.addEdge(candidate,candidate.start);
			continue;
		}*/
		//else
		{
			tree.addEdge(candidate,candidate.start);
			if(cycle(tree,candidate.start,candidate.start,stos,visited))
			{
				tree.tab[candidate.start].pop_back();
				tree.tab[candidate.end].pop_back();	
			}
		}
		
		
	}
	tree.show();
	
}

void KruskalM(GraphM & graf)
{

	int nodes=graf.nodes;
	int lines=graf.lines;
	bool visited[nodes];
	stack <int> stosik;
	
	for(int i=0; i<nodes; i++)
		visited[i]=false;
	
	GraphM wynikowy;
	wynikowy.createEmpty(nodes,false);

	priority_queue < EdgM, vector < EdgM >, compareEdge > lista;
	
	for(int i=0; i<lines; i++)
	{
		EdgM krawedz;
		krawedz.pos=i;
		krawedz.weight=graf.Weight[i];
		lista.push(krawedz);	
	}
	
	int newedge=0;
	while(!lista.empty())	//dopoki na liscie sa elementy
	{
		//stack <int> stos;
		for (int i=0; i<nodes; i++)	//oznacz wszystkie wierzcholki jako nieodwiedzone - przyda sie w rekurencyjnej funkcji sprawdzania czy jest cykl
			visited[i]=false;
		EdgM kraw;					//stworz pomocnicza zmienna
		kraw=lista.top();			//sciagnij z kolejki krawedz o najmniejszej wadze
		lista.pop();				//usun go z kolejki
		int nrkraw=kraw.pos;			//pobierz dane ktora to krawedz w zrodlowym grafie
		int poczkraw=graf.findStartEdge(kraw.pos);		//sprawdz gdzie sie zaczyna
		int konckraw=graf.findEndEdge(kraw.pos,poczkraw);	//sprawdz gdzie sie konczy
		wynikowy.addEdge(poczkraw,konckraw,kraw.weight);	//dodaj ja do grafu wynikowego
		/*
		for(int i=0; i<nodes; i++)
		{
			wynikowy.Matrix[i][newedge]=graf.Matrix[i][kraw.pos];
		}
		wynikowy.Weight[newedge]=kraw.weight;*/
		
		if(cycleM(wynikowy,wynikowy.findStartEdge(newedge),wynikowy.findStartEdge(newedge),stosik,visited)) //jesli dodana krawedz spowodowala ze powstal cykl
		{
			wynikowy.deleteEdge();		//to usun ja z grafu wyniokwego
		}	
		else newedge++;		//a jesli nie, to zostaw i zwieksz licznik, ktory pozwoli na dodanie kolejnych 
	}
	
	wynikowy.show();

}

bool cycleM(GraphM &graf, int v, int w, stack <int> &S, bool * visited2)
{
	int u;
	visited2[w]=true;
	stack <int> sasiedzi;
	for(int i=0; i<graf.lines; i++)
	{
		if(graf.Matrix[w][i]==1)
		{
			sasiedzi.push(graf.findEndEdge(i,w));		
		}
	}
	int nbr=sasiedzi.size();	
		
		
	while(nbr>0)
	{
		u=sasiedzi.top();
		sasiedzi.pop();
		if (!S.empty())
		{
			if(u==S.top())
			{
				nbr--;
				continue;
			}		
		}
		S.push(w);
		if(u==v) return true;
		if(visited2[u]==false && cycleM(graf,v,u,S,visited2)==true) return true;
		S.pop();
		nbr--;
	}
	return false;
}


















