#include "choice.h"
#include "config.h"
#include "dialogue.h"
#include "visualnovel.h"
#include <curses.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {Invalid, Next, Prev, Accept, Exit} Input;

void endVNCurses(VisualNovel* vn) {
	endwin();
	freeVisualNovel(vn);
	exit(0);
}

int mod(const int a, const int b) {
	if (b == 0) return 0;
	return (a % b + b) % b;
}

void fill(int y, int x, int rows, int cols) {
	for (int i = 0; i < rows; ++i) {
		mvhline(y + i, x, ' ', cols);
	}
}

Input getInput() {
	Input input;

	chtype ch = getch();
	switch (ch) {
		case 'j': case 's': case 'l': case 'd':
			input = Next;
			break;
		case 'k': case 'w': case 'h': case 'a':
			input = Prev;
			break;
		case ' ': case '\n': case '\r':
			input = Accept;
			break;
		case 'q':
			input = Exit;
			break;
		default:
			input = Invalid;
	}

	return input;
}

int countStrHeight(const char* str, int width) {
	int height = 1;
	int col = 0;
	for (int i = 0; str[i] != '\0'; ++i) {
		if (str[i] == '\n' || col >= width) {
			height++;
			col = 1;
		}
		col++;
	}
	return height;
}

int getChoiceHeight(VisualNovel* vn) {
	int height = 0;

	Choice* choice = getFirstChoice(vn->currentScene->choices, vn->flags);
	while (choice != NULL) {
		int choiceHeight = countStrHeight(choice->text, getmaxx(stdscr) - 1);
		height += choiceHeight;
		choice = nextChoice(choice, vn->flags);
	}

	return height;
}

int getDialogueHeight(VisualNovel* vn, Dialogue* dialogue) {
	int height = countStrHeight(dialogue->text, getmaxx(stdscr)) + 1;
	height = (height > vn->dialogueWindowHeight) ? height : vn->dialogueWindowHeight;
	return height;
}

int printStr(const char* str, int y, int x, int width) {
	move(y, x);
	for (int i = 0, j = 0; str[i] != '\0'; ++i) {
		if (str[i] == '\n' || j >= width) {
			move(++y, x);
			if (str[i] != '\n') {
				addch(str[i]);
			}
			j = 0;
		} else {
			addch(str[i]);
		}
		j++;
	}
	return y;
}

void printImageCurses(char image[IMAGE_SIZE]) {
	FILE* file = fopen(image, "r");
	if (file == NULL) {
		return;
	}
	char text[DEFAULT_STRING_SIZE];
	attron(COLOR_PAIR(1));
	while (fgets(text, DEFAULT_STRING_SIZE, file) != NULL) {
		addstr(text);
	}
	attroff(COLOR_PAIR(1));
	fclose(file);
}

void printDialoguesCurses(VisualNovel* vn) {
	Dialogue* head = getFirstDialogue(vn->currentScene->dialogues, vn->flags);
	Dialogue* curr = head;
	while (curr != NULL) {
		int dialogueWindowHeight = getDialogueHeight(vn, curr);

		if (curr != head) {
			Input input = Invalid;
			while (input == Invalid) input = getInput();
			if (input == Exit) {
				endVNCurses(vn);
			}
		}

		clear();

		int y = getmaxy(stdscr) - dialogueWindowHeight;

		if (curr->image[0] != '\0') {
			strcpy(vn->currentImage, curr->image);
		}

		printImageCurses(vn->currentImage);

		attron(COLOR_PAIR(2));
		mvhline(y, 0, 0, getmaxx(stdscr));
		attroff(COLOR_PAIR(2));

		fill(y + 1, 0, vn->dialogueWindowHeight, getmaxx(stdscr));

		if (curr->speaker[0] != '\0') {
			mvprintw(y, 3, "[ %s ]", curr->speaker);
		}

		move(y + 1, 0);
		for (int i = 0; curr->text[i] != '\0'; ++i) {
			addch(curr->text[i]);
			refresh();
			napms(1000/vn->cps);
		}

		flushinp();
		curr = nextDialogue(curr, vn->flags);
	}
}

void printChoicesCurses(VisualNovel* vn) {
	int choiceWindowHeight = getChoiceHeight(vn);
	int dialogueHeight = getDialogueHeight(vn, tailDialogue(vn->currentScene->dialogues));
	int y = getmaxy(stdscr) - dialogueHeight - choiceWindowHeight;

	attron(COLOR_PAIR(2));
	mvvline(y, 0, 0, choiceWindowHeight);
	attroff(COLOR_PAIR(2));

	Choice* curr = getFirstChoice(vn->currentScene->choices, vn->flags);
	while (curr != NULL) {
		if (curr == vn->currentChoice) {
			attron(A_REVERSE);
			mvaddch(y, 0, '>');
		}
		y = printStr(curr->text, y, 1, getmaxx(stdscr) - 1) + 1;
		if (curr == vn->currentChoice) {
			attroff(A_REVERSE); 
		}
		curr = nextChoice(curr, vn->flags);
	}
	refresh();
}

void chooseMenuCurses(VisualNovel* vn) {
	Input input = Invalid;
	while (input != Accept) {
		printChoicesCurses(vn);
		Choice* next = nextChoice(vn->currentChoice, vn->flags);
		Choice* prev = prevChoice(vn->currentChoice, vn->flags);
		input = getInput();
		switch (input) {
			case Next:
				vn->currentChoice = (next == NULL) ? vn->currentChoice : next;
				break;
			case Prev:
				vn->currentChoice = (prev == NULL) ? vn->currentChoice : prev;
				break;
			case Exit:
				endVNCurses(vn);
				break;
			default:
				break;
		}
	}

	choose(vn);
}

void startVisualNovelCurses(VisualNovel* vn) {
	initscr();
	noecho();
	curs_set(0);

	if (has_colors()) {
		start_color();
		use_default_colors();
		init_pair(1, COLOR_WHITE, -1);
		init_pair(2, COLOR_BLUE, -1);
	}

	setScene(vn, &vn->scenes[0]);
	while (1) {
		printDialoguesCurses(vn);
		if (isEndingScene(*vn->currentScene)) {
			break;
		}
		chooseMenuCurses(vn);
	}

	getch();
	endVNCurses(vn);
}
