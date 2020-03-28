// бинарные файлы.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <fstream>
#include <iostream>
#include <windows.h>
#include <string>
#include <sstream>
#include "Teacher.h"
void Swap(Teacher& t1, Teacher& t2)
{
	Teacher t3;
	t3 = t2;
	t2 = t1;
	t1 = t3;	
}
void writeBin(int k,Teacher tch[],ostream& os)
{
	for (int i = 0; i < k - 1; i++)
	{
		os.write((char*)&tch[i], sizeof(tch[i]));
	}
}
using namespace std;
ifstream fin1("input1.txt");
ifstream fin2("input2.txt");
ofstream fout("output.txt");
ofstream fout1("M1.bin", ios::binary | ios::out);
int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	Teacher teacher[100];
	Proff pfc[100];
	int t = 0,k=0;
	while (!fin1.eof())
	{
		fin1 >> teacher[k];
		k++;
	}
	for (int i = 0; i < k - 1; i++)
	{
		for (int j = 0; j < k - 2; j++)
		{
			
			if (teacher[j].GetIndnum() > teacher[j + 1].GetIndnum())
			{
				
				Swap(teacher[j], teacher[j + 1]);
			
			}
		}
		
	}
	while (!fin2.eof())
	{
		fin2 >> pfc[t];
		
		t++;
	}
	for (int i = 0; i < k - 1; i++)
	{
		for (int j = 0; j < t - 1; j++)
		{
			
			if (teacher[i].GetKey() == pfc[j].Getkey())
			{
				teacher[i].SetProf_chair(pfc[j].Getname());
			}
		}
	}
	fin1.close();
	fin2.close();
	for (int i = 0; i < k - 1; i++)
	{
		fout << teacher[i];
	}
	writeBin(k, teacher, fout1);
	fout1.close();
	ofstream fo("M1.bin", ios::binary | ios::out);



	fo.close();
	return 0;
}

