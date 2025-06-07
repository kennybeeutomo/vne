#include "choice.h"
#include "config.h"
#include "dialogue.h"
#include "visualnovel.h"
#include "utils.h"
#include <curses.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {Invalid, Next, Prev, Accept, Exit} Input;

void fill(int y, int x, int rows, int cols) {
	for (int i = 0; i < rows; ++i) {
		mvhline(y + i, x, ' ', cols);
	}
}

int printStr(WINDOW* win, const char* str, int y, int x, int width) {
	wmove(win, y, x);
	for (int i = 0, j = 0; str[i] != '\0'; ++i) {
		if (str[i] == '\n' || j >= width) {
			wmove(win, ++y, x);
			if (str[i] != '\n') {
				waddch(win, str[i]);
			}
			j = 0;
		} else {
			waddch(win, str[i]);
		}
		j++;
	}
	return y;
}

void printHelp() {
	const char helpText[] = "wasd/hjkl - Navigation\n"
	                        "q - Quit\n"
	                        "Space/Enter - Confirm\n"
	                        "\nPress any key to continue...";
	const char helpTitle[] = "[ Controls ]";

	int helpWidth = 35;
	int helpHeight = countStrHeight(helpText, helpWidth) + 2;
	int x = getmaxx(stdscr) / 2 - helpWidth / 2;
	int y = getmaxy(stdscr) / 2 - helpHeight / 2;

	WINDOW* win = newwin(helpHeight, helpWidth, y, x);

	wattron(win, COLOR_PAIR(4));
	box(win, 0, 0);
	mvwprintw(win, 0, helpWidth / 2 - strlen(helpTitle) / 2, "%s", helpTitle);
	wattroff(win, COLOR_PAIR(4));

	printStr(win, helpText, 1, 1, helpWidth - 2);

	wrefresh(win);
	wgetch(win);
	wclear(win);
	wrefresh(win);

	delwin(win);
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
			printHelp();
			input = Invalid;
	}

	return input;
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

void printImageCurses(char image[IMAGE_SIZE]) {
	FILE* file = fopen(image, "r");
	if (file == NULL) {
		return;
	}
	char text[DEFAULT_STRING_SIZE];
	attron(COLOR_PAIR(7));
	while (fgets(text, DEFAULT_STRING_SIZE, file) != NULL) {
		addstr(text);
	}
	attroff(COLOR_PAIR(7));
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
			if (input == Exit) { endVNCurses(vn); }
		}

		clear();

		int y = getmaxy(stdscr) - dialogueWindowHeight;

		if (curr->image[0] != '\0') {
			strcpy(vn->currentImage, curr->image);
		}

		printImageCurses(vn->currentImage);

		attron(COLOR_PAIR(4));
		mvhline(y, 0, 0, getmaxx(stdscr));
		attroff(COLOR_PAIR(4));

		fill(y + 1, 0, vn->dialogueWindowHeight, getmaxx(stdscr));

		if (curr->speaker[0] != '\0') {
			mvprintw(y, 3, "[ %s ]", curr->speaker);
		}

		bool isBold = false, isItalic = false;

		move(y + 1, 0);
		for (int i = 0; curr->text[i] != '\0'; ++i) {
			if (curr->text[i] == '\\') {
				i++;
				if (curr->text[i] == 'w') {
					i++;
					int delay;
					sscanf(&curr->text[i], "%d", &delay);
					i = skipNumbers(i, curr->text) - 1;
					napms(delay);
					continue;
				}
				if (curr->text[i] == 'b') {
					if (isBold) { attroff(A_BOLD); }
					else { attron(A_BOLD); }
					isBold = !isBold;
					continue;
				}
				if (curr->text[i] == 'i') {
					if (isItalic) { attroff(A_ITALIC); }
					else { attron(A_ITALIC); }
					isItalic = !isItalic;
					continue;
				}
				if (curr->text[i] == 'c') {
					i++;
					int color;
					sscanf(&curr->text[i], "%d", &color);
					i = skipNumbers(i, curr->text) - 1;
					if (color == -1) { attroff(A_COLOR); }
					else { attron(COLOR_PAIR(color)); }
					continue;
				}
			}

			addch(curr->text[i]);
			refresh();
			napms(1000/vn->cps);
		}

		attroff(A_BOLD); attroff(A_ITALIC); attroff(A_COLOR);

		flushinp();
		curr = nextDialogue(curr, vn->flags);
	}
}

void printChoicesCurses(VisualNovel* vn) {
	int choiceWindowHeight = getChoiceHeight(vn);
	int dialogueHeight = getDialogueHeight(vn, tailDialogue(vn->currentScene->dialogues));
	int y = getmaxy(stdscr) - dialogueHeight - choiceWindowHeight;

	attron(COLOR_PAIR(4));
	mvvline(y, 0, 0, choiceWindowHeight);
	attroff(COLOR_PAIR(4));

	Choice* curr = getFirstChoice(vn->currentScene->choices, vn->flags);
	while (curr != NULL) {
		if (curr == vn->currentChoice) {
			attron(A_REVERSE);
			mvaddch(y, 0, '>');
		}
		y = printStr(stdscr, curr->text, y, 1, getmaxx(stdscr) - 1) + 1;
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
		Choice* next = nextChoice(vn->currentChoice, vn->flags);
		Choice* prev = prevChoice(vn->currentChoice, vn->flags);
		printChoicesCurses(vn);
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
		for (int i = 0; i < 8; ++i) {
			init_pair(i, i, -1);
		}
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

void endVNCurses(VisualNovel* vn) {
	endwin();
	freeVisualNovel(vn);
	exit(0);
}
