#include "dialogue.h"
#include <stdlib.h>
#include <string.h>

Dialogue* initDialogue(char speaker[SPEAKER_SIZE], char text[TEXT_SIZE]) {
	Dialogue* dialogue = malloc(sizeof(Dialogue));
	strcpy(dialogue->text, text);
	strcpy(dialogue->speaker, speaker);
	strcpy(dialogue->requiredFlags, "");
	strcpy(dialogue->image, "");
	dialogue->next = NULL;
	dialogue->prev = NULL;
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
		if (evaluateFlags(flags, dialogue->requiredFlags)) {
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
	if (!evaluateFlags(flags, dialogues->requiredFlags)) {
		return nextDialogue(dialogues, flags);
	}
	return dialogues;
}

Dialogue* getLastDialogue(Dialogue* dialogues, Flag* flags) {
	Dialogue* curr = dialogues;
	Dialogue* last = curr;
	while (curr != NULL) {
		last = curr;
		curr = nextDialogue(curr, flags);
	}
	return last;
}

Dialogue* prependDialogue(Dialogue* dialogue, char speaker[SPEAKER_SIZE], char text[TEXT_SIZE]) {
	Dialogue* newDialogue = initDialogue(speaker, text);

	if (dialogue == NULL) {
		return newDialogue;
	}

	dialogue->prev = newDialogue;
	newDialogue->next = dialogue;
	return newDialogue;
}

Dialogue* appendDialogue(Dialogue* dialogue, char speaker[SPEAKER_SIZE], char text[TEXT_SIZE]) {
	Dialogue* newDialogue = initDialogue(speaker, text);

	if (dialogue == NULL) {
		return newDialogue;
	}

	Dialogue* curr = dialogue;
	while (curr->next != NULL) curr = curr->next;
	newDialogue->prev = curr;
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

void requireDialogueFlag(Dialogue* dialogue, char flag[DEFAULT_STRING_SIZE]) {
	strcpy(dialogue->requiredFlags, flag);
}
