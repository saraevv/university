#include <iostream>
#include <string>
using namespace std;

//int FCountWords1(char*p, int n)
//{
//	_asm
//	{
//		sub esp, 4
//		mov edi, [ebp+8]
//		mov al, 32
//		mov ecx, [ebp+12]
//		dec ecx
//		cld
//		xor ebx, ebx
//		c1:
//			test al, 1
//			repz scasb
//			je Fin
//			dec edi
//			inc ecx
//			inc ebx
//			//
//			mov edx, ecx
//			repnz scasb
//			jecxz Fin
//			dec edi
//			inc ecx
//			sub edx, ecx
//			test edx,1
//			jnz IfOdd
//			jz c1
//			//jmp c1
//		IfOdd:
//			push eax
//			push ecx
//			push ebx
//			mov ecx, edi; l
//			sub ecx, edx
//			mov eax, edx; i
//			dec eax
//			shr eax, 1
//			mov edx, edi; r
//			dec edx
//			c2:
//				cmp eax, 0
//				je endc2
//				mov bl, byte ptr[ecx]
//				mov byte ptr[ebp - 4], bl; *l
//				mov bl, byte ptr[edx]; *r
//				xor byte ptr[ebp - 4], bl
//				xor bl, byte ptr[ebp - 4]
//				xor byte ptr[ebp - 4], bl
//				mov byte ptr[edx], bl
//				mov bl, byte ptr [ebp-4]
//				mov byte ptr [ecx], bl
//				dec eax
//				inc ecx
//				dec edx
//				jmp c2
//		endc2:
//			pop ebx
//			pop ecx
//			pop eax
//			jmp c1
//		Fin:
//			mov eax, ebx
//			add esp, 4
//	}
//}

//int FCountWords2(char* p, int n, char *ans)
//{
//	_asm
//	{
//		sub esp, 4
//		// адрес текущего символа строки
//		mov edi, [ebp + 8]
//		mov al, ' '
//		// текущий символ строки
//		mov ecx, [ebp + 12]
//		cld
//		// счетчик слов
//		xor ebx, ebx
//		// счетчик символов, записанных в новую строку
//		xor edx, edx
//		c1:
//			// Проход пробелов
//			test al, 1
//			repz scasb
//			je Fin
//			// Чтобы не ввести пробел вначале
//			cmp ebx, dword ptr 0
//			je NFLSpace
//			jecxz NFLSpace
//			// Добавление пробела в новую строку
//			push ebx
//			mov ebx, dword ptr [ebp+16]
//			add ebx, edx
//			mov byte ptr[ebx], al
//			inc edx
//			pop ebx
//			//
//			NFLSpace :
//			dec edi
//			inc ecx
//			inc ebx
//			// Проход слова
//			mov [ebp-4], ecx
//			repnz scasb
//			jecxz LastW
//			// Выполняется, если слово не последнее в строке
//			dec edi
//			inc ecx
//			sub [ebp-4], ecx
//			jmp NLastW
//			// Проверка на последний символ в строке
//			LastW:
//				push ecx
//				mov ecx, edi
//				dec ecx
//				mov cl, byte ptr[ecx]
//				cmp cl, al
//				pop ecx
//				jne NLastW
//				dec edi
//				dec dword ptr [ebp-4]
//			// Определение длины слова
//			NLastW:
//			push eax
//			push ebx
//			push ecx
//			test [ebp-4], 1
//			jnz IfOdd
//			jz IfEven
//			// нечетное слово
//			IfOdd:
//				// eax указывает а крайний справа симол слова
//				mov eax, edi
//				dec eax
//				c21:
//					cmp [ebp-4], dword ptr 0
//					je endc2
//					mov bl, byte ptr [eax]
//					mov ecx, dword ptr[ebp + 16]
//					add ecx, edx
//					mov byte ptr[ecx], bl
//					inc edx
//					dec eax
//					dec dword ptr [ebp-4]
//					jmp c21
//			IfEven:
//				// eax указывает на крайний левый символ слова
//				mov eax, edi
//				sub eax, [ebp-4]
//				c22 :
//					cmp[ebp - 4], dword ptr 0
//					je endc2
//					mov bl, byte ptr[eax]
//					mov ecx, dword ptr[ebp + 16]
//					add ecx, edx
//					mov byte ptr[ecx], bl
//					inc edx
//					inc eax
//					dec dword ptr[ebp - 4]
//					jmp c22
//			endc2:
//				pop ecx
//				pop ebx
//				pop eax
//				jecxz Fin
//				jmp c1
//			Fin:
//				mov eax, ebx
//				add esp, 4
//	}
//}

int FCountWords(char* p, int n, char *ans)
{
	_asm
	{
		mov edi, [ebp + 8]
		mov al, ' '
		mov ecx, [ebp + 12]
		mov esi, edi
		add esi, ecx
		dec esi
		spaces:
			cmp byte ptr[esi], al
			jne endspaces
			dec esi
			dec ecx
			jmp spaces
		endspaces :
		xor ebx, ebx
		jecxz Fin
		cld
		
		xor edx, edx
		test al, 1
		repz scasb
		dec edi
		inc ecx
		c1: 
			test al, 1
			mov esi, ecx
			repnz scasb
			jecxz NInc
			dec edi
			inc ecx
		NInc:
			sub esi, ecx
			test esi, 1
			push eax
			mov eax, edi
			push ebx
			push ecx
			push edi
			jz IfEven
			dec eax
			mov edi, -1
			jmp c2
			IfEven:
			sub eax, esi
			mov edi, 1
			jmp c2
		cont:
			test al, 1
			repz scasb
			dec edi
			inc ecx
			push ebx
			mov ebx, dword ptr[ebp + 16]
			add ebx, edx
			mov byte ptr[ebx], al
			inc edx
			pop ebx
			jmp c1
		c2:
			cmp esi, dword ptr 0
			je endc2
			mov bl, byte ptr[eax]
			mov ecx, dword ptr[ebp + 16]
			add ecx, edx
			mov byte ptr[ecx], bl
			inc edx
			add eax, edi
			dec esi
			jmp c2
		endc2 :
				pop edi
				pop ecx
				pop ebx
				pop eax
				inc ebx
				jecxz Fin
				jmp cont
		Fin :
			mov eax, ebx
	}
}

int main()
{
	setlocale(LC_ALL, "rus");
	////cout << "Введите длину строки: ";
	////int n;
	////cin >> n;
	////++n;
	////char* str = new char[n];
	//cout << "Введите строку:" << endl;
	////cin.get();
	////cin.getline(str, n);
	//string s;
	//getline(cin, s);
	//int n = s.length();
	//++n;
	//char *str = new char[n];
	//for (int i = 0; i < n; ++i)
	//	str[i] = s[i];
	//str[n - 1] = '/0';
	string s;
	cout << "Введите строку: ";
	getline(cin, s);

	int n = s.length();
	char* string = new char[n + 1];
	string[n] = 0;
	for (int i = 0; i < n; ++i)
	{
		string[i] = s[i];
	}
	char *ans = new char[n];
	for (int i = 0; i < n ; ++i)
		ans[i] = '!';
	cout << "Количество слов в строке: " << FCountWords(string, n, ans) << endl << "Измененная строка:" << endl;
	for (int i = 0; i < n; ++i)
		if(ans[i]!='!')
			cout << ans[i];
	cout << ";" << endl;
	return 0;
}