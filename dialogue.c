#include "dialogue.h"
#include "stdlib.h"
#include <stdio.h>
#include <string.h>

Dialogue* initDialogue(char speaker[SPEAKER_SIZE], char text[TEXT_SIZE]) {
	Dialogue* dialogue = malloc(sizeof(Dialogue));
	strcpy(dialogue->text, text);
	strcpy(dialogue->speaker, speaker);
	dialogue->next = NULL;
	return dialogue;
}

void printDialogue(Dialogue* dialogue) {
	if (dialogue == NULL) {
		printf("\n");
		return;
	}
	if (dialogue->speaker[0] != '\0') {
		printf("%s: ", dialogue->speaker);
	}
	printf("%s\n", dialogue->text);
	getchar();
	printDialogue(dialogue->next);
}

Dialogue* appendDialogue(Dialogue* dialogue, char speaker[SPEAKER_SIZE], char text[TEXT_SIZE]) {
	Dialogue* newDialogue = initDialogue(speaker, text);

	if (dialogue == NULL) {
		return newDialogue;
	}

	Dialogue* curr = dialogue;
	while (curr->next != NULL) curr = curr->next;
	curr->next = newDialogue;

	return dialogue;
}

Dialogue* freeDialogues(Dialogue* dialogue) {
	if (dialogue == NULL) {
		return NULL;
	}

	freeDialogues(dialogue->next);
	free(dialogue);

	return NULL;
}
