#include "pch.h"
#include "Localization_Engine.h"
#include <iostream>
#include <string>

static HMODULE hModule = LoadLibraryA("Localization_Engine.old.dll");

void Init(const char* lang) {
	void(*Old_Init)(const char*) = (void(*)(const char*))GetProcAddress(hModule, "Init");
	Old_Init(lang);
}

const char* GetStr1() {
	const char* (*Old_GetStr1)() = (const char* (*)())GetProcAddress(hModule, "GetStr1");
	return Old_GetStr1();
}

const char* GetStr2() {
	return "Hacked!";
}