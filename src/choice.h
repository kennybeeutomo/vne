#pragma once

#include "flag.h"
#include <stdbool.h>
#include "config.h"

typedef struct Scene Scene;

typedef struct Choice Choice;
typedef struct Choice {
	char text[CHOICE_SIZE];
	char requiredFlag[FLAG_SIZE];
	char flagToAdd[FLAG_SIZE];
	Scene* scene;
	Choice* next;
} Choice;

Choice* initChoice(char text[CHOICE_SIZE], Scene* scene);
void printChoices(Choice* choice, Flag* flags);
Choice* tailChoice(Choice* choice);
Choice* appendChoice(Choice* choice, char text[CHOICE_SIZE], Scene* scene);
Choice* deleteChoice(Choice* choice, char text[CHOICE_SIZE]);
Choice* freeChoices(Choice* choice);
void requireChoiceFlag(Choice* choice, char flag[FLAG_SIZE]);
void setFlag(Choice* choice, char flag[FLAG_SIZE]);
