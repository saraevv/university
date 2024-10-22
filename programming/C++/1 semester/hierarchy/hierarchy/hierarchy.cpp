#include "pch.h"
#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <windows.h>
#include <iomanip>
using namespace std;
const double PI = 3.14159265;

class Location
{
public:
	double x;
	double y;
	Location(double tx = 0, double ty = 0) :x(tx), y(ty) {}
	virtual ~Location() {}
};

class Point :public Location
{
protected:
	string color;
	bool visible;
public:
	Point(string tc = "black", double tx = 0, double ty = 0) :Location(tx, ty), color(tc), visible(true) {}
	virtual void Draw() { }
	void Hide(){ visible = false; }
	void Show() { visible = true; system("cls"); Draw(); cout << endl; }
	void MoveTo(double tx, double ty) { x = tx; y = ty; Draw(); }
	void Shift(double tx, double ty) { x += tx; y += ty; Draw(); }
	virtual void Rotate(double tc) { }
	virtual void Explode(double tc) { }
};

class Shape :public Point
{
protected:
	double corner;
	double coef;
	bool flag1;
	bool flag2;
public:
	Shape(double tcorn = 0, string tc = "black", double tx = 0, double ty = 0) :corner(tcorn), coef(1), flag1(true), flag2(true), Point(tc, tx, ty) {}
	void Rotate(double tc)override { corner += tc; Draw(); }
	void Explode(double tc)override { coef *= tc; flag1 = false; flag2 = false; Draw(); }
};

class Rect :public Shape
{
protected:
	double base;
	double side;
	Location p[4];
	void VertexCalculation()
	{
		if (!flag1)
		{
			base *= coef;
			side *= coef;
			flag1 = true;
		}
		p[0].x = p[1].x = x - base / 2;
		p[2].x = p[3].x = x + base / 2;
		p[0].y = p[3].y = y - side / 2;
		p[1].y = p[2].y = y + side / 2;
		if (corner)
		{
			double ax, ay;
			for (int i = 0; i < 4; ++i)
			{
				ax = x + (p[i].x - x)*cos(corner*PI / 180) - (p[i].y - y)*sin(corner*PI / 180);
				ay = y + (p[i].y - y)*cos(corner*PI / 180) + (p[i].x - x)*sin(corner*PI / 180);
				p[i].x = ax;
				p[i].y = ay;
			}
		}
	}
public:
	Rect(double tbase = 0, double tside = 0, double tcorn = 0, string tc = "black", double tx = 0, double ty = 0) :
		Shape(tcorn, tc, tx, ty), base(tbase), side(tside) {}
	void Draw()override
	{
		if (visible)
		{
			VertexCalculation();
			cout << "Прямоугольник:" << endl;
			cout << "Стороны равны: " << base << " , " << side << endl;
			cout << "Координаты точек:" << endl;
			for (int i = 0; i < 4; ++i)
				cout << "(" << p[i].x << " ; " << p[i].y << ") ";
			cout << endl;
			cout << "Координаты точки пересечения диагоналей: " << "(" << x << " ; " << y << ") " << endl;
			cout << "Цвет: " << color << endl;
			cout << "Угол наклона к Ox: "<< corner << endl;
			cout << "Коэффициент растяжения: " << coef << endl;
		}
	}
};

class RectWithD :public Rect
{
protected:
	bool  d;
public:
	RectWithD(bool td, double tbase = 0, double tside = 0, double tcorn = 0, string tc = "black", double tx = 0, double ty = 0) :
		Rect(tbase, tside, tcorn, tc, tx, ty), d(td) {}
	void Draw()override
	{
			if (visible)
			{
				VertexCalculation();
				cout << "Прямоугольник с диагональю:" << endl;
				cout << "Стороны равны: " << base << " , " << side << endl;
				cout << "Координаты точек:" << endl;
				for (int i = 0; i < 4; ++i)
					cout << "(" << p[i].x << " ; " << p[i].y << ") ";
				cout << endl;
				cout << "Координаты точки пересечения диагоналей: " << "(" << x << " ; " << y << ") " << endl;
				cout << "Цвет: " << color << endl;
				cout << "Угол наклона к Ox: "<< corner << endl;
				cout << "Коэффициент растяжения: " << coef << endl;
				cout << "Диагональ проведена от точки ";
				if (d)
					cout << "(" << p[0].x << " ; " << p[0].y << ")";
				else
					cout << "(" << p[1].x << " ; " << p[1].y << ")";
				cout << " к точке ";
				if (d)
					cout << "(" << p[2].x << " ; " << p[2].y << ")";
				else
					cout << "(" << p[3].x << " ; " << p[3].y << ")";
				cout << endl;

			}
	}
};

