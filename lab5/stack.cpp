#include <iostream>
#include <list>
#include <cstring>

using namespace std;

short charType(char character){ // Returns 0 for left, 1 for right, -1 for invalid
	if(character=='['||character=='('||character=='<'||character=='{') return 0;
	if(character==']'||character==')'||character=='>'||character=='}') return 1;
	return -1;
}

bool matches(char char1, char char2){ //char1 is left, char2 is right
	if(char1=='['&&char2==']') return true;
	if(char1=='('&&char2==')') return true;
	if(char1=='<'&&char2=='>') return true;
	if(char1=='{'&&char2=='}') return true;
	return false;
}

int main(int argc, char* argv[]){
	list<char> stack;
	for(int i = 0; i <= strlen(argv[1]); i++){
		cout << "Stack: ";
		for(list<char>::const_iterator iterator = stack.begin(); iterator != stack.end(); ++iterator){
			cout << *iterator << " ";
		}
		cout << endl;
		
		if(i == strlen(argv[1])){
			cout << "Reached end of string" << endl;
			if(stack.empty())
				cout << "String is properly balanced" << endl;
			else
				cout << "Error: unmatched left symbol " << stack.back() << endl;
			return 0;
		}
		
		cout << "Character: " << argv[1][i] << endl;
		
		short type = charType(argv[1][i]);
		if(type == -1){
			cout << "Error: invalid character " << argv[1][i] << endl;
			return 0;
		}
		if(type == 0){
			cout << "Push" << endl;
			stack.push_back(argv[1][i]);
		}
		if(type == 1){
			if(!stack.empty()){
				char back = stack.back();
				bool match = matches(back,argv[1][i]);
				if(match){
					cout << "Matching " << back << " and " << argv[1][i] << endl;
					cout << "Pop" << endl;
					stack.pop_back();
				}
				else{
					cout << "Error: mismatched pair " << back << " and " << argv[1][i];
					return 0;
				}
			}
			else{
				cout << "Error: unmatched right symbol " << argv[1][i];
				return 0;
			}
		}
	}
	
} 