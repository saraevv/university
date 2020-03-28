#pragma once
#include <fstream>
#include <cmath>
using namespace std;
const double PI = 3.14159265;

bool IsDotInTriangle(POINT p0, POINT p1, POINT p2, POINT p3)
{
	if (((p1.x - p0.x)*(p2.y - p1.y) - (p2.x - p1.x)*(p1.y - p0.y)) > 0)
	{
		if (((p2.x - p0.x)*(p3.y - p2.y) - (p3.x - p2.x)*(p2.y - p0.y)) > 0 &&
			((p3.x - p0.x)*(p1.y - p3.y) - (p1.x - p3.x)*(p3.y - p0.y)) > 0)
			return true;
		else
			return false;
	}
	else
	{
		if (((p2.x - p0.x)*(p3.y - p2.y) - (p3.x - p2.x)*(p2.y - p0.y)) < 0 &&
			((p3.x - p0.x)*(p1.y - p3.y) - (p1.x - p3.x)*(p3.y - p0.y)) < 0)
			return true;
		else
			return false;
	}
}

void RotateF(POINT &p, double &corner, double &x, double &y)
{
	double ax, ay;
	ax = x + (p.x - x)*cos(corner*PI / 180) - (p.y - y)*sin(corner*PI / 180);
	ay = y + (p.y - y)*cos(corner*PI / 180) + (p.x - x)*sin(corner*PI / 180);
	p.x = ax;
	p.y = ay;
}

bool CheckSquare(char* word)
{
	char sample[7] = "square";
	for (int i = 0; i < 6; ++i)
	{
		if (sample[i] != word[i])
			return false;
	}
	return true;
}

bool CheckRectangle(char* word)
{
	char sample[10] = "rectangle";
	for (int i = 0; i < 6; ++i)
	{
		if (sample[i] != word[i])
			return false;
	}
	return true;
}

bool CheckParallelogramm(char* word)
{
	char sample[15] = "parallelogramm";
	for (int i = 0; i < 6; ++i)
	{
		if (sample[i] != word[i])
			return false;
	}
	return true;
}

bool CheckTrapezium(char* word)
{
	char sample[10] = "trapezium";
	for (int i = 0; i < 6; ++i)
	{
		if (sample[i] != word[i])
			return false;
	}
	return true;
}

bool CheckCircle(char* word)
{
	char sample[7] = "circle";
	for (int i = 0; i < 6; ++i)
	{
		if (sample[i] != word[i])
			return false;
	}
	return true;
}

bool CheckTriangle(char* word)
{
	char sample[9] = "triangle";
	for (int i = 0; i < 6; ++i)
	{
		if (sample[i] != word[i])
			return false;
	}
	return true;
}


class Shape
{
protected:
	Shape() :x(0), y(0), corner(0), coef(1), exploded(false), width(1), circuit(RGB(0, 0, 0)), background(RGB(255, 255, 255)) {}
	virtual ~Shape() {}
	double x, y, corner, coef;
	bool exploded;
	int width;
	COLORREF circuit, background;

public:
	void Shift(double dx, double dy) { x += dx; y += dy; }
	void Rotate(double dcorner) { corner += dcorner; }
	void Explode(double dcoef) { coef += dcoef; exploded = true; }
	bool IsExploded() { return exploded; }
	void SetWidth(unsigned int new_width) { width = new_width; }
	void SetCircuit(COLORREF color) { circuit = color; }
	void SetBackgrond(COLORREF color) { background = color; }
	virtual void Draw(HDC hdc) = 0;
	virtual void SetBase(double) { }
	virtual void SetSide(double) { }
	virtual void SetIntCorner(double) { }
	virtual void ChangeIntCorner(double) { }
	virtual void SetSBase(double) { }
	virtual void SetRadius(double) { }
	virtual bool IsDotIn(POINT) = 0;
};

