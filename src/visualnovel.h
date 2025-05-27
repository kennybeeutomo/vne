#pragma once

#include "dialogue.h"
#include "choice.h"
#include "config.h"

typedef struct Scene {
	Dialogue* dialogues;
	Choice* choices;
} Scene;

typedef struct VisualNovel {
	Scene scenes[SCENES_MAX];
	Flag* flags;
} VisualNovel;

Dialogue* addDialogue(VisualNovel* vn, int sceneId, char speaker[SPEAKER_SIZE], char text[TEXT_SIZE]);
Choice* addChoice(VisualNovel* vn, int sceneId, char text[CHOICE_SIZE], int destId);
Scene choose(Scene scene, Flag** flags);
bool isEndingScene(Scene scene);
void freeScene(Scene* scene);
void startVisualNovel(VisualNovel* vn);
void freeVisualNovel(VisualNovel* vn);
void loadVisualNovel(VisualNovel* vn, const char* filename);
