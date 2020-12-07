#include <stdio.h>

void vuln();

void main () {
	vuln();
}

void vuln () {
	char buf[512];

	printf("What is cooler?\n");
	printf("A pointer on the stack: %p\n", &buf);
	printf("or\n");
	printf("A pointer in the text segment: %p\n", &main);
	printf("Your choice: ");
	fflush(stdout);
	gets(buf);
}
