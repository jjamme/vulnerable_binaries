// gcc -m32 -fno-stack-protector -z execstack 10_degree.c -o 10_degree
#include <stdio.h>
#include <stdlib.h>

int win () {
	system("/bin/sh");
}

int vuln () {
	char guess[512];

	printf("Guess my favourite course code.\n");
	printf("BINF\n");
	printf("COMM\n");
	printf("PHYS\n");
	printf("ENGG\n");

	while (1) {
		printf("Your guess: ");
		fflush(stdout);

		fgets(guess, sizeof(guess), stdin);
		printf("You guessed ");
		printf(guess);

		printf("Nice try! But I don't really like ");
		printf(guess);
		printf("Keep trying though!\n");
	}
}

int main () {
	vuln();
}
