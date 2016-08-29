#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

class Matrix {
	private:
		int a,b,c,d;
	public:
		Matrix (int w, int x, int y, int z);
		string toString();
		Matrix operator+ (Matrix m) const;
};

Matrix::Matrix(int w, int x, int y, int z){
	a=w;b=x;c=y;d=z;
}

string Matrix::toString(){
	return "[ "+to_string(a)+" "+to_string(b)+" ; "+to_string(c)+" "+to_string(d)+" ]";
}

Matrix Matrix::operator+ (Matrix m) const {
	return Matrix(a+m.a,b+m.b,c+m.c,d+m.d);
}

int main() {
	Matrix m1 = Matrix(1,2,3,4);
	Matrix m2 = Matrix(5,6,7,8);
	cout << m1.toString() << endl;
	cout << m2.toString() << endl;
	Matrix m3 = m1+m2;
	cout << m3.toString() << endl;
}