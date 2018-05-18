#include "Lista.h"

GraphL::GraphL()
{
	tab = new vector<Edge> [1];
	size=1;
	edges=1;
	direct=false;
}

GraphL::GraphL(bool direction)
{
	tab = new vector<Edge> [1];
	size=1;
	edges=1;
	direct=direction;
}

GraphL::GraphL(GraphL & ref)
{
	tab = new vector <Edge> [ref.size];
	size=ref.size;
	direct=ref.direct;
	
	for(int i=0; i<size; i++)
	{
		int ile= ref.tab[i].size();
		for(int j=0; j<ile; j++)
		{
			addEdge(ref.tab[i][j],i);
		}
	}
	edges=ref.edges;
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

void GraphL::create(bool directed, string filename)
{
	ifstream fin;
	int edges2;
	fin.open(filename.c_str());
	fin>>edges2>>size;
	
	
	direct = directed;
	tab = new vector<Edge> [size];
	
	int start;
	
	for(int i=0; i<edges2; i++)
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
	edges=edges2;	
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




