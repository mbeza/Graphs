#include "Krawedz.h"

Edge::Edge(int s, int e, int w)
{
	start=s;
	end=e;
	weight=w;
}

Edge::Edge()
{
	end=0;
	weight=0;
	start=0;
}


void Edge::show()
{
	cout<<start<<" "<<end<<" "<<weight<<endl;
}
int Edge::getW()
{
	return weight;
}
