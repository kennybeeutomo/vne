#include "visualnovel.h"
#include "choice.h"
#include "config.h"
#include "dialogue.h"
#include "flag.h"
#include "image.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

VisualNovel initVN() {
	VisualNovel vn = {.scenes = {},
	                  .flags = NULL,
	                  .currentScene = NULL,
	                  .currentDialogue = NULL,
	                  .currentChoice = NULL,
	                  .images = {},
	                  .history = NULL,
	                  .path = DEFAULT_SCRIPT_PATH,
	                  .cursesMode = CURSES_MODE,
	                  .cps = DEFAULT_CPS,
	                  .dialogueWindowHeight = DEFAULT_DIALOGUE_WINDOW_HEIGHT,
	                  .autoplay = false,
	                  .transparentCharacter = DEFAULT_TRANSPARENT_CHARACTER};
	return vn;
}

void endVN(VisualNovel* vn) {
	freeVisualNovel(vn);
	exit(0);
}

Dialogue* addDialogue(VisualNovel* vn, int sceneId, wchar_t speaker[SPEAKER_SIZE], wchar_t text[TEXT_SIZE]) {
	Dialogue* dialogue = appendDialogue(vn->scenes[sceneId].dialogues, speaker, text);
	vn->scenes[sceneId].dialogues = dialogue;
	return tailDialogue(dialogue);
}

Choice* addChoice(VisualNovel* vn, int sceneId, wchar_t text[CHOICE_SIZE], int destId) {
	Choice* choice = appendChoice(vn->scenes[sceneId].choices, text, &vn->scenes[destId]);
	vn->scenes[sceneId].choices = choice;
	return tailChoice(choice);
}

void addImage(Dialogue* dialogue, Image image) {
	memcpy(&dialogue->images[image.zOrder], &image, sizeof(Image));
}

void addDialogueToHistory(VisualNovel* vn) {
	if (vn->currentDialogue == NULL) {
		return;
	}
	wchar_t text[TEXT_SIZE];
	wcscpy(text, vn->currentDialogue->text);
	removeSequences(text);
	vn->history = prependDialogue(vn->history, vn->currentDialogue->speaker, text);
}

void addChoiceToHistory(VisualNovel* vn) {
	if (vn->currentChoice == NULL) {
		return;
	}
	wchar_t speaker[SPEAKER_SIZE] = L"You chose";
	wchar_t text[TEXT_SIZE];
	wcscpy(text, vn->currentChoice->text);
	vn->history = prependDialogue(vn->history, speaker, text);
}

void removeSequences(wchar_t* str) {
	wchar_t temp[TEXT_SIZE];
	memset(temp, 0, sizeof(temp));
	int j = 0;
	for (int i = 0; str[i] != '\0'; ++i) {
		if (str[i] == '\\') {
			switch (str[++i]) {
				case 'w':
				case 'c':
					i = skipNumbers(++i, str);
					i--;
					continue;
				case 'b':
				case 'i':
					continue;
			}
		}
		temp[j++] = str[i];
	}
	wcscpy(str, temp);
}

bool isEndingScene(VisualNovel* vn, Scene* scene) {
	return scene == &vn->scenes[SCENES_MAX - 1];
}

bool isEmptyScene(VisualNovel* vn, Scene* scene) {
	if (scene == NULL) {
		return true;
	}
	Dialogue* dialogue = getFirstDialogue(scene->dialogues, vn->flags);
	Choice* choice = getFirstChoice(scene->choices, vn->flags);
	return dialogue == NULL && choice == NULL;
}

void freeScene(Scene* scene) {
	scene->dialogues = freeDialogues(scene->dialogues);
	scene->choices = freeChoices(scene->choices);
}

void setScene(VisualNovel* vn, Scene* scene) {
	vn->currentScene = scene;
	if (scene == NULL) {
		return;
	}
	vn->currentDialogue = getFirstDialogue(scene->dialogues, vn->flags);
	vn->currentChoice = getFirstChoice(scene->choices, vn->flags);
}

void choose(VisualNovel* vn) {

	Scene* scene = NULL;

	if (vn->currentChoice != NULL) {
		vn->flags = appendFlags(vn->flags, vn->currentChoice->flagsToSet);
		vn->flags = deleteFlags(vn->flags, vn->currentChoice->flagsToUnset);
		scene = vn->currentChoice->scene;
	}

	if (scene == NULL) {
		for (scene = vn->currentScene + 1; !isEndingScene(vn, scene); ++scene) {
			if (!isEmptyScene(vn, scene)) {
				break;
			}
		}
	}

	if (isEndingScene(vn, scene)) {
		scene = NULL;
	}

	setScene(vn, scene);
}

void getImagePath(char imagePath[PATH_MAX], VisualNovel* vn, Image image) {
	strcpy(imagePath, vn->path);
	strcat(imagePath, "/images/");
	strcat(imagePath, image.imagePath);
}

void printImage(VisualNovel* vn, Image image) {
	char imagePath[PATH_MAX];
	getImagePath(imagePath, vn, image);

	FILE* file = fopen(imagePath, "r");
	if (file == NULL) {
		return;
	}
	wchar_t text[DEFAULT_STRING_SIZE];
	while (fgetws(text, DEFAULT_STRING_SIZE, file) != NULL) {
		printf("%ls", text);
	}
	fclose(file);
}

void printDialogue(VisualNovel* vn) {
	Dialogue* dialogue = vn->currentDialogue;

	if (dialogue == NULL) {
		return;
	}

	for (int i = 0; i < IMAGE_CAPACITY; ++i) {
		printImage(vn, vn->currentDialogue->images[i]);
	}

	if (notnullstr(vn->currentDialogue->speaker)) {
		printf("%ls: ", vn->currentDialogue->speaker);
	}

	removeSequences(dialogue->text);
	printf("%ls\n", dialogue->text);
}

void printDialogues(VisualNovel* vn) {
	Dialogue* head = vn->currentDialogue;
	Dialogue* last = getLastDialogue(head, vn->flags);
	while (1) {
		printDialogue(vn);
		if (vn->currentDialogue == last) {
			break;
		}
		getchar();
		vn->currentDialogue = nextDialogue(vn->currentDialogue, vn->flags);
	}
}

void printChoices(VisualNovel* vn) {
	int i = 1;
	Choice* curr = getFirstChoice(vn->currentScene->choices, vn->flags);
	while (curr != NULL) {
		printf("%d. %ls\n", i++, curr->text);
		curr = nextChoice(curr, vn->flags);
	}
}

void choiceMenu(VisualNovel* vn) {
	int choice;

	if (vn->currentChoice != NULL) {
		do {
			printChoices(vn);
			scanf("%d", &choice);
			getchar();
			vn->currentChoice = choiceAt(vn->currentScene->choices, vn->flags, choice);
		} while (vn->currentChoice == NULL);
	} else {
		getchar();
	}

	choose(vn);
}

void startVisualNovel(VisualNovel* vn) {
	if (vn->cursesMode) {
		startVisualNovelCurses(vn);
		return;
	}

	setScene(vn, &vn->scenes[0]);
	while (vn->currentScene != NULL) {
		printDialogues(vn);
		if (vn->currentScene->isEnd) {
			break;
		}
		choiceMenu(vn);
	}

	endVN(vn);
}

void freeVisualNovel(VisualNovel* vn) {
	for (int i = 0; i < SCENES_MAX; ++i) {
		freeScene(&vn->scenes[i]);
	}
	vn->flags = freeFlags(vn->flags);
	vn->history = freeDialogues(vn->history);
}
