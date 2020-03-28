#include "View.h"

void View::Update()
{
	SendDlgItemMessage(hDlg, IDC_LIST, LB_RESETCONTENT, 0, 0);
	if (!list->IsEmpty())
	{
		char buffer[100];
		int n = list->count();
		for (int i = 0; i < n; ++i)
		{
			int x = list->getItemReal(i);
			int y = list->getItemImg(i);
			sprintf_s(buffer, 100, "%d+%di", x,y);
			SendDlgItemMessage(hDlg, IDC_LIST, LB_ADDSTRING, 0, (LPARAM)buffer);
		}
		Complex* min = list->Min();
		sprintf_s(buffer, 100, "%d+%di", min->real, min->img);
		SendDlgItemMessage(hDlg, IDC_EDIT1, WM_SETTEXT, 0, (LPARAM)buffer);
		Complex* max = list->Max();
		sprintf_s(buffer, 100, "%d+%di", max->real, max->img);
		SendDlgItemMessage(hDlg, IDC_EDIT2, WM_SETTEXT, 0, (LPARAM)buffer);
	}

}