class Square :public Shape
{
public:
	Square() :base(0),Shape() {}
	void SetBase(double new_base)override { base = new_base; }

	void Draw(HDC hdc)override
	{
		if (IsExploded())
		{
			base *= coef;
			exploded = false;
			coef = 1;
		}
		HPEN pen = CreatePen(PS_SOLID, width, circuit);
		HBRUSH brush = CreateSolidBrush(background);
		HGDIOBJ tpen = SelectObject(hdc, pen);
		HGDIOBJ tbrush = SelectObject(hdc, brush);
		POINT *points = new POINT[4];
		points[0].x = x - base / 2;
		points[1].x = points[0].x;
		points[2].x = x + base / 2;
		points[3].x = points[2].x;
		points[0].y = y - base / 2;
		points[1].y = y + base / 2;
		points[2].y = points[1].y;
		points[3].y = points[0].y;
		if (corner)
		{
			for (int i = 0; i < 4; ++i)
				RotateF(points[i], corner, x, y);
		}
		Polygon(hdc, points, 4);
		DeleteObject(pen);
		DeleteObject(brush);
		SelectObject(hdc, tpen);
		SelectObject(hdc, tbrush);
		delete[]points;
	}

	bool IsDotIn(POINT p)override
	{
		POINT *points = new POINT[4];
		points[0].x = x - base / 2;
		points[1].x = points[0].x;
		points[2].x = x + base / 2;
		points[3].x = points[2].x;
		points[0].y = y - base / 2;
		points[1].y = y + base / 2;
		points[2].y = points[1].y;
		points[3].y = points[0].y;
		if (corner)
		{
			for (int i = 0; i < 4; ++i)
				RotateF(points[i], corner, x, y);
		}
		return IsDotInTriangle(p, points[0], points[1], points[2]) || IsDotInTriangle(p, points[2], points[3], points[0]);
	}
protected:
	double base;
};

class Rectangle_ : public Square
{
public:
	Rectangle_() :side(0), Square() {}
	void SetSide(double new_side)override { side = new_side; }

	void Draw(HDC hdc)override
	{
		if (IsExploded())
		{
			base *= coef;
			side *= coef;
			exploded = false;
			coef = 1;
		}
		HPEN pen = CreatePen(PS_SOLID, width, circuit);
		HBRUSH brush = CreateSolidBrush(background);
		HGDIOBJ tpen = SelectObject(hdc, pen);
		HGDIOBJ tbrush = SelectObject(hdc, brush);
		POINT *points = new POINT[4];
		points[0].x = x - base / 2;
		points[1].x = points[0].x;
		points[2].x = x + base / 2;
		points[3].x = points[2].x;
		points[0].y = y - side / 2;
		points[1].y = y + side / 2;
		points[2].y = points[1].y;
		points[3].y = points[0].y;
		if (corner)
		{
			for (int i = 0; i < 4; ++i)
				RotateF(points[i], corner, x, y);
		}
		Polygon(hdc, points, 4);
		DeleteObject(pen);
		DeleteObject(brush);
		SelectObject(hdc, tpen);
		SelectObject(hdc, tbrush);
	}

	bool IsDotIn(POINT p)override
	{
		POINT *points = new POINT[4];
		points[0].x = x - base / 2;
		points[1].x = points[0].x;
		points[2].x = x + base / 2;
		points[3].x = points[2].x;
		points[0].y = y - side / 2;
		points[1].y = y + side / 2;
		points[2].y = points[1].y;
		points[3].y = points[0].y;
		if (corner)
		{
			for (int i = 0; i < 4; ++i)
				RotateF(points[i], corner, x, y);
		}
		return IsDotInTriangle(p, points[0], points[1], points[2]) || IsDotInTriangle(p, points[2], points[3], points[0]);
	}
protected:
	double side;
};

class Parallelogramm :public Rectangle_
{
public:
	Parallelogramm() :int_corner(0), Rectangle_() {}
	void SetIntCorner(double new_corner)override { int_corner = new_corner; }

