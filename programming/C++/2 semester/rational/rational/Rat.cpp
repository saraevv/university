#include "Rat.h"
using namespace std;

int gcd(int a, int b) { return b ? gcd(b, a % b) : a; }

void Rat::reduction()
{
	int x = gcd(num, den);
	num /= x;
	den /= x;
}

Rat & Rat::operator+=(const Rat & R2)
{
	int tmnum, tmden;
	tmnum = num * R2.den + R2.num * den;
	tmden = den * R2.den;
	num = tmnum;
	den = tmden;
	reduction();
	return *this;
}

Rat & Rat::operator-=(const Rat & R2)
{
	int tmnum, tmden;
	tmnum = num * R2.den - R2.num * den;
	tmden = den * R2.den;
	num = tmnum;
	den = tmden;
	reduction();
	return *this;
}

Rat & Rat::operator*=(const Rat & R2)
{
	num *= R2.num;
	den *= R2.den;
	reduction();
	return *this;
}

Rat & Rat::operator/=(const Rat & R2)
{
	Rat R3(R2.den, R2.num);
	*this *= R3;
	reduction();
	return *this;
}

Rat Rat::operator+(const Rat & R2) const
{
	Rat R3 = *this;
	R3 += R2;
	R3.reduction();
	return R3;
}

Rat Rat::operator-(const Rat & R2) const
{
	Rat R3 = *this;
	R3 -= R2;
	R3.reduction();
	return R3;
}

Rat Rat::operator*(const Rat & R2) const
{
	Rat R3 = *this;
	R3 *= R2;
	R3.reduction();
	return R3;
}

Rat Rat::operator/(const Rat & R2) const
{
	Rat R3 = *this;
	R3 /= R2;
	R3.reduction();
	return R3;
}

bool Rat::operator==(const Rat & R2) const
{
	return ((num == R2.num) && (den == R2.den));
}

bool Rat::operator!=(const Rat & R2) const
{
	return !(*this == R2);
}

istream & operator>>(istream & is, Rat & R)
{
	is >> R.num >> R.den;
	R.reduction();
	return is;
}

ostream & operator<<(ostream & os, const Rat & R)
{
	os << "(" << R.num << "/" << R.den << ")";
	return os;
}
