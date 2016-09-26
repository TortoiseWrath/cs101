#include <iostream>
#include <typeinfo>
#include <array>

using namespace std;

template < typename T, unsigned int D > class darr {
	private:
		int count;
		T* myarray;
	public:
		darr(){
			if (D == 1){
				myarray = new T[count];
			}
			else{
				myarray = darr<array<T,count>,D-1>;
			}
		}
};