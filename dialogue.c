#include "dialogue.h"
#include "flag.h"
#include "stdlib.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

Dialogue* initDialogue(char speaker[SPEAKER_SIZE], char text[TEXT_SIZE]) {
	Dialogue* dialogue = malloc(sizeof(Dialogue));
	strcpy(dialogue->text, text);
	strcpy(dialogue->speaker, speaker);
	strcpy(dialogue->requiredFlag, "");
	dialogue->next = NULL;
	return dialogue;
}

void printDialogue(Dialogue* dialogue, Flag* flags) {
	Dialogue* head = dialogue;
	while (dialogue != NULL) {
		if (findFlag(flags, dialogue->requiredFlag)) {
			if (dialogue != head) {
				getchar();
			}
			if (dialogue->speaker[0] != '-') {
				printf("%s: ", dialogue->speaker);
			}
			printf("%s\n", dialogue->text);
		}
		dialogue = dialogue->next;
	}
}

Dialogue* tailDialogue(Dialogue* dialogue) {
	if (dialogue == NULL) {
		return NULL;
	}
	while (dialogue->next != NULL) dialogue = dialogue->next;
	return dialogue;
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

void requireDialogueFlag(Dialogue* dialogue, char flag[FLAG_SIZE]) {
	strcpy(dialogue->requiredFlag, flag);
}
