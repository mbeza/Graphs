#include "funkcjesciezka.h"

struct compareVertex
{
	bool operator ()( Vertex & v1, Vertex & v2 )
    {
        //kolejno�� - rosn�co
        if( v1.cost > v2.cost ) return true;
        if( v1.cost < v2.cost ) return false;
        return false;
    }
};

void DijkstryL(GraphL & graf, int s, int e)
{
	int size=graf.size;
	Vertex vert[size];
	bool visited[size];
	
	priority_queue < Vertex, vector < Vertex >, compareVertex > kolejka;
	
	for(int i=0; i<size; i++)
	{
		vert[i].number=i;
		vert[i].cost=2147483647;
		vert[i].prev=-1;
		visited[i]=false;
	}
	
	vert[s].cost=0;		
	bool path=true;
	Vertex l;
	kolejka.push(vert[s]);
	
	while(!visited[e])
	{
		if(!kolejka.empty())
		{
			l=kolejka.top();
			kolejka.pop();			
		}
		else
		{
			path=false;
			break;
		}		
		visited[l.number]=true;
		int nbr=graf.tab[l.number].size();
		while(nbr>0)
		{
			Edge k=graf.tab[l.number][nbr-1];
			nbr--;
			if(visited[k.end]) continue;
			if(vert[k.end].cost > vert[l.number].cost+k.weight)
			{
				vert[k.end].cost = vert[l.number].cost+k.weight;
				vert[k.end].prev = l.number;
				kolejka.push(vert[k.end]);
			}	
		}
	}
	
	
	
	if(!path)	cout<<"\nNie znaleziono drogi\n";
	else	
	{
		cout<<"Koszt dojcia z "<<s<<" do "<<e<<" wynosi: "<<vert[e].cost<<endl<<"Droga: ";
		
		stack <int> kolejnosc;
		int skoczek=e;
		kolejnosc.push(e);
		while(skoczek!=s)
		{
			kolejnosc.push(vert[skoczek].prev);
			skoczek=vert[skoczek].prev;
		}
		
		cout<<kolejnosc.top();
		kolejnosc.pop();
		
		while(!kolejnosc.empty())
		{
			cout<<"->"<<kolejnosc.top();
			kolejnosc.pop();
		}	
	}
		
	
}

void DijkstryM(GraphM & graf, int s, int e)
{
	int size=graf.nodes;
	Vertex vert[size];
	bool visited[size];
	
	priority_queue < Vertex, vector < Vertex >, compareVertex > kolejka;
	
	for(int i=0; i<size; i++)
	{
		vert[i].number=i;
		vert[i].cost=2147483647;
		vert[i].prev=-1;
		visited[i]=false;
	}
	
	vert[s].cost=0;		
	bool path=true;
	Vertex l;	
	kolejka.push(vert[s]);
	
	while(!visited[e])
	{
		if(!kolejka.empty())
		{
			l=kolejka.top();
			kolejka.pop();			
		}
		else
		{
			path=false;
			break;
		}		
		visited[l.number]=true;
		stack <EdgM> nbrs;
		for(int i=0; i<graf.lines; i++)
		{
			if(graf.Matrix[l.number][i]==1)
			{
				EdgM somsiad;
				somsiad.pos=graf.findEndEdge(i,l.number);
				somsiad.weight=graf.Weight[i];
				nbrs.push(somsiad);
			}
		}
			
		while(!nbrs.empty())
		{
			EdgM nbr=nbrs.top();
			nbrs.pop();
			
			if(visited[nbr.pos]) continue;
			if(vert[nbr.pos].cost > vert[l.number].cost+nbr.weight)
			{
				vert[nbr.pos].cost = vert[l.number].cost+nbr.weight;
				vert[nbr.pos].prev = l.number;
				kolejka.push(vert[nbr.pos]);
			}	
		}
	}
	
	if(!path)	cout<<"\nNie znaleziono drogi\n";
	else	
	{
		cout<<"Koszt dojcia z "<<s<<" do "<<e<<" wynosi: "<<vert[e].cost<<endl<<"Droga: ";
		
		stack <int> kolejnosc;
		int skoczek=e;
		kolejnosc.push(e);
		while(skoczek!=s)
		{
			kolejnosc.push(vert[skoczek].prev);
			skoczek=vert[skoczek].prev;
		}
		
		cout<<kolejnosc.top();
		kolejnosc.pop();
		
		while(!kolejnosc.empty())
		{
			cout<<"->"<<kolejnosc.top();
			kolejnosc.pop();
		}	
	}
	
}









