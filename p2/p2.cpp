/***********************************
** CS 101 - Programming Project 2 **
**          Sean Gillen           **
**         CWID 11718859          **
***********************************/

#include <iostream>
#include <string>
#include <vector> //sorry
#include <sstream>
#include <limits>

using namespace std;

class Array {
	private:
		int dimensions;
		vector<int> sizes;
		vector<int> values;
	public:
		Array(){} //Private variables remain uninitialized until Array(D,S,V) is called
		Array(int numdims, string dimlist, string valuelist){
			dimensions = numdims;
			
			if (dimensions > 0){
				stringstream dl(dimlist); //Comma-separated list of integers (dimlist)
				string size;
				while(getline(dl,size,',')) //For each comma-separated value
					sizes.push_back(stoi(size)); //Insert into sizes vector
			}
			
			stringstream vl(valuelist); //Comma-separated list of integers (valuelist)
			string value;
			while(getline(vl,value,',')) //For each comma-separated value
				values.push_back(stoi(value)); //Insert into values vector
		}
		Array(int numdims, vector<int> dimlist, vector<int> valuelist){
			dimensions = numdims;
			sizes = dimlist;
			values = valuelist;
		}
		
		Array apply(Array array2, string operation){
			vector<int> resultValues;
			resultValues.resize(values.size());
			
			for(int i = 0; i < values.size(); i++){
				if(operation=="+") resultValues[i] = values[i]+array2.values[i];
				if(operation=="-") resultValues[i] = values[i]-array2.values[i];
				if(operation=="*") resultValues[i] = values[i]*array2.values[i];
				if(operation=="/") resultValues[i] = values[i]/array2.values[i];
				if(operation=="%") resultValues[i] = values[i]%array2.values[i];
				if(operation=="max") resultValues[i] = values[i]>array2.values[i]?values[i]:array2.values[i];
				if(operation=="min") resultValues[i] = values[i]<array2.values[i]?values[i]:array2.values[i];
			}
			
			return Array(dimensions,sizes,resultValues);
		}
		
		Array cross(Array array2, string operation){
			int numdims = dimensions + array2.dimensions;
			
			vector<int> dimSizes = sizes;
			dimSizes.insert(dimSizes.end(), array2.sizes.begin(), array2.sizes.end());
			
			vector<int> resultValues = {};
			for(int i = 0; i < values.size(); i++){
				for(int j = 0; j < array2.values.size(); j++){
					if(operation=="+") resultValues.push_back(values[i]+array2.values[j]);
					if(operation=="-") resultValues.push_back(values[i]-array2.values[j]);
					if(operation=="*") resultValues.push_back(values[i]*array2.values[j]);
					if(operation=="/") resultValues.push_back(values[i]/array2.values[j]);
					if(operation=="%") resultValues.push_back(values[i]%array2.values[j]);
					if(operation=="max") resultValues.push_back(values[i]>array2.values[j]?values[i]:array2.values[j]);
					if(operation=="min") resultValues.push_back(values[i]<array2.values[j]?values[i]:array2.values[j]);
				}
			}
			
			return Array(numdims,dimSizes,resultValues);
		}
		
		Array join(Array array2, string operation){
			int numdims = dimensions + array2.dimensions - 1;
			
			vector<int> dimSizes = sizes;
			dimSizes.insert(dimSizes.end(), array2.sizes.begin()+1, array2.sizes.end());
			
			vector<int> resultValues;
			int resultSize = 1;
			for(int i = 0; i < numdims; i++){ resultSize *= dimSizes[i]; }
			resultValues.resize(resultSize);
			
			for(int i = 0; i < resultSize; i++){
				resultValues[i] = values[i / (resultSize / values.size())] * array2.values[i % array2.values.size()]; //My best guess as to how this is supposed to work - I don't fully understand the description of what join does
			}
			
			return Array(numdims,dimSizes,resultValues);
		}
		
		Array reduce(string operation, int dimension){
			int numdims = dimensions - 1;
			
			vector<int> dimSizes;
			dimSizes = sizes;
			dimSizes.erase(dimSizes.begin()+dimension);
			dimSizes.resize(numdims);
			
			vector<int> resultValues;
			
			int groups = 1;
			for(int i = 0; i < dimension; i++) groups *= sizes[i];
			int groupsize = values.size()/groups;
			int combineEvery = groupsize/sizes[dimension];
			
			for(int group = 0; group < groups; group++){
				for(int offset = 0; offset < combineEvery; offset++){
					int combinedValue;
					if(operation=="+" || operation=="max") combinedValue=0;
					if(operation=="*") combinedValue=1;
					if(operation=="min") combinedValue=numeric_limits<int>::max();
					
					for(int n = 0; n < groupsize; n+=combineEvery){
						int index = group*groupsize + n + offset;
						if(operation=="+") combinedValue += values[index];
						if(operation=="*") combinedValue *= values[index];
						if(operation=="max") combinedValue = combinedValue>values[n] ? combinedValue : values[index];
						if(operation=="min") combinedValue = combinedValue<values[n] ? combinedValue : values[index];
					}
					
					resultValues.push_back(combinedValue);
				}
			}
			
			return Array(numdims,dimSizes,resultValues);
		}
		
