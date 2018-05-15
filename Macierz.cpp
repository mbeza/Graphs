#include "Macierz.h"
#include <fstream>

GraphM::GraphM()
{
	Matrix = new int *[1];
	Matrix[0] = new int [1];
	Matrix[0][0]=0;
	Weight = new int [0];
	nodes=0;
	lines=0;
	direct = false;
}

void GraphM::fill(bool directed)
{
	ifstream fin;
	fin.open("dane.txt");
	fin>>lines>>nodes;
	
	direct = directed;
	Weight = new int [lines];
	Matrix = new int *[nodes];
	for(int i=0; i<nodes; ++i)
	{
		Matrix[i] = new int[lines];
		for(int j=0; j<lines; ++j)
			Matrix[i][j]=0;
	}
	
	int start, end, weight;
	
	for(int i=0; i<lines; ++i)
	{	
		fin>>start>>end>>weight;
		Weight[i]=weight;
		if(direct)
		{
			Matrix[start][i]=1;
			Matrix[end][i]=-1;	
		}
		else
		{
			Matrix[start][i]=1;
			Matrix[end][i]=1;
		}
	}
}

void GraphM::show()
{
	cout<<"   ";
	for(int i=0; i<lines; i++)
	{
		cout<<setw(2);
		cout<<i<<" ";
	}
	cout<<endl<<endl;
	
	for(int i=0; i<nodes; ++i)
	{
		cout<<i<<"  ";
		for(int j=0; j<lines; ++j)
		{
			cout<<setw(2);
			cout<<Matrix[i][j]<<" ";
		}
			
		cout<<endl;
	}
	
}

void GraphM::showEdge(int edg)
{
	bool first=false, last=false;
	
	int vrtx=0;
	int start,end;
	
	while(!(first && last))
	{
		if(direct)
		{
			if(Matrix[vrtx][edg]==1)
			{
				start=vrtx;
				first=true;
			}
			if(Matrix[vrtx][edg]==-1)
			{
				end=vrtx;
				last=true;
			}
			vrtx++;	
		}
		else
		{
			if(Matrix[vrtx][edg]==1 && !first)
			{
				start=vrtx;
				first=true;
				vrtx++;
			}
			if(Matrix[vrtx][edg]==1 && first)
			{
				end=vrtx;
				last=true;
			}
			vrtx++;
		}
	}
	
	cout<<start<<"-"<<end<<" "<<Weight[edg];
	

}




