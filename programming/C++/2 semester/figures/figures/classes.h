#pragma once
#include <windows.h>
#include <cmath>
const double PI = 3.14159265;

bool IsDotInTriangle(POINT p0, POINT p1, POINT p2, POINT p3)
{
		//(x1 - x0) * (y2 - y1) - (x2 - x1) * (y1 - y0)
		//(x2 - x0) * (y3 - y2) - (x3 - x2) * (y2 - y0)
		//(x3 - x0) * (y1 - y3) - (x1 - x3) * (y3 - y0)
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

struct PParam
{
	double x, y, corner, base, side, int_corner;
	int width;
	COLORREF circuit, background;
};

struct PPParam
{
	double x, y, corner, base, side, int_corner;
	int width;
	COLORREF circuit, bcolor, lcolor, tcolor, rcolor;
};

struct TParam
{
	double x, y, corner, bbase, sbase, side, int_corner;
	int width;
	COLORREF circuit, background;
};

struct PTParam
{
	double x, y, corner, bbase, sbase, side, int_corner;
	int width;
	COLORREF circuit , lcolor, ccolor, rcolor;
};

class Shape
{
public:
	Shape(double x, double y, double corner, int width, COLORREF circuit, COLORREF background) :
		x(x), y(y), corner(corner), width(width), circuit(circuit), background(background),visible(true),exploded(false), coef(1) {}
	virtual ~Shape() {};
	virtual void Draw(HDC hdc) = 0;
	void Shift(double tx, double ty) { x += tx; y += ty; }
	void Explode(double tcoef) { coef += tcoef; exploded = true; }
	bool IsVisible() { return visible; }
	bool IsExploded() { return exploded; }
	void Show() { visible = true; }
	void Hide() { visible = false; }
	void Rotate(double tcorner) { corner += tcorner; }
	void SetCircuitColor(COLORREF tcircuit) { circuit = tcircuit; }
	void SetBackgroundColor(COLORREF tbackground) { background = tbackground; }
	void IncreaseWidth(int twidth)
	{
		if ((width + twidth) > 0)
			width += twidth;
		else
			width = 1;
	}
	virtual bool IsDotIn(POINT p) = 0;
	virtual int Type() = 0;
	void ChageColor(COLORREF color) { background = color; }
	virtual bool IsDotInSegment(int, POINT) { return false; };
	virtual void ChangeSegmentColor(int, COLORREF) { };
	virtual void ChangeIntCorner(double) = 0;
protected:
	double x, y, corner, coef;
	int width;
	COLORREF circuit, background;
	bool visible, exploded;
	
};

class Parallelogram :public Shape
{
public:
	Parallelogram(PParam p) :Shape(p.x, p.y, p.corner, p.width, p.circuit, p.background), base(p.base), side(p.side), int_corner(p.int_corner) {}
	Parallelogram(double x, double y, double corner, int width, COLORREF circuit, COLORREF background, double base, double side, double int_corner) :
		Shape(x, y, corner, width, circuit, background), base(base), side(side), int_corner(int_corner) {}
	void Draw(HDC hdc)override
	{
		if (IsVisible())
		{
			if (IsExploded())
			{
				base *= coef;
				side *= coef;
				exploded = false;
				coef = 1;
			}
			POINT points[4];
			VertexCalculation(points);
			HPEN pen = CreatePen(PS_SOLID, width, circuit);
			HBRUSH brush = CreateSolidBrush(background);
			HGDIOBJ tpen = SelectObject(hdc, pen);
			HGDIOBJ tbrush = SelectObject(hdc, brush);
			Polygon(hdc, points, 4);
			DeleteObject(pen);
			DeleteObject(brush);
			SelectObject(hdc, tpen);
			SelectObject(hdc, tbrush);
		}
	}
	bool IsDotIn(POINT p)override
	{
		POINT points[4];
		VertexCalculation(points);
		return IsDotInTriangle(p, points[0], points[1], points[2]) || IsDotInTriangle(p, points[2], points[3], points[0]);
	}
	int Type()override { return 1; }
	void ChangeIntCorner(double delta)override { int_corner += delta; }
protected:
	double base;
	double side;
	double int_corner;

	void VertexCalculation(POINT * points)
	{
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
			double ax, ay;
			for (int i = 0; i < 4; ++i)
			{
				ax = x + (points[i].x - x)*cos(corner*PI / 180) - (points[i].y - y)*sin(corner*PI / 180);
				ay = y + (points[i].y - y)*cos(corner*PI / 180) + (points[i].x - x)*sin(corner*PI / 180);
				points[i].x = ax;
				points[i].y = ay;
			}
		}
	}
};

