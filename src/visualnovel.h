#pragma once

#include "dialogue.h"
#include "choice.h"
#include "config.h"

#include <curses.h>

typedef enum {
	Next, Prev, Accept, Auto,
	History, Exit, Save, Resize,
	NoInput, Invalid
} Input;

#define isInvalid(input) (\
	(input) == Invalid ||\
	(input) == NoInput ||\
	(input) == History ||\
	(input) == Save\
)

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
	Dialogue* history;

	char path[PATH_MAX];
	bool cursesMode;
	int cps;
	int dialogueWindowHeight;
	bool autoplay;
} VisualNovel;

// visualnovel.c
VisualNovel initVN();
void endVN(VisualNovel* vn);

Dialogue* addDialogue(VisualNovel* vn, int sceneId, char speaker[SPEAKER_SIZE], char text[TEXT_SIZE]);
Choice* addChoice(VisualNovel* vn, int sceneId, char text[CHOICE_SIZE], int destId);
void addImage(Dialogue* dialogue, char image[IMAGE_SIZE]);

void addDialogueToHistory(VisualNovel* vn);
void addChoiceToHistory(VisualNovel* vn);

void removeSequences(char* str);
void getImagePath(char imagePath[PATH_MAX], VisualNovel* vn, char image[IMAGE_SIZE]);
bool isEndingScene(VisualNovel* vn, Scene* scene);
bool isEmptyScene(VisualNovel* vn, Scene* scene);

void setScene(VisualNovel* vn, Scene* scene);
void choose(VisualNovel* vn);
void freeScene(Scene* scene);
void startVisualNovel(VisualNovel* vn);
void freeVisualNovel(VisualNovel* vn);

// visualnovel_loader.c
void loadVisualNovel(VisualNovel* vn);

// visualnovel_curses_utils.c
void fill(int y, int x, int rows, int cols, chtype ch);
int printStr(WINDOW* win, const char* str, int y, int x, int width);
WINDOW* printTempWindow(const char* title, const char* text, int width, int height);
void editWindow(const char* title, char* text, int width, int cap);
Input getInput(WINDOW* win);
Input getInputVN(WINDOW* win, VisualNovel* vn);
int getChoiceHeight(VisualNovel* vn);
int getDialogueHeight(VisualNovel* vn, Dialogue* dialogue);
void getHistoryText(Dialogue* history, char* text, int width, int height);

// visualnovel_curses.c
void printHelp();
void printHistory(VisualNovel* vn);
void printImageCurses(VisualNovel* vn, char image[IMAGE_SIZE]);
void printDialogueCurses(VisualNovel* vn, bool instant, bool saveToHistory);
void printDialoguesCurses(VisualNovel* vn);
void printChoicesCurses(VisualNovel* vn);
void chooseMenuCurses(VisualNovel* vn);
void startVisualNovelCurses(VisualNovel* vn);
void endVNCurses(VisualNovel* vn);
