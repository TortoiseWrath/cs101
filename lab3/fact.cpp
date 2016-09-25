#include <iostream>
using namespace std;

unsigned long fact (unsigned long n) {
	if (n==0) return 1;
	return n * fact(n-1);
}

int main ( ) {
  cout << "fact(3) = " << fact(3) << endl;
  cout << "fact(4) = " << fact(4) << endl;
  cout << "fact(5) = " << fact(5) << endl;
  cout << "fact(6) = " << fact(6) << endl;
  cout << "fact(7) = " << fact(7) << endl;
  cout << "fact(8) = " << fact(8) << endl;
  cout << "fact(10) = " << fact(10) << endl;
  cout << "fact(15) = " << fact(15) << endl;
  cout << "fact(20) = " << fact(20) << endl;
// cout << "fact(-1) = " << fact(-1) << endl;
// cout << "fact(21) = " << fact(21) << endl;
  return 0;
}

