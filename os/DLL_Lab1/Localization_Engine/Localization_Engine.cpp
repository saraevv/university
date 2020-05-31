#include "pch.h"
#include "Localization_Engine.h"
#include <iostream>
#include <string>

static HMODULE hModule;

void Init(const char* lang) {
	if (!lang && hModule) {
		FreeLibrary(hModule);
	}
	else if(lang) {
		std::string s("Localization_" + (std::string)lang + ".dll");
		hModule = LoadLibraryA(s.c_str());

		if (!hModule) {
			std::cerr << "Library not found\n";
		}
	}
}

const char* GetStr1() {
	if (!hModule) {
		return "str1";
	}

	return *(char**)(GetProcAddress(hModule, "str1"));
}

const char* GetStr2() {
	if (!hModule) {
		return "str2";
	}

	return *(char**)(GetProcAddress(hModule, "str2"));
}