#pragma comment(lib, "Localization_Engine.lib")

#include "Localization_Engine.h"
#include <iostream>


int main(int argc, char* argv[])
{
	const char* code = argc > 1 ? argv[1] : "EN";
	Init(code);
	std::cout << GetStr1() << '\n' << GetStr2();
	Init(nullptr);
	return 0;
}

