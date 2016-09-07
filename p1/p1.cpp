/***********************************
** CS 101 - Programming Project 1 **
**          Sean Gillen           **
**         CWID 11718859          **
***********************************/


#include <iostream> //cin, cout
#include <vector> //vector
#include <fstream> //ifstream, ofstream
#include <algorithm> //find, sort

using namespace std;

bool invector(vector<string> vector,string value){ //true if vector contains value, false if not contained
	return (find(vector.begin(),vector.end(),value) != vector.end());
}

bool intcomp(string in1, string in2){ //compares strings i and j as int
	int i = stoi(in1);
	int j = stoi(in2);
	return (i<j);
}

vector<string> outv(vector<string> in1, vector<string> in2, string type){ //returns sorted vector containing values found in in1 but not in2
	vector<string> output;
	for(auto i : in1){
		if(invector(in2,i)) continue; //skip values found in in2
		if(invector(output,i)) continue; //skip duplicate values
		output.push_back(i); //add remaining values to output
	}
	if(type == "int") sort(output.begin(),output.end(),intcomp); //sort output for type int
	else sort(output.begin(),output.end()); //sort output for type str
	return output;
}

int main(int argc, char* argv[]) {
	vector<string> in1, in2;	//int inputs will be cast to string
	string buffer;
	
	while(cin >> buffer) {		//inputs from stdin
		in1.push_back(buffer);
	}
	
	ifstream infile;			//inputs from file
	infile.open(argv[2]);
	while(infile >> buffer) {
		in2.push_back(buffer);
	}
	infile.close();
	
	vector<string> out1, out2;
	out1 = outv(in1,in2,argv[1]); //outputs for stdout
	out2 = outv(in2,in1,argv[1]); //outputs for file
	
	for(auto i : out1) { //output to stdout
		cout << i << endl;
	}
	
	ofstream outfile;			//output to file
	outfile.open(argv[3]);
	for(auto i : out2) {	
		outfile << i << endl;
	}
	outfile.close();
	
	return 0;
}