#include "View.h"

View::View(HWND hwnd, Set* set, int list)
{
	hDlg = hwnd;
	s = set;
	IDC_LIST = list;
}

void View::Update()
{
	SendDlgItemMessage(hDlg, IDC_LIST, LB_RESETCONTENT, 0, 0);
	if (!s->IsEmpty())
	{
		char buffer[100];
		int n = s->Count();
		for (int i = 0; i < n; ++i)
		{
			int tm = s->GetItem(i);
			sprintf_s(buffer, 100, "%d", tm);
			SendDlgItemMessage(hDlg, IDC_LIST, LB_ADDSTRING, 0, (LPARAM)buffer);
		}
	}
}
