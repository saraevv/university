#pragma once
#include <stdio.h>
#include <tchar.h>
#include<iostream>
#include<fstream>
#include<iomanip>


class Teacher
{
public:
	Teacher() {};
	Teacher(char*, char*, char*, char*, char*, int, int);
	Teacher(const char*, const char*, const char*, const char*, const char*, int, int);
	~Teacher() {};
	inline void SetId( int);
	inline void SetId(const  int);
	inline void SetFirstName(char*);
	inline void SetFirstName(const char*);
	inline void SetLastName(char*);
	inline void SetLastName(const char*);
	inline void SetPatronymic(char*);
	inline void SetPatronymic(const char*);
	inline void SetCode( int);
	inline void SetCode(const  int);
	inline void SetPost(char*);
	inline void SetPost(const char*);
	inline void AcDegree(char*);
	inline void AcDegree(const char*);
	

	inline char* GetFirstName();
	inline char* GetLastName();
	inline char* GetPost();
	inline char* GetPatronymic();
	inline char* GetAcDegree();
	inline int	GetCode();
	inline int	GetId();


private:
	int id;
	char fname[20];
	char lname[20];
	char patr[20];
	char post[20];
	char ac_degree[20];
	int code;
};

