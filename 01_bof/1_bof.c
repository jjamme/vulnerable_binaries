// gcc -m32 -fno-stack-protector -z execstack -no-pie 1_bof.c -o 1_bof

#include <stdio.h>
#include <strings.h>

int main() {
	int vuln = 0x1234;
	char arr[36] = {0};

	printf("Did you know that 4660 is 0x%x in hex?\n", vuln);
	printf("It's my favourite number.\n");
	printf("Can you make the number go backwards in hex?\n");

	gets(arr);

	if (vuln == 0x4321) {
		printf("That is a cool number too, you win!\n");
		return 0;
	}

	printf("Here's the number again. 0x%x\n", vuln);

	return 0;
}