	void Draw(HDC hdc)override
	{
		if (IsExploded())
		{
			base *= coef;
			side *= coef;
			exploded = false;
			coef = 1;
		}
		HPEN pen = CreatePen(PS_SOLID, width, circuit);
		HBRUSH brush = CreateSolidBrush(background);
		HGDIOBJ tpen = SelectObject(hdc, pen);
		HGDIOBJ tbrush = SelectObject(hdc, brush);
		POINT *points = new POINT[4];
		points[0].x = x - (base + side * cos(int_corner*PI / 180)) / 2;
		points[0].y = y - side * sin(int_corner*PI / 180) / 2;
		points[1].x = points[0].x + side * cos(int_corner*PI / 180);
		points[1].y = y + side * sin(int_corner*PI / 180) / 2;
		points[2].x = points[1].x + base;
		points[2].y = points[1].y;
		points[3].x = points[0].x + base;
		points[3].y = points[0].y;
		if (corner)
		{
			for (int i = 0; i < 4; ++i)
				RotateF(points[i], corner, x, y);
		}
		Polygon(hdc, points, 4);
		DeleteObject(pen);
		DeleteObject(brush);
		SelectObject(hdc, tpen);
		SelectObject(hdc, tbrush);
	}

	bool IsDotIn(POINT p)override
	{
		POINT *points = new POINT[4];
		points[0].x = x - (base + side * cos(int_corner*PI / 180)) / 2;
		points[0].y = y - side * sin(int_corner*PI / 180) / 2;
		points[1].x = points[0].x + side * cos(int_corner*PI / 180);
		points[1].y = y + side * sin(int_corner*PI / 180) / 2;
		points[2].x = points[1].x + base;
		points[2].y = points[1].y;
		points[3].x = points[0].x + base;
		points[3].y = points[0].y;
		if (corner)
		{
			for (int i = 0; i < 4; ++i)
				RotateF(points[i], corner, x, y);
		}
		return IsDotInTriangle(p, points[0], points[1], points[2]) || IsDotInTriangle(p, points[2], points[3], points[0]);
	}

	void ChangeIntCorner(double dcorner) { int_corner += dcorner; }
protected:
	double int_corner;
};

class Trapezium : public Parallelogramm
{
public:
	Trapezium() :sbase(0), Parallelogramm() {}
	void SetSBase(double new_sbase)override { sbase = new_sbase; }

	void Draw(HDC hdc)override
	{
		if (IsExploded())
		{
			base *= coef;
			side *= coef;
			sbase *= coef;
			exploded = false;
			coef = 1;
		}
		HPEN pen = CreatePen(PS_SOLID, width, circuit);
		HBRUSH brush = CreateSolidBrush(background);
		HGDIOBJ tpen = SelectObject(hdc, pen);
		HGDIOBJ tbrush = SelectObject(hdc, brush);
		POINT *points = new POINT[4];
		double height = side * sin(int_corner*PI / 180);
		points[0].x = (4 * x - 2 * side*cos(int_corner*PI / 180) - sbase - base) / 4;
		points[1].x = points[0].x + side * cos(int_corner*PI / 180);
		points[2].x = points[1].x + base;
		points[3].x = sbase + points[0].x;
		points[0].y = points[3].y = -height / 2 + y;
		points[1].y = points[2].y = height / 2 + y;
		if (corner)
		{
			for (int i = 0; i < 4; ++i)
				RotateF(points[i], corner, x, y);
		}
		Polygon(hdc, points, 4);
		DeleteObject(pen);
		DeleteObject(brush);
		SelectObject(hdc, tpen);
		SelectObject(hdc, tbrush);
	}

