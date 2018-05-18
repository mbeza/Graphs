#include "Macierz.h"
#include <fstream>

GraphM::GraphM()
{
	Matrix = new int *[0];
	Matrix[0] = new int [0];
	Weight = new int [0];
	nodes=0;
	lines=0;
	direct = false;
	connectivity=false;
}

void GraphM::create(bool directed, string filename)
{
	ifstream fin;
	fin.open(filename.c_str());

	for(int i=0; i<nodes; i++)
	{
		delete [] Matrix[i];	
	}
	
	delete [] Matrix;
	delete [] Weight;
	
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
		if(!check(start,end))
		{
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
	
	checkConnectivity();
	fin.close();
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
	cout<<endl;
	
}

void GraphM::showEdge(int s, int e)
{	
	if(direct)
		{
			for(int i=0; i<lines; i++)
			{
				if(Matrix[s][i]==1 && Matrix[e][i]==-1) cout<<s<<"->"<<e<<" $"<<Weight[i]<<endl;
			}
		}
		else
		{
			for(int i=0; i<lines; i++)
			{
				if(Matrix[s][i]==1 && Matrix[e][i]==1) cout<<s<<"-"<<e<<" $"<<Weight[i]<<endl;
			}
		}	
}

void GraphM::addEdge(int s, int e, int w)
{
	if(!check(s,e))
	{
		lines++;
		int * tmp;
		for(int i=0; i<nodes; ++i)
		{
			tmp = new int[lines];
			for(int j=0; j<lines; ++j)
			{
				if(j==lines-1) tmp[j]=0;
				else tmp[j]=Matrix[i][j]; 
			}
			delete Matrix[i];
			Matrix[i]=tmp;		
		}
		
		if(direct)
		{
			Matrix[s][lines-1]=1;
			Matrix[e][lines-1]=-1;	
		}
		else
		{
			Matrix[s][lines-1]=1;
			Matrix[e][lines-1]=1;
		}
	
		int *tmpW = new int [lines];
		
		for(int i=0; i<lines-1; i++)
			tmpW[i]=Weight[i];
		tmpW[lines-1]=w;
		delete Weight;
		Weight=tmpW;
	}
	checkConnectivity();
}

void GraphM::addNode()
{
	nodes++;
	int **tmpM = new int *[nodes];
	for(int i=0; i<nodes-1; i++)
		tmpM[i]=Matrix[i];
	tmpM[nodes-1]=new int [lines];
	
	for(int i=0; i<lines; i++)
		tmpM[nodes-1][i]=0;
	delete [] Matrix;
	Matrix=tmpM;
	checkConnectivity();
}


void GraphM::createEmpty(int v, bool directed, int edg)
{
	Matrix = new int *[v];
	for(int i=0; i<v; i++)
		Matrix[i] = new int [edg];
	Weight = new int [edg];
	nodes=v;
	lines=edg;
	direct=directed;
}

int GraphM::findStartEdge(int edg)
{
	bool first=false,last=false;
	
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
	return start;
}

int GraphM::findEndEdge(int edg, int strt)
{
	bool first=false,last=false;
	
	int vrtx=0;
	int start,end;
	
	for(int i=0; i<nodes; i++)
	{
		if(direct)
		{
			if(Matrix[i][edg]==-1) return i;
		}
		else
		{
			if(Matrix[i][edg]==1 && i!=strt) return i;
		}
	}
	
}

void GraphM::deleteEdge()
{
	lines--;
	
	int **tmpM = new int *[nodes];
	for(int i=0; i<nodes; ++i)
	{
		tmpM[i] = new int[lines];
		for(int j=0; j<lines; ++j)
		{
			tmpM[i][j]=Matrix[i][j]; 
		}		
	}
	
	for(int i=0; i<nodes; i++)
	{
		delete [] Matrix[i];	
	}
	delete [] Matrix;
	Matrix=tmpM;
	
	int *tmpW = new int [lines];
	
	for(int i=0; i<lines; i++)
		tmpW[i]=Weight[i];
	delete Weight;
	Weight=tmpW;
	
}

bool GraphM::check(int s, int e)
{
	if(direct)
	{
		for(int i=0; i<lines; i++)
		{
			if(Matrix[s][i]==1 && Matrix[e][i]==-1) return true;
		}
		return false;
	}
	else
	{
		for(int i=0; i<lines; i++)
		{
			if(Matrix[s][i]==1 && Matrix[e][i]==1) return true;
		}
		return false;
	}
}
	
void GraphM::editEdge(int s, int e, int w)
{
	if(direct)
	{
		for(int i=0; i<lines; i++)
		{
			if(Matrix[s][i]==1 && Matrix[e][i]==-1) Weight[i]=w;
		}
	}
	else
	{
		for(int i=0; i<lines; i++)
		{
			if(Matrix[s][i]==1 && Matrix[e][i]==1) Weight[i]=w;
		}
	}	
}

void GraphM::checkConnectivity()
{	
	GraphM graf2;
	graf2.createEmpty(nodes,false,lines);
	for(int i=0; i<nodes; i++)
	{
		for(int j=0; j<lines; j++)
		{
			if(Matrix[i][j]==1 || Matrix[i][j]==-1) graf2.Matrix[i][j]=1;
		}
	}
	
	
	bool visited[nodes];
	for(int i=0; i<nodes; i++)
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
		
		stack <int> nbrs;
		for(int n=0; n<lines; n++)
		{
			if(graf2.Matrix[v][n]==1)
			{
				nbrs.push(graf2.findEndEdge(n,v));
			}
		}
		
		while(!nbrs.empty())
		{
			int u=nbrs.top();
			nbrs.pop();
			if(!visited[u])
			{
				visited[u]=true;
				stos.push(u);
			}
		}
	}
	
	if(countvisited==nodes) connectivity=true;
	else connectivity=false;
}