class PaintedParallelogram :public Parallelogram
{
public:
	PaintedParallelogram(PPParam p) :Parallelogram(p.x, p.y, p.corner, p.width, p.circuit, RGB(0, 0, 0), p.base, p.side, p.int_corner), lcolor(p.lcolor), bcolor(p.bcolor),
		rcolor(p.rcolor), tcolor(p.tcolor) {}
	void Draw(HDC hdc)override
	{
		if (IsVisible())
		{
			if (IsExploded())
			{
				base *= coef;
				side *= coef;
				exploded = false;
				coef = 1;
			}
			POINT points[4];
			HPEN pen = CreatePen(PS_SOLID, width, circuit);
			HGDIOBJ tpen = SelectObject(hdc, pen);
			CenterCalculation(points);
			POINT tm[3];
			tm[0] = points[0];
			tm[1] = points[1];
			tm[2] = center;
			HBRUSH brush = CreateSolidBrush(lcolor);
			HGDIOBJ tbrush = SelectObject(hdc, brush);
			Polygon(hdc, tm, 3);
			DeleteObject(brush);

			tm[0] = points[1];
			tm[1] = points[2];
			brush = CreateSolidBrush(bcolor);
			SelectObject(hdc, brush);
			Polygon(hdc, tm, 3);
			DeleteObject(brush);

			tm[0] = points[2];
			tm[1] = points[3];
			brush = CreateSolidBrush(rcolor);
			SelectObject(hdc, brush);
			Polygon(hdc, tm, 3);
			DeleteObject(brush);

			tm[0] = points[3];
			tm[1] = points[0];
			brush = CreateSolidBrush(tcolor);
			SelectObject(hdc, brush);
			Polygon(hdc, tm, 3);
			DeleteObject(brush);

			DeleteObject(pen);
			SelectObject(hdc, tpen);
			SelectObject(hdc, tbrush);
		}
	}
	int Type()override { return 2; }
	bool IsDotInSegment(int n, POINT p)override
	{
		POINT points[4];
		CenterCalculation(points);
		if(n==1)
			return IsDotInTriangle(p, points[0], points[3], center);
		else if(n==2)
			return IsDotInTriangle(p, points[0], points[1], center);
		else if(n==3)
			return IsDotInTriangle(p, points[1], points[2], center);
		else if(n==4)
			return IsDotInTriangle(p, points[2], points[3], center);
		else 
			return false;
	}
	void ChangeSegmentColor(int n, COLORREF color)
	{
		if (n == 1)
			tcolor = color;
		else if (n == 2)
			lcolor = color;
		else if (n == 3)
			bcolor = color;
		else if (n == 4)
			rcolor = color;
	}
protected:
	POINT center;
	COLORREF bcolor, lcolor, tcolor, rcolor;
	void CenterCalculation(POINT *points)
	{
		VertexCalculation(points);
		double tx=0, ty=0;
		for (int i = 0; i < 4; ++i)
		{
			tx += points[i].x;
			ty += points[i].y;
		}
		center.x = tx / 4;
		center.y = ty / 4;
	}
};

class Trapezium :public Shape
{
public:
	Trapezium(TParam p) :Shape(p.x, p.y, p.corner, p.width, p.circuit, p.background), bbase(p.bbase), sbase(p.sbase), side(p.side), int_corner(p.int_corner) {}
	Trapezium(double x, double y, double corner, int width, COLORREF circuit, COLORREF background, double bbase, double sbase, double side, double int_corner ):
		Shape(x, y, corner, width, circuit, RGB(0,0,0)), bbase(bbase), sbase(sbase), side(side), int_corner(int_corner) {}
	void Draw(HDC hdc)override
	{
		if (IsVisible())
		{
			if (IsExploded())
			{
				bbase *= coef;
				sbase *= coef;
				side *= coef;
				exploded = false;
				coef = 1;
			}
			POINT points[4];
			VertexCalculation(points);
			HPEN pen = CreatePen(PS_SOLID, width, circuit);
			HBRUSH brush = CreateSolidBrush(background);
			HGDIOBJ tpen = SelectObject(hdc, pen);
			HGDIOBJ tbrush = SelectObject(hdc, brush);
			Polygon(hdc, points, 4);
			DeleteObject(pen);
			DeleteObject(brush);
			SelectObject(hdc, tpen);
			SelectObject(hdc, tbrush);
		}
	}
	bool IsDotIn(POINT p)
	{
		POINT points[4];
		VertexCalculation(points);
		return IsDotInTriangle(p, points[0], points[1], points[2]) || IsDotInTriangle(p, points[2], points[3], points[0]);
	}
	int Type()override { return 3; }
	void ChangeIntCorner(double delta)override { int_corner += delta; }
protected:
	double bbase;
	double sbase;
	double side;
	double int_corner;
	virtual void VertexCalculation(POINT *points)
	{
		double height = side * sin(int_corner*PI / 180);
		points[0].x = (4 * x - 2 * side*cos(int_corner*PI / 180) - sbase - bbase) / 4;
		points[1].x = points[0].x + side * cos(int_corner*PI / 180);
		points[2].x = points[1].x + bbase;
		points[3].x = sbase + points[0].x;
		points[0].y = points[3].y = -height / 2 + y;
		points[1].y = points[2].y = height / 2 + y;
		if (corner)
		{
			double ax, ay;
			for (int i = 0; i < 4; ++i)
			{
				ax = x + (points[i].x - x)*cos(corner*PI / 180) - (points[i].y - y)*sin(corner*PI / 180);
				ay = y + (points[i].y - y)*cos(corner*PI / 180) + (points[i].x - x)*sin(corner*PI / 180);
				points[i].x = ax;
				points[i].y = ay;
			}
		}
	}
};

