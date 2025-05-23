#include "visualnovel.h"
#include <string.h>

int main(int argc, char** argv) {

	VisualNovel visualNovel = {0};

	char file[4096] = "tutorial.vn";

	if (argc > 1) {
		strcpy(file, argv[1]);
	}

	loadVisualNovel(&visualNovel, file);

	startVisualNovel(&visualNovel);
	freeVisualNovel(&visualNovel);

	return 0;
}
