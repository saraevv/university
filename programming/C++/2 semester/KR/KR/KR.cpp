#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>
#include <unordered_map>
#include <string>
#include <set>
#include <algorithm>
using namespace std;

struct way
{
	int b;
	int e;
	int num;

	bool operator == (way const& e2) const { return b == e2.b && e == e2.e && num == e2.num; }

	friend istream& operator >> (istream& is, way& ed)
	{
		return is >> ed.b >> ed.e >> ed.num;
	}
	friend ostream& operator << (ostream& os, way const& ed)
	{
		return os << "(" << ed.b << "," << ed.e << "," << ed.num << ")";
	}
};

struct stop
{
	int n;
	string name;
	friend istream& operator >> (istream& is, stop& ed)
	{
		return is >> ed.n >> ed.name;
	}
	bool operator !=(stop const&s) { return n != s.n && name != s.name; }
};

int main()
{
	setlocale(LC_ALL, "rus");
	vector<way> vw;
	typedef istream_iterator<way> is_iterWay;

	ifstream fi_w("in.txt");
	if (fi_w)
	{
		copy(is_iterWay(fi_w), is_iterWay(), back_inserter(vw));
	}

	vector<stop> vs;
	typedef istream_iterator<stop> is_iterStop;

	ifstream fi_s("stop.txt");
	if (fi_s)
	{
		copy(is_iterStop(fi_s), is_iterStop(), back_inserter(vs));
	}

	// 1
	unordered_map<int, set<int>> mw;
	for_each(vw.begin(), vw.end(), [&](way const& e)
	{
		mw[e.b].insert(e.num); 
		mw[e.e].insert(e.num);
	});

	unordered_map<pair<int, int>, set<int>> ans;
	
	for_each(vs.begin(), vs.end(), [&](stop&s1)
	{
		for_each(vs.begin(), vs.end(), [&](stop&s2)
		{
			if (s1 != s2)
			{
				set<int> res;
				set_intersection(mw[s1.n].begin(), mw[s1.n].end(),
					mw[s2.n].begin(), mw[s2.n].end(),
					std::inserter(res, res.begin()));
				ans[{s1.n, s2.n}] = res;
			}
		});
	}
	);
	// ответ хранится в ans


	// 2


	// 3
	unordered_map<int, set<int>> m1;
	for_each(vw.begin(), vw.end(), [&](way const& e) {m1[e.b].insert(e.e); });


	int max = 0;
	stop anser;
	for_each(vs.begin(), vs.end(), [&](stop const& s)
	{
		if (max < (sizeof(m1[s.n])/ 4))
		{
			max= sizeof(m1[s.n])/4;
			anser=s;
		}
	});
	cout << anser.n;
	return 0;
}