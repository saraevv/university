#include "pch.h"
#include <iostream>
#include <fstream>
using namespace std;


class Monomial
{
public:
	int pow;
	double coef;
	Monomial * next;
	Monomial() :pow(0), coef(0), next(nullptr) {}
	Monomial(int apow, double acoef) :pow(apow), coef(acoef), next(nullptr) {}

	double Coeff()
	{
		return coef;
	}

	int Degree()
	{
		return pow;
	}

	void Print()
	{
		if (coef < 0)
			cout << "(" << coef << ")";
		else
			cout << coef;
		if (pow == 0)
			cout << " ";
		else if (pow == 1)
			cout << "*x" << " ";
		else
			cout << "*x^" << pow << " ";
		cout << endl;
	}
};


class Polynomial
{
public:
	Polynomial() :first(nullptr), last(&first) {}
	Polynomial(const Polynomial &P)
	{
		first = nullptr;
		last = &first;
		Monomial *ptr = P.first;
		while (ptr)
		{
			PushBack(ptr->pow, ptr->coef);
			ptr = ptr->next;
		}
	}
	~Polynomial()
	{
		Erase(first);
	}

	void PushBack(int apow, double acoef)
	{
		Monomial * p = new Monomial(apow, acoef);
		*last = p;
		last = &p->next;
		
	}

	bool  IsEmpty()const
	{
		return last == &first;
	}

	void Clear()
	{
		Erase(first);
		first = nullptr;
		last = &first;
	}

	int Count()
	{
		Monomial * p = first;
		int i = 0;
		while (p)
		{
			++i;
			p = p->next;
		}
		return i;
	}

	void Swap(Polynomial & P2)
	{
		swap(first, P2.first);
		swap(last, P2.last);
	}

	bool Delete(int x)
	{
		Monomial *p = first, *pprev = first;
		bool a = false, b = false;
		while (p)
		{
			if (p->coef == x)
			{
				if (p == first)
				{
					first = p->next;
					delete p;
					b = true;
					break;
				}
				else if (p->next == nullptr)
				{
					pprev->next = nullptr;
					last = &pprev->next;
					delete p;
					b = true;
					break;
				}
				else
				{
					pprev->next = p->next;
					delete p;
					b = true;
					break;
				}
			}
			p = p->next;
			if (a)
				pprev = pprev->next;
			a = true;
		}
		return b;
	}

	void DeleteAll(int x)
	{
		while (Delete(x));
	}

	void Push(int pow, double coef)
	{
		if (!first)
			PushBack(pow, coef);
		else if (first->pow < pow)
		{
			Monomial *tm = new Monomial(pow, coef);
			tm->next = first;
			first = tm;
		}
		else
		{
			Monomial *prev = first;
			Monomial *p = prev->next;
			bool a = false;
			while (p)
			{
				if (p->pow<pow && prev->pow>pow)
				{
					Monomial *tm = new Monomial(pow, coef);
					prev->next = tm;
					tm->next = p;
					a = true;
					break;
				}
				p = p->next;
				prev = prev->next;
			}
			if (!a)
				PushBack(pow, coef);
		}
	}

	Polynomial & operator = (const Polynomial & P2)
	{
		if (this != &P2)
		{
			Polynomial t(P2);
			Swap(t);
		}
		return *this;
	}

	Polynomial & operator += (Polynomial & P2)
	{
		Monomial *p1 = first;
		Monomial *p2 = P2.first;
		bool tr;
		while (p2)
		{
			tr = false;
			while (p1)
			{
				if (p1->pow == p2->pow)
				{
					p1->coef += p2->coef;
					tr = true;
					break;
				}
				p1 = p1->next;
			}
			if (tr == false)
				Push(p2->pow, p2->coef);
			p1 = first;
			p2 = p2->next;
		}
		DeleteAll(0);
		return *this;
	}

	Polynomial & operator -= (Polynomial & P2)
	{
		Monomial *p1 = first;
		Monomial *p2 = P2.first;
		bool tr;
		while (p2)
		{
			tr = false;
			while (p1)
			{
				if (p1->pow == p2->pow)
				{
					p1->coef -= p2->coef;
					tr = true;
				}
				p1 = p1->next;
			}
			if (tr == false)
				Push(p2->pow, -p2->coef);
			p1 = first;
			p2 = p2->next;
		}
		DeleteAll(0);
		return *this;
	}
	
	Polynomial &operator *= (Polynomial & P2)
	{
		Polynomial *ArP = new Polynomial[P2.Count()];
		int i = 0;
		Monomial *ptr1 = first;
		Monomial *ptr2 = P2.first;
		while (ptr2)
		{
			while (ptr1)
			{
				ArP[i].PushBack(ptr1->pow + ptr2->pow, ptr1->coef*ptr2->coef);
				ptr1 = ptr1->next;
			}
			ptr1 = first;
			ptr2 = ptr2->next;
			++i;
		}
		Polynomial P;
		for (i = 0; i < P2.Count(); ++i)
			P += ArP[i];
		*this = P;
		return *this;

	}
	
	Polynomial &operator /=(Polynomial & P2)
	{
		Monomial *ptr;
		Polynomial P3, P4 = *this, P5;
		double umn, del = P2.first->coef;
		int pow1, pow2 = P2.first->pow;
		while (true)
		{
			P3 = P2;
			umn = P4.first->coef;
			pow1 = P4.first->pow;
			ptr = P3.first;
			while (ptr)
			{
				ptr->pow = ptr->pow + pow1 - pow2;
				ptr->coef = (ptr->coef*umn) / del;
				ptr = ptr->next;
			}
			P5.PushBack(pow1 - pow2, umn / del);
			P4 -= P3;
			if (P4.first == nullptr || pow2 > P4.first->pow)
				break;
		}
		*this = P5;
		return *this;
	}

