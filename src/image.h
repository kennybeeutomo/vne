#pragma once

#include "config.h"
#include <stdbool.h>
#include <wchar.h>

typedef struct Image {
	char imagePath[IMAGE_SIZE * sizeof(wchar_t)];
	int x;
	int y;
	int zOrder;
	bool clear;
} Image;
