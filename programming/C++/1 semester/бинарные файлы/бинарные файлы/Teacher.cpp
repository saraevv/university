#include "pch.h"
#include "Teacher.h"

Teacher::Teacher(int num, char FullN[], char pos[], char a_deg[], int key, char prof[])
{
	this->indnum = num;
	this->key = key;
	int k = 0;
	for (int i = 0; FullN[i] != '\0'; i++)
	{
		this->FullName[i] = FullN[i];
		
		k++;
	}
	this->FullName[k] = '\0';
	k = 0;
	for (int i = 0; a_deg[i] != '\0'; i++)
	{
		this->academ_deg[i] = a_deg[i];
		k++;
	}
	this->academ_deg[k] = '\0';
	k = 0;
	for (int i = 0; pos[i] != '\0'; i++)
	{
		this->position[i] = pos[i];
		k++;
	}
	this->position[k] = '\0';
	k = 0;
	for (int i = 0; prof[i] != '\0'; i++)
	{
		this->prof_chair[i] = prof[i];
		k++;

	}
	this->prof_chair[k] = '\0';
}
inline void Teacher::SetFullName(char FN[])
{
	int k = 0;
	for (int i = 0; FN[i] != '\0'; i++)
	{
		this->FullName[i] = FN[i];
		k++;
	}
	this->FullName[k] = '\0';
}
inline void Teacher::SetFullName(const char* FN)
{
	strcpy_s(this->FullName, FN);
}
inline void Teacher::SetPosition(char pos[])
{
	int k = 0;
	for (int i = 0; pos[i] != '\0'; i++)
	{
		this->position[i] = pos[i];
		k++;
	}
	this->position[k] = '\0';
}
inline void Teacher::SetPosition(const char* pos)
{
	strcpy_s(this->position, pos);
}
inline void Teacher::SetAcadem_deg(char ad[])
{
	int k = 0;
	for (int i = 0; ad[i] != '\0'; i++)
	{
		this->academ_deg[i] = ad[i];
		k++;
	}
	this->academ_deg[k] = '\0';
}
inline void Teacher::SetAcadem_deg(const char* ad)
{
	strcpy_s(this->academ_deg, ad);
}
inline void Teacher::SetProf_chair(char pf[])
{
	int k = 0;
	for (int i = 0; pf[i] != '\0'; i++)
	{
		this->prof_chair[i] = pf[i];

		k++;
	}
	this->prof_chair[k] = '\0';
}

inline void Teacher::SetProf_chair(const char* pf)
{
	strcpy_s(this->prof_chair, pf);
}
inline void Teacher::SetIndnum(int in)
{
	this->indnum = in;
}
inline void Teacher::SetKey(int key)
{
	this->key = key;
}

inline int Teacher::GEtSPKey()
{
	return 0;
}

inline char* Teacher::GetFullName()
{
	return this->FullName;
}
inline char* Teacher::GetPosition()
{
	return this->position;
}
inline char* Teacher::GetAcadem_deg()
{
	return this->academ_deg;
}
inline char* Teacher::GetProf_chair()
{
	return this->prof_chair;
}
inline int Teacher::GetKey()
{
	return this->key;
}
inline int Teacher::GetIndnum()
{
	return this->indnum;

}
istream& operator >>(istream& is, Teacher& teacher)
{
	char FullName[20], position[20], academ_deg[20];
	int key;
	char prof_chair[20];
	int indnum;
	is >> indnum;
	
	teacher.SetIndnum(indnum);
	char a;
	int i = 0;
	while (true)
	{
		is >> a;
		if (a == ';')
		{
			i = 0;
			break;
		}
		FullName[i] = a;
		i++;
	}
	teacher.SetFullName(FullName);
	while (true)
	{
		is >> a;
		if (a == ';')
		{
			i = 0;
			break;
		}
		position[i] = a;
		i++;
	}
	teacher.SetPosition(position);
	while (true)
	{
		is >> a;
		if (a == ';')
		{
			i = 0;
			break;
		}
		academ_deg[i] = a;
		i++;
	}
	teacher.SetAcadem_deg(academ_deg);
	is >> key;
	teacher.SetKey(key);
	while (true)
	{
		is >> a;
		if (a == ';')
		{
			i = 0;
			break;
		}
		prof_chair[i] = a;
		i++;
	}
	teacher.SetProf_chair(prof_chair);
	return is;
}

