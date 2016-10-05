#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
using namespace std;

class Nation {
	string nation, capital, currency, continent;
	int numcode;
public:
	Nation (string nat, string cap, string cur, string con, int num)
		: nation(nat), capital(cap), currency(cur), continent(con), numcode(num) { }
	string getNation() { return nation; }
	string getCapital() { return capital; }
	string getCurrency() { return currency; }
	string getContinent() { return continent; }
	int getNumcode() { return numcode; }
	void print( ) { cout << nation << "\t" << capital << "\t" << currency << "\t" << continent << "\t" << numcode; }
};

struct LessCapital {
	bool operator() (Nation a, Nation b) {
		return a.getCapital() < b.getCapital();
	}
};

struct LessCurrencyNation {
	bool operator() (Nation a, Nation b) {
		if(a.getCurrency() < b.getCurrency()) return true;
		if(a.getCurrency() > b.getCurrency()) return false;
		return a.getNation() < b.getNation();
	}
};

struct LessContinentNation {
	bool operator() (Nation a, Nation b) {
		if(a.getContinent() < b.getContinent()) return true;
		if(a.getContinent() > b.getContinent()) return false;
		return a.getNation() < b.getNation();
	}
};

struct LessCurrencyContinentNumcode {
	bool operator() (Nation a, Nation b) {
		if(a.getCurrency() < b.getCurrency()) return true;
		if(a.getCurrency() > b.getCurrency()) return false;
		if(a.getContinent() < b.getContinent()) return true;
		if(a.getContinent() > b.getContinent()) return false;
		return a.getNumcode() < b.getNumcode();
		
	}
};

struct LessContinentCurrencyNumcode {
	bool operator() (Nation a, Nation b) {
		if(a.getContinent() < b.getContinent()) return true;
		if(a.getContinent() > b.getContinent()) return false;
		if(a.getCurrency() < b.getCurrency()) return true;
		if(a.getCurrency() > b.getCurrency()) return false;
		return a.getNumcode() < b.getNumcode();
		
	}
};

void print (string s, vector<Nation> v) {
	cout << s << endl;
	vector<Nation>::iterator i;
	for (i=v.begin(); i!=v.end(); ++i) {
		cout << "\t";
		i->print();
		cout << endl;
	}
	cout << endl;
}

int main() {
	vector<Nation> v;
	v.push_back(Nation("United States","Washington","Dollar","North America",840));
	v.push_back(Nation("Mexico","Mexico City","Peso","North America",484));
	v.push_back(Nation("Canada","Ottawa","Dollar","North America",124));
	v.push_back(Nation("Brazil","Brasilia","Real","South America",76));
	v.push_back(Nation("Argentina","Buenos Aires","Peso","South America",32));
	v.push_back(Nation("Venezuela","Caracas","Bolivar","South America",862));
	v.push_back(Nation("Russia","Moscow","Ruble","Asia & Europe",643));
	v.push_back(Nation("Turkey","Ankara","Lira","Asia & Europe",792));
	v.push_back(Nation("France","Paris","Euro","Europe",250));
	v.push_back(Nation("Spain","Madrid","Euro","Europe",724));
	v.push_back(Nation("United Kingdom","London","Pound","Europe",826));
	v.push_back(Nation("Italy","Rome","Euro","Europe",380));
	v.push_back(Nation("Germany","Berlin","Euro","Europe",276));
	v.push_back(Nation("Japan","Tokyo","Yen","Asia",392));
	v.push_back(Nation("China","Beijing","Yuan","Asia",156));
	v.push_back(Nation("India","New Delhi","Rupee","Asia",356));
	v.push_back(Nation("Taiwan","Taipei","Dollar","Asia",158));
	v.push_back(Nation("Pakistan","Islamabad","Rupee","Asia",586));
	v.push_back(Nation("Iran","Tehran","Rial","Asia",364));
	v.push_back(Nation("Sri Lanka","Colombo","Rupee","Asia",144));
	v.push_back(Nation("Saudi Arabia","Riyadh","Rial","Asia",682));
	v.push_back(Nation("Egypt","Cairo","Pound","Africa",818));
	v.push_back(Nation("South Africa","Cape Town","Rand","Africa",710));
	v.push_back(Nation("Australia","Canberra","Dollar","Oceania",36));
	v.push_back(Nation("New Zealand","Wellington","Dollar","Oceania",554));
	
	print( "Nations (unsorted)", v );
	
	sort( v.begin(), v.end(), LessCapital() );
	print( "Nations (sorted by capital)", v );
	
	sort( v.begin(), v.end(), LessCurrencyNation() );
	print( "Nations (sorted by currency then nation)", v );
	
	sort( v.begin(), v.end(), LessContinentNation() );
	print( "Nations (sorted by continent then nation)", v );
	
	sort( v.begin(), v.end(), LessCurrencyContinentNumcode() );
	print( "Nations (sorted by currency then continent then numcode)", v );
	
	sort( v.begin(), v.end(), LessContinentCurrencyNumcode() );
	print( "Nations (sorted by continent then currency then numcode)", v );
	
	return 0;
}