class RectWithRect :public Rect
{
protected:
	double sbase;
	double sside;
	bool bottom;
	bool left;
	bool top;
	bool right;
	Location sp[4];
	void sVertexCalculation()
	{
		if (!flag2)
		{
			sbase *= coef;
			sside *= coef;
			flag2 = true;
		}
		sp[0].x = sp[1].x = x - sbase / 2;
		sp[2].x = sp[3].x = x + sbase / 2;
		sp[0].y = sp[3].y = y - sside / 2;
		sp[1].y = sp[2].y = y + sside / 2;
		if (corner)

		{
			double ax, ay;
			for (int i = 0; i < 4; ++i)
			{
				ax = x + (sp[i].x - x)*cos(corner*PI / 180) - (sp[i].y - y)*sin(corner*PI / 180);
				ay = y + (sp[i].y - y)*cos(corner*PI / 180) + (sp[i].x - x)*sin(corner*PI / 180);
				sp[i].x = ax;
				sp[i].y = ay;
			}
		}
	}
public:
	RectWithRect(double tsbase, double tsside, bool tbottom, bool tleft, bool ttop, bool tright, double tbase = 0, double tside = 0, double tcorn = 0, string tc = "black", double tx = 0, double ty = 0) :
		Rect(tbase, tside, tcorn, tc, tx, ty), sbase(tsbase), sside(tsside), bottom(tbottom), left(tleft), top(ttop), right(tright) {}
	void Draw()override
	{
		if (visible)
		{
			VertexCalculation();
			sVertexCalculation();
			cout << "Прямоугольник со внутренним прямоугольником:" << endl;
			cout << "Стороны равны: " << base << " , " << side << endl;
			cout << "Координаты точек:" << endl;
			for (int i = 0; i < 4; ++i)
				cout << "(" << p[i].x << " ; " << p[i].y << ") ";
			cout << endl;
			cout << "Координаты точки пересечения диагоналей: " << "(" << x << " ; " << y << ") " << endl;
			cout << "Цвет: " << color << endl;
			cout << "Угол наклона к Ox: " << corner << endl;
			cout << "Коэффициент растяжения: " << coef << endl;
			cout << "Стороны внутреннего прямоугольника равны: " << sbase << " , " << sside << endl;
			cout << "Координаты точек внутреннего прямогольника:" << endl;
			for (int i = 0; i < 4; ++i)
				cout << "(" << sp[i].x << " ; " << sp[i].y << ") ";
			cout << endl;
			cout << "Закрашенные сегменты:" << endl;
			if (bottom) cout << "нижний" << endl;
			if (left) cout << "левый" << endl;
			if (top) cout << "верхний" << endl;
			if (right) cout << "правый" << endl;
		}
	}
};

class Circle :public Shape
{
protected:
	double radius;
public:
	Circle(double tradius, string tc = "black", double tx = 0, double ty = 0) :Shape(0, tc, tx, ty), radius(tradius) {}
	void Draw()override
	{
		if (visible)
		{
			if (!flag1)
			{
				radius *= coef;
				flag1 = true;
			}
			cout << "Окружность:" << endl;
			cout << "Радиус равен: " << radius << endl;
			cout << "Координаты центра: " << "(" << x << " ; " << y << ") " << endl;
			cout << "Цвет: " << color << endl;
			cout << "Коэффициент растяжения: " << coef << endl;
		}
	}
};

