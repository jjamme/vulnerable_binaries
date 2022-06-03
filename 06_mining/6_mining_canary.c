// gcc -m32 6_mining_canary.c -o 6_mining_canary
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void win() {
	printf("Hey get outta here!");
	system("/bin/sh");
}

void vuln() {
        char buf[64];
		char *canary = (char *) (&buf + 1);

        printf("You know my cool fact now!\n");

		printf("Here's a secret: ");
		fflush(stdout);
		write(1, canary, 4);
		printf("%p", &win);
		printf("\n");

        printf("It's your turn to tell me a secret, don't lie or my canary will tell me!\n");
        fgets(buf, 85, stdin);
}

void main() {
        vuln();
        printf("Well that was boring!\n");
}

