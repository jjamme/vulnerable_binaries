// gcc -m32 -fno-stack-protector -z execstack -no-pie 2_my_echo.c  -o 2_my_echo

#include <stdio.h>

int main(){
	int flag = 0;
	char input[64];

	printf("This is my address %p\n", &flag);
	printf("Input something cool and I'll repeat it.\n");
	fgets(input, sizeof(input), stdin);
	printf(input);

	if(flag){
		printf("Wow how'd you get here?\nWelcome to my house!\n");
	}

	return 0;
}