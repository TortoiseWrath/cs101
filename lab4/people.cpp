#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class Person {
	string first, last;
	unsigned cwid;
public:
	Person (string f, string l, unsigned c)
		: first(f), last(l), cwid(c) { }
	string getFirst( ) { return first; }
	string getLast( ) { return last; }
	unsigned getCwid( ) { return cwid; }
	void print( ) { cout << first << "\t" << last << "\t" << cwid; }
};

struct LessCwid {
	bool operator() ( Person p, Person q ) {
		return p.getCwid() < q.getCwid();
	}
};

struct LessLastFirstCwid {
	bool operator() ( Person p, Person q ) {
		if (p.getLast() < q.getLast()) return true;
		if (p.getLast() > q.getLast()) return false;
		if (p.getFirst() < q.getFirst()) return true;
		if (p.getFirst() > q.getFirst()) return false;
		return p.getCwid() < q.getCwid();
	}
};

void print (string s, vector<Person> v) {
	cout << s << endl;
	vector<Person>::iterator i;
	for (i=v.begin(); i!=v.end(); ++i) {
		cout << "\t";
		i->print();
		cout << endl;
	}
	cout << endl;
}

int main ( ) {
	vector<Person> v;
	v.push_back( Person( "John", "Smith", 99999999) );
	v.push_back( Person( "Jane", "Roe", 77777777) );
	v.push_back( Person( "Richard", "Miles", 55555555) );
	v.push_back( Person( "John", "Doe", 33333333) );
	v.push_back( Person( "Joe", "Public", 11111111) );
	v.push_back( Person( "Richard", "Roe", 88888888) );
	v.push_back( Person( "Jane", "Doe", 66666666) );
	v.push_back( Person( "John", "Roe", 44444444) );
	v.push_back( Person( "Mary", "Major", 22222222) );
	v.push_back( Person( "John", "Public", 12345678) );
	v.push_back( Person( "Mary", "Smith", 98765432) );
	v.push_back( Person( "John", "Doe", 90000000) );
	v.push_back( Person( "Joe", "Bloggs", 87654321) );
	v.push_back( Person( "Jane", "Public", 23456789) );
	v.push_back( Person( "John", "Stiles", 10000000) );

	print( "People (unsorted)", v );
	sort( v.begin(), v.end(), LessCwid() );
	print( "People (sorted by cwid)", v );
	sort( v.begin(), v.end(), LessLastFirstCwid() );
	print( "People (sorted by last name then first name then cwid)", v );
	return 0;
}
