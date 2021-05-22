// gcc -m32 -fno-stack-protector -z execstack -no-pie 3_im_lost.c -o 3_im_lost

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

void ask () {
	char response[400];

	printf("Um, I got lost again. Please help me\n");
	printf("I live at %p\n", &response);

	printf("Do you want to help? (Yes/No)\n");

	fgets(&response, 424, stdin);
	for (int i = 0; i < strlen(response); i++) {
		response[i] = response[i];
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
