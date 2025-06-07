#pragma once

#include <stdbool.h>
#include "config.h"

typedef struct Flag Flag;
typedef struct Flag {
	char name[FLAG_SIZE];
	Flag* next;
} Flag;

Flag* initFlag(char name[FLAG_SIZE]);
Flag* appendFlag(Flag* flag, char name[FLAG_SIZE]);
Flag* deleteFlag(Flag* flag, char name[FLAG_SIZE]);

Flag* appendFlags(Flag* flag, Flag* flagsToAppend);
Flag* deleteFlags(Flag* flag, Flag* flagsToDelete);

bool isFlag(char flag[FLAG_SIZE]);

Flag* freeFlags(Flag* flag);

bool findFlag(Flag* flag, char name[FLAG_SIZE]);
int evaluateFlags(Flag* flags, const char requiredFlags[DEFAULT_STRING_SIZE]);
