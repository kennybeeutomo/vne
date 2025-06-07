#include "utils.h"

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
			col = 1;
		}
		col++;
	}
	return height;
}
