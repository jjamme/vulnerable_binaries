// gcc -m32 -fno-stack-protector -z execstack 6_mining.c -o 6_mining
#include <stdio.h>
#include <stdlib.h>

void vuln () {
	int fake_canary = 0x12345678;
	char buf[64];

	printf("Did you know that canaries used to be used to test carbon monoxide levels in coal mines?\n");
	gets(buf);

	if (fake_canary == 0x454d414a) {
		printf("Very nice, you saved the canary!\n");
		system("/bin/sh");
	} else {
		printf("Well if you answered no then now you know\n");
	}
}

void main () {
	vuln();
}
