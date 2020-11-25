#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

void home (void) {
	printf("Thanks! I'm home now");
	system("/bin/sh");
}

void ask () {
	char response[4];
	gets(&response);
	for (int i = 0; i < strlen(response); i++) {
		response[i] = tolower(response[i]);
	}

	if (strcmp(response, "yes") == 0) {
		printf("Wow, how will you help?");
	} else if (strcmp(response, "no") == 0) {
		printf(":\(");
	} else {
		printf("What?");
	}
}

int main (void) {

	printf("Help me! I'm lost, can you bring me home?\n");
	printf("I live at %p\n", home);

	printf("Do you want to help? (Yes/No)\n");
	ask();
}
