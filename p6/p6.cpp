/***********************************
** CS 101 - Programming Project 6 **
**          Sean Gillen           **
**         CWID 11718859          **
***********************************/

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

struct Path {
	int cost, duration;
	Path(){
		cost = duration = 1000000;
	}
	Path(int c, int d){
		cost = c;
		duration = d;
	}
};
struct Edge {
	int from, to, cost, duration;
	Edge(){
		from = to = 1000000;
		cost = duration = 1000000;
	}
	Edge(int a, int b, int c, int d){
		from = a;
		to = b;
		cost = c;
		duration = d;
	}
};


int main(int argc, char *argv[]) {
	ifstream input(argv[1]);
	istringstream sFrom(argv[2]);
	istringstream sTo(argv[3]);
	istringstream sMax(argv[4]);
	
	int from, to, maxDuration, numVertices, numEdges;
	sFrom >> from; sTo >> to; sMax >> maxDuration;
	input >> numVertices >> numEdges;
	
	Edge *edges[numEdges];
	vector<Path> vertices[numVertices];
	
	int a, b, c, d, i, j;
	for(i = 0; i < numEdges; i++){
		input >> a >> b >> c >> d;
		edges[i] = new Edge(a,b,c,d);
	}
	
	vertices[from].push_back(Path(0,0));
	
	bool changed = false;
	bool panic = false;
	for(i = 0; i < numVertices - 1; i++) {
		changed = false;
		for(j = 0; j < numEdges; j++) {
			for(vector<Path>::iterator it = vertices[edges[j]->from].begin(); it != vertices[edges[j]->from].end(); it++) {
				if(it->duration + edges[j]->duration > maxDuration) continue;
				if(!vertices[edges[j]->to].empty()) for(vector<Path>::iterator it2 = vertices[edges[j]->to].begin(); it2 != vertices[edges[j]->to].end(); it2++) {
					panic = false;
					if(it->duration + edges[j]->duration > it2->duration && it->cost + edges[j]->cost > it2->cost){
						panic = true;
						continue;
					} 
					if (panic) continue;
					if(it->duration + edges[j]->duration < it2->duration && it->cost + edges[j]->cost < it2->cost){
						
						it = vertices[edges[j]->to].erase(it2);
					} 
				}
				vertices[edges[j]->to].push_back(Path(it->cost + edges[j]->cost, it->duration + edges[j]->duration));
			}
		}
		if(!changed) break;
	}
	
	
	if(vertices[to].empty()) cout << "0" << endl;
	else {
		int cost = 1000000;
		for(vector<Path>::iterator it = vertices[to].begin(); it != vertices[to].end(); it++){
			if(it->cost < cost) cost = it->cost;
		}
		cout << cost << endl;
	}
}