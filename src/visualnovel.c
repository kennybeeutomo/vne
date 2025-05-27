#include "visualnovel.h"
#include "choice.h"
#include "dialogue.h"
#include "flag.h"
#include <stdio.h>
#include <string.h>

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

Scene choose(Scene scene, Flag** flags) {
	printChoices(scene.choices, *flags);

	int choice;
	scanf("%d", &choice); getchar();

	Choice* curr = scene.choices;

	int i = 1;
	while (curr != NULL) {
		if (findFlag(*flags, curr->requiredFlag)) {
			if (choice == i) {
				break;
			}
			i++;
		}
		curr = curr->next;
	}

	if (curr == NULL) {
		return choose(scene, flags);
	}

	*flags = appendFlag(*flags, curr->flagToAdd);

	return *curr->scene;
}

bool isEndingScene(Scene scene) {
	return scene.choices == NULL;
}

void freeScene(Scene* scene) {
	scene->dialogues = freeDialogues(scene->dialogues);
	scene->choices = freeChoices(scene->choices);
}

void startVisualNovel(VisualNovel* vn) {
	Scene scene = vn->scenes[0];
	while (1) {
		printDialogue(scene.dialogues, vn->flags);
		if (isEndingScene(scene)) {
			break;
		}
		scene = choose(scene, &vn->flags);
	}
}

void freeVisualNovel(VisualNovel* vn) {
	for (int i = 0; i < SCENES_MAX; ++i) {
		freeScene(&vn->scenes[i]);
	}
	vn->flags = freeFlags(vn->flags);
}
