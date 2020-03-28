#pragma once
#include <windows.h>
#include "resource.h"
#include "Set.h"


class View
{
public:
	View(HWND, Set*,int);
	void Update();
private:
	HWND hDlg;
	Set* s;
	int IDC_LIST;
};

