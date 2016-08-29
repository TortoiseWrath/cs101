#include <iostream>

using namespace std;

int main() {
	int a, b, c, d;
	a = 1; b = 2; c = 3; d = 4;
	int row, col, k;
	row = 1; col = 0; k = 37;
	row?(col?d=k:c=k):(col?b=k:a=k);
	row = 1; col = 0;
	cout << (row?(col?d:c):(col?b:a));
}