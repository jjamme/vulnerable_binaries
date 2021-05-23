#include <stdio.h>
#include <stdlib.h>

void win () {
	system("/bin/sh");
}

void vuln () {
	char arr[64];

	printf("I'm starving, there's nothing in my esp, can you feed me something?\n");
	gets(arr);
}

int main () {
	vuln();
}
