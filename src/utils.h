#pragma once

#include <wchar.h>

#define eq(a, b) (wcscmp((a), (b)) == 0)
#define eqn(a, b) (strcmp((a), (b)) == 0)
#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))
#define nullstr(str) ((str)[0] == '\0')
#define notnullstr(str) ((str)[0] != '\0')

int mod(const int a, const int b);
int countStrHeight(const wchar_t* str, int width);
int skipNumbers(int i, const wchar_t* str);
void setstr(wchar_t* str, int n, wchar_t c);
