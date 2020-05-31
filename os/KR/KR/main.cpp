#include <windows.h>
#include <process.h>
#include <iostream>

const int N = 20;
const int M = 10;
unsigned count;

struct Parametrs {
	HANDLE hMutex;
	int i;
};

unsigned int WINAPI func(LPVOID t) {
	Parametrs* param = (Parametrs*)t;
	for (int i = 0; i < 10; ++i) {
		WaitForSingleObject(param->hMutex, INFINITE);
		InterlockedExchangeAdd(&count, param->i);
		std::cout << param->i << '\n';
		ReleaseMutex(param->hMutex);
	}
	return 0;
}

int main() {
	HANDLE hMutex = CreateMutex(NULL, FALSE, NULL);
	HANDLE threads[N];
	Parametrs params[N];
	for (int i = 0; i < N; ++i) {
		params[i] = { hMutex, i };
		threads[i] = (void*)_beginthreadex(NULL, NULL, func, (void*)&(params[i]), CREATE_SUSPENDED, NULL); 
	}
	for (int i = 0; i < N; ++i) {
		ResumeThread(threads[i]);
	}
	WaitForMultipleObjects(N, threads, TRUE, INFINITE);
	std::cout << "Answer: " <<count;
	CloseHandle(hMutex);
	for (int i = 0; i < N; ++i) {
		CloseHandle(threads[i]);
	}

	return 0;
}