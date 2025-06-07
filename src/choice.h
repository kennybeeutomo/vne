#pragma once

#include "flag.h"
#include "config.h"

typedef struct Scene Scene;

typedef struct Choice Choice;
typedef struct Choice {
	char text[CHOICE_SIZE];
	char requiredFlags[DEFAULT_STRING_SIZE];
	Flag* flagsToSet;
	Flag* flagsToUnset;
	Scene* scene;
	Choice* next;
	Choice* prev;
} Choice;

Choice* initChoice(char text[CHOICE_SIZE], Scene* scene);

Choice* choiceAt(Choice* choices, Flag* flags, int i);
Choice* tailChoice(Choice* choice);
Choice* nextChoice(Choice* choice, Flag* flags);
Choice* prevChoice(Choice* choice, Flag* flags);
Choice* getFirstChoice(Choice* choices, Flag* flags);

Choice* appendChoice(Choice* choices, char text[CHOICE_SIZE], Scene* scene);
Choice* deleteChoice(Choice* choices, Choice* target);
Choice* freeChoices(Choice* choice);

void requireChoiceFlag(Choice* choice, char flag[DEFAULT_STRING_SIZE]);
void setFlag(Choice* choice, char flag[FLAG_SIZE]);
void unsetFlag(Choice* choice, char flag[FLAG_SIZE]);
