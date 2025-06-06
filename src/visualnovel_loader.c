#include "choice.h"
#include "config.h"
#include "dialogue.h"
#include "flag.h"
#include "visualnovel.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void error(FILE* file, const char* msg) {
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
		error(file, "Invalid int parsing");
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
		error(file, "Invalid string parsing");
	}

	while (1) {
		c = fgetc(file);
		if (c == '"') {
			break;
		}
		if (c == '\\') {
			c = fgetc(file);
			if (c == 'n') {
				c = '\n';
			}
		}
		if (i >= n - 1) {
			error(file, "Parsed string is too long");
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
		error(file, "Invalid file name");
	}

	freeVisualNovel(vn);

	int sceneId = 0;
	Dialogue* dialogue;
	Choice* choice;
	enum {Dialogue, Choice} state;

	char command[16];
	while (fscanf(file, " %s", command) == 1) {
		if (strcmp(command, "#") == 0) {
			fscanf(file, "%*[^\n\r]%*[\n\r]");
		} else

		if (strcmp(command, "scene") == 0) {
			getInt(file, &sceneId);
		} else

		if (strcmp(command, "dialogue") == 0) {
			char speaker[SPEAKER_SIZE];
			char text[TEXT_SIZE];
			getString(file, speaker, SPEAKER_SIZE);
			getString(file, text, TEXT_SIZE);
			dialogue = addDialogue(vn, sceneId, speaker, text);
			state = Dialogue;
		} else

		if (strcmp(command, "choice") == 0) {
			char text[CHOICE_SIZE];
			int destId;
			getString(file, text, CHOICE_SIZE);
			getInt(file, &destId);
			choice = addChoice(vn, sceneId, text, destId);
			state = Choice;
		} else

		if (strcmp(command, "set") == 0) {
			if (state != Choice) {
				error(file, "Invalid usage of set");
			}
			char flag[FLAG_SIZE];
			getString(file, flag, FLAG_SIZE);
			setFlag(choice, flag);
		} else

		if (strcmp(command, "unset") == 0) {
			if (state != Choice) {
				error(file, "Invalid usage of unset");
			}
			char flag[FLAG_SIZE];
			getString(file, flag, FLAG_SIZE);
			unsetFlag(choice, flag);
		} else

		if (strcmp(command, "unsetall") == 0) {
			if (state != Choice) {
				error(file, "Invalid usage of unsetall");
			}
			char flag[FLAG_SIZE] = "*";
			unsetFlag(choice, flag);
		} else

		if (strcmp(command, "require") == 0) {
			char flag[FLAG_SIZE];
			getString(file, flag, FLAG_SIZE);
			if (state == Dialogue) {
				requireDialogueFlag(dialogue, flag);
			} else if (state == Choice) {
				requireChoiceFlag(choice, flag);
			} else {
				error(file, "Invalid usage of require");
			}
		} else

		if (strcmp(command, "image") == 0) {
			if (state != Dialogue) {
				error(file, "Invalid usage of image");
			}
			char image[IMAGE_SIZE];
			getString(file, image, IMAGE_SIZE);
			addImage(vn, dialogue, image);
		} else

		if (strcmp(command, "option") == 0) {
			char option[DEFAULT_STRING_SIZE];
			getString(file, option, DEFAULT_STRING_SIZE);
			if (strcmp(option, "curses") == 0) {
				vn->cursesMode = true;
			} else if (strcmp(option, "nocurses") == 0) {
				vn->cursesMode = false;
			} else if (strcmp(option, "cps") == 0) {
				getInt(file, &vn->cps);
			} else if (strcmp(option, "dialogueheight") == 0) {
				getInt(file, &vn->dialogueWindowHeight);
			} else {
				error(file, "Invalid option");
			}
		} else

		{
			error(file, "Invalid Command");
		}
	}

	fclose(file);
}
