/***********************************
** CS 101 - Programming Project 4 **
**          Sean Gillen           **
**         CWID 11718859          **
***********************************/

#include <iostream>
#include <fstream>
using namespace std;

struct node {
	int value;
	node *left, *right;
	node(int v) {
		value = v;
		left = right = NULL;
	}
};

class tree {
	public:
		tree() {root = NULL;}
		void ins(int v, node* &n){
			if(n == NULL) n = new node(v);
			else ins(v,(v < n->value ? n->left : n->right));
		}
		void ins(int v) { ins(v,root); }
		void print(node* n, int level = 0){
			if (n) {
				print(n->left, level + 1);
				print(n->right, level + 1);
				cout << n->value << " : " << level << endl;
			}
		}
		void print() { print(root); }
	private:
		node *root;
};

int main(int argc, char* argv[]) {
	ifstream input(argv[1]);
	int v;
	tree t;
	while(input >> v) t.ins(v);
	t.print();
}