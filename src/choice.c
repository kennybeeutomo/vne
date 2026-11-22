#include "choice.h"
#include "flag.h"
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

Choice* initChoice(wchar_t text[CHOICE_SIZE], Scene* scene) {
	Choice* choice = malloc(sizeof(Choice));
	wcscpy(choice->text, text);
	memset(choice->requiredFlags, 0, sizeof(choice->requiredFlags));
	choice->flagsToUnset = NULL;
	choice->flagsToSet = NULL;
	choice->next = NULL;
	choice->prev = NULL;
	choice->scene = scene;
	return choice;
}

Choice* choiceAt(Choice* choices, Flag* flags, int i) {
	int n = 1;
	while (choices != NULL) {
		if (evaluateFlags(flags, choices->requiredFlags)) {
			if (n == i) {
				break;
			}
			n++;
		}
		choices = choices->next;
	}
	return choices;
}

Choice* tailChoice(Choice* choice) {
	if (choice == NULL) {
		return NULL;
	}
	while (choice->next != NULL)
		choice = choice->next;
	return choice;
}

Choice* nextChoice(Choice* choice, Flag* flags) {
	if (choice == NULL) {
		return choice;
	}

	choice = choice->next;
	while (choice != NULL) {
		if (evaluateFlags(flags, choice->requiredFlags)) {
			break;
		}
		choice = choice->next;
	}

	return choice;
}

Choice* prevChoice(Choice* choice, Flag* flags) {
	if (choice == NULL) {
		return choice;
	}

	choice = choice->prev;
	while (choice != NULL) {
		if (evaluateFlags(flags, choice->requiredFlags)) {
			break;
		}
		choice = choice->prev;
	}

	return choice;
}

Choice* getFirstChoice(Choice* choices, Flag* flags) {
	if (choices == NULL) {
		return NULL;
	}
	if (!evaluateFlags(flags, choices->requiredFlags)) {
		return nextChoice(choices, flags);
	}
	return choices;
}

Choice* getLastChoice(Choice* choices, Flag* flags) {
	Choice* curr = choices;
	Choice* last = curr;
	while (curr != NULL) {
		last = curr;
		curr = nextChoice(curr, flags);
	}
	return last;
}

Choice* appendChoice(Choice* choices, wchar_t text[CHOICE_SIZE], Scene* scene) {
	Choice* newChoice = initChoice(text, scene);

	if (choices == NULL) {
		return newChoice;
	}

	Choice* curr = choices;
	while (curr->next != NULL)
		curr = curr->next;
	curr->next = newChoice;
	newChoice->prev = curr;

	return choices;
}

Choice* freeChoice(Choice* choice) {
	freeFlags(choice->flagsToSet);
	freeFlags(choice->flagsToUnset);
	free(choice);
	return NULL;
}

Choice* freeChoices(Choice* choice) {
	if (choice == NULL) {
		return NULL;
	}

	freeChoices(choice->next);
	freeChoice(choice);

	return NULL;
}

Choice* copyChoices(Choice* from, Choice* to) {
	while (from != NULL) {
		to = appendChoice(to, from->text, from->scene);
		wcscpy(to->requiredFlags, from->requiredFlags);
		to->flagsToSet = appendFlags(to->flagsToSet, from->flagsToSet);
		to->flagsToUnset = appendFlags(to->flagsToUnset, from->flagsToUnset);
		from = from->next;
	}
	return to;
}

void requireChoiceFlag(Choice* choice, wchar_t flag[DEFAULT_STRING_SIZE]) {
	wcscpy(choice->requiredFlags, flag);
}

void setFlag(Choice* choice, wchar_t flag[FLAG_SIZE]) {
	choice->flagsToSet = appendFlag(choice->flagsToSet, flag);
}

void unsetFlag(Choice* choice, wchar_t flag[FLAG_SIZE]) {
	choice->flagsToUnset = appendFlag(choice->flagsToUnset, flag);
}
