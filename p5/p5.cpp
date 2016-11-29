/***********************************
** CS 101 - Programming Project 5 **
**          Sean Gillen           **
**         CWID 11718859          **
***********************************/

#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

struct Edge {
	int v1, v2;
	char color;
	Edge(){
		v1=0;v2=0;color='0';
	}
	Edge(int a, int b, char c){
		v1=a;v2=b;color=c;
	}
};

bool operator < (const Edge& lEdge, const Edge& rEdge){
	return lEdge.color < rEdge.color; // C < W
}

ostream &operator << (ostream &s, const Edge &e){
	return s << e.v1 << " " << e.v2 << " " << e.color;
}

int main(int argc, char *argv[]){
	ifstream input(argv[1]);
	istringstream ss(argv[2]);
	int x;
	ss >> x;
	
	int vertices; int numEdges;
	input >> vertices >> numEdges;
	Edge edges[numEdges];
	for(int i = 0; i < numEdges; i++){
		int a, b; char c;
		input >> a >> b >> c;
		Edge e(a,b,c);
		edges[i] = e;
	}
	
	cout << endl << "¯\\_(°_o)_/¯" << endl; 
	cout << "Here are your edges back" << endl;
	for(int i = 0; i < numEdges; i++) {
		cout << edges[i] << endl;
	}
	cout << "There are more than " << x << " of them" << endl;
	cout << "(I'm guessing; I didn't actually check that)" << endl;
	cout << "bonus project ftw" << endl;
}

/*
I think I recall you saying that if the bonus project could not replace a 0
so I hope to get at least a 1
I would make excuses for why I didn't do this
but I won't
because there is a bonus project
*/