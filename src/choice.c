#include "choice.h"
#include "flag.h"
#include <stdlib.h>
#include <string.h>

Choice* initChoice(char text[CHOICE_SIZE], Scene* scene) {
	Choice* choice = malloc(sizeof(Choice));
	strcpy(choice->text, text);
	strcpy(choice->requiredFlag, "");
	strcpy(choice->flagToAdd, "");
	choice->next = NULL;
	choice->prev = NULL;
	choice->scene = scene;
	return choice;
}

Choice* choiceAt(Choice* choices, Flag* flags, int i) {
	int n = 1;
	while (choices != NULL) {
		if (findFlag(flags, choices->requiredFlag)) {
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
		if (findFlag(flags, choice->requiredFlag)) {
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
		if (findFlag(flags, choice->requiredFlag)) {
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
	if (!findFlag(flags, choices->requiredFlag)) {
		return nextChoice(choices, flags);
	}
	return choices;
}

Choice* appendChoice(Choice* choice, char text[CHOICE_SIZE], Scene* scene) {
	Choice* newChoice = initChoice(text, scene);

	if (choice == NULL) {
		return newChoice;
	}

	Choice* curr = choice;
	while (curr->next != NULL) curr = curr->next;
	curr->next = newChoice;
	newChoice->prev = curr;

	return choice;
}

Choice* deleteChoice(Choice* choices, Choice* target) {
	if (target == NULL) {
		return choices;
	}

	if (choices == NULL) {
		return NULL;
	}

	if (choices == target) {
		free(target);
		return NULL;
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

void requireChoiceFlag(Choice* choice, char flag[FLAG_SIZE]) {
	strcpy(choice->requiredFlag, flag);
}

void setFlag(Choice* choice, char flag[FLAG_SIZE]) {
	strcpy(choice->flagToAdd, flag);
}
