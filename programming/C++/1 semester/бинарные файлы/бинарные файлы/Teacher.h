#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;
class Teacher
{
private:
	int indnum;
	char FullName[20];
	char position[20];
	char academ_deg[20];
	int key;
	char prof_chair[50];
public:

	Teacher() {}
	Teacher(int, char[], char[], char[], int, char[]);
	
	~Teacher();
	
	inline void SetFullName(char[]);
	inline void SetFullName(const char*);
	inline void SetPosition(char[]);
	inline void SetPosition(const char*);
	inline void SetAcadem_deg(char []);
	inline void SetAcadem_deg(const char*);
	inline void SetProf_chair(char[]);
	inline void SetProf_chair(const char*);
	inline void SetIndnum(int);
	inline void SetKey(int);
	inline int GEtSPKey();
	
	inline char* GetFullName();
	inline char* GetPosition();
	inline char* GetAcadem_deg();
	inline char* GetProf_chair();
	inline int GetKey();
	inline int GetIndnum();
	friend istream& operator >>(istream&, Teacher&);
	friend ostream& operator <<(ostream&, Teacher&);
	friend ifstream& operator >>(ifstream&, Teacher&);
	friend ofstream& operator <<(ofstream&, Teacher&);
	
};
class Proff
{
private:
	int key;
	char name[50];
public:
	Proff();
	Proff(int, char[]);
	inline char* Getname()
	{
		return this->name;
	}
	inline int Getkey()
	{
		return this->key;
	}
	~Proff();
	friend ifstream& operator >>(ifstream&, Proff&);
	friend ofstream& operator <<(ofstream&, Proff&);
};