		Array catenate(Array array2, int dimension){
			int numdims = dimensions;
			
			vector<int> dimSizes = sizes;
			dimSizes[dimension] += array2.sizes[dimension];
			
			vector<int> resultValues;
			
			int groups = 1;
			for(int i = 0; i < dimension; i++) groups *= sizes[i];
			int groupsize1 = values.size()/groups;
			int groupsize2 = array2.values.size()/groups;
			
			for(int group = 0; group < groups; group++){
				for(int i = 0; i < groupsize1; i++){
					resultValues.push_back(values[group*groupsize1 + i]);
				}
				for(int i = 0; i < groupsize2; i++){
					resultValues.push_back(array2.values[group*groupsize2 + i]);
				}
			}			
			
			return Array(numdims,dimSizes,resultValues);
		}
		
		string toString(){			
			stringstream str;
			
			if(dimensions == 0) {
				str << values[0];
				return str.str();
			}
			
			vector<int> dimCounters;
			dimCounters.resize(dimensions);
			fill(dimCounters.begin(),dimCounters.end(),0);
			
			vector<int> dimCounterLimits = dimCounters;
			dimCounterLimits[0] = values.size();
			for(int i = 1; i < dimensions; i++){
				dimCounterLimits[i] = dimCounterLimits[i-1] / sizes[i-1];
			}
			
			for(int i = 0; i < dimensions; i++){ //Opening brackets
				str << "[";
			}
			
			for(int i = 0; i < values.size(); i++){ //Iterate over values
				str << values[i];
				
				for(int counter = 0; counter <= dimensions; counter++){
					if(counter == dimensions) { //If no counters matched
						str << ",";
						break;
					}
					dimCounters[counter]++;
					if(dimCounters[counter] == dimCounterLimits[counter]){
						for(int j = dimensions; j > counter; j--){
							str << "]"; //Close brackets for all finished dimensions
							dimCounters[j-1] = 0; //Reset counters for finished dimensions
						}
						if(counter > 0) { //If we didn't just close the last dimension...
							str << ",";
							for(int j = dimensions; j > counter; j--) str << "["; //Open brackets for next list with counters reset to 0
						}
						
						break; //Subsequent counters have been reset to 0
					}
				}
			}
			
			
			return str.str();
		}
};

int index(char name){ //Array name -> index in arrays[]
	int n = name;
	return n - 65;
}

int main() {
	Array arrays[26];
	char name;
	while (cin >> name){
		int n = index(name);
		
		string command;
		cin >> command;
		
		if (command == "build"){
			int numdims;
			string colon, dimlist, valuelist;
			cin >> numdims >> colon;
			if (numdims == 0) dimlist="";
			else cin >> dimlist;
			cin >> colon >> valuelist;
			arrays[n] = Array(numdims,dimlist,valuelist);
		}
		
		if (command == "apply" || command == "cross" || command == "join"){
			char name1, name2;
			string operation;
			cin >> name1 >> name2 >> operation;
			int n1 = index(name1);
			int n2 = index(name2);
			if (command == "apply") arrays[n] = arrays[n1].apply(arrays[n2],operation);
			if (command == "cross") arrays[n] = arrays[n1].cross(arrays[n2],operation);
			if (command == "join")  arrays[n] = arrays[n1].join (arrays[n2],operation);
		}
		
		if (command == "reduce"){
			char name1;
			string operation;
			int dimension;
			cin >> name1 >> operation >> dimension;
			int n1 = index(name1);
			arrays[n] = arrays[n1].reduce(operation,dimension);
		}
		
		if (command == "catenate"){
			char name1, name2;
			int dimension;
			cin >> name1 >> name2 >> dimension;
			int n1 = index(name1);
			int n2 = index(name2);
			arrays[n] = arrays[n1].catenate(arrays[n2],dimension);
		}
		
		cout << name << " = " << arrays[n].toString() << endl;
	}
}