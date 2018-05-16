#include "Lista.h"

GraphL::GraphL()
{
	tab = new vector<Edge> [1];
	size=1;
	edges=1;
	direct=false;
}

void GraphL::addNode()
{
	++size;
	vector<Edge> * tmp;
	tmp = new vector<Edge> [size];
	
	for(int i=0; i<size-1; i++)
		tmp[i]=tab[i];
	
	delete [] tab;
	tab=tmp;
}

void GraphL::addEdge(Edge e, int pos)
{
	tab[pos].push_back(e);
	edges++;
}

void GraphL::create(bool directed)
{
	ifstream fin;
	fin.open("dane2.txt");
	fin>>edges>>size;
	
	direct = directed;
	tab = new vector<Edge> [size];
	
	int start;
	
	for(int i=0; i<edges; i++)
	{
		Edge k,l;
		if(directed)
		{
			fin>>k.start>>k.end>>k.weight;
			if(!check(k.start,k.end))
				addEdge(k,k.start);
		}
		else
		{
			fin>>k.start>>k.end>>k.weight;
			if(!check(k.start,k.end))
				addEdge(k,k.start);
			
			l.end=k.start;
			l.start=k.end;
			l.weight=k.weight;
			if(!check(l.start,l.end))
				addEdge(l,l.start);
			
		}
	}	
}

void GraphL::show()
{
	for(int i=0; i<size; i++)
	{
		int length = tab[i].size();
		cout<<i<<" ";
		for(int j=0; j<length; j++)
		{
			cout<<tab[i][j].end<<" ";
		}
		cout<<endl;
	}
}

bool GraphL::check(int s, int e)
{

		int edg = tab[s].size();
		for(int i=0; i<edg; i++)
		{
			if (tab[s][i].end == e)
				return true;
		}
		return false;		
}

void GraphL::createEmpty(int v, bool directed)
{
	tab = new vector<Edge> [v];
	size=v;
	edges=1;
	direct=directed;
}




