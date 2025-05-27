#pragma once

#include "flag.h"
#include "config.h"

typedef struct Dialogue Dialogue;
typedef struct Dialogue {
	char speaker[SPEAKER_SIZE];
	char text[TEXT_SIZE];
	char requiredFlag[FLAG_SIZE];
	Dialogue* next;
} Dialogue;

Dialogue* initDialogue(char speaker[SPEAKER_SIZE], char text[TEXT_SIZE]);
void printDialogue(Dialogue* dialogue, Flag* flags);
Dialogue* tailDialogue(Dialogue* dialogue);
Dialogue* appendDialogue(Dialogue* dialogue, char speaker[SPEAKER_SIZE], char text[TEXT_SIZE]);
Dialogue* freeDialogues(Dialogue* dialogue);
void requireDialogueFlag(Dialogue* dialogue, char flag[FLAG_SIZE]);