	Polynomial &operator %=(Polynomial &P2)
	{
		Polynomial P3 = *this / P2;
		P3 *= P2;
		*this -= P3;
		return *this;
	}

	Polynomial operator +(Polynomial & P2)
	{
		Polynomial P3;
		P3 = *this;
		P3 += P2;
		return P3;
	}
	
	Polynomial operator -(Polynomial & P2)
	{
		Polynomial P3;
		P3 = *this;
		P3 -= P2;
		return P3;
	}
	
	Polynomial operator * (Polynomial & P2)
	{
		Polynomial P3;
		P3 = *this;
		P3 *= P2;
		return P3;
	}
	
	Polynomial operator /(Polynomial & P2)
	{
		Polynomial P3(*this);
		P3 /= P2;
		return P3;
	}

	Polynomial operator %(Polynomial & P2)
	{
		Polynomial P3=*this;
		Polynomial P4 = *this/P2;
		P4 *= P2;
		P3 -= P4;
		return P3;
	}


	friend ostream & operator <<(ostream &os, Polynomial P)
	{
		
			Monomial *ptr = P.first;
			bool a = false;
			while (ptr)
			{
				if (a)
					os << " + ";
				a = true;
				if (ptr->coef < 0)
					os << "(" << ptr->coef << ")";
				else
					os << ptr->coef;
				if (ptr->pow == 0)
					os << " ";
				else if (ptr->pow == 1)
					os << "*x" << " ";
				else
					os << "*x^" << ptr->pow << " ";
				ptr = ptr->next;
			}
			if (!a)
				cout << "0";
			os << endl << endl;
					
		return os;
	}

	friend istream & operator >>(istream &is, Polynomial &P)
	{
		int n, pow;
		double coef;
		cout << "Enter number of elments: ";
		cin >> n;
		cout << "Enter powers and coefficients of elements:" << endl;
		for (int i = 0; i < n; ++i)
		{
			is >> pow >> coef;
			P.PushBack(pow, coef);
		}
		cout << endl;
		return is;
	}

	bool operator ==(Polynomial P2)
	{
		bool tr = true;
		Monomial *p1 = first, *p2 = P2.first;
		if (Count() != P2.Count())
			tr = false;
		else
			while (p1)
			{
				if (p1->pow != p2->pow || p1->coef!=p2->coef)
				{
					tr = false;
					break;
				}
				p1 = p1->next;
				p2 = p2->next;
			}
		return tr;
	}

	Monomial operator[](int i)
	{
		Monomial M;
		Monomial *p = first;
		int a = 1;
		while (p) 
		{
			if (a == i)
			{
				M.pow = p->pow;
				M.coef = p->coef;
				break;
			}
			p = p->next;
			++a;
		}
		if (a != i)
		{
			M.pow = 0;
			M.coef = 0;
		}
		return M;
	}
private:
	Monomial * first;
	Monomial ** last;

	void Erase(Monomial *&ptr)
	{
		while (ptr)
		{
			Monomial * p = ptr;
			ptr = ptr->next;
			delete p;
		}
	}
};


int main()
{/*
	ifstream fi("input.txt");
	Polynomial P1, P2, P3;
	int num1, num2, pow;
	double coef;
	fi >> num1;
	for (int i = 0; i < num1; ++i)
	{
		fi >> pow >> coef;
		P1.PushBack(pow, coef);
	}
	cout << "P1:" << P1;
	fi >> num2;
	for (int i = 0; i < num2; ++i)
	{
		fi >> pow >> coef;
		P2.PushBack(pow, coef);
	}
	cout << "P2:" << P2;
	fi >> pow >> coef;*/

	Polynomial P1, P2, P3;
	cin >> P1 >> P2;
	cout <<"P1: "<< P1<< "P2: " << P2;
	
	

	// ОПЕРАТОРЫ

	// =
	cout << "P1=P2" << endl << "P1=";
	P3 = P2;
	cout << P3;

	// +=
	cout << "P1+=P2" << endl << "P1=";
	P3 = P1;
	P3 += P2;
	cout << P3;

	// -=
	cout << "P1-=P2" << endl << "P1=";
	P3 = P1;
	P3 -= P2;
	cout << P3;

	// *=
	cout << "P1*=P2" << endl << "P1=";
	P3 = P1;
	P3 *= P2;
	cout << P3;
	/*
	// /=
	cout << "P1/=P2" << endl << "P1=";
	P3 = P1;
	P3 /= P2;
	cout << P3;*/

	// %=
	cout << "P1%=P2" << endl << "P1=";
	P3 = P1;
	P3 %= P2;
	cout << P3;

	// +
	cout << "P3=P1+P2" << endl << "P3=";
	P3 = P1 + P2;
	cout << P3;

	// -
	cout << "P3=P1-P2" << endl << "P3=";
	P3 = P1 - P2;
	cout << P3;

	// *
	cout << "P3=P1*P2" << endl << "P3=";
	P3 = P1 * P2;
	cout << P3;
	/*
	// /
	cout << "P3=P1/P2" << endl << "P3=";
	P3 = P1 / P2;
	cout << P3;
	*/
	// %
	cout << "P3=P1%P2" << endl << "P3=";
	P3 = P1 % P2;
	cout << P3;


	cout << "P1==P2:";
	if (P1 == P2)
		cout << "true";
	else
		cout << "false";
	cout << endl;

	cout << "Enter n: ";
	int n;
	cin >> n;
	P1[n].Print();
	P2[n].Print();
	return 0;
}

