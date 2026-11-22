#pragma once

#include "config.h"
#include <stdbool.h>
#include <wchar.h>

typedef struct Flag Flag;
typedef struct Flag {
	wchar_t name[FLAG_SIZE];
	Flag* next;
} Flag;

Flag* initFlag(wchar_t name[FLAG_SIZE]);
Flag* appendFlag(Flag* flag, wchar_t name[FLAG_SIZE]);
Flag* deleteFlag(Flag* flag, wchar_t name[FLAG_SIZE]);

Flag* appendFlags(Flag* flag, Flag* flagsToAppend);
Flag* deleteFlags(Flag* flag, Flag* flagsToDelete);

bool isFlag(wchar_t flag[FLAG_SIZE]);

Flag* freeFlags(Flag* flag);

bool findFlag(Flag* flag, wchar_t name[FLAG_SIZE]);
int evaluateFlags(Flag* flags, const wchar_t requiredFlags[DEFAULT_STRING_SIZE]);
