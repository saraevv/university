#include <iostream>
#include <map>
#include <bitset>
#include <string>
#include <algorithm>
#include <iterator>
#include <fstream>
#include "C:\Users\v\Desktop\C++\2 sem\rational\rational\Rat.h"
using namespace std;

map<int, string> f()
{
	map<int, string >  a = { {14,"asd"}, { 8,"fgh" }};
	return a;
}

struct Length
{
	bool operator()(const string& lhs, const string& rhs) const
	{
		return lhs.length() < rhs.length();
	}
};


struct Length2
{
	Length2(string s) {}
	bool operator()(const string& lhs, const string& rhs) const
	{
		return lhs.length() < rhs.length();
	}
};

int main()
{

	map<string, string, Length> M;
	
	string s = "abc";
	Length2 L(s);
	map<string, string, Length2> M1(L);



	// 1

	////Присваеваемый
	//map<int, char > m1= { {1, 'a'}, { 2,'b' }, { 3,'c' }};
	//map<int, char>m2(m1);
	//m2 = m1;
	//struct A { int a; double b; };
	//
	//// Конструируемый по умолчнию
	//map <int, int> m3;
	//// =Сравнимый
	//cout << (m1 == m2) << endl;
	//cout << (m1 != m2) << endl;
	//// <Сравнимый
	//cout << (m1 < m2) << endl;
	//cout << (m1 > m2) << endl;
	//cout << (m1 <= m2) << endl;
	//cout << (m1 >= m2) << endl;


	// 2
	//auto it1 = m1.begin();
	//auto it2 = m1.end();
	//auto it3 = m1.cbegin();
	//auto it4 = m1.cend();
	//auto it5 = m1.rbegin();
	//auto it6 = m1.rend();
	//auto it7 = m1.crbegin();
	//auto it8 = m1.crend();


	// 3
	
	/*map<int, int> m1;
	map<int, int>m2(m1);
	map<int, int>m3(*(&m1));
	map<float, char> m4 = { {2.2,'q'}, {3.3,'w'}, {4.4,'e'} };
	map<int, int>m5(m1.begin(), m1.end());*/

	// 4

	/*map<Rat, int> m1;
	Rat r1(4, 3);
	Rat r2(9, 8);
	Rat r3(1, 7);
	m1.insert({ r1,1 });
	m1.insert({ r2,22});
	m1.insert({ r3,14 });*/
	
	// 5

	// <

	// 6

	/*map<int, string> m1 = { {1,"qwe"},{2,"abc"},{3,"xyz"} };
	map<int, string> m2(move(m1));
	m2 = f();*/

	// 7

	/*map<int, Rat> m1;
	m1.emplace(piecewise_construct, make_tuple(12), make_tuple(7, 8));
	for_each(m1.begin(), m1.end(), [](pair<int, Rat>p)
	{
		cout << p.second;
	});*/
	/*m1.emplace(22, 9, 11);
	m1.emplace_hint(m1.end(), 121, 33, 33);
	m1.emplace_hint(m1.begin(), 44, 12, 14);
	m1.try_emplace(13, 1, 1);*/


	// 8

	//map<double, double> m1 = { {1.1,3.14},{2.2,1.73},{0.1,9.81} };
	//map<double, double> m2;
	//find_if(m1.begin(),m1.end(),[](pair<double,double> p)
	//{
	//	return p.first == p.second;
	//}
	//);
	////copy(m1.begin(), m1.end(), inserter(m2, m2.end()));

	//copy_if(m1.begin(), m1.end(), inserter(m2, m2.end()), [](pair<double, double> p)
	//{
	//	return p.first == 1;
	//});

	//none_of(m1.begin(), m1.end(), [](pair<double, double>p)
	//{
	//	return p.first <= p.second;
	//});

	// 9


	// 10

	/*map <int, int> M = { {1,1},{2,2} };
	cout << M.empty() << endl;*/


	// 11

	/*char c;
	map <char, int> Map;
	Map.insert({ 'a',22 });
	Map.insert({ 'z',1 });
	Map.insert({ 'r',14 });
	Map.insert({ 'p',8 });
	Map.insert({ 'b',222 });
	Map.insert({ 's',20 });

	for (auto it = Map.begin(); it != Map.end(); ++it)
	{
		cout << (*it).first << " : " << (*it).second << endl;
	}*/

	/*map <string, int> words;

	ifstream in;
	in.open("in.txt");

	string word;

	while (in >> word)
	{
		words[word]++;
	}

	ofstream out;
	out.open("out.txt");

	int count = 0;

	map <string, int>::iterator cur;

	out << "Words count:" << endl;

	for (cur = words.begin(); cur != words.end(); cur++)
	{
		out << (*cur).first << ": " << (*cur).second << endl; count += (*cur).second;
	}*/


	return 0;
}