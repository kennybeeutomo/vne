#include "visualnovel.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void error(FILE* file, const char* msg) {
	long pos = ftell(file);
	rewind(file);
	int lines = 1;
	int cols = 0;
	while (ftell(file) < pos) {
		int c = fgetc(file);
		cols++;
		if (c == '\n' || c == '\r') {
			lines++;
			cols = 0;
		}
	}
	fprintf(stderr, "Load error: %s at line: %d, col: %d\n", msg, lines, cols);
	exit(1);
}

void getInt(FILE* file, int* n) {
	if (fscanf(file, " %d", n) == 0) {
		error(file, "Invalid Int parsing");
		exit(1);
	}
}

void getString(FILE* file, char* string) {
	if (fscanf(file, " \"%[^\"]\"", string) == 0) {
		error(file, "Invalid String parsing");
		exit(1);
	}
}

void loadVisualNovel(VisualNovel* vn, const char* filename) {
	FILE* file = fopen(filename, "r");

	if (file == NULL) {
		error(file, "Invalid file name");
		exit(1);
	}

	int sceneId = 0;
	Dialogue* dialogue;
	Choice* choice;
	int state = 0;

	char command[16];
	while (fscanf(file, " %s", command) == 1) {
		if (strcmp(command, "scene") == 0) {
			getInt(file, &sceneId);
		} else

		if (strcmp(command, "dialogue") == 0) {
			char speaker[SPEAKER_SIZE];
			char text[TEXT_SIZE];
			getString(file, speaker);
			getString(file, text);
			dialogue = addDialogue(vn, sceneId, speaker, text);
			state = 1;
		} else

		if (strcmp(command, "choice") == 0) {
			char text[CHOICE_SIZE];
			int destId;
			getString(file, text);
			getInt(file, &destId);
			choice = addChoice(vn, sceneId, text, destId);
			state = 2;
		} else

		if (strcmp(command, "set") == 0) {
			char flag[FLAG_SIZE];
			getString(file, flag);
			setFlag(choice, flag);
		} else

		if (strcmp(command, "require") == 0) {
			char flag[FLAG_SIZE];
			getString(file, flag);
			if (state == 1) {
				requireDialogueFlag(dialogue, flag);
			} else if (state == 2) {
				requireChoiceFlag(choice, flag);
			} else {
				error(file, "Invalid usage of require");
				exit(1);
			}
		} else {
			error(file, "Invalid Command");
			exit(1);
		}
	}

	fclose(file);
}
