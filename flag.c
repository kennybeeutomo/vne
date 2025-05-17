#include "flag.h"

#include <stdlib.h>
#include <string.h>

Flag* initFlag(char name[FLAG_SIZE]) {
	Flag* flag = malloc(sizeof(Flag));
	strcpy(flag->name, name);
	flag->next = NULL;
	return flag;
}

Flag* appendFlag(Flag* flag, char name[FLAG_SIZE]) {
	if (name[0] == '\0') {
		return flag;
	}

	Flag* newFlag = initFlag(name);

	if (flag == NULL) {
		return newFlag;
	}

	Flag* curr = flag;
	while (curr->next != NULL) {
		if (strcmp(curr->name, name) == 0) {
			return flag;
		}
		curr = curr->next;
	}
	curr->next = newFlag;

	return flag;
}

Flag* freeFlags(Flag* flag) {
	if (flag == NULL) {
		return NULL;
	}

	freeFlags(flag->next);
	free(flag);

	return NULL;
}

bool findFlag(Flag* flag, char name[FLAG_SIZE]) {
	if (name[0] == '\0') {
		return true;
	}
	while (flag != NULL) {
		if (strcmp(flag->name, name) == 0) {
			return true;
		}
		flag = flag->next;
	}
	return false;
}
