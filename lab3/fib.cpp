#include <iostream>
using namespace std;

unsigned long fib (unsigned long n) {
	if (n<2) return 1;
	return fib(n-1) + fib(n-2);
}

int main ( ) {
  cout << "fib(0) = "  << fib(0) << endl;
  cout << "fib(5) = "  << fib(5) << endl;
  cout << "fib(10) = " << fib(10) << endl;
  cout << "fib(15) = " << fib(15) << endl;
  cout << "fib(20) = " << fib(20) << endl;
  cout << "fib(25) = " << fib(25) << endl;
  cout << "fib(30) = " << fib(30) << endl;
  cout << "fib(35) = " << fib(35) << endl;
  cout << "fib(40) = " << fib(40) << endl;
  cout << "fib(45) = " << fib(45) << endl;
// cout << "fib(-1) = " << fib(-1) << endl;
// cout << "fib(50) = " << fib(50) << endl;
  return 0;
}