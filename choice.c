#include "choice.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Choice* initChoice(char text[CHOICE_SIZE], Scene* scene) {
	Choice* choice = malloc(sizeof(Choice));
	strcpy(choice->text, text);
	choice->next = NULL;
	choice->scene = scene;
	return choice;
}

void printChoice(Choice* choice) {
	if (choice == NULL) {
		printf("END\n");
		return;
	}
	printf("%s\n", choice->text);
	printChoice(choice->next);
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

Choice* freeChoices(Choice* choice) {
	if (choice == NULL) {
		return NULL;
	}

	freeChoices(choice->next);
	free(choice);

	return NULL;
}
