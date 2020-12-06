// gcc -m32 -no-pie 4_got_skillz.c -o 4_got_skillz

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main () {
	char name[5] = "WHAT";
	char response[512];

	printf("My first name is %s?\n", name);
	printf("My last name is %p\n", &name);
	printf("Am I lying? (Y/N) ");

	fgets(response, sizeof(response), stdin);
	response[strlen(response) - 1] = '\0';

	printf("Why do you think ");
	printf(response);

	if (strcmp(name, "JAME") == 0) {
		printf("Wow how did you find my name?\n");
		system("/bin/sh");
	} else {
		printf("because you're wrong.\n");
		printf("That's because my name is %s\n", name);
	}
}
