#include "utils.h"
#include "visualnovel.h"
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void parseOpts(VisualNovel* vn, const char* arg) {
	if (eqn(arg, "-nocurses")) {
		vn->cursesMode = false;
	} else

	{
		fprintf(stderr, "Invalid option\n");
		exit(1);
	}
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

	setlocale(LC_ALL, "en_US.UTF-8");

	VisualNovel visualNovel = initVN();

	parseArgs(&visualNovel, argc, argv);

	loadVisualNovel(&visualNovel);

	parseArgs(&visualNovel, argc, argv);

	startVisualNovel(&visualNovel);

	return 0;
}
