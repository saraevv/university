#include "stdafx.h"
#include <iostream>
using namespace std;

struct point
{
	int x;
	bool begin;
};

point* srt(point* s, int l, int r)
{
	if (r - l == 1)
	{
		point* ans;
		ans = new point[1];
		ans[0] = s[l];
		return ans;
	}
	else
	{
		int m = (r + l) / 2;
		point* left;
		point* right;
		left = new point[(r - l) / 2];
		right = new point[(r - l) - ((r - l) / 2)];
		if (m - l > 0)
		{
			left = srt(s, l, m);
		}
		if (r - m > 0)
		{
			right = srt(s, m, r);
		}
		point* ans;
		ans = new point[r - l];
		int i = 0;
		int j = 0;
		for (int k = 0; k < r - l; k++)
		{
			if ((i < ((r - l) / 2)) && (j < ((r - l) - ((r - l) / 2))))
			{
				if (left[i].x <= right[j].x)
				{
					if ((left[i].x < right[i].x) || (left[i].begin))
					{
						ans[k] = left[i];
						i++;
					}
					else
					{
						ans[k] = right[j];
						j++;
					}
				}
				else
				{
					ans[k] = right[j];
					j++;
				}
			}
			else
			{
				if (i < ((r - l) / 2))
				{
					ans[k] = left[i];
					i++;
				}
				else
				{
					ans[k] = right[j];
					j++;
				}
			}
		}
		return ans;
	}
}

int main()
{
	int N;
	cout << "Input amount of segments ";
	cin >> N;
	point *s;
	s = new point[2 * N];
	cout << "Input segments\n";
	point A, B;
	A.begin = true;
	B.begin = false;
	for (int i = 0; i < N; i++)
	{
		cin >> A.x >> B.x;
		s[2 * i] = A;
		s[(2 * i) + 1] = B;
	}
	s = srt(s, 0, 2 * N);
	int ans = 0;
	int cnt = 0;
	for (int i = 0; i < 2 * N; i++)
	{
		if (s[i].begin)
		{
			cnt++;
		}
		else
		{
			cnt--;
		}
		if (cnt > ans)
		{
			ans = cnt;
		}
	}
	cout << ans;
	return 0;
}
