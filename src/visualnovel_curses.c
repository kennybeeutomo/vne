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

void printHelp() {
	const char helpText[] = "WASD/HJKL - Navigation\n"
	                        "Q - Quit\n"
	                        "Space/Enter - Confirm\n"
	                        "P - Toggle Autoplay\n"
	                        "G - Show History\n"
	                        "\nPress any key to continue...";
	const char helpTitle[] = "[ Controls ]";

	WINDOW* win = printTempWindow(helpTitle, helpText, 37, -1);

	wgetch(win);
	wclear(win);
	wrefresh(win);

	delwin(win);

	redrawwin(stdscr);
	refresh();
}

void printHistory(VisualNovel* vn) {
	Dialogue* history = vn->history;

	int width = getmaxx(stdscr) * 0.9 - 2;
	int height = getmaxy(stdscr) * 0.9 - 2;

	char text[width * height];

	while (1) {
		memset(text, 0, sizeof(text));
		getHistoryText(history, text, width, height);
		WINDOW* win = printTempWindow("[ History ]", text, width + 2, height + 2);

		Input input = getInput(win);
		wclear(win);

		if (input == Next) {
			history = history->next == NULL ? history : history->next;
		} else if (input == Prev) {
			history = history->prev == NULL ? history : history->prev;
		} else {
			break;
		}
		delwin(win);
	}

	redrawwin(stdscr);
	refresh();
}

