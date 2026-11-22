#include "config.h"
#include "flag.h"
#include "utils.h"

#include <stdlib.h>
#include <string.h>
#include <wchar.h>

wchar_t TRUE[FLAG_SIZE] = L"T";
wchar_t FALSE[FLAG_SIZE] = L"F";

Flag* push(Flag* flag, wchar_t name[FLAG_SIZE]) {
	Flag* newFlag = initFlag(name);
	if (flag == NULL) {
		return newFlag;
	}

	newFlag->next = flag;
	return newFlag;
}

Flag* append(Flag* flag, wchar_t name[FLAG_SIZE]) {
	Flag* newFlag = initFlag(name);

	if (flag == NULL) {
		return newFlag;
	}

	Flag* curr = flag;
	while (curr->next != NULL) {
		curr = curr->next;
	}

	curr->next = newFlag;
	return flag;
}

Flag* pop(Flag* flag) {
	if (flag == NULL) {
		return NULL;
	}

	Flag* temp = flag->next;
	free(flag);
	return temp;
}

bool findFlag(Flag* flag, wchar_t name[FLAG_SIZE]) {
	if (nullstr(name)) {
		return true;
	}
	while (flag != NULL) {
		if (eq(flag->name, name)) {
			return true;
		}
		flag = flag->next;
	}
	return false;
}

Flag* tokenize(const wchar_t expression[DEFAULT_STRING_SIZE]) {
	Flag* flags = NULL;

	wchar_t temp[DEFAULT_STRING_SIZE];
	wcscpy(temp, expression);

	wchar_t delimiters[] = L" \n\r\t\v\f";
	wchar_t* buffer;
	wchar_t* word = wcstok(temp, delimiters, &buffer);

	while (word != NULL) {
		flags = append(flags, word);
		word = wcstok(NULL, delimiters, &buffer);
	}

	return flags;
}

Flag* postfix(Flag* flags) {
	Flag* stack = NULL;
	Flag* postfix = NULL;

	while (flags != NULL) {
		if (eq(flags->name, L"not")) {
			stack = push(stack, flags->name);

		} else if (eq(flags->name, L"and") || eq(flags->name, L"or")) {
			if (stack == NULL || eq(stack->name, L"(")) {
				stack = push(stack, flags->name);
			} else {
				postfix = append(postfix, stack->name);
				stack = pop(stack);
				stack = push(stack, flags->name);
			}

		} else if (eq(flags->name, L"(")) {
			stack = push(stack, flags->name);

		} else if (eq(flags->name, L")")) {
			while (1) {
				if (stack == NULL) {
					freeFlags(flags);
					return NULL;
				}
				if (eq(stack->name, L"(")) {
					break;
				}
				postfix = append(postfix, stack->name);
				stack = pop(stack);
			}
			stack = pop(stack);

		} else {
			postfix = append(postfix, flags->name);
		}
		flags = flags->next;
	}

	while (stack != NULL) {
		postfix = append(postfix, stack->name);
		stack = pop(stack);
	}

	freeFlags(flags);
	return postfix;
}

void substitute(Flag* flags, Flag* flagsToSubstitute) {
	Flag* curr = flagsToSubstitute;
	while (curr != NULL) {
		if (!(eq(curr->name, L"and") || eq(curr->name, L"or") || eq(curr->name, L"not") || eq(curr->name, L"(") ||
		      eq(curr->name, L")"))) {
			bool result = findFlag(flags, curr->name);
			wcscpy(curr->name, result ? TRUE : FALSE);
		}
		curr = curr->next;
	}
}

Flag* evaluate(Flag* postfix) {
	Flag* stack = NULL;

	while (postfix != NULL) {
		if (eq(postfix->name, L"and")) {
			bool result = eq(stack->name, TRUE) && eq(stack->next->name, TRUE);
			if (stack == NULL) {
				return NULL;
			}
			stack = pop(stack);
			if (stack == NULL) {
				return NULL;
			}
			stack = pop(stack);
			stack = push(stack, result ? TRUE : FALSE);
		} else if (eq(postfix->name, L"or")) {
			bool result = eq(stack->name, TRUE) || eq(stack->next->name, TRUE);
			if (stack == NULL) {
				return NULL;
			}
			stack = pop(stack);
			if (stack == NULL) {
				return NULL;
			}
			stack = pop(stack);
			stack = push(stack, result ? TRUE : FALSE);
		} else if (eq(postfix->name, L"not")) {
			bool result = eq(stack->name, FALSE);
			if (stack == NULL) {
				return NULL;
			}
			stack = pop(stack);
			stack = push(stack, result ? TRUE : FALSE);
		} else {
			stack = push(stack, postfix->name);
		}
		postfix = postfix->next;
	}

	if (stack == NULL) {
		return NULL;
	}

	if (stack->next != NULL) {
		return NULL;
	}

	return stack;
}

int evaluateFlags(Flag* flags, const wchar_t requiredFlags[DEFAULT_STRING_SIZE]) {
	if (nullstr(requiredFlags)) {
		return true;
	}

	Flag* required = tokenize(requiredFlags);
	required = postfix(required);
	substitute(flags, required);
	Flag* result = evaluate(required);

	if (result == NULL) {
		return -1;
	}

	return eq(result->name, TRUE);
}
