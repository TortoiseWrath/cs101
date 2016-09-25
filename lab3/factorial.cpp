#include <iostream>
using namespace std;

template < unsigned long N >
struct Fact
{
  enum { value = N * Fact<N-1>::value };
};

template <>
struct Fact<0>
{
  enum { value = 1 };
};

int main ( )
{
  cout << "Fact<3>::value = " << Fact<3>::value << endl;
  cout << "Fact<4>::value = " << Fact<4>::value << endl;
  cout << "Fact<5>::value = " << Fact<5>::value << endl;
  cout << "Fact<6>::value = " << Fact<6>::value << endl;
  cout << "Fact<7>::value = " << Fact<7>::value << endl;
  cout << "Fact<8>::value = " << Fact<8>::value << endl;
  cout << "Fact<10>::value = " << Fact<10>::value << endl;
  cout << "Fact<15>::value = " << Fact<15>::value << endl;
  cout << "Fact<20>::value = " << Fact<20>::value << endl;
// cout << "Fact<-1>::value = " << Fact<-1>:::value << endl;
// cout << "Fact<21>::value = " << Fact<21>::value << endl;
  return 0;
}

