#pragma once
#include<iostream>
using namespace std;

struct node {

	int id;
	int year;
	string cause;
	string state;
	int deaths;
	float DR;

	node(int i = 0, int y = 0, string c = "", string s = "", int d = 0, float dr = 0) {
		id = i;
		year = y;
		cause = c;
		state = s;
		deaths = d;
		DR = dr;
	}
	friend istream& operator >> (istream& in, node& c);
};

ostream& operator<<(ostream& out, const node& c)
{
	out << "Data of Node ID " << c.id << " : \n";
	out << "Year : " << c.year << endl;
	out << "Cause : " << c.cause << endl;
	out << "State : " << c.state << endl;
	out << "No of Deaths : " << c.deaths << endl;
	out << "Death Rate : " << c.DR << endl << endl;
	return out;
}