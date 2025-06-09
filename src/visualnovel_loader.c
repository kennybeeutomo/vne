#include "choice.h"
#include "config.h"
#include "dialogue.h"
#include "flag.h"
#include "visualnovel.h"
#include "utils.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char errmsg[DEFAULT_STRING_SIZE * 2];

void errorParse(FILE* file, const char* msg) {
	fprintf(stderr, "Load error: %s", msg);
	if (file != NULL) {
		long pos = ftell(file);
		rewind(file);
		int lines = 1;
		int cols = 1;
		while (ftell(file) < pos) {
			int c = fgetc(file);
			cols++;
			if (c == '\n' || c == '\r') {
				lines++;
				cols = 1;
			}
		}
		fprintf(stderr, " at line: %d, col: %d", lines, cols);
	}

	fprintf(stderr, "\n");
	exit(1);
}

void getInt(FILE* file, int* n) {
	if (fscanf(file, " %d", n) == 0) {
		errorParse(file, "Invalid int parsing");
	}
}

void getString(FILE* file, char* string, int n) {
	memset(string, 0, n);
	char c;
	int i = 0;

	do {
		c = fgetc(file);
	} while (isspace(c));

	if (c != '"') {
		errorParse(file, "Invalid string parsing");
	}

	while (1) {
		c = fgetc(file);
		if (c == '"') {
			break;
		}
		if (c == '\\') {
			c = fgetc(file);
			switch (c) {
				case 'n':
					c = '\n';
					break;
				case 'w':
				case 'b':
				case 'i':
				case 'c':
				case '\\':
					string[i++] = '\\';
					break;
			}
		}
		if (i >= n - 1) {
			sprintf(errmsg, "Parsed string is too long (%d max)", n);
			errorParse(file, errmsg);
		}
		string[i] = c;
		i++;
	}
}

void loadVisualNovel(VisualNovel* vn) {
	char script[PATH_MAX];
	strcpy(script, vn->path);
	strcat(script, "/script.vn");
	FILE* file = fopen(script, "r");

	if (file == NULL) {
		errorParse(file, "Invalid file name");
	}

	freeVisualNovel(vn);

	int sceneId = 0;
	Dialogue* dialogue;
	Choice* choice;
	enum {Dialogue, Choice} state;

	char command[16];
	while (fscanf(file, " %s", command) == 1) {
		if (eq(command, "#")) {
			fscanf(file, "%*[^\n\r]%*[\n\r]");
		} else

		if (eq(command, "scene")) {
			getInt(file, &sceneId);
		} else

		if (eq(command, "dialogue")) {
			char speaker[SPEAKER_SIZE];
			char text[TEXT_SIZE];
			getString(file, speaker, SPEAKER_SIZE);
			getString(file, text, TEXT_SIZE);
			dialogue = addDialogue(vn, sceneId, speaker, text);
			state = Dialogue;
		} else

		if (eq(command, "choice")) {
			char text[CHOICE_SIZE];
			int destId;
			getString(file, text, CHOICE_SIZE);
			getInt(file, &destId);
			choice = addChoice(vn, sceneId, text, destId);
			state = Choice;
		} else

		if (eq(command, "reuse")) {
			int sourceSceneId;
			getInt(file, &sourceSceneId);
			vn->scenes[sceneId].choices = copyChoices(vn->scenes[sourceSceneId].choices, vn->scenes[sceneId].choices);
		} else

		if (eq(command, "preset")) {
			char flag[FLAG_SIZE];
			getString(file, flag, FLAG_SIZE);
			if (!isFlag(flag)) {
				sprintf(errmsg, "Invalid flag parsing \"%s\"", flag);
				errorParse(file, errmsg);
			}
			vn->flags = appendFlag(vn->flags, flag);
		} else

		if (eq(command, "set")) {
			if (state != Choice) {
				errorParse(file, "Invalid usage of set");
			}
			char flag[FLAG_SIZE];
			getString(file, flag, FLAG_SIZE);
			if (!isFlag(flag)) {
				sprintf(errmsg, "Invalid flag parsing \"%s\"", flag);
				errorParse(file, errmsg);
			}
			setFlag(choice, flag);
		} else

		if (eq(command, "unset")) {
			if (state != Choice) {
				errorParse(file, "Invalid usage of unset");
			}
			char flag[FLAG_SIZE];
			getString(file, flag, FLAG_SIZE);
			if (!isFlag(flag)) {
				sprintf(errmsg, "Invalid flag parsing \"%s\"", flag);
				errorParse(file, errmsg);
			}
			unsetFlag(choice, flag);
		} else

		if (eq(command, "unsetall")) {
			if (state != Choice) {
				errorParse(file, "Invalid usage of unsetall");
			}
			char flag[FLAG_SIZE] = "*";
			unsetFlag(choice, flag);
		} else

		if (eq(command, "if")) {
			char condition[DEFAULT_STRING_SIZE];
			getString(file, condition, DEFAULT_STRING_SIZE);
			if (evaluateFlags(NULL, condition) == -1) {
				sprintf(errmsg, "Invalid condition syntax \"%s\"", condition);
				errorParse(file, errmsg);
			}
			if (state == Dialogue) {
				requireDialogueFlag(dialogue, condition);
			} else if (state == Choice) {
				requireChoiceFlag(choice, condition);
			} else {
				errorParse(file, "Invalid usage of if");
			}
		} else

		if (eq(command, "image")) {
			if (state != Dialogue) {
				errorParse(file, "Invalid usage of image");
			}
			char image[IMAGE_SIZE];
			getString(file, image, IMAGE_SIZE);
			addImage(vn, dialogue, image);
		} else

		if (eq(command, "option")) {
			char option[DEFAULT_STRING_SIZE];
			getString(file, option, DEFAULT_STRING_SIZE);
			if (eq(option, "curses")) {
				vn->cursesMode = true;
			} else if (eq(option, "nocurses")) {
				vn->cursesMode = false;
			} else if (eq(option, "cps")) {
				getInt(file, &vn->cps);
			} else if (eq(option, "dialogueheight")) {
				getInt(file, &vn->dialogueWindowHeight);
			} else if (eq(option, "autoplay")) {
				vn->autoplay = true;
			} else {
				sprintf(errmsg, "Invalid option \"%s\"", option);
				errorParse(file, errmsg);
			}
		} else

		{
			sprintf(errmsg, "Invalid Command \"%s\"", command);
			errorParse(file, errmsg);
		}
	}

	fclose(file);
}
