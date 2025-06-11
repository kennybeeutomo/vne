#include "visualnovel.h"
#include "utils.h"

#include <ctype.h>
#include <string.h>

void fill(int y, int x, int rows, int cols, chtype ch) {
	for (int i = 0; i < rows; ++i) {
		mvhline(y + i, x, ch, cols);
	}
}

int printStr(WINDOW* win, const char* str, int y, int x, int width) {
	wmove(win, y, x);
	for (int i = 0, j = 0; str[i] != '\0'; ++i) {
		if (str[i] == '\n' || j >= width) {
			wmove(win, ++y, x);
			j = 0;
			if (str[i] == '\n') { continue; }
		}
		waddch(win, str[i]);
		j++;
	}
	return y;
}

WINDOW* printTempWindow(const char* title, const char* text, int width, int height) {
	height = height == -1 ? countStrHeight(text, width - 2) + 2 : height;
	int x = getmaxx(stdscr) / 2 - width / 2;
	int y = getmaxy(stdscr) / 2 - height / 2;

	WINDOW* win = newwin(height, width, y, x);

	wattron(win, COLOR_PAIR(4));
	box(win, 0, 0);
	mvwprintw(win, 0, width / 2 - strlen(title) / 2, "%s", title);
	wattroff(win, COLOR_PAIR(4));

	printStr(win, text, 1, 1, width - 2);

	wrefresh(win);

	return win;
}

void editWindow(const char* title, char* text, int width, int cap) {

	WINDOW* win;
	bool running = true;

	int i = strlen(text);
	while (running) {
		win = printTempWindow(title, text, width, -1);
		keypad(win, true);

		curs_set(1);
		Input input = wgetch(win);
		curs_set(0);

		if (input == '\e') {
			running = false;
		} else if (input == KEY_BACKSPACE) {
			if (i - 1 >= 0) {
				text[--i] = '\0';
				wclear(win);
				wrefresh(win); 
			}
		} else if (isprint(input) || input == '\n') {
			if (i + 1 < cap) { text[i++] = input; }
		}
		
		delwin(win);
	}

	redrawwin(stdscr);
}

Input getInput(WINDOW* win) {
	Input input;

	chtype ch = wgetch(win);
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
		case 'p':
			input = Auto;
			break;
		case 'g':
			input = History;
			break;
		case KEY_RESIZE:
			input = Resize;
			break;
		case ERR:
			input = NoInput;
			break;
		default:
			input = Invalid;
	}

	flushinp();
	return input;
}

Input getInputVN(WINDOW* win, VisualNovel* vn) {
	Input input = getInput(win);

	switch (input) {
		case Exit:
			endVNCurses(vn);
			break;
		case Auto:
			vn->autoplay = !vn->autoplay;
			break;
		case History:
			printHistory(vn);
			break;
		case Invalid:
			printHelp();
			break;
		default:
			break;
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
	if (vn->currentDialogue == NULL) { return vn->dialogueWindowHeight; }
	int height = countStrHeight(dialogue->text, getmaxx(stdscr)) + 1;
	height = max(height, vn->dialogueWindowHeight);
	return height;
}

void getHistoryText(Dialogue* history, char* text, int width, int height) {
	Dialogue* curr = history;
	while (curr != NULL) {
		char dialogueText[TEXT_SIZE + SPEAKER_SIZE + 8];
		if (notnullstr(curr->speaker)) {
			sprintf(dialogueText, "%s: ", curr->speaker);
			strcat(dialogueText, curr->text);
		} else {
			sprintf(dialogueText, "%s", curr->text);
		}

		strcat(dialogueText, "\n");
		char line[width + 1];
		setstr(line, width + 1, '-');
		strcat(dialogueText, line);
		strcat(dialogueText, "\n");

		if (countStrHeight(text, width) + countStrHeight(dialogueText, width) > height) {
			break;
		}

		strcat(text, dialogueText);
		curr = curr->next;
	}
}
