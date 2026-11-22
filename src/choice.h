#pragma once

#include "config.h"
#include "flag.h"
#include <wchar.h>

typedef struct Scene Scene;

typedef struct Choice Choice;
typedef struct Choice {
	wchar_t text[CHOICE_SIZE];
	wchar_t requiredFlags[DEFAULT_STRING_SIZE];
	Flag* flagsToSet;
	Flag* flagsToUnset;
	Scene* scene;
	Choice* next;
	Choice* prev;
} Choice;

Choice* initChoice(wchar_t text[CHOICE_SIZE], Scene* scene);

Choice* choiceAt(Choice* choices, Flag* flags, int i);
Choice* tailChoice(Choice* choice);
Choice* nextChoice(Choice* choice, Flag* flags);
Choice* prevChoice(Choice* choice, Flag* flags);
Choice* getFirstChoice(Choice* choices, Flag* flags);
Choice* getLastChoice(Choice* choices, Flag* flags);

Choice* appendChoice(Choice* choices, wchar_t text[CHOICE_SIZE], Scene* scene);
Choice* freeChoice(Choice* choice);
Choice* freeChoices(Choice* choice);

Choice* copyChoices(Choice* from, Choice* to);

void requireChoiceFlag(Choice* choice, wchar_t flag[DEFAULT_STRING_SIZE]);
void setFlag(Choice* choice, wchar_t flag[FLAG_SIZE]);
void unsetFlag(Choice* choice, wchar_t flag[FLAG_SIZE]);
