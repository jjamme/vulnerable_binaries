#include <stdio.h>

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