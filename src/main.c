#include "visualnovel.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void parseOpts(VisualNovel* vn, const char* arg) {
	if (strcmp(arg, "-nocurses") == 0) {
		vn->cursesMode = false;
		return;
	}
	if (strcmp(arg, "-curses") == 0) {
		vn->cursesMode = true;
		return;
	}
	fprintf(stderr, "Invalid option\n");
	exit(1);
}

void parseArgs(VisualNovel* vn, int argc, char** argv) {
	for (int i = 1; i < argc; ++i) {
		if (argv[i][0] == '-') {
			parseOpts(vn, argv[i]);
		} else {
			strcpy(vn->path, argv[i]);
		}
	}
}

int main(int argc, char** argv) {

	VisualNovel visualNovel = initVN();

	parseArgs(&visualNovel, argc, argv);

	loadVisualNovel(&visualNovel);

	parseArgs(&visualNovel, argc, argv);

	startVisualNovel(&visualNovel);

	return 0;
}
