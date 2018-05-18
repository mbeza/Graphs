#include "Macierz.h"
#include <fstream>

GraphM::GraphM()
{
	Matrix = new int *[1];
	Matrix[0] = new int [0];
	Matrix[0][0]=0;
	Weight = new int [0];
	nodes=0;
	lines=0;
	direct = false;
}

void GraphM::create(bool directed, string filename)
{
	ifstream fin;
	fin.open(filename.c_str());
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
	
	cout<<start<<"-"<<end<<" "<<Weight[edg]<<endl;
	
}

void GraphM::addEdge(int s, int e, int w)
{
	lines++;
	
	int **tmpM = new int *[nodes];
	for(int i=0; i<nodes; ++i)
	{
		tmpM[i] = new int[lines];
		for(int j=0; j<lines; ++j)
		{
			if(j==lines-1) tmpM[i][j]=0;
			else tmpM[i][j]=Matrix[i][j]; 
		}		
	}
	
	if(direct)
	{
		tmpM[s][lines-1]=1;
		tmpM[e][lines-1]=-1;	
	}
	else
	{
		tmpM[s][lines-1]=1;
		tmpM[e][lines-1]=1;
	}
	
	
	for(int i=0; i<nodes; i++)
	{
		delete [] Matrix[i];	
	}
	delete [] Matrix;	
	Matrix=tmpM;
	
	int *tmpW = new int [lines];
	
	for(int i=0; i<lines-1; i++)
		tmpW[i]=Weight[i];
	tmpW[lines-1]=w;
	delete Weight;
	Weight=tmpW;
	
}

void GraphM::addNode()
{
	nodes++;
	int **tmpM = new int *[nodes];
	for(int i=0; i<nodes-1; i++)
		tmpM[i]=Matrix[i];
	tmpM[nodes-1]=new int [lines];
	tmpM[nodes-1][0]={0};
	delete [] Matrix;
	Matrix=tmpM;
}


void GraphM::createEmpty(int v, bool directed)
{
	Matrix = new int *[v];
	for(int i=0; i<v; i++)
		Matrix[i] = new int [0];
	Weight = new int [0];
	nodes=v;
	lines=0;
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
	
	