void printImageCurses(VisualNovel* vn, char image[IMAGE_SIZE]) {
	char imagePath[PATH_MAX];
	getImagePath(imagePath, vn, image);

	FILE* file = fopen(imagePath, "r");
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

void printDialogueCurses(VisualNovel* vn, bool instant, bool saveToHistory) {
	clear();

	Dialogue* dialogue = vn->currentDialogue;

	if (saveToHistory) {
		addDialogueToHistory(vn);
	}

	int dialogueWindowHeight = getDialogueHeight(vn, dialogue);

	int y = getmaxy(stdscr) - dialogueWindowHeight;

	if (dialogue != NULL && notnullstr(dialogue->image)) {
		strcpy(vn->currentImage, dialogue->image);
	}

	printImageCurses(vn, vn->currentImage);

	attron(COLOR_PAIR(4));
	mvhline(y, 0, 0, getmaxx(stdscr));
	attroff(COLOR_PAIR(4));

	fill(y + 1, 0, vn->dialogueWindowHeight, getmaxx(stdscr), ' ');

	if (dialogue != NULL && notnullstr(dialogue->speaker)) {
		mvprintw(y, 3, "[ %s ]", dialogue->speaker);
	}

	if (vn->autoplay) {
		char autoplayText[] = "AUTOPLAY";
		mvprintw(y, getmaxx(stdscr) - strlen(autoplayText), "%s", autoplayText);
	}

	if (vn->currentDialogue == NULL) { return; }

	bool isBold = false, isItalic = false;

	int interval = instant ? 0 : 1000/vn->cps;

	Input input = Invalid;

	move(y + 1, 0);
	for (int i = 0; dialogue->text[i] != '\0'; ++i) {
		input = getInputVN(stdscr, vn);
		if (input == Auto) { break; }
		if (input != Invalid && input != NoInput) { interval = 0; }
		if (dialogue->text[i] == '\\') {
			i++;
			if (dialogue->text[i] == 'w') {
				i++;
				int delay;
				sscanf(&dialogue->text[i], "%d", &delay);
				i = skipNumbers(i, dialogue->text) - 1;
				if (interval != 0) { napms(delay); }
				continue;
			}
			if (dialogue->text[i] == 'b') {
				if (isBold) { attroff(A_BOLD); }
				else { attron(A_BOLD); }
				isBold = !isBold;
				continue;
			}
			if (dialogue->text[i] == 'i') {
				if (isItalic) { attroff(A_ITALIC); }
				else { attron(A_ITALIC); }
				isItalic = !isItalic;
				continue;
			}
			if (dialogue->text[i] == 'c') {
				i++;
				int color;
				sscanf(&dialogue->text[i], "%d", &color);
				i = skipNumbers(i, dialogue->text) - 1;
				if (color == -1) { attroff(A_COLOR); }
				else { attron(COLOR_PAIR(color)); }
				continue;
			}
		}

		addch(dialogue->text[i]);
		refresh();
		napms(interval);
	}

	attroff(A_BOLD); attroff(A_ITALIC); attroff(A_COLOR);

	if (input == Auto) { printDialogueCurses(vn, true, false); }
}

void printDialoguesCurses(VisualNovel* vn) {
	Dialogue* head = vn->currentDialogue;
	Dialogue* last = getLastDialogue(head, vn->flags);
	while (1) {

		printDialogueCurses(vn, false, true);

		if (vn->currentDialogue == last && vn->currentChoice != NULL) {
			break;
		}

		if (vn->autoplay) {
			// Autoplay delay
			int len = strlen(vn->currentDialogue->text);
			for (int i = 0; i < len; ++i) {
				Input input = getInputVN(stdscr, vn);
				if (input == Auto || input == Resize) { printDialogueCurses(vn, true, false); break; }
				if (!isInvalid(input)) { break; }
				napms(AUTOPLAY_CHAR_DELAY);
			}
		} else {
			// Wait for input to continue
			Input input = Invalid;
			while (isInvalid(input) || input == Resize) {
				input = getInputVN(stdscr, vn);
				if (input == Resize) { printDialogueCurses(vn, true, false); }
				char endingIndicator[] = "->";
				attron(A_BOLD);
				mvaddstr(getmaxy(stdscr)-1, getmaxx(stdscr)-strlen(endingIndicator), endingIndicator);
				attroff(A_BOLD);
				napms(DEBOUNCE_DURATION);
			}
		}

		if (vn->currentDialogue == last && vn->currentChoice == NULL) {
			break;
		}

		if (vn->currentDialogue == NULL) { break; }
		vn->currentDialogue = nextDialogue(vn->currentDialogue, vn->flags);
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
	bool chosen = false;

	Choice* head = getFirstChoice(vn->currentScene->choices, vn->flags);
	Choice* last = getLastChoice(vn->currentScene->choices, vn->flags);

	while (!chosen) {
		if (vn->currentChoice == NULL) { break; }

		Choice* next = nextChoice(vn->currentChoice, vn->flags);
		Choice* prev = prevChoice(vn->currentChoice, vn->flags);

		printChoicesCurses(vn);

		Input input = Invalid;
		while (isInvalid(input)) {
			input = getInputVN(stdscr, vn);
			napms(DEBOUNCE_DURATION);
		}

		switch (input) {
			case Next:
				vn->currentChoice = (next == NULL) ? head : next;
				break;
			case Prev:
				vn->currentChoice = (prev == NULL) ? last : prev;
				break;
			case Auto: case Resize:
				printDialogueCurses(vn, true, false);
				break;
			case Accept:
				chosen = true;
				break;
			default:
				break;
		}
	}

	addChoiceToHistory(vn);

	choose(vn);
}

void startVisualNovelCurses(VisualNovel* vn) {
	initscr();
	noecho();
	curs_set(0);
	nodelay(stdscr, true);

	if (has_colors()) {
		start_color();
		use_default_colors();
		for (int i = 0; i < 8; ++i) {
			init_pair(i, i, -1);
		}
	}

	setScene(vn, &vn->scenes[0]);
	while (vn->currentScene != NULL) {
		printDialoguesCurses(vn);
		chooseMenuCurses(vn);
	}

	endVNCurses(vn);
}

void endVNCurses(VisualNovel* vn) {
	endwin();
	freeVisualNovel(vn);
	exit(0);
}
