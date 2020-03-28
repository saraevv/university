#include <windows.h>
#include <cstdio>
#include <cstdlib>
#include "Set.h"
#include "View.h"
#include "resource.h"

INT_PTR CALLBACK MainWindow(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, MainWindow);

}

INT_PTR CALLBACK MainWindow(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	static View* view;
	static Set* model;
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
	{
		model = new Set();
		view = new View(hDlg, model, IDC_LIST_OUTPUT);
	}
	break;
	case WM_CLOSE:
		DestroyWindow(hDlg);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
		case IDC_BUTTON_ADD:
			{
				int current = 0;
				current = GetDlgItemInt(hDlg, IDC_INPUT, NULL, FALSE);
				model->Add(current);
				view->Update();
			}
			break;
		case IDC_BUTTON_DELETE:
			{
				int number = SendDlgItemMessage(hDlg, IDC_LIST_OUTPUT, LB_GETCURSEL, 0, 0);
				if (number != LB_ERR)
				{
					char buffer[100];
					SendDlgItemMessage(hDlg, IDC_LIST_OUTPUT, LB_GETTEXT, (WPARAM)number, (LPARAM)buffer);
					int n = atoi(buffer);
					model->Delete(n);
					view->Update();
				}
			}
			break;
		}
	}
	return (INT_PTR)FALSE;
}