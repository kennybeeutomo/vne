#pragma once

#include "config.h"
#include "flag.h"

typedef struct Dialogue Dialogue;
typedef struct Dialogue {
	char speaker[SPEAKER_SIZE];
	char text[TEXT_SIZE];
	char requiredFlags[DEFAULT_STRING_SIZE];
	char image[IMAGE_SIZE];
	Dialogue* next;
	Dialogue* prev;
} Dialogue;

Dialogue* initDialogue(char speaker[SPEAKER_SIZE], char text[TEXT_SIZE]);

Dialogue* tailDialogue(Dialogue* dialogue);
Dialogue* nextDialogue(Dialogue* dialogue, Flag* flags);
Dialogue* getFirstDialogue(Dialogue* dialogues, Flag* flags);
Dialogue* getLastDialogue(Dialogue* dialogues, Flag* flags);

Dialogue* prependDialogue(Dialogue* dialogue, char speaker[SPEAKER_SIZE], char text[TEXT_SIZE]);
Dialogue* appendDialogue(Dialogue* dialogue, char speaker[SPEAKER_SIZE], char text[TEXT_SIZE]);
Dialogue* freeDialogues(Dialogue* dialogue);

void requireDialogueFlag(Dialogue* dialogue, char flag[DEFAULT_STRING_SIZE]);
