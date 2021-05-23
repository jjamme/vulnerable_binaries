// gcc -m32 -fno-stack-protector -z execstack -no-pie 4_im_lost.c -o 4_im_lost

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

void ask () {
	char response[4];

	printf("Help me! I'm lost, can you bring me home?\n");
	printf("I live at %p\n", &response);

	printf("Do you want to help? (Yes/No)\n");

	gets(&response);
	for (int i = 0; i < strlen(response); i++) {
		response[i] = tolower(response[i]);
	}

	if (strcmp(response, "yes") == 0) {
		printf("Wow, how will you help?");
	} else if (strcmp(response, "no") == 0) {
		printf(":(\n");
	} else {
		printf("What?\n");
	}
}

int main (void) {
	ask();
}
