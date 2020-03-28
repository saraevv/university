#pragma once
#include <iostream>
using namespace std;
class Matrix
{
public:
	Matrix();
	Matrix(int, int);
	Matrix(Matrix const& M2);
	~Matrix();
	void Swap(Matrix &M2);
	int Rows() { return height; }
	int Cols() { return width; }
	bool IsEmpty() { return p == nullptr; }
	friend istream & operator >> (istream &is, Matrix &M);
	friend ostream & operator << (ostream &os, Matrix &M);
	Matrix & operator =(Matrix const& M2);
	bool operator == (Matrix &M2);
	bool operator != (Matrix &M2);
	Matrix & operator +=(Matrix &M2);
	Matrix operator + (Matrix &M2);
	Matrix & operator -=(Matrix &M2);
	Matrix operator - (Matrix &M2);
	Matrix  operator *(Matrix &M2);
	Matrix & operator *=(Matrix &M2);
	double & operator() (int i, int j);
private:
	int height;
	int width;
	double **p;
};

