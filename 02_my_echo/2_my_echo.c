// gcc -m32 -no-pie 2_my_echo.c  -o 2_my_echo

#include <stdlib.h>
#include <stdio.h>

int main(){
	int flag = 0;
	char input[64];

	printf("This is my address %p\n", &flag);
	printf("You can come over if you tell me the password.\n");
	fgets(input, sizeof(input), stdin);
	printf("Don't know where you heard ");
	printf(input);
	printf("It isn't the password though\n");

	if(flag == 42){
		printf("Wow how'd you get here?\nWelcome to my house!\n");
		system("/bin/sh");
	}

	return 0;
}
