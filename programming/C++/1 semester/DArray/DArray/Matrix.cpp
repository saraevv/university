#include "pch.h"
#include "Matrix.h"


Matrix::Matrix()
{
	height = 0;
	width = 0;
	p = nullptr;
}

Matrix::Matrix(int theight, int twidth)
{
	height = theight;
	width = twidth;
	p = new double*[width];
	for (int i = 0; i < width; ++i)
		p[i] = new double[height];
}

Matrix::Matrix(Matrix const & M2)
{
	height = M2.height;
	width = M2.width;
	p = new double*[width];
	for (int i = 0; i < width; ++i)
		p[i] = new double[height];
	for (int i = 0; i < height; ++i)
		for (int j = 0; j < width; ++j)
			p[j][i] = M2.p[j][i];
}


Matrix::~Matrix()
{
	if (p!=nullptr)
	{
		for (int i = 0; i < width; ++i)
			delete[] p[i];
	}
}

void Matrix::Swap(Matrix & M2)
{
	swap(height, M2.height);
	swap(width, M2.width);
	swap(p, M2.p);
}

Matrix & Matrix::operator=(const Matrix & M2)
{
	Matrix tm(M2);
	Swap(tm);
	return *this;
}

bool Matrix::operator==(Matrix & M2)
{
	if (height == M2.height&&width == M2.width)
	{
		bool tr = true;
		for (int i = 0; i < height; ++i)
		{
			for (int j = 0; j < width; ++j)
			{
				if (p[j][i] != M2.p[j][i])
				{
					tr = false;
					break;
				}
				if (!tr) break;
			}
		}
		return tr;		
	}
	else return false;
}

bool Matrix::operator!=(Matrix & M2)
{
	return !(*this==M2);
}

Matrix & Matrix::operator+=(Matrix & M2)
{
	if (height == M2.height&&width == M2.width)
	{
		for (int i = 0; i < height; ++i)
			for (int j = 0; j < width; ++j)
				p[j][i] += M2.p[j][i];
	}
	else cout << "Нельзя складывать матрицы с разным количеством строк/столбцов!" << endl;
	return *this;
}

Matrix Matrix::operator+(Matrix & M2)
{
	Matrix M3(M2);
	M3 += *this;
	return M3;
}

Matrix & Matrix::operator-=(Matrix & M2)
{
	if (height == M2.height&&width == M2.width)
	{
		for (int i = 0; i < height; ++i)
			for (int j = 0; j < width; ++j)
				p[j][i] -= M2.p[j][i];
	}
	else cout << "Нельзя отнимать матрицы с разным количеством строк/столбцов!" << endl;
	return *this;
}

Matrix Matrix::operator-(Matrix & M2)
{
	Matrix M3(M2);
	M3 -= *this;
	return M3;
}

Matrix Matrix::operator*(Matrix & M2)
{
	if (width == M2.height)
	{
		Matrix M3(height, M2.width);
		for (int i = 0; i < M3.height; ++i)
		{
			for (int j = 0; j < M3.width; ++j)
			{
				M3.p[j][i] = 0;
				for (int n = 0; n < width; ++n)
					M3.p[j][i]+=p[n][i]*M2.p[j][n];
			}
		}
		return M3;
	}
	else
	{
		cout << "Нельзя перемножать несогласованные матрицы!";
		Matrix M3;
		return M3;
	}
	
}

Matrix & Matrix::operator*=(Matrix & M2)
{
	*this = *this*M2;
	return *this;
}

double & Matrix::operator()(int i, int j)
{
	while (!(i < width&&j < height))
	{
		cout << "Такого элемента нет!" << endl;
		cout << "Введите другой номер: ";
		cin >> i >> j;
	}
	return p[i][j];
}





istream & operator>>(istream & is, Matrix & M)
{
	cout << "Введите количество столбцов в матрице: ";
	is >> M.width;
	cout << "Введите количество строк в матрице: ";
	is >> M.height;
	M.p = new double *[M.width];
	for(int i=0;i<M.width;++i)
		M.p[i] = new double[M.height];
	cout << "Введите элементы матрицы:" << endl;
	for (int i = 0; i < M.height; ++i)
		for (int j = 0; j < M.width; ++j)
			is >> M.p[j][i];
	return is;
}

ostream & operator<<(ostream & os, Matrix & M)
{
	for (int i = 0; i < M.height; ++i)
	{
		for (int j = 0; j < M.width; ++j)
		{
			os << M.p[j][i] << " ";
			if (j == M.width - 1)
				os << endl;
		}
	}
	return os;
}
