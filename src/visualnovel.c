#include "visualnovel.h"
#include "choice.h"
#include "config.h"
#include "dialogue.h"
#include "flag.h"
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
		.path = DEFAULT_SCRIPT_PATH,
		.cursesMode = CURSES_MODE,
		.cps = DEFAULT_CPS,
		.dialogueWindowHeight = DEFAULT_DIALOGUE_WINDOW_HEIGHT,
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

void printDialogues(VisualNovel* vn) {
	Dialogue* head = vn->currentScene->dialogues;
	Dialogue* curr = head;
	while (curr != NULL) {
		if (evaluateFlags(vn->flags, curr->requiredFlags)) {
			if (curr != head) {
				getchar();
			}
			printImage(curr->image);
			if (curr->speaker[0] != '\0') {
				printf("%s: ", curr->speaker);
			}
			printf("%s\n", curr->text);
		}
		curr = curr->next;
	}
}

void printChoices(VisualNovel* vn) {
	int i = 1;
	Choice* curr = vn->currentScene->choices;
	while (curr != NULL) {
		if (evaluateFlags(vn->flags, curr->requiredFlags)) {
			printf("%d. %s\n", i, curr->text);
			i++;
		}
		curr = curr->next;
	}
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

void choiceMenu(VisualNovel* vn) {
	int choice;
	do {
		printChoices(vn);
		scanf("%d", &choice); getchar();
		vn->currentChoice = choiceAt(vn->currentScene->choices, vn->flags, choice);
	} while (choose(vn) == NULL);
}

bool isEndingScene(Scene scene) {
	return scene.choices == NULL;
}

void freeScene(Scene* scene) {
	scene->dialogues = freeDialogues(scene->dialogues);
	scene->choices = freeChoices(scene->choices);
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
}
