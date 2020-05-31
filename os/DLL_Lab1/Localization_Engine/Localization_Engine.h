#pragma once

extern "C" __declspec(dllexport) void Init(const char* lang);
extern "C" __declspec(dllexport) const char* GetStr1();
extern "C" __declspec(dllexport) const char* GetStr2();