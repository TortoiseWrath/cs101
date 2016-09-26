#include <iostream>
#include <typeinfo>
#include <array>

using namespace std;

int main() {
	typedef int blarg;
	typedef blarg arblarg[2];
	typedef array<arblarg, 2> abrblarg;
	abrblarg x;
	array<typeid(x), 2> y;
	cout << typeid(x).name();
}