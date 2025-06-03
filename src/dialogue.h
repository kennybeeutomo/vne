#pragma once

#include "config.h"
#include "flag.h"

typedef struct Dialogue Dialogue;
typedef struct Dialogue {
	char speaker[SPEAKER_SIZE];
	char text[TEXT_SIZE];
	char requiredFlag[FLAG_SIZE];
	char image[IMAGE_SIZE];
	Dialogue* next;
} Dialogue;

Dialogue* initDialogue(char speaker[SPEAKER_SIZE], char text[TEXT_SIZE]);

Dialogue* tailDialogue(Dialogue* dialogue);
Dialogue* nextDialogue(Dialogue* dialogue, Flag* flags);
Dialogue* getFirstDialogue(Dialogue* dialogues, Flag* flags);

Dialogue* appendDialogue(Dialogue* dialogue, char speaker[SPEAKER_SIZE], char text[TEXT_SIZE]);
Dialogue* freeDialogues(Dialogue* dialogue);

void requireDialogueFlag(Dialogue* dialogue, char flag[FLAG_SIZE]);
