// gcc -m32 -fno-stack-protector -z execstack -no-pie 3_feed_me.c -o 3_feed_me

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