class PaintedTrapezium :public Trapezium
{
public:
	PaintedTrapezium(PTParam p) :Trapezium(p.x, p.y, p.corner, p.width, p.circuit, RGB(0, 0, 0), p.bbase, p.sbase, p.side, p.int_corner), lcolor(p.lcolor),
		ccolor(p.ccolor), rcolor(p.rcolor) {}
	void Draw(HDC hdc)override
	{
		if (IsVisible())
		{
			if (IsExploded())
			{
				bbase *= coef;
				sbase *= coef;
				side *= coef;
				exploded = false;
				coef = 1;
			}
			POINT points[6];
			VertexCalculation(points);
			HPEN pen = CreatePen(PS_SOLID, width, circuit);
			HGDIOBJ tpen = SelectObject(hdc, pen);

			POINT tm1[3];
			tm1[0] = points[0];
			tm1[1] = points[1];
			tm1[2] = points[4];
			HBRUSH brush = CreateSolidBrush(lcolor);
			HGDIOBJ tbrush = SelectObject(hdc, brush);
			Polygon(hdc, tm1, 3);
			DeleteObject(brush);

			tm1[0] = points[3];
			tm1[1] = points[2];
			tm1[2] = points[5];
			brush = CreateSolidBrush(rcolor);
			SelectObject(hdc, brush);
			Polygon(hdc, tm1, 3);
			DeleteObject(brush);

			POINT tm2[4];
			tm2[0] = points[0];
			tm2[1] = points[4];
			tm2[2] = points[5];
			tm2[3] = points[3];
			brush = CreateSolidBrush(ccolor);
			SelectObject(hdc, brush);
			Polygon(hdc, tm2, 4);
			DeleteObject(brush);

			DeleteObject(pen);
			SelectObject(hdc, tpen);
			SelectObject(hdc, tbrush);
		}
	}
	int Type()override { return 4; }

	COLORREF lcolor, ccolor, rcolor;
	bool IsDotInSegment(int n, POINT p)override
	{
		POINT points[6];
		VertexCalculation(points);
		if (n == 1)
			return IsDotInTriangle(p, points[0], points[1], points[4]);
		else if (n == 2)
			return IsDotInTriangle(p, points[0], points[4], points[5]) || IsDotInTriangle(p, points[0], points[3], points[5]);
		else if (n == 3)
			return IsDotInTriangle(p, points[2], points[3], points[5]);
		else
			return false;
	}
	void ChangeSegmentColor(int n, COLORREF color)
	{
		if (n == 1)
			lcolor = color;
		else if (n == 2)
			ccolor = color;
		else if (n == 3)
			rcolor = color;
	}
	bool IsDotIn(POINT p)override
	{
		POINT points[6];
		VertexCalculation(points);
		return IsDotInTriangle(p, points[0], points[1], points[2]) || IsDotInTriangle(p, points[2], points[3], points[0]);
	}
protected:
	void VertexCalculation(POINT *points)
	{
		double height = side * sin(int_corner*PI / 180);
		points[0].x = (4 * x - 2 * side*cos(int_corner*PI / 180) - sbase - bbase) / 4;
		points[1].x = points[0].x + side * cos(int_corner*PI / 180);
		points[2].x = points[1].x + bbase;
		points[3].x = sbase + points[0].x;
		points[0].y = points[3].y = -height / 2 + y;
		points[1].y = points[2].y = height / 2 + y;
		points[4].x = points[1].x + side * cos((180 - int_corner)*PI / 180);
		points[4].y = points[1].y;
		points[5].x = points[4].x + sbase;
		points[5].y = points[1].y;

		if (corner)
		{
			double ax, ay;
			for (int i = 0; i < 6; ++i)
			{
				ax = x + (points[i].x - x)*cos(corner*PI / 180) - (points[i].y - y)*sin(corner*PI / 180);
				ay = y + (points[i].y - y)*cos(corner*PI / 180) + (points[i].x - x)*sin(corner*PI / 180);
				points[i].x = ax;
				points[i].y = ay;
			}
		}
	}
	
};