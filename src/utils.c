#include "utils.h"
#include <wchar.h>
#include <wctype.h>

int mod(const int a, const int b) {
	if (b == 0)
		return 0;
	return (a % b + b) % b;
}

int countStrHeight(const wchar_t* str, int width) {
	int height = 1;
	int col = 0;
	for (int i = 0; str[i] != '\0'; ++i) {
		if (str[i] == '\n' || col >= width) {
			height++;
			col = 0;
			if (str[i] == '\n') {
				continue;
			}
		} else {
			col++;
		}
	}
	return height;
}

int skipNumbers(int i, const wchar_t* str) {
	if (str[i] == '\0') {
		return i;
	}
	if (str[i] == '-') {
		i++;
	}
	while (iswdigit(str[i])) {
		i++;
	}
	return i;
}

void setstr(wchar_t* str, int n, wchar_t c) {
	int i;
	for (i = 0; i < n - 1; ++i) {
		str[i] = c;
	}
	str[i] = '\0';
}
