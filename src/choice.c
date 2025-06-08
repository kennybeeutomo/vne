#include "choice.h"
#include <stdlib.h>
#include <string.h>

Choice* initChoice(char text[CHOICE_SIZE], Scene* scene) {
	Choice* choice = malloc(sizeof(Choice));
	strcpy(choice->text, text);
	strcpy(choice->requiredFlags, "");
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
	while (choice->next != NULL) choice = choice->next;
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

Choice* appendChoice(Choice* choices, char text[CHOICE_SIZE], Scene* scene) {
	Choice* newChoice = initChoice(text, scene);

	if (choices == NULL) {
		return newChoice;
	}

	Choice* curr = choices;
	while (curr->next != NULL) curr = curr->next;
	curr->next = newChoice;
	newChoice->prev = curr;

	return choices;
}

Choice* deleteChoice(Choice* choices, Choice* target) {
	if (target == NULL) {
		return choices;
	}

	if (choices == NULL) {
		return NULL;
	}

	if (choices == target) {
		Choice* next = choices->next;
		free(target);
		return next;
	}

	Choice* curr = choices->next;
	while (curr != NULL) {
		if (curr == target) {
			curr->prev->next = curr->next;
			free(curr);
		}
		curr = curr->next;
	}

	return choices;
}

Choice* freeChoices(Choice* choice) {
	if (choice == NULL) {
		return NULL;
	}

	freeChoices(choice->next);
	free(choice);

	return NULL;
}

void requireChoiceFlag(Choice* choice, char flag[DEFAULT_STRING_SIZE]) {
	strcpy(choice->requiredFlags, flag);
}

void setFlag(Choice* choice, char flag[FLAG_SIZE]) {
	choice->flagsToSet = appendFlag(choice->flagsToSet, flag);
}

void unsetFlag(Choice* choice, char flag[FLAG_SIZE]) {
	choice->flagsToUnset = appendFlag(choice->flagsToUnset, flag);
}