ostream& operator << (ostream& os, Teacher& teacher)
{

	os << teacher.GetIndnum() << " " << teacher.GetFullName() << " " << teacher.GetPosition() << " " << teacher.GetAcadem_deg() << " " << teacher.GetKey() << " " << teacher.GetProf_chair() << endl;
	return os;
}
ofstream& operator <<(ofstream& of, Teacher& teacher)
{
	of << teacher.indnum << ";" << teacher.FullName << ";" << teacher.position << ";" << teacher.academ_deg << ";"  << teacher.prof_chair << ";" << endl;
	return of;
}

ifstream & operator>>(ifstream & ifs, Proff &pf)
{
	char a = 0;
	char b[50];
	int num;
	ifs >> num;
	pf.key = num;
	if (num < 0)
	{
		
		return ifs;
	}
	else
	{
		
		int i = 0;

		ifs >> a;
		if (a == 0)
		{
			return ifs;
		}
		
		while (a != '\n')
		{
			a = ifs.get();
			b[i] = a;
			i++;
			
			if (a == ';')
			{
				
				for (int j = 0; b[j] != ';'; j++)
				{
					pf.name[j] = b[j];

				}
				pf.name[i - 1] = '\0';
				i = 0;
				a = ifs.get();
				break;

			}

		}
	}
	return ifs;
}
ofstream & operator<<(ofstream &of, Proff &pf)
{
	of << pf.key << ";" << pf.name << ";" << endl;
	return of;
}
ifstream& operator >>(ifstream& ifs, Teacher& teacher)
{
	char a=0;
	char b[20];
	int num;
	ifs >> num;
	if (num < 0)
	{
		return ifs;
	}
	else
	{
		teacher.indnum = num;
		int i = 0;
		num = 0;
		ifs >> a;
		if (a == 0)
		{
			return ifs;
		}
		while (a != '\n')
		{
			a = ifs.get();
			b[i] = a;
			i++;
			if (a == ';')
			{
				if (num == 0)
				{
					for (int j = 0; b[j] != ';'; j++)
					{
						teacher.FullName[j] = b[j];

					}
					b[i] = '\0';
					teacher.FullName[i - 1] = '\0';
					num = 1;
					i = 0;
				}
				else if (num == 1)
				{
					for (int j = 0; b[j] != ';'; j++)
					{
						teacher.position[j] = b[j];

					}
					num = 2;
					b[i] = '\0';
					teacher.position[i - 1] = '\0';
					
					i = 0;
				}
				else if (num == 2)
				{
					for (int j = 0; b[j] != ';'; j++)
					{
						teacher.academ_deg[j] = b[j];
					}
					b[i] = '\0';
					teacher.academ_deg[i - 1] = '\0';
					
					ifs >> num;
					teacher.key = num;
					num = 3;
					i = 0;
				}
				else if (num == 3)
				{
					for (int j = 0; b[j] != ';'; j++)
					{
						teacher.prof_chair[j] = b[j];

					}
					b[i] = '\0';
					teacher.prof_chair[i - 1] = '\0';
					
					i = 0;
				}

			}
			
		}
		return ifs;
	}
}


Teacher::~Teacher()
{
}

Proff::Proff()
{
}

Proff::Proff(int k, char n[])
{
	this->key = k;
	int t= 0;
	for (int i = 0; n[i] != '\0'; i++)
	{
		this->name[i] = n[i];
		t++;
	}
	this->name[t] = '\0';
}

Proff::~Proff()
{
}
