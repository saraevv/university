#include <iostream>
using namespace std;

int f(int n, int x)
{
	int c = 1, s = 0, p = 1, m=1;
	for (int i = 1; i <= n; ++i)
	{
		c = (c * (n - i + 1)) / i;
		s += c;
		m *= x;
		p *= m * s;
	}
	return p;
}

int __declspec(naked) f_asm(int n, int x)
{
	_asm
	{
		push ebp
		mov ebp, esp
		sub esp, 16
		mov dword ptr[ebp - 4], 1; c
		mov dword ptr[ebp - 8], 0; s
		mov dword ptr[ebp - 12], 1; m
		mov dword ptr[ebp - 16], 1; p
		mov ecx, 0; i
		c :
			mov eax, [ebp + 8]
			inc ecx
			inc eax
			sub eax, ecx
			imul dword ptr[ebp - 4]
			idiv ecx
			mov[ebp - 4], eax
			add[ebp - 8], eax
			mov eax, [ebp - 12]
			imul dword ptr[ebp + 12]
			mov[ebp - 12], eax
			mov eax, [ebp - 16]
			imul dword ptr[ebp - 12]
			imul dword ptr[ebp - 8]
			mov[ebp - 16], eax
			cmp ecx, [ebp + 8]
			je endc
			jmp c
		endc:
			mov eax, [ebp - 16]
			add esp, 16
			pop ebp
			ret
	}
}


int main()
{
	setlocale(LC_ALL, "rus");
	cout << "Введите n и x: ";
	int n, x;
	cin >> n >> x;
	cout << "Ответ (без использования ассемблера): " << f(n, x) << endl;
	cout << "Ответ (с использованием ассемблера): " << f_asm(n, x);
	return 0;
}