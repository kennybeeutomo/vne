#pragma once

#include <stdbool.h>

#define CHOICE_SIZE 200

typedef struct Scene Scene;

typedef struct Choice Choice;
typedef struct Choice {
	char text[CHOICE_SIZE];
	Scene* scene;
	Choice* next;
} Choice;

Choice* initChoice(char text[CHOICE_SIZE], Scene* scene);
Choice* appendChoice(Choice* choice, char text[CHOICE_SIZE], Scene* scene);
Choice* freeChoices(Choice* choice);
