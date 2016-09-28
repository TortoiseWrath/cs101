#include <iostream>
using namespace std;

template < unsigned long N >
struct Fib
{
  enum { value = Fib<N-1>::value+Fib<N-2>::value };
};

template < >
struct Fib<0>
{
	enum { value = 1 };
};

template < >
struct Fib<1>
{
	enum { value = 1 };
};


int main ( )
{
  cout << "Fib<0>::value = "  << Fib<0>::value << endl;
  cout << "Fib<5>::value = "  << Fib<5>::value << endl;
  cout << "Fib<10>::value = " << Fib<10>::value << endl;
  cout << "Fib<15>::value = " << Fib<15>::value << endl;
  cout << "Fib<20>::value = " << Fib<20>::value << endl;
  cout << "Fib<25>::value = " << Fib<25>::value << endl;
  cout << "Fib<30>::value = " << Fib<30>::value << endl;
  cout << "Fib<35>::value = " << Fib<35>::value << endl;
  cout << "Fib<40>::value = " << Fib<40>::value << endl;
  cout << "Fib<45>::value = " << Fib<45>::value << endl;
// cout << "Fib<-1>::value = " << Fib<-1>::value << endl;
// cout << "Fib<50>::value = " << Fib<50>::value << endl;
  return 0;
}

