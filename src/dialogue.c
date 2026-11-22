#include "dialogue.h"
#include "config.h"
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

Dialogue* initDialogue(wchar_t speaker[SPEAKER_SIZE], wchar_t text[TEXT_SIZE]) {
	Dialogue* dialogue = malloc(sizeof(Dialogue));
	wcscpy(dialogue->text, text);
	wcscpy(dialogue->speaker, speaker);
	memset(dialogue->requiredFlags, 0, sizeof(dialogue->requiredFlags));
	memset(dialogue->images, 0, sizeof(dialogue->images));
	dialogue->next = NULL;
	dialogue->prev = NULL;
	return dialogue;
}

Dialogue* tailDialogue(Dialogue* dialogue) {
	if (dialogue == NULL) {
		return NULL;
	}
	while (dialogue->next != NULL)
		dialogue = dialogue->next;
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

Dialogue* prependDialogue(Dialogue* dialogue, wchar_t speaker[SPEAKER_SIZE], wchar_t text[TEXT_SIZE]) {
	Dialogue* newDialogue = initDialogue(speaker, text);

	if (dialogue == NULL) {
		return newDialogue;
	}

	dialogue->prev = newDialogue;
	newDialogue->next = dialogue;
	return newDialogue;
}

Dialogue* appendDialogue(Dialogue* dialogue, wchar_t speaker[SPEAKER_SIZE], wchar_t text[TEXT_SIZE]) {
	Dialogue* newDialogue = initDialogue(speaker, text);

	if (dialogue == NULL) {
		return newDialogue;
	}

	Dialogue* curr = dialogue;
	while (curr->next != NULL)
		curr = curr->next;
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

void requireDialogueFlag(Dialogue* dialogue, wchar_t flag[DEFAULT_STRING_SIZE]) {
	wcscpy(dialogue->requiredFlags, flag);
}
