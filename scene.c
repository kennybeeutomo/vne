#include "scene.h"
#include "choice.h"
#include "dialogue.h"
#include <stdio.h>
#include <stdlib.h>

void addDialogue(VisualNovel* vn, int sceneId, char speaker[SPEAKER_SIZE], char text[TEXT_SIZE]) {
	vn->scenes[sceneId].dialogues = appendDialogue(vn->scenes[sceneId].dialogues, speaker, text);
}

void addChoice(VisualNovel* vn, int sceneId, char text[CHOICE_SIZE], int destId) {
	vn->scenes[sceneId].choices = appendChoice(vn->scenes[sceneId].choices, text, &vn->scenes[destId]);
}

Scene showChoices(Scene scene) {
	Choice* curr = scene.choices;

	for (int i = 1; curr != NULL; ++i) {
		printf("%d. %s\n", i, curr->text);
		curr = curr->next;
	}

	int choice;
	scanf("%d", &choice); getchar();

	curr = scene.choices;
	for (int i = 1; curr != NULL; ++i) {
		if (i == choice) {
			break;
		}
		curr = curr->next;
	}

	if (curr == NULL) {
		return showChoices(scene);
	}

	return *curr->scene;
}

bool endOfScene(Scene scene) {
	return scene.choices == NULL;
}

void freeScene(Scene* scene) {
	scene->dialogues = freeDialogues(scene->dialogues);
	scene->choices = freeChoices(scene->choices);
}

void freeVisualNovel(VisualNovel* vn) {
	for (int i = 0; i < CAPACITY; ++i) {
		freeScene(&vn->scenes[i]);
	}
}
