#include "Lista.h"

GraphL::GraphL()
{
	tab = new vector<Edge> [0];
	size=0;
	edges=0;
	direct=false;
	connectivity=false;
}

GraphL::GraphL(bool direction)
{
	tab = new vector<Edge> [0];
	size=0;
	edges=0;
	direct=direction;
	connectivity=false;
}

GraphL::GraphL(GraphL & ref)
{
	tab = new vector <Edge> [ref.size];
	size=ref.size;
	direct=ref.direct;
	connectivity=ref.connectivity;
	
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
	checkConnectivity();
}

void GraphL::addEdge(Edge e, int pos)
{
	if(direct)
	{
		if(!check(e.start,e.end))
			tab[pos].push_back(e);
	}
	else
	{
		Edge k;
		if(!check(e.start,e.end))
			tab[pos].push_back(e);
			
		k.end=e.start;
		k.start=e.end;
		k.weight=e.weight;
		if(!check(k.start,k.end))
			tab[k.start].push_back(k);
	}
	edges++;
	checkConnectivity();	
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
		Edge k;
		fin>>k.start>>k.end>>k.weight;
		addEdge(k,k.start);		
	}
	edges=edges2;
	fin.close();
	checkConnectivity();
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
	edges=0;
	direct=directed;
	connectivity=false;
}

void GraphL::checkConnectivity()
{	
	GraphL graf2;
	graf2.createEmpty(size,false);
	for(int i=0; i<size; i++)
	{
		for(int j=0; j<tab[i].size(); j++)
		{
			if(direct)
			{
				Edge k=tab[i][j],l;
				graf2.tab[i].push_back(k);
					
				l.end=k.start;
				l.start=k.end;
				l.weight=k.weight;
				graf2.tab[l.start].push_back(l);
			}
			else
			{
				graf2.tab[i].push_back(tab[i][j]);
			}
		}
	}
		
	bool visited[size];
	for(int i=0; i<size; i++)
		visited[i]=false;
	int countvisited=0;
	stack <int> stos;
	stos.push(0);
	visited[0]=true;
	
	while(!stos.empty())
	{
		int v=stos.top();
		stos.pop();
		countvisited++;
		
		for(int i=0; i<graf2.tab[v].size(); i++)
		{
			int u=graf2.tab[v][i].end;
			if(!visited[u])
			{
				visited[u]=true;
				stos.push(u);
			}
		}
	}
	
	if(countvisited==size) connectivity=true;
	else connectivity=false;
}




