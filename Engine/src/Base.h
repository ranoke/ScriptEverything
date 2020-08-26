#pragma once
#define CONFIG_DIR "C:/ScriptEverything/"



#include <Windows.h>
#include <string>
#include <iostream>
#include <assert.h>

#define BIT(x) x << 1



static std::wstring string2wstring(const std::string& s)
{
    int len;
    int slength = (int)s.length() + 1;
    len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
    wchar_t* buf = new wchar_t[len];
    MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
    std::wstring r(buf);
    delete[] buf;
    return r;
}