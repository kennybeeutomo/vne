#include "utils.h"
#include <ctype.h>

int mod(const int a, const int b) {
	if (b == 0) return 0;
	return (a % b + b) % b;
}

int countStrHeight(const char* str, int width) {
	int height = 1;
	int col = 0;
	for (int i = 0; str[i] != '\0'; ++i) {
		if (str[i] == '\n' || col >= width) {
			height++;
			col = 0;
			if (str[i] == '\n') { continue; }
		} else {
			col++;
		}
	}
	return height;
}

int skipNumbers(int i, const char* str) {
	if (str[i] == '\0') { return i; }
	if (str[i] == '-') { i++; }
	while (isdigit(str[i])) { i++; }
	return i;
}

void setstr(char* str, int n, char c) {
	int i;
	for (i = 0; i < n - 1; ++i) {
		str[i] = c;
	}
	str[i] = '\0';
}
