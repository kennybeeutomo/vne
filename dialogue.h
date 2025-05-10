#pragma once

#define TEXT_SIZE 1000
#define SPEAKER_SIZE 20

typedef struct Dialogue Dialogue;
typedef struct Dialogue {
	char speaker[SPEAKER_SIZE];
	char text[TEXT_SIZE];
	Dialogue* next;
} Dialogue;

Dialogue* initDialogue(char speaker[SPEAKER_SIZE], char text[TEXT_SIZE]);
void printDialogue(Dialogue* dialogue);
Dialogue* appendDialogue(Dialogue* dialogue, char speaker[SPEAKER_SIZE], char text[TEXT_SIZE]);
Dialogue* freeDialogues(Dialogue* dialogue);