class CircleWithR :public Circle
{
protected:
	double rcorner;
	double rx;
	double ry;
	void Calculation()
	{
		if (!flag1)
		{
			radius *= coef;
			flag1 = true;
		}
		rx = x + radius * cos(rcorner*PI / 180);
		ry = y + radius * sin(rcorner*PI / 180);
	}
public:
	CircleWithR(double trcorner, double tradius, string tc = "black", double tx = 0, double ty = 0) :Circle(tradius, tc, tx, ty), rcorner(trcorner) {}
	void Draw()override
	{
		if (visible)
		{
			Calculation();
			cout << "Окружность с радиусом:" << endl;
			cout << "Радиус равен: " << radius << endl;
			cout << "Координаты центра: " << "(" << x << " ; " << y << ") " << endl;
			cout << "Цвет: " << color << endl;
			cout << "Коэффициент растяжения: " << coef << endl;
			cout << "Угол наклона радиуса к Ox: " << rcorner << endl;
			cout << "Точка пересечения радиуса и окружности: " << "(" << rx << " ; " << ry << ") " << endl;
		}
	}
};

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	cout << setprecision(4);

	//Прямоугольник

	cout << "Введите стороны прямоугольника (основание, боковая сторона): " << endl;
	double base, side;
	cin >> base >> side;

	cout << "Введите цвет прямоугольника: " << endl;
	string color;
	cin >> color;

	cout << "Введите координаты точки пересечения диагоналей прямоугольника: " << endl;
	double x, y;
	cin >> x >> y;

	Rect R(base, side, 0, color, x, y);
	R.Show();
	system("pause");
	int n, corner, dx, dy;
	while (true)
	{
		system("cls");
		cout << "Выберите пункт, который хотите выполнить: " << endl;
		cout << "1. Скрыть фигуру" << endl;
		cout << "2. Показать фигуру" << endl;
		cout << "3. Повернуть фигуру" << endl;
		cout << "4. Переместить фигуру" << endl;
		cout << "5. Задать новые координаты x, y" << endl;
		cout << "6. Растянуть фигуру" << endl;
		cout << "0. Перейти к следующей фигуре" << endl;
		cin >> n;
		if (n == 0 || n > 6) break;
		else if (n == 1)
		{
			R.Hide();
		}
		else if (n == 2)
		{
			R.Show();
			system("pause");
		}
		else if (n == 3)
		{
			cout << "Введите угол, на который хотите повернуть фигуру: ";
			cin >> corner;
			R.Rotate(corner);
		}
		else if (n == 4)
		{
			cout << "Введите дельта x, дельта y: ";
			cin >> dx >> dy;
			R.Shift(dx, dy);
		}
		else if (n == 5)
		{
			cout << "Введите новые x, y:";
			cin >> dx >> dy;
			R.MoveTo(dx, dy);
		}
		else if (n == 6)
		{
			cout << "Введите коэффициент растяжения: ";
			cin >> dx;
			R.Explode(dx);
		}
	}
	system("cls");

	//Прямоугольник со внутренним прямоугольником

	cout << "Введите стороны прямоугольника (основание, боковая сторона): " << endl;
	cin >> base >> side;

	cout << "Введите стороны внутреннего прямоугольника (основание, боковая сторона): " << endl;
	double sbase, sside;
	cin >> sbase >> sside;

	cout << "Введите цвет прямоугольника: " << endl;
	cin >> color;

	cout << "Введите координаты точки пересечения диагоналей прямоугольника: " << endl;
	cin >> x >> y;

	cout << "Введите количество закрашенных сегментов в прямоугольнике (n<=4): " << endl;
	int num;
	cin >> num;

	cout << "Введите номера закрашенных сегментов (от нижнего по часовой стрелке):" << endl;
	int*p = new int[num];
	for (int i = 0; i < num; ++i)
	{
		cin >> p[i];
	}
	bool bottom = false, left = false, top = false, right = false;
	for (int i = 0; i < num; ++i)
	{
		if (p[i] == 1) bottom = true;
		if (p[i] == 2) left = true;
		if (p[i] == 3) top = true;
		if (p[i] == 4) right = true;
	}

	RectWithRect RwR(sbase, sside, bottom, left, top, right, base, side, 0, color, x, y);
	RwR.Show();
	system("pause");
	while (true)
	{
		system("cls");
		cout << "Выберите пункт, который хотите выполнить: " << endl;
		cout << "1. Скрыть фигуру" << endl;
		cout << "2. Показать фигуру" << endl;
		cout << "3. Повернуть фигуру" << endl;
		cout << "4. Переместить фигуру" << endl;
		cout << "5. Задать новые координаты x, y" << endl;
		cout << "6. Растянуть фигуру" << endl;
		cout << "0. Перейти к следующей фигуре" << endl;
		cin >> n;
		if (n == 0 || n > 6) break;
		else if (n == 1)
		{
			RwR.Hide();
		}
		else if (n == 2)
		{
			RwR.Show();
			system("pause");
		}
		else if (n == 3)
		{
			cout << "Введите угол, на который хотите повернуть фигуру: ";
			cin >> corner;
			RwR.Rotate(corner);
		}
		else if (n == 4)
		{
			cout << "Введите дельта x, дельта y: ";
			cin >> dx >> dy;
			RwR.Shift(dx, dy);
		}
		else if (n == 5)
		{
			cout << "Введите новые x, y:";
			cin >> dx >> dy;
			RwR.MoveTo(dx, dy);
		}
		else if (n == 6)
		{
			cout << "Введите коэффициент растяжения: ";
			cin >> dx;
			RwR.Explode(dx);
		}
	}
	system("cls");

	//Прямоугольник с диагональю

	cout << "Введите стороны прямоугольника (основание, боковая сторона): " << endl;
	cin >> base >> side;

	cout << "Введите цвет прямоугольника: " << endl;
	cin >> color;

	cout << "Введите координаты точки пересечения диагоналей прямоугольника: " << endl;
	cin >> x >> y;

	cout << "Введите 1, если хотите провести диагональ справа налево,"<<endl<<" 0, если хотите провести диагональ слева направо: ";
	bool tr;
	cin >> tr;

	RectWithD RwD(tr, base, side, 0, color, x, y);
	RwD.Show();
	system("pause");
	while (true)
	{
		system("cls");
		cout << "Выберите пункт, который хотите выполнить: " << endl;
		cout << "1. Скрыть фигуру" << endl;
		cout << "2. Показать фигуру" << endl;
		cout << "3. Повернуть фигуру" << endl;
		cout << "4. Переместить фигуру" << endl;
		cout << "5. Задать новые координаты x, y" << endl;
		cout << "6. Растянуть фигуру" << endl;
		cout << "0. Перейти к следующей фигуре" << endl;
		cin >> n;
		if (n == 0 || n > 6) break;
		else if (n == 1)
		{
			RwD.Hide();
		}
		else if (n == 2)
		{
			RwD.Show();
			system("pause");
		}
		else if (n == 3)
		{
			cout << "Введите угол, на который хотите повернуть фигуру: ";
			cin >> corner;
			RwD.Rotate(corner);
		}
		else if (n == 4)
		{
			cout << "Введите дельта x, дельта y: ";
			cin >> dx >> dy;
			RwD.Shift(dx, dy);
		}
		else if (n == 5)
		{
			cout << "Введите новые x, y:";
			cin >> dx >> dy;
			RwD.MoveTo(dx, dy);
		}
		else if (n == 6)
		{
			cout << "Введите коэффициент растяжения: ";
			cin >> dx;
			RwD.Explode(dx);
		}
	}
	system("cls");

	//Окружнось

	cout << "Введите радиус окружности: " << endl;
	double radius;
	cin >> radius;

	cout << "Введите цвет окружности: " << endl;
	cin >> color;

	cout << "Введите координаты центра точки окружности: " << endl;
	cin >> x >> y;

	Circle C(radius, color, x, y);
	C.Show();
	system("pause");
	while (true)
	{
		system("cls");
		cout << "Выберите пункт, который хотите выполнить: " << endl;
		cout << "1. Скрыть фигуру" << endl;
		cout << "2. Показать фигуру" << endl;
		cout << "3. Переместить фигуру" << endl;
		cout << "4. Задать новые координаты x, y" << endl;
		cout << "5. Растянуть фигуру" << endl;
		cout << "0. Перейти к следующей фигуре" << endl;
		cin >> n;
		if (n == 0 || n > 6) break;
		else if (n == 1)
		{
			C.Hide();
		}
		else if (n == 2)
		{
			C.Show();
			system("pause");
		}
		else if (n == 3)
		{
			cout << "Введите дельта x, дельта y: ";
			cin >> dx >> dy;
			C.Shift(dx, dy);
		}
		else if (n == 4)
		{
			cout << "Введите новые x, y:";
			cin >> dx >> dy;
			C.MoveTo(dx, dy);
		}
		else if (n == 5)
		{
			cout << "Введите коэффициент растяжения: ";
			cin >> dx;
			C.Explode(dx);
		}
	}
	system("cls");

	//Окружнось с радиусом

	cout << "Введите радиус окружности: " << endl;
	cin >> radius;

	cout << "Введите цвет окружности: " << endl;
	cin >> color;

	cout << "Введите координаты центра точки окружности: " << endl;
	cin >> x >> y;

	cout << "Введите угол наклона радиуса к Ox: "<<endl;
	cin >> corner;

	CircleWithR CwR(corner, radius, color, x, y);
	CwR.Show();
	system("pause");
	while (true)
	{
		system("cls");
		cout << "Выберите пункт, который хотите выполнить: " << endl;
		cout << "1. Скрыть фигуру" << endl;
		cout << "2. Показать фигуру" << endl;
		cout << "3. Переместить фигуру" << endl;
		cout << "4. Задать новые координаты x, y" << endl;
		cout << "5. Растянуть фигуру" << endl;
		cout << "0. Перейти к следующей фигуре" << endl;
		cin >> n;
		if (n == 0 || n > 6) break;
		else if (n == 1)
		{
			CwR.Hide();
		}
		else if (n == 2)
		{
			CwR.Show();
			system("pause");
		}
		else if (n == 3)
		{
			cout << "Введите дельта x, дельта y: ";
			cin >> dx >> dy;
			CwR.Shift(dx, dy);
		}
		else if (n == 4)
		{
			cout << "Введите новые x, y:";
			cin >> dx >> dy;
			CwR.MoveTo(dx, dy);
		}
		else if (n == 5)
		{
			cout << "Введите коэффициент растяжения: ";
			cin >> dx;
			CwR.Explode(dx);
		}
	}
	system("cls");

	return 0;
}

