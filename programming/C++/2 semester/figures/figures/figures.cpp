// figures.cpp : Определяет точку входа для приложения.
//

#include "stdafx.h"
#include "figures.h"
#include "classes.h"
#include <windowsx.h>
#include <list>
using namespace std;

#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна
PParam pparam{ 300,300,0,250,150,30,2,RGB(0, 0, 0),RGB(255, 0, 0) };
PPParam ppparam{ 300,300,0,250,150,30,2,RGB(0, 0, 0),RGB(60, 179, 113),RGB(0, 139, 139),RGB(0, 255, 255),RGB(139, 0, 139)};
TParam tparam{ 300,300,0,250,100,150,120,2,RGB(0, 0, 0),RGB(127, 255, 212) };
PTParam ptparam{ 300,300,0,250,100,150,120,2,RGB(0, 0, 0),RGB(75, 0, 130),RGB(176, 224, 230), RGB(218, 112, 214) };
bool LBUTTDOWN = false;
bool IsInside = false;
POINT Cur = { 0,0 };

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Разместите код здесь.

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_FIGURES, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_FIGURES));

    MSG msg;
	

    // Цикл основного сообщения:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  ФУНКЦИЯ: MyRegisterClass()
//
//  ЦЕЛЬ: Регистрирует класс окна.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;
	HBRUSH brush = CreateSolidBrush(RGB(240, 248, 255));
    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_FIGURES));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = brush;
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_FIGURES);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   ЦЕЛЬ: Сохраняет маркер экземпляра и создает главное окно
//
//   КОММЕНТАРИИ:
//
//        В этой функции маркер экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ЦЕЛЬ: Обрабатывает сообщения в главном окне.
//
//  WM_COMMAND  - обработать меню приложения
//  WM_PAINT    - Отрисовка главного окна
//  WM_DESTROY  - отправить сообщение о выходе и вернуться
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static list <Shape *> list;
	static Shape * current;
    switch (message)
    {	
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            switch (wmId)
            {
            case IDM_ABOUT:
				DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
			case ID_CrPar:
			{
				current = { new Parallelogram(pparam) };
				list.push_front(current);
				InvalidateRect(hWnd, 0, true);
			}
				break;
			case ID_CrParDiag:
			{
				current = { new PaintedParallelogram(ppparam) };
				list.push_front(current);
				InvalidateRect(hWnd, 0, true);
			}
			break;
			case ID_CrTr:
			{
				current = { new Trapezium(tparam) };
				list.push_front(current);
				InvalidateRect(hWnd, 0, true);
			}
			break;
			case ID_CrTrDiag:
			{
				current = { new PaintedTrapezium(ptparam) };
				list.push_front(current);
				InvalidateRect(hWnd, 0, true);
			}
			break;
			case ID_MyDelete:
			{
				if (!list.empty())
				{
					list.pop_front();
					Shape * tm;
					swap(tm, current);
					delete tm;
					if (!list.empty())
					{
						current = *(list.begin());
					}
					else
						current = nullptr;
					InvalidateRect(hWnd, 0, true);
				}
			}
			break;
			case ID_MyDeleteAll:
			{
				list.clear();
				current = nullptr;
				InvalidateRect(hWnd, 0, true);
			}
			break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
			for (auto it = list.rbegin(); it != list.rend(); ++it)
				(*it)->Draw(hdc);
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
	case WM_LBUTTONDOWN:
	{
		LBUTTDOWN = true;
		Cur.x = GET_X_LPARAM(lParam);
		Cur.y = GET_Y_LPARAM(lParam);
		for (auto it = list.begin(); it != list.end(); ++it)
		{
			if ( (*it)->IsDotIn(Cur)==true ) 
			{
				IsInside = true;
				current = *it;
				list.erase(it);
				list.push_front(current);
				InvalidateRect(hWnd, 0, false);
				break;
			}
		}
	}
	break;
	case WM_LBUTTONUP:
	{
		LBUTTDOWN = false;
		IsInside = false;
	}
	break;
	case WM_RBUTTONDOWN:
	{
		bool tr=false;
		Cur.x = GET_X_LPARAM(lParam);
		Cur.y = GET_Y_LPARAM(lParam);
		for (auto it = list.begin(); it != list.end(); ++it)
		{
			if ((*it)->IsDotIn(Cur) == true)
			{
				current = *it;
				list.erase(it);
				list.push_front(current);
				InvalidateRect(hWnd, 0, false);
				tr = true;
				break;
			}
		}
		if (tr)
		{
			CHOOSECOLOR cc = { 0 };
			cc.lStructSize = sizeof(cc);
			COLORREF cust_colors[16] = { 0 };
			cc.lpCustColors = cust_colors;
			if (ChooseColor(&cc))
			{
				if (current->Type() == 1 || current->Type() == 3)
				{
					current->ChageColor(cc.rgbResult);
					InvalidateRect(hWnd, 0, true);
				}
				else
				{
					for (int i = 1; i <= 4; ++i)
					{
						if (current->IsDotInSegment(i, Cur))
						{
							current->ChangeSegmentColor(i, cc.rgbResult);
							InvalidateRect(hWnd, 0, true);
							break;
						}
					}
				}
			}
			
		}
	}
	break;
	case WM_MOUSEMOVE:
	{
		if (LBUTTDOWN && IsInside)
		{
			if (!list.empty())
			{
				POINT newCur;
				newCur.x = GET_X_LPARAM(lParam);
				newCur.y = GET_Y_LPARAM(lParam);
				current->Shift(newCur.x - Cur.x, newCur.y - Cur.y);
				Cur = newCur;
				InvalidateRect(hWnd, 0, true);
			}
		}
	}
	break;
	case WM_KEYDOWN:
	{
		switch (wParam)
		{
		case VK_DELETE:
		{
			if (!list.empty())
			{
				list.pop_front();
				Shape * tm;
				swap(tm, current);
				delete tm;
				if (!list.empty())
				{
					current = *(list.begin());
				}
				else
					current = nullptr;
				InvalidateRect(hWnd, 0, true);
			}
		}
		break;
		case VK_LEFT:
		{
			if (current)
			{
				current->Shift(-5,0);
				InvalidateRect(hWnd, 0, true);
			}
		}
		break;
		case VK_RIGHT:
		{
			if (current)
			{
				current->Shift(5, 0);
				InvalidateRect(hWnd, 0, true);
			}
		}
		break;
		case VK_UP:
		{
			if (current)
			{
				current->Shift(0,-5);
				InvalidateRect(hWnd, 0, true);
			}
		}
		break;
		case VK_DOWN:
		{
			if (current)
			{
				current->Shift(0, 5);
				InvalidateRect(hWnd, 0, true);
			}
		}
		break;
		case 0x51:
		{
			if (current)
			{
				current->Rotate(-5);
				InvalidateRect(hWnd, 0, true);
			}
		}
		break;
		case 0x45:
		{
			if (current)
			{
				current->Rotate(5);
				InvalidateRect(hWnd, 0, true);
			}
		}
		break;
		case 0x57:
		{
			if (current)
			{
				current->Explode(0.1);
				InvalidateRect(hWnd, 0, true);
			}
		}
		break;
		case 0x53:
		{
			if (current)
			{
				current->Explode(-0.1);
				InvalidateRect(hWnd, 0, true);
			}
		}
		break;
		case 0x41:
		{
			if (current)
			{
				current->ChangeIntCorner(5);
				InvalidateRect(hWnd, 0, true);
			}
		}
		break;
		case 0x44:
		{
			if (current)
			{
				current->ChangeIntCorner(-5);
				InvalidateRect(hWnd, 0, true);
			}
		}
		break;
		default:
			break;
		}
	}
	break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Обработчик сообщений для окна "О программе".
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
