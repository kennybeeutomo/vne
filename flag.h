#pragma once

#include <stdbool.h>
#define FLAG_SIZE 30

typedef struct Flag Flag;
typedef struct Flag {
	char name[FLAG_SIZE];
	Flag* next;
} Flag;

Flag* initFlag(char name[FLAG_SIZE]);
Flag* appendFlag(Flag* flag, char name[FLAG_SIZE]);
Flag* freeFlags(Flag* flag);
bool findFlag(Flag* flag, char name[FLAG_SIZE]);
