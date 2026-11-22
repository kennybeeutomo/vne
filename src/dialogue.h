#pragma once

#include "config.h"
#include "flag.h"
#include "image.h"
#include <wchar.h>

typedef struct Dialogue Dialogue;
typedef struct Dialogue {
	wchar_t speaker[SPEAKER_SIZE];
	wchar_t text[TEXT_SIZE];
	wchar_t requiredFlags[DEFAULT_STRING_SIZE];
	Image images[IMAGE_CAPACITY];
	Dialogue* next;
	Dialogue* prev;
} Dialogue;

Dialogue* initDialogue(wchar_t speaker[SPEAKER_SIZE], wchar_t text[TEXT_SIZE]);

Dialogue* tailDialogue(Dialogue* dialogue);
Dialogue* nextDialogue(Dialogue* dialogue, Flag* flags);
Dialogue* getFirstDialogue(Dialogue* dialogues, Flag* flags);
Dialogue* getLastDialogue(Dialogue* dialogues, Flag* flags);

Dialogue* prependDialogue(Dialogue* dialogue, wchar_t speaker[SPEAKER_SIZE], wchar_t text[TEXT_SIZE]);
Dialogue* appendDialogue(Dialogue* dialogue, wchar_t speaker[SPEAKER_SIZE], wchar_t text[TEXT_SIZE]);
Dialogue* freeDialogues(Dialogue* dialogue);

void requireDialogueFlag(Dialogue* dialogue, wchar_t flag[DEFAULT_STRING_SIZE]);
