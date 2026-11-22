#include "choice.h"
#include "config.h"
#include "dialogue.h"
#include "flag.h"
#include "utils.h"
#include "visualnovel.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <wctype.h>

wchar_t errmsg[DEFAULT_STRING_SIZE * 2];

void errorParse(FILE* file, const wchar_t* msg) {
	fprintf(stderr, "Load error: %ls", msg);
	if (file != NULL) {
		long pos = ftell(file);
		rewind(file);
		int lines = 1;
		int cols = 1;
		while (ftell(file) < pos) {
			int c = fgetwc(file);
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
	if (fwscanf(file, L" %d", n) == 0) {
		errorParse(file, L"Invalid int parsing");
	}
}

void getIntRange(FILE* file, int* n, int min, int max) {
	if (fwscanf(file, L" %d", n) == 0) {
		errorParse(file, L"Invalid int parsing");
	}
	if (*n < min || *n >= max) {
		wchar_t errorMessage[DEFAULT_STRING_SIZE];
		swprintf(errorMessage, DEFAULT_STRING_SIZE, L"Int out of bounds (valid range: [%d, %d], got %d)", min, max, *n);
		errorParse(file, errorMessage);
	}
}

void getString(FILE* file, wchar_t* string, int n) {
	memset(string, 0, sizeof(wchar_t) * n);
	wchar_t c;
	int i = 0;

	do {
		c = fgetwc(file);
	} while (iswspace(c));

	if (c != '"') {
		errorParse(file, L"Invalid string parsing");
	}

	while (1) {
		c = fgetwc(file);
		if (c == '"') {
			break;
		}
		if (c == '\\') {
			c = fgetwc(file);
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
			swprintf(errmsg, DEFAULT_STRING_SIZE, L"Parsed string is too long (%d max, got %d)", n, i);
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
		errorParse(file, L"Invalid file name");
	}

	freeVisualNovel(vn);

	int sceneId = 0;
	Dialogue* dialogue;
	Choice* choice;
	enum { Dialogue, Choice } state;

	wchar_t command[16];
	while (fwscanf(file, L" %ls", command) == 1) {
		if (eq(command, L"#")) {
			fwscanf(file, L"%*[^\n\r]%*[\n\r]");

		} else if (eq(command, L"scene")) {
			getInt(file, &sceneId);

		} else if (eq(command, L"ending")) {
			vn->scenes[sceneId].isEnd = true;

		} else if (eq(command, L"dialogue")) {
			wchar_t speaker[SPEAKER_SIZE];
			wchar_t text[TEXT_SIZE];
			getString(file, speaker, SPEAKER_SIZE);
			getString(file, text, TEXT_SIZE);
			dialogue = addDialogue(vn, sceneId, speaker, text);
			state = Dialogue;

		} else if (eq(command, L"choice")) {
			wchar_t text[CHOICE_SIZE];
			int destId;
			getString(file, text, CHOICE_SIZE);
			getInt(file, &destId);
			choice = addChoice(vn, sceneId, text, destId);
			state = Choice;

		} else if (eq(command, L"reuse")) {
			int sourceSceneId;
			getInt(file, &sourceSceneId);
			vn->scenes[sceneId].choices = copyChoices(vn->scenes[sourceSceneId].choices, vn->scenes[sceneId].choices);

		} else if (eq(command, L"preset")) {
			wchar_t flag[FLAG_SIZE];
			getString(file, flag, FLAG_SIZE);
			if (!isFlag(flag)) {
				swprintf(errmsg, DEFAULT_STRING_SIZE, L"Invalid flag parsing \"%ls\"", flag);
				errorParse(file, errmsg);
			}
			vn->flags = appendFlag(vn->flags, flag);

		} else if (eq(command, L"set")) {
			if (state != Choice) {
				errorParse(file, L"Invalid usage of set");
			}
			wchar_t flag[FLAG_SIZE];
			getString(file, flag, FLAG_SIZE);
			if (!isFlag(flag)) {
				swprintf(errmsg, DEFAULT_STRING_SIZE, L"Invalid flag parsing \"%ls\"", flag);
				errorParse(file, errmsg);
			}
			setFlag(choice, flag);

		} else if (eq(command, L"unset")) {
			if (state != Choice) {
				errorParse(file, L"Invalid usage of unset");
			}
			wchar_t flag[FLAG_SIZE];
			getString(file, flag, FLAG_SIZE);
			if (!isFlag(flag)) {
				swprintf(errmsg, DEFAULT_STRING_SIZE, L"Invalid flag parsing \"%ls\"", flag);
				errorParse(file, errmsg);
			}
			unsetFlag(choice, flag);

		} else if (eq(command, L"unsetall")) {
			if (state != Choice) {
				errorParse(file, L"Invalid usage of unsetall");
			}
			wchar_t flag[FLAG_SIZE] = L"*";
			unsetFlag(choice, flag);

		} else if (eq(command, L"if")) {
			wchar_t condition[DEFAULT_STRING_SIZE];
			getString(file, condition, DEFAULT_STRING_SIZE);
			if (evaluateFlags(NULL, condition) == -1) {
				swprintf(errmsg, DEFAULT_STRING_SIZE, L"Invalid condition syntax \"%ls\"", condition);
				errorParse(file, errmsg);
			}
			if (state == Dialogue) {
				requireDialogueFlag(dialogue, condition);
			} else if (state == Choice) {
				requireChoiceFlag(choice, condition);
			} else {
				errorParse(file, L"Invalid usage of if");
			}

		} else if (eq(command, L"image")) {
			if (state != Dialogue) {
				errorParse(file, L"Invalid usage of image");
			}
			Image image = {0};
			wchar_t imagePath[IMAGE_SIZE] = {0};
			getString(file, imagePath, IMAGE_SIZE);
			wcstombs(image.imagePath, imagePath, IMAGE_SIZE * sizeof(wchar_t));
			getIntRange(file, &image.zOrder, 0, IMAGE_CAPACITY);
			addImage(dialogue, image);

		} else if (eq(command, L"imageat")) {
			if (state != Dialogue) {
				errorParse(file, L"Invalid usage of imageat");
			}
			Image image = {0};
			wchar_t imagePath[IMAGE_SIZE] = {0};
			getString(file, imagePath, IMAGE_SIZE);
			wcstombs(image.imagePath, imagePath, IMAGE_SIZE * sizeof(wchar_t));
			getIntRange(file, &image.zOrder, 0, IMAGE_CAPACITY);
			getInt(file, &image.x);
			getInt(file, &image.y);
			addImage(dialogue, image);

		} else if (eq(command, L"clearimage")) {
			if (state != Dialogue) {
				errorParse(file, L"Invalid usage of clearimage");
			}
			Image image = {0};
			image.clear = true;
			getIntRange(file, &image.zOrder, 0, IMAGE_CAPACITY);
			addImage(dialogue, image);

		} else if (eq(command, L"clearallimages")) {
			if (state != Dialogue) {
				errorParse(file, L"Invalid usage of clearimage");
			}
			for (int i = 0; i < IMAGE_CAPACITY; ++i) {
				addImage(dialogue, (Image){.zOrder = i, .clear = true});
			}

		} else if (eq(command, L"option")) {
			wchar_t option[DEFAULT_STRING_SIZE];
			getString(file, option, DEFAULT_STRING_SIZE);

			if (eq(option, L"nocurses")) {
				vn->cursesMode = false;

			} else if (eq(option, L"cps")) {
				getInt(file, &vn->cps);

			} else if (eq(option, L"dialogueheight")) {
				getInt(file, &vn->dialogueWindowHeight);

			} else if (eq(option, L"transparentcharacter")) {
				wchar_t ch[2];
				getString(file, ch, 2);
				vn->transparentCharacter = ch[0];

			} else if (eq(option, L"autoplay")) {
				vn->autoplay = true;

			} else {
				swprintf(errmsg, DEFAULT_STRING_SIZE, L"Invalid option \"%ls\"", option);
				errorParse(file, errmsg);
			}

		} else {
			swprintf(errmsg, DEFAULT_STRING_SIZE, L"Invalid Command \"%ls\"", command);
			errorParse(file, errmsg);
		}
	}

	fclose(file);
}