	bool IsDotIn(POINT p)override
	{
		POINT *points = new POINT[4];
		double height = side * sin(int_corner*PI / 180);
		points[0].x = (4 * x - 2 * side*cos(int_corner*PI / 180) - sbase - base) / 4;
		points[1].x = points[0].x + side * cos(int_corner*PI / 180);
		points[2].x = points[1].x + base;
		points[3].x = sbase + points[0].x;
		points[0].y = points[3].y = -height / 2 + y;
		points[1].y = points[2].y = height / 2 + y;
		if (corner)
		{
			for (int i = 0; i < 4; ++i)
				RotateF(points[i], corner, x, y);
		}
		return IsDotInTriangle(p, points[0], points[1], points[2]) || IsDotInTriangle(p, points[2], points[3], points[0]);
	}
protected:
	double sbase;
};

class Circle : public Shape
{
public:
	Circle() :radius(0), Shape() {}
	void SetRadius(double new_radius)override { radius = new_radius; }

	void Draw(HDC hdc)override
	{
		if (IsExploded())
		{
			radius*=coef;
			exploded = false;
			coef = 1;
		}
		HPEN pen = CreatePen(PS_SOLID, width, circuit);
		HBRUSH brush = CreateSolidBrush(background);
		HGDIOBJ tpen = SelectObject(hdc, pen);
		HGDIOBJ tbrush = SelectObject(hdc, brush);
		Ellipse(hdc, x - radius, y - radius, x + radius, y + radius);
		DeleteObject(pen);
		DeleteObject(brush);
		SelectObject(hdc, tpen);
		SelectObject(hdc, tbrush);
	}

	bool IsDotIn(POINT p)override
	{
		return ((p.x - x)*(p.x - x) + (p.y - y)*(p.y - y)) <= (radius*radius);
	}
protected:
	double radius;
};

class Triangle :public Parallelogramm
{
	void Draw(HDC hdc)override
	{
		if (IsExploded())
		{
			base *= coef;
			side *= coef;
			exploded = false;
			coef = 1;
		}
		HPEN pen = CreatePen(PS_SOLID, width, circuit);
		HBRUSH brush = CreateSolidBrush(background);
		HGDIOBJ tpen = SelectObject(hdc, pen);
		HGDIOBJ tbrush = SelectObject(hdc, brush);
		
		POINT points[3];
		double Mx;
		double median = sqrt(side*side + base * base / 4 + side * base*cos(int_corner*PI / 180));
		double sinb = side * sin(int_corner*PI / 180) / median;
		double height = median * sinb;
		double cosb = sqrt(1 - sinb * sinb);
		double segment = median * cosb;
		points[0].y = y - height * 2 / 3;
		points[0].x = x - segment * 2 / 3;
		points[1].y = points[2].y = points[0].y + height;
		Mx = x + segment / 3;
		points[1].x = Mx - base / 2;
		points[2].x = Mx + base / 2;
		if (corner)
		{
			for (int i = 0; i < 3; ++i)
				RotateF(points[i], corner, x, y);
		}
		Polygon(hdc, points, 3);
		DeleteObject(pen);
		DeleteObject(brush);
		SelectObject(hdc, tpen);
		SelectObject(hdc, tbrush);
	}

	bool IsDotIn(POINT p)override
	{
		POINT points[3];
		double Mx;
		double median = sqrt(side*side + base * base / 4 + side * base*cos(int_corner*PI / 180));
		double sinb = side * sin(int_corner*PI / 180) / median;
		double height = median * sinb;
		double cosb = sqrt(1 - sinb * sinb);
		double segment = median * cosb;
		points[0].y = y - height * 2 / 3;
		points[0].x = x - segment * 2 / 3;
		points[1].y = points[2].y = points[0].y + height;
		Mx = x + segment / 3;
		points[1].x = Mx - base / 2;
		points[2].x = Mx + base / 2;
		if (corner)
		{
			for (int i = 0; i < 3; ++i)
				RotateF(points[i], corner, x, y);
		}
		return IsDotInTriangle(p, points[0], points[1], points[2]);
	}
};