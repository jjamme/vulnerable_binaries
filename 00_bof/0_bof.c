// gcc -m32 -fno-stack-protector -z execstack -no-pie 0_bof.c -o 0_bof
#include <stdio.h>

int main(){
	char vuln = 'B';
	char arr[50] = {};

	printf("My favourite letter is: %c\n", vuln);
	printf("Don't change my favourite letter to A, I hate A\n");
	printf("What is your favourite letter?\n");

	gets(arr);

	if (vuln == 'A'){
		printf("Wow you changed my favourite letter :\(\n");
		return 0;
	}
	printf("Here's my favourite character again: %c\n", vuln);

	return 0;
}
