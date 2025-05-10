#pragma once

#include "dialogue.h"
#include "choice.h"

#define CAPACITY 1000

typedef struct Scene {
	Dialogue* dialogues;
	Choice* choices;
} Scene;

typedef struct VisualNovel {
	Scene scenes[CAPACITY];
} VisualNovel;

void addDialogue(VisualNovel* vn, int sceneId, char speaker[SPEAKER_SIZE], char text[TEXT_SIZE]);
void addChoice(VisualNovel* vn, int sceneId, char text[CHOICE_SIZE], int destId);
Scene showChoices(Scene scene);
bool endOfScene(Scene scene);
void freeScene(Scene* scene);
void freeVisualNovel(VisualNovel* vn);
