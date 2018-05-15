#include "funkcje.h"


int Prims(GraphL & graf)
{
	
	Heap priority;
	
	int nodes = graf.size;
	bool visited [nodes]; 
	
	for(int i=0; i<nodes; i++)
	{
		visited[i]=false;
	}
	
	list <Edge> zwracane;
	
	int iter=0;
	visited[iter] = true;
	
	
	
	for(int i = 0; i<nodes-1; i++)
	{
		int vecsize = graf.tab[iter].size();
		
		for(int j=0; j<vecsize; j++)
		{
			if (!visited[graf.tab[iter][j].end])
			{
				priority.add(graf.tab[iter][j]);
			}
		}
	
		Edge k;
		
		do
		{
			k=priority.remove();			
		}while(visited[k.end]);
		
		
		zwracane.push_back(k);
		visited[k.end]=i+2;
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

