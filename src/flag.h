#pragma once

#include <stdbool.h>
#include "config.h"

typedef struct Flag Flag;
typedef struct Flag {
	char name[FLAG_SIZE-1];
	Flag* next;
} Flag;

Flag* initFlag(char name[FLAG_SIZE]);
Flag* appendFlag(Flag* flag, char name[FLAG_SIZE]);
Flag* deleteFlag(Flag* flag, char name[FLAG_SIZE]);
Flag* freeFlags(Flag* flag);

bool findFlag(Flag* flag, char name[FLAG_SIZE]);
