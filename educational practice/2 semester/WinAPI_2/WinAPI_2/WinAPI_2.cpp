// WinAPI_2.cpp : Определяет точку входа для приложения.
//

#include "stdafx.h"
#include "WinAPI_2.h"
#include "classes.h"
#include <list>
#include <fstream>
#include <io.h>
#include <windowsx.h>

#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна
static list<Shape*> figures;
static Shape* figure;
bool IsInside = false;
bool LBUTTDOWN = false;
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


	double x, y;
	int width, r, g, b;
	char tm;
    // Ввод
	ifstream fi;
	fi.open("in.txt");
	char buff[15];

	while(true)
	{
		fi.getline(buff, 15, ':');
		if (CheckSquare(buff))
		{
			figure = new Square;
			fi >> x >> y;
			figure->Shift(x, y);
			fi >> x;
			figure->SetBase(x);
			fi >> x;
			figure->Rotate(x);
			fi >> width;
			figure->SetWidth(width);
			fi >> tm >> r >> tm >> g >> tm >> b >> tm;
			figure->SetCircuit(RGB(r, g, b));
			fi >> tm >> r >> tm >> g >> tm >> b >> tm;
			figure->SetBackgrond(RGB(r, g, b));
			figures.push_back(figure);
			fi >> tm;
		}
		else if (CheckRectangle(buff))
		{
			figure = new Rectangle_;
			fi >> x >> y;
			figure->Shift(x, y);
			fi >> x;
			figure->SetBase(x);
			fi >> x;
			figure->SetSide(x);
			fi >> x;
			figure->Rotate(x);
			fi >> width;
			figure->SetWidth(width);
			fi >> tm >> r >> tm >> g >> tm >> b >> tm;
			figure->SetCircuit(RGB(r, g, b));
			fi >> tm >> r >> tm >> g >> tm >> b >> tm;
			figure->SetBackgrond(RGB(r, g, b));
			figures.push_back(figure);
			fi >> tm;
		}
		else if (CheckParallelogramm(buff))
		{
			figure = new Parallelogramm;
			fi >> x >> y;
			figure->Shift(x, y);
			fi >> x;
			figure->SetBase(x);
			fi >> x;
			figure->SetSide(x);
			fi >> x;
			figure->SetIntCorner(180-x);
			fi >> x;
			figure->Rotate(x);
			fi >> width;
			figure->SetWidth(width);
			fi >> tm >> r >> tm >> g >> tm >> b >> tm;
			figure->SetCircuit(RGB(r, g, b));
			fi >> tm >> r >> tm >> g >> tm >> b >> tm;
			figure->SetBackgrond(RGB(r, g, b));
			figures.push_back(figure);
			fi >> tm;
		}
		else if (CheckTrapezium(buff))
		{
			figure = new Trapezium;
			fi >> x >> y;
			figure->Shift(x, y);
			fi >> x;
			figure->SetBase(x);
			fi >> x;
			figure->SetSide(x);
			fi >> x;
			figure->SetSBase(x);
			fi >> x;
			figure->SetIntCorner(180-x);
			fi >> x;
			figure->Rotate(x);
			fi >> width;
			figure->SetWidth(width);
			fi >> tm >> r >> tm >> g >> tm >> b >> tm;
			figure->SetCircuit(RGB(r, g, b));
			fi >> tm >> r >> tm >> g >> tm >> b >> tm;
			figure->SetBackgrond(RGB(r, g, b));
			figures.push_back(figure);
			fi >> tm;
		}
		else if (CheckCircle(buff))
		{
			figure = new Circle;
			fi >> x >> y;
			figure->Shift(x, y);
			fi >> x;
			figure->SetRadius(x);
			fi >> width;
			figure->SetWidth(width);
			fi >> tm >> r >> tm >> g >> tm >> b >> tm;
			figure->SetCircuit(RGB(r, g, b));
			fi >> tm >> r >> tm >> g >> tm >> b >> tm;
			figure->SetBackgrond(RGB(r, g, b));
			figures.push_back(figure);
			fi >> tm;
		}
		else if (CheckTriangle(buff))
		{
			figure = new Triangle;
			fi >> x >> y;
			figure->Shift(x, y);
			fi >> x;
			figure->SetBase(x);
			fi >> x;
			figure->SetSide(x);
			fi >> x;
			figure->SetIntCorner(180-x);
			fi >> x;
			figure->Rotate(x);
			fi >> width;
			figure->SetWidth(width);
			fi >> tm >> r >> tm >> g >> tm >> b >> tm;
			figure->SetCircuit(RGB(r, g, b));
			fi >> tm >> r >> tm >> g >> tm >> b >> tm;
			figure->SetBackgrond(RGB(r, g, b));
			figures.push_back(figure);
			fi >> tm;
		}
		else
			break;
		fi.get(tm);
		if (tm == EOF)
			break;
	}

	fi.close();

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINAPI2, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINAPI2));

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
	HBRUSH brush = CreateSolidBrush(RGB(230, 230, 250));
    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINAPI2));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground  = brush;
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WINAPI2);
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
		
    switch (message)
    {
	case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Разобрать выбор в меню:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
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
			for (auto it = figures.rbegin(); it != figures.rend(); ++it)
				(*it)->Draw(hdc);
            EndPaint(hWnd, &ps);
        }
        break;
	case WM_LBUTTONDOWN:
	{
		LBUTTDOWN = true;
		Cur.x = GET_X_LPARAM(lParam);
		Cur.y = GET_Y_LPARAM(lParam);
		for (auto it = figures.begin(); it != figures.end(); ++it)
		{
			if ((*it)->IsDotIn(Cur) == true)
			{
				IsInside = true;
				figure = *it;
				figures.erase(it);
				figures.push_front(figure);
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
		bool tr = false;
		Cur.x = GET_X_LPARAM(lParam);
		Cur.y = GET_Y_LPARAM(lParam);
		for (auto it = figures.begin(); it != figures.end(); ++it)
		{
			if ((*it)->IsDotIn(Cur) == true)
			{
				figure = *it;
				figures.erase(it);
				figures.push_front(figure);
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
					figure->SetBackgrond(cc.rgbResult);
					InvalidateRect(hWnd, 0, true);
			}

		}
	}
	break;
	case WM_MOUSEMOVE:
	{
		if (LBUTTDOWN && IsInside)
		{
			if (!figures.empty())
			{
				POINT newCur;
				newCur.x = GET_X_LPARAM(lParam);
				newCur.y = GET_Y_LPARAM(lParam);
				figure->Shift(newCur.x - Cur.x, newCur.y - Cur.y);
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
		case VK_LEFT:
		{
			if (figure)
			{
				figure->Shift(-5, 0);
				InvalidateRect(hWnd, 0, true);
			}
		}
		break;
		case VK_RIGHT:
		{
			if (figure)
			{
				figure->Shift(5, 0);
				InvalidateRect(hWnd, 0, true);
			}
		}
		break;
		case VK_UP:
		{
			if (figure)
			{
				figure->Shift(0, -5);
				InvalidateRect(hWnd, 0, true);
			}
		}
		break;
		case VK_DOWN:
		{
			if (figure)
			{
				figure->Shift(0, 5);
				InvalidateRect(hWnd, 0, true);
			}
		}
		break;
		case 0x51:
		{
			if (figure)
			{
				figure->Rotate(-5);
				InvalidateRect(hWnd, 0, true);
			}
		}
		break;
		case 0x45:
		{
			if (figure)
			{
				figure->Rotate(5);
				InvalidateRect(hWnd, 0, true);
			}
		}
		break;
		case 0x57:
		{
			if (figure)
			{
				figure->Explode(0.1);
				InvalidateRect(hWnd, 0, true);
			}
		}
		break;
		case 0x53:
		{
			if (figure)
			{
				figure->Explode(-0.1);
				InvalidateRect(hWnd, 0, true);
			}
		}
		break;
		case 0x41:
		{
			if (figure)
			{
				figure->ChangeIntCorner(5);
				InvalidateRect(hWnd, 0, true);
			}
		}
		break;
		case 0x44:
		{
			if (figure)
			{
				figure->ChangeIntCorner(-5);
				InvalidateRect(hWnd, 0, true);
			}
		}
		break;
		default:
			break;
		}
	}
	break;
    case WM_DESTROY:
        PostQuitMessage(0);
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
