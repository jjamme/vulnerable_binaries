// gcc -m32 -no-pie 6_got_skillz.c -o 6_got_skillz

#include <stdio.h>
#include <stdlib.h>

void cool () {
	printf("Dang that is cool!\n");
	system("/bin/sh");
}

void notCool (char *response) {
	printf("Not impressed at ");
	printf(response);
}

void main () {
	char response[64];
	printf("If you GOT 5k1llz.\nShow me your sk1llz!\n");
	fgets(response, sizeof(response), stdin);
	notCool(response);
	printf("Well, goodbye!\n");

	exit(0);
}
