#pragma once
#include <iostream>
using namespace std;
class Rat
{
public:
	Rat() :num(0), den(0) {}
	Rat(int num, int den = 1) :num(num), den(den) { reduction(); }
	void reduction();
	Rat& operator += (const Rat& R2);
	Rat& operator -= (const Rat& R2);
	Rat& operator *= (const Rat& R2);
	Rat& operator /= (const Rat& R2);
	Rat operator + (const Rat& R2) const;
	Rat operator - (const Rat& R2) const;
	Rat operator * (const Rat& R2) const;
	Rat operator / (const Rat& R2) const;
	bool operator == (const Rat& R2)const;
	bool operator != (const Rat& R2)const;
	friend istream & operator >> (istream & is, Rat&R);
	friend ostream & operator << (ostream & os, const Rat & R);
	int num;
	int den;
};

