#pragma once
#include <windows.h>
#include "List.h"

class View
{
	HWND hDlg;
	List* list;
	int IDC_LIST;
	int IDC_EDIT1;
	int IDC_EDIT2;
public:
	View(HWND hDlg, List* list, int IDC_LIST, int IDC_EDIT1, int IDC_EDIT2) :hDlg(hDlg), list(list), IDC_LIST(IDC_LIST), IDC_EDIT1(IDC_EDIT1), IDC_EDIT2(IDC_EDIT2) {}
	void Update();
};

