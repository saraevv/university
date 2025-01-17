#include <iostream>
#include <cmath>
#include <vector>
#include <windows.h>
using namespace std;
const double PI = 3.14159265;

struct Point
{
	double x;
	double y;
};

double SquareFig(vector<Point> figure)
{
	double res = 0;
	for (unsigned i = 0; i < figure.size(); i++)
	{
		Point
			p1 = i ? figure[i - 1] : figure.back(),
			p2 = figure[i];
		res += (p1.x - p2.x) * (p1.y + p2.y);
	}
	return fabs(res) / 2;
}

double SquareRect(vector<Point> figure)
{
	double left=figure[0].x, right=figure[0].x, top=figure[0].y, bottom=figure[0].y;
	for (unsigned int i = 1; i < figure.size(); ++i)
	{
		if (figure[i].x < left)
			left=figure[i].x;
		if (figure[i].x > right)
			right = figure[i].x;
		if (figure[i].y < bottom)
			bottom = figure[i].y;
		if (figure[i].y > top)
			top = figure[i].y;
	}
	return (top - bottom)*(right - left);

}

void Rotation(vector<Point> & figure, double fi)
{
	double ax, ay;
	for (unsigned int i = 0; i < figure.size(); ++i)
	{
		ax = figure[i].x*cos(fi*PI) - figure[i].y*sin(fi*PI);
		ay = figure[i].x*sin(fi*PI) + figure[i].y*cos(fi*PI);
		figure[i].x = ax;
		figure[i].y = ay;
	}
}

int main()
{
	SetConsoleOutputCP(1251);
	int n;
	Point p;
	cout << "Введите колчество точек: ";
	cin >> n;
	vector<Point> figure;
	cout << "Введите точки:" << endl;
	for (int i = 0; i < n; ++i)
	{
		cin >> p.x >> p.y;
		figure.push_back(p);
	}
	
	double squarefig = SquareFig(figure);
	cout << "Площадь фигуры равна: " << squarefig << endl;
	double squarerect = SquareRect(figure);

	vector<Point> afigure = figure;
	double a = 0, amax;

	for (int i = 0; i < 500; ++i)
	{
		Rotation(afigure, 0.001);
		a += 0.001;

		if (squarerect > SquareRect(afigure))
		{
			squarerect = SquareRect(afigure);
			amax = a;
		}
	}
	cout << "Площадь ограничивающего прямоугольника равна: " << squarerect << endl;
	cout << "Прямоугольность фигуры равна: " << squarefig / squarerect <<endl << 90-(amax*180) << endl;

	return 0;
}



