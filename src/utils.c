#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

int mod(const int a, const int b) {
	if (b == 0) return 0;
	return (a % b + b) % b;
}
