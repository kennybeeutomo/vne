#include "visualnovel.h"
#include "choice.h"
#include "config.h"
#include "dialogue.h"
#include "flag.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

VisualNovel initVN() {
	VisualNovel vn = {
		.scenes = {},
		.flags = NULL,
		.currentScene = NULL,
		.currentDialogue = NULL,
		.currentChoice = NULL,
		.currentImage = {},
		.history = NULL,
		.path = DEFAULT_SCRIPT_PATH,
		.cursesMode = CURSES_MODE,
		.cps = DEFAULT_CPS,
		.dialogueWindowHeight = DEFAULT_DIALOGUE_WINDOW_HEIGHT,
		.autoplay = false,
	};
	return vn;
}

void endVN(VisualNovel* vn) {
	freeVisualNovel(vn);
	exit(0);
}

Dialogue* addDialogue(VisualNovel* vn, int sceneId, char speaker[SPEAKER_SIZE], char text[TEXT_SIZE]) {
	Dialogue* dialogue = appendDialogue(vn->scenes[sceneId].dialogues, speaker, text);
	vn->scenes[sceneId].dialogues = dialogue;
	return tailDialogue(dialogue);
}

Choice* addChoice(VisualNovel* vn, int sceneId, char text[CHOICE_SIZE], int destId) {
	Choice* choice = appendChoice(vn->scenes[sceneId].choices, text, &vn->scenes[destId]);
	vn->scenes[sceneId].choices = choice;
	return tailChoice(choice);
}

void addImage(VisualNovel* vn, Dialogue* dialogue, char image[IMAGE_SIZE]) {
	strcpy(dialogue->image, vn->path);
	strcat(dialogue->image, "/images/");
	strcat(dialogue->image, image);
}

void addDialogueToHistory(VisualNovel* vn) {
	char text[TEXT_SIZE];
	strcpy(text, vn->currentDialogue->text);
	removeSequences(text);
	vn->history = prependDialogue(vn->history, vn->currentDialogue->speaker, text);
}

void addChoiceToHistory(VisualNovel* vn) {
	char speaker[SPEAKER_SIZE] = "You chose";
	char text[TEXT_SIZE]; strcpy(text, vn->currentChoice->text);
	vn->history = prependDialogue(vn->history, speaker, text);
}

void removeSequences(char* str) {
	char temp[TEXT_SIZE];
	memset(temp, 0, TEXT_SIZE);
	int j = 0;
	for (int i = 0; str[i] != '\0'; ++i) {
		if (str[i] == '\\') {
			switch (str[++i]) {
				case 'w': case 'c':
					i = skipNumbers(++i, str);
					i--;
					continue;
				case 'b': case 'i':
					continue;
			}
		}
		temp[j++] = str[i];
	}
	strcpy(str, temp);
}

bool isEndingScene(Scene scene) {
	return scene.choices == NULL;
}

void freeScene(Scene* scene) {
	scene->dialogues = freeDialogues(scene->dialogues);
	scene->choices = freeChoices(scene->choices);
}

void setScene(VisualNovel* vn, Scene* scene) {
	vn->currentScene = scene;
	vn->currentDialogue = getFirstDialogue(scene->dialogues, vn->flags);
	vn->currentChoice = getFirstChoice(scene->choices, vn->flags);
}

Choice* choose(VisualNovel* vn) {
	Choice* curr = vn->currentScene->choices;

	while (curr != NULL) {
		if (curr == vn->currentChoice) {
			break;
		}
		curr = curr->next;
	}

	if (curr != NULL) {
		vn->flags = appendFlags(vn->flags, curr->flagsToSet);
		vn->flags = deleteFlags(vn->flags, curr->flagsToUnset);
		setScene(vn, curr->scene);
	}

	return curr;
}

void printImage(char image[IMAGE_SIZE]) {
	FILE* file = fopen(image, "r");
	if (file == NULL) {
		return;
	}
	char text[DEFAULT_STRING_SIZE];
	while (fgets(text, DEFAULT_STRING_SIZE, file) != NULL) {
		printf("%s", text);
	}
	fclose(file);
}

void printDialogue(VisualNovel* vn) {
	Dialogue* dialogue = vn->currentDialogue;
	printImage(vn->currentDialogue->image);

	if (vn->currentDialogue->speaker[0] != '\0') {
		printf("%s: ", vn->currentDialogue->speaker);
	}

	removeSequences(dialogue->text);
	printf("%s\n", dialogue->text);
}

void printDialogues(VisualNovel* vn) {
	Dialogue* head = vn->currentDialogue;
	Dialogue* last = getLastDialogue(head, vn->flags);
	while (1) {
		printDialogue(vn);
		if (vn->currentDialogue == last) { break; }
		getchar();
		vn->currentDialogue = nextDialogue(vn->currentDialogue, vn->flags);
	}
}

void printChoices(VisualNovel* vn) {
	int i = 1;
	Choice* curr = getFirstChoice(vn->currentScene->choices, vn->flags);
	while (curr != NULL) {
		printf("%d. %s\n", i++, curr->text);
		curr = nextChoice(curr, vn->flags);
	}
}

void choiceMenu(VisualNovel* vn) {
	int choice;
	do {
		printChoices(vn);
		scanf("%d", &choice); getchar();
		vn->currentChoice = choiceAt(vn->currentScene->choices, vn->flags, choice);
	} while (choose(vn) == NULL);
}

void startVisualNovel(VisualNovel* vn) {
	if (vn->cursesMode) {
		startVisualNovelCurses(vn);
		return;
	}

	setScene(vn, &vn->scenes[0]);
	while (1) {
		printDialogues(vn);
		if (isEndingScene(*vn->currentScene)) {
			break;
		}
		choiceMenu(vn);
	}

	getchar();
	endVN(vn);
}

void freeVisualNovel(VisualNovel* vn) {
	for (int i = 0; i < SCENES_MAX; ++i) {
		freeScene(&vn->scenes[i]);
	}
	vn->flags = freeFlags(vn->flags);
	vn->history = freeDialogues(vn->history);
}
