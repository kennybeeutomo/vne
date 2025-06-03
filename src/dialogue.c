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
	strcpy(dialogue->image, "");
	dialogue->next = NULL;
	return dialogue;
}

Dialogue* tailDialogue(Dialogue* dialogue) {
	if (dialogue == NULL) {
		return NULL;
	}
	while (dialogue->next != NULL) dialogue = dialogue->next;
	return dialogue;
}

Dialogue* nextDialogue(Dialogue* dialogue, Flag* flags) {
	if (dialogue == NULL) {
		return dialogue;
	}

	dialogue = dialogue->next;
	while (dialogue != NULL) {
		if (findFlag(flags, dialogue->requiredFlag)) {
			break;
		}
		dialogue = dialogue->next;
	}

	return dialogue;
}

Dialogue* getFirstDialogue(Dialogue* dialogues, Flag* flags) {
	if (dialogues == NULL) {
		return NULL;
	}
	if (!findFlag(flags, dialogues->requiredFlag)) {
		return nextDialogue(dialogues, flags);
	}
	return dialogues;
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
