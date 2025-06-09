#pragma once

#define eq(a, b) (strcmp((a), (b)) == 0)
#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))

int mod(const int a, const int b);
int countStrHeight(const char* str, int width);
int skipNumbers(int i, const char* str);
void setstr(char* str, int n, char c);
