/***********************************
** CS 101 - Programming Project 3 **
**          Sean Gillen           **
**         CWID 11718859          **
***********************************/

#include <iostream>
#include <fstream>
#include <string>
using namespace std;


struct Node {
	int quantity;
	float price;
	Node *prev, *next;
};

class BalanceList {
	public:
		BalanceList() {
			firstNode = NULL;
			lastNode = NULL;
		}
		void push(int q, float p) {
			if(lastNode == NULL) {
				Node *n = new Node;
				n->quantity=q; n->price=p;
				n->prev = NULL; n->next = NULL;
				firstNode = n;
				lastNode = n;
			}
			else {
				Node *n = new Node;
				n->quantity=q; n->price=p; n->next=NULL;
				lastNode->next = n;
				n->prev = lastNode;
				lastNode = n;
			}
		}
		void enqueue(int q, float p) {
			if(firstNode == NULL) { push(q,p); }
			else {
				Node *n = new Node;
				n->quantity=q; n->price=p; n->prev=NULL;
				firstNode->prev = n;
				n->next = firstNode;
				firstNode = n;
			}
		}
		Node* pop() {
			Node *n = lastNode;
			if(n->prev == NULL) {
				lastNode = NULL;
				firstNode = NULL;
			}
			else {
				lastNode = n->prev;
				lastNode->next = NULL;
			}
			return n;
		}
	private:
		Node *firstNode;
		Node *lastNode;
};

int main() {
	string transactionType;
	BalanceList fifo, lifo;
	int sharesOwned = 0; float meanCost = 0; //for weighted average
	float totalFIFO = 0, totalLIFO = 0, totalWtAvg = 0;
	ifstream input("Transactions.txt");
	ofstream outFIFO("FIFO.txt"), outLIFO("LIFO.txt"), outWtAvg("WtAvg.txt");
	while (input >> transactionType) {
		if (transactionType == "Buy") {
			int quantity; float price;
			input >> quantity >> price;
			fifo.enqueue(quantity, price);
			lifo.push(quantity, price);
			meanCost = (meanCost * sharesOwned + quantity * price) / (sharesOwned + quantity);
			sharesOwned += quantity;
		}
		else if (transactionType == "Sell") {
			int quantity; float price;
			input >> quantity >> price;
			
			//Weighted average
			sharesOwned -= quantity;
			float gain = quantity * (price - meanCost);
			totalWtAvg += gain;
			outWtAvg << "Gain = " << gain << endl;
			
			//LIFO
			int remainingQuantity = quantity;
			float totalCost = 0;
			while (remainingQuantity > 0) {
				Node *n = lifo.pop();
				if (n->quantity > remainingQuantity) {
					totalCost += n->price * remainingQuantity;
					lifo.push(n->quantity - remainingQuantity, n->price);
					remainingQuantity = 0;
				}
				else {
					totalCost += n->price * n->quantity;
					remainingQuantity -= n->quantity;
				}
			}
			gain = price * quantity - totalCost;
			totalLIFO += gain;
			outLIFO << "Gain = " << gain << endl;
			
			//FIFO
			remainingQuantity = quantity;
			totalCost = 0;
			while (remainingQuantity > 0) {
				Node *n = fifo.pop();
				if (n->quantity > remainingQuantity) {
					totalCost += n->price * remainingQuantity;
					fifo.enqueue(n->quantity - remainingQuantity, n->price);
					remainingQuantity = 0;
				}
				else {
					totalCost += n->price * n->quantity;
					remainingQuantity -= n->quantity;
				}
			}
			gain = price * quantity - totalCost;
			totalFIFO += gain;
			outFIFO << "Gain = " << gain << endl;
		}
		else {
			cout << "Invalid input: " << transactionType << endl;
			break;
		}
	}
	outFIFO << "Total = " << totalFIFO;
	outLIFO << "Total = " << totalLIFO;
	outWtAvg << "Total = " << totalWtAvg;
	return 0;
}