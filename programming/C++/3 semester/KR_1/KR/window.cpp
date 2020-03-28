#include <windows.h>
#include <windows.h>
#include <cstdio>
#include <cstdlib>
#include <string>
#include "List.h"
#include "View.h"
#include "resource.h"

INT_PTR CALLBACK Controller(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, Controller);
}

INT_PTR CALLBACK Controller(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	static View* view;
	static List* model;
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
	{
		model = new List();
		view = new View(hDlg, model, IDC_LISTBOX, IDC_EDIT_MIN, IDC_EDIT_MAX);
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
		case IDC_BUTTON_PUSHFRONT:
		{
			/*int current = 0;
			current = GetDlgItemInt(hDlg, IDC_EDIT, NULL, FALSE);
			model->push_back(current);
			view->Update();*/
			char* buffer = new char[100];
			int x, y;
			SendDlgItemMessage(hDlg, IDC_EDIT_REAL, WM_GETTEXT, 100, (LPARAM)buffer);
			x = atoi(buffer);
			std::string s1 = std::to_string(x);
			std::string s2 = buffer;
			if (s1 == s2)
			{
				/*model->push_front(x);
				view->Update();*/
				SendDlgItemMessage(hDlg, IDC_EDIT_IMG, WM_GETTEXT, 100, (LPARAM)buffer);
				y = atoi(buffer);
				s1 = std::to_string(y);
				s2 = buffer;
				if (s1 == s2)
				{
					model->push_front(x, y);
					view->Update();
				}
				else
					MessageBox(hDlg, "¬ведите целое число!", "ќшибка!", MB_OK | MB_ICONWARNING);
			}
			else
			{
				MessageBox(hDlg, "¬ведите целое число!", "ќшибка!", MB_OK | MB_ICONWARNING);
			}
		}
		break;
		case IDC_BUTTON_PUSHBACK:
		{
			char* buffer = new char[100];
			int x, y;
			SendDlgItemMessage(hDlg, IDC_EDIT_REAL, WM_GETTEXT, 100, (LPARAM)buffer);
			x = atoi(buffer);
			std::string s1 = std::to_string(x);
			std::string s2 = buffer;
			if (s1 == s2)
			{
				/*model->push_front(x);
				view->Update();*/
				SendDlgItemMessage(hDlg, IDC_EDIT_IMG, WM_GETTEXT, 100, (LPARAM)buffer);
				y = atoi(buffer);
				s1 = std::to_string(y);
				s2 = buffer;
				if (s1 == s2)
				{
					model->push_back(x, y);
					view->Update();
				}
				else
					MessageBox(hDlg, "¬ведите целое число!", "ќшибка!", MB_OK | MB_ICONWARNING);
			}
			else
			{
				MessageBox(hDlg, "¬ведите целое число!", "ќшибка!", MB_OK | MB_ICONWARNING);
			}
		}
		break;
		case IDC_BUTTON_POPFRONT:
		{
			if (model->IsEmpty())
				MessageBox(hDlg, "—писок пуст!", "ќшибка!", MB_OK | MB_ICONWARNING);
			else
			{
				model->pop_front();
				view->Update();
			}
		}
		break;
		/*case IDC_BUTTON_VISITOR:
		{
			std::string str = model->GetStr();
			char* writable = new char[str.size() + 1];
			std::copy(str.begin(), str.end(), writable);
			writable[str.size()] = '\0';
			MessageBox(hDlg, writable, "to_String", MB_OK);
			delete[] writable;
		}
		break;*/
		}
	}
	return (INT_PTR)FALSE;
}