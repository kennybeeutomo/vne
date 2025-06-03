#pragma once

#include "dialogue.h"
#include "choice.h"
#include "config.h"

#include <curses.h>

typedef struct Scene {
	Dialogue* dialogues;
	Choice* choices;
} Scene;

typedef struct VisualNovel {
	Scene scenes[SCENES_MAX];
	Flag* flags;
	Scene* currentScene;
	Dialogue* currentDialogue;
	Choice* currentChoice;
	char currentImage[IMAGE_SIZE];

	char path[PATH_MAX];
	bool cursesMode;
	int cps;
	int dialogueWindowHeight;
} VisualNovel;

VisualNovel initVN();
void endVN(VisualNovel* vn);

Dialogue* addDialogue(VisualNovel* vn, int sceneId, char speaker[SPEAKER_SIZE], char text[TEXT_SIZE]);
Choice* addChoice(VisualNovel* vn, int sceneId, char text[CHOICE_SIZE], int destId);
void addImage(VisualNovel* vn, Dialogue* dialogue, char image[IMAGE_SIZE]);

void setScene(VisualNovel* vn, Scene* scene);
Choice* choose(VisualNovel* vn);

bool isEndingScene(Scene scene);

void freeScene(Scene* scene);

void startVisualNovel(VisualNovel* vn);
void freeVisualNovel(VisualNovel* vn);

void loadVisualNovel(VisualNovel* vn);

void startVisualNovelCurses(VisualNovel* vn);
void endVNCurses(VisualNovel* vn);
