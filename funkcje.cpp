#include "funkcje.h"


void PrimsL(GraphL & graf)
{
	
	Heap priority;				//kolejka priorytetowa na bazie kopca
	
	int nodes = graf.size;		
	bool visited [nodes]; 		//tablica odwiedzonych wierzcholkow
	
	for(int i=0; i<nodes; i++)	//uzupelniamy tablice odwiedzonych wierzcholkow wartosciami false
	{
		visited[i]=false;
	}
	
	list <Edge> zwracane;		//lista na ktorej bedzie drzewo rozpinajace
	
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
		
		
		zwracane.push_back(k);		//do drzewa rozpinajacego dodajemy krawedz
		visited[k.end]=true;		//wierzcholek na drugim koncu krawedzi oznaczamy jako odwiedzony
		iter=k.end;					//i przechodzimy do niego kontynuujac petle
	}
	
	
	int sztuki= zwracane.size();	//pobieramy liczbe krawedzi drzewa rozpinajacego
	for (int i=0; i<sztuki; i++)
	{
		Edge zwr=zwracane.front();	//sciagamy krawedzie z listy, powstaje drzewo rozpinajace
		zwracane.pop_front();		//usuwamy ten element
		cout<<zwr.start<<"-"<<zwr.end<<" ";	//i wyswietlamy
	}
	
	
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
	
	list <Edge> zwracane;		//lista na ktorej bedzie drzewo rozpinajace
	
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
		
		
		zwracane.push_back(k);
		visited[k.end]=true;
		iter=k.end;	
	}
	
	int sztuki= zwracane.size();
	for (int i=0; i<sztuki; i++)
	{
		Edge zwr=zwracane.front();
		zwracane.pop_front();
		cout<<zwr.start<<"-"<<zwr.end<<" ";
	}
}


bool cycle(GraphL &graf, int v, int w, stack<int> &S, bool * visited2)
{
	cout<<"\nwywolanie\n";
	int u;
	visited2[w]=true;
	int nbr=graf.tab[w].size();
	while(nbr>0)
	{
		cout<<"\nwhile\n";
		u=graf.tab[w][nbr-1].end;
		if (!S.empty())
		{
			if(u==S.top())
			{
				cout<<"\nif\n";
				nbr--;
				continue;
			}		
		}
		cout<<"\nprzed push\n";
		S.push(w);
		cout<<"\npush\n";
		if(u==v) return true;
		if(visited2[u]==false && cycle(graf,v,u,S,visited2)==true) return true;
		S.pop();
		nbr--;
	}
	return false;	
}

void KruskalL(GraphL &graf)
{
	Heap lista;
	vector <Edge> zwracane;
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
	tree.createEmpty(nodes);
	stack <int> stosik;
		
	
//				if(cycle(graf,5,5,stosik,visited)) cout<<"\njest cykl\n";
	//		else cout<<"\nnie ma\n";
	
	while (lista.size!=0)
	{
		stack <int> stos;
		for (int i=0; i<nodes; i++)
			visited[i]=false;
		
		Edge candidate = lista.remove();
		candidate.show();
		if(tree.edges==0)
		{
			tree.addEdge(candidate,candidate.start);
			cout<<" -dodane\n";
			continue;
		}
		else
		{
			tree.addEdge(candidate,candidate.start);
			cout<<" -dodane ";
			if(cycle(tree,candidate.start,candidate.start,stos,visited))
			{
				tree.tab[candidate.start].pop_back();
				cout<<" i usuniete\n";	
			}
		}
		
		
	}
	
	tree.show();
	

	
	
}




