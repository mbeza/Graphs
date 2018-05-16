#include "funkcjesciezka.h"

struct compareVertex
{
	bool operator ()( VertexL & v1, VertexL & v2 )
    {
        //kolejnoœæ - rosn¹co
        if( v1.cost > v2.cost ) return true;
       
        if( v1.cost < v2.cost ) return false;
       
        return false;
    }
};

void DijkstryL(GraphL & graf,int s, int e)
{
	int size=graf.size;
	VertexL vert[size];
	bool visited[size];
	
	int copystart=s;
	priority_queue < VertexL, vector < VertexL >, compareVertex > kolejka;
	
	for(int i=0; i<size; i++)
	{
		vert[i].number=i;
		vert[i].cost=2147483647;
		vert[i].prev=-1;
		visited[i]=false;
	}
	
	vert[s].cost=0;
	visited[s]=true;
	
	bool path=true;
	
	while(!visited[e])
	{
		if(graf.tab[s].empty())
		{
			path=false;
			break;				
		}
		while(!graf.tab[s].empty())
		{

			Edge k=graf.tab[s].back();
			graf.tab[s].pop_back();
			if(vert[k.end].cost > vert[s].cost+k.weight)
			{
				vert[k.end].cost = vert[s].cost+k.weight;
				vert[k.end].prev = s;
				kolejka.push(vert[k.end]);
				cout<<"Wrzucam do kolejki "<<k.end<<endl;
			}
		}
		VertexL d=kolejka.top();
		kolejka.pop();
		visited[d.number]=true;
		s=d.number;
		cout<<"Odwiedzony "<<s<<endl;

	}
		if(!path)	cout<<"\nNie znaleziono drogi\n";
		else cout<<"Koszt dojcia z "<<copystart<<" do "<<e<<" wynosi: "<<vert[e].cost<<endl<<"Na stosie: "<<kolejka.size();
	
}
