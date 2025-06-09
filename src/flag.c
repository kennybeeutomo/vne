#include "flag.h"
#include "config.h"
#include "utils.h"

#include <ctype.h>
#include <stdlib.h>
#include <string.h>

Flag* initFlag(char name[FLAG_SIZE]) {
	Flag* flag = malloc(sizeof(Flag));
	strcpy(flag->name, name);
	flag->next = NULL;
	return flag;
}

Flag* appendFlag(Flag* flag, char name[FLAG_SIZE]) {
	if (nullstr(name)) {
		return flag;
	}

	Flag* newFlag = initFlag(name);

	if (flag == NULL) {
		return newFlag;
	}

	Flag* curr = flag;
	while (curr->next != NULL) {
		if (eq(curr->name, name)) {
			return flag;
		}
		curr = curr->next;
	}

	if (eq(curr->name, name)) {
		return flag;
	}

	curr->next = newFlag;

	return flag;
}

Flag* deleteFlag(Flag* flag, char name[FLAG_SIZE]) {
	if (eq(name, "*")) {
		return freeFlags(flag);
	}

	if (nullstr(name) || flag == NULL) {
		return flag;
	}

	if (eq(flag->name, name)) {
		Flag* next = flag->next;
		free(flag);
		return next;
	}

	Flag* curr = flag->next;
	Flag* prev = flag;

	while (curr != NULL) {
		if (eq(curr->name, name)) {
			prev->next = curr->next;
			free(curr);
		}
		prev = curr;
		curr = curr->next;
	}

	return flag;
}

Flag* appendFlags(Flag* flag, Flag* flagsToAppend) {
	while (flagsToAppend != NULL) {
		flag = appendFlag(flag, flagsToAppend->name);
		flagsToAppend = flagsToAppend->next;
	}

	return flag;
}

Flag* deleteFlags(Flag* flag, Flag* flagsToDelete) {
	while (flagsToDelete != NULL) {
		flag = deleteFlag(flag, flagsToDelete->name);
		flagsToDelete = flagsToDelete->next;
	}

	return flag;
}

bool isFlag(char flag[FLAG_SIZE]) {
	for (int i = 0; flag[i] != '\0'; ++i) {
		if (!(isalnum(flag[i]) || flag[i] == '_')) {
			return false;
		}
	}
	return true;
}

Flag* freeFlags(Flag* flag) {
	if (flag == NULL) {
		return NULL;
	}

	freeFlags(flag->next);
	free(flag);

	return NULL;
}
