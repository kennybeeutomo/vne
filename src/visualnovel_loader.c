#include "choice.h"
#include "dialogue.h"
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
		}
		if (i >= n - 1) {
			error(file, "Parsed string is too long");
		}
		string[i] = c;
		i++;
	}
}

void loadVisualNovel(VisualNovel* vn, const char* filename) {
	FILE* file = fopen(filename, "r");

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
		} else {
			error(file, "Invalid Command");
		}
	}

	fclose(file);
}
