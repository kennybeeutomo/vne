#pragma once

#include "choice.h"
#include "config.h"
#include "dialogue.h"
#include "image.h"

#include <curses.h>
#include <wchar.h>

typedef enum { Next, Prev, Accept, Auto, History, Exit, Save, Resize, NoInput, Invalid } Input;

#define isInvalid(input) ((input) == Invalid || (input) == NoInput || (input) == History || (input) == Save)

typedef struct Scene {
	Dialogue* dialogues;
	Choice* choices;
	bool isEnd;
} Scene;

typedef struct VisualNovel {
	Scene scenes[SCENES_MAX];
	Flag* flags;

	Scene* currentScene;
	Dialogue* currentDialogue;
	Choice* currentChoice;
	Image images[IMAGE_CAPACITY];
	Dialogue* history;

	char path[PATH_MAX];
	bool cursesMode;
	int cps;
	int dialogueWindowHeight;
	chtype transparentCharacter;
	bool autoplay;
} VisualNovel;

// visualnovel.c
VisualNovel initVN();
void endVN(VisualNovel* vn);

Dialogue* addDialogue(VisualNovel* vn, int sceneId, wchar_t speaker[SPEAKER_SIZE], wchar_t text[TEXT_SIZE]);
Choice* addChoice(VisualNovel* vn, int sceneId, wchar_t text[CHOICE_SIZE], int destId);
void addImage(Dialogue* dialogue, Image image);

void addDialogueToHistory(VisualNovel* vn);
void addChoiceToHistory(VisualNovel* vn);

void removeSequences(wchar_t* str);
void getImagePath(char imagePath[PATH_MAX], VisualNovel* vn, Image image);
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
int printStr(WINDOW* win, const wchar_t* str, int y, int x, int width);
WINDOW* printTempWindow(const wchar_t* title, const wchar_t* text, int width, int height);
Input getInput(WINDOW* win);
Input getInputVN(WINDOW* win, VisualNovel* vn);
int getChoiceHeight(VisualNovel* vn);
int getDialogueHeight(VisualNovel* vn, Dialogue* dialogue);
void getHistoryText(Dialogue* history, wchar_t* text, int width, int height);

// visualnovel_curses.c
void printHelp();
void printHistory(VisualNovel* vn);
void printImageCurses(VisualNovel* vn, Image image);
void printDialogueCurses(VisualNovel* vn, bool instant, bool saveToHistory);
void printDialoguesCurses(VisualNovel* vn);
void printChoicesCurses(VisualNovel* vn);
void chooseMenuCurses(VisualNovel* vn);
void startVisualNovelCurses(VisualNovel* vn);
void endVNCurses(VisualNovel* vn);
