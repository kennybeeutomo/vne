#include "choice.h"
#include "flag.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

Choice* initChoice(char text[CHOICE_SIZE], Scene* scene) {
	Choice* choice = malloc(sizeof(Choice));
	strcpy(choice->text, text);
	strcpy(choice->requiredFlag, "");
	strcpy(choice->flagToAdd, "");
	choice->next = NULL;
	choice->scene = scene;
	return choice;
}

void printChoices(Choice* choice, Flag* flags) {
	int i = 1;
	while (choice != NULL) {
		if (findFlag(flags, choice->requiredFlag)) {
			printf("%d. %s\n", i, choice->text);
			i++;
		}
		choice = choice->next;
	}
}

Choice* tailChoice(Choice* choice) {
	if (choice == NULL) {
		return NULL;
	}
	while (choice->next != NULL) choice = choice->next;
	return choice;
}

Choice* appendChoice(Choice* choice, char text[CHOICE_SIZE], Scene* scene) {
	Choice* newChoice = initChoice(text, scene);

	if (choice == NULL) {
		return newChoice;
	}

	Choice* curr = choice;
	while (curr->next != NULL) curr = curr->next;
	curr->next = newChoice;

	return choice;
}

Choice* deleteChoice(Choice* choice, char text[CHOICE_SIZE]) {
	if (choice == NULL) {
		return NULL;
	}

	if (strcmp(choice->text, text) == 0) {
		free(choice);
		return NULL;
	}

	Choice* curr = choice->next;
	Choice* prev = choice;
	while (curr != NULL) {
		if (strcmp(curr->text, text) == 0) {
			prev->next = curr->next;
			free(curr);
			break;
		}
		prev = curr;
		curr = curr->next;
	}

	return choice;
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
