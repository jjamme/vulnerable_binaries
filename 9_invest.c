// gcc -m32 -fno-stack-protector -z execstack -no-pie 7_invest.c -o 7_invest -lm

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <math.h>
#include <time.h>

typedef struct player {
	char name[50];
	float balance;
} Player;

void win () {
	printf("Wow you really won the gamble\n");
	system("/bin/sh");
}

int generate_square () {
	return pow(rand() % 1000, 2);
}

int not_square () {
	int random = rand() % 1000000;
	while (pow(floor(sqrt(random)), 2) == random) {
		random = rand() % 1000000;
	}

	return random;
}

void gamble (Player *player) {
	char player_name[50];
	if (player->balance <= 0) {
		printf("You have no money to gamble with\n");
		return;
	}

	float bet;
	printf("How much do you want to bet?\n");
	scanf("%f", &bet);

	if (bet > player->balance) {
		printf("Woah there, you aren't that rich.\n");
		return;
	}
	
	printf("I'm thinking of a number between 0 and 1,000,000\n");
	printf("What is it?\n");
	
	int choices[4];
	srand(time(NULL));
	int placement = rand() % 4;
	for (int i = 0; i < 3; i++, placement++) {
		placement %= 4;
		choices[placement] = generate_square();
	}
	placement %= 4;
	choices[placement] = not_square();
	
	printf("(a) %d\n", choices[0]);
	printf("(b) %d\n", choices[1]);
	printf("(c) %d\n", choices[2]);
	printf("(d) %d\n", choices[3]);

	char buf[50];
	fgets(buf, sizeof(buf), stdin);
	char choice = buf[0];

	printf("Your choice: ");
	scanf("%c", &choice);
	getchar();

	srand(time(NULL));
	if (choice - 'a' == placement) {
		double gain = (bet * rand() / RAND_MAX);
		player->balance = player->balance + gain;
		strcpy(player_name, player->name);
		printf("Good job ");
		printf(player_name);
	   	printf(" you won %.2f!", gain);
		return;
	}

	double loss = bet + (bet * rand() / RAND_MAX);
	player->balance = player->balance - loss;
	printf("Boo you just lost %.2f\n", loss);
}

void invest (Player *player) {
	if (player->balance <= 0) {
		printf("Sorry, you're in debt, you aren't cut out for IB.\n");
		return;
	}
	
	float amount;
	printf("How much would you like to invest in stonks?\n");
	printf("Amount to bet:\n");
	scanf("%f", &amount);
	getchar();

	if(amount > player->balance) {
		printf("Woah there, you aren't that rich.\n");
		return;
	}
	printf("Investing... Wait a couple seconds\n");
	sleep(3);

	srand(time(NULL));
	int win = rand() % 2;
	win = 0;
	if (win) {
		double gain = (amount * rand() / RAND_MAX);
		printf("Ok rich\n");
		printf("You made $%.2f\n", gain);
		player->balance = player->balance + gain;
	} else {
		double loss = (amount * rand() / RAND_MAX) + amount;
		printf("You just lost %.2f\n", loss);
		player->balance = player->balance - loss;
	}
}

void name_change (Player *player) {
	printf("What do you want to change your name to?\n");
	fgets(player->name, sizeof(player->name), stdin);
}

void display_board (Player *player) {
	char split[] = "=======================================";

	printf("\nCurrent Stats\n");
	printf("%s\n", split);
	printf("Name: %s\n", player->name);
	printf("Balance %.2f\n", player->balance);
	printf("%s\n", split);
}

char get_input () {
	char buf[20];
	printf("(I)nvest\n");
	printf("(G)amble\n");
	printf("(C)hange name\n");
	printf("(E)xit\n");
	printf("Give me a command:\n");
	fgets(buf, sizeof(buf), stdin);
	char input = buf[0];
	return input;
}

int game_loop (Player *player) {
	display_board(player);

	char input = tolower(get_input());

	if (input == 'e') {
		printf("Goodbye!\n");
		exit(0);
	} else if (input == 'c') {
		name_change(player);
	} else if (input == 'i') {
		invest(player);
	} else if (input == 'g') {
		gamble(player);
	} else if (input == '\n') {
		printf("bruh");
		return 1;
	} else {
		printf("Uh, what?\n");
	}

	return 1;
}

void main () {
	Player *player = malloc(sizeof(Player));

	printf("Oh you do IB?\n");
	printf("What is your name?\n");

	fgets(player->name, sizeof(player->name), stdin);
	player->name[strlen(player->name) - 1] = '\0';
	player->balance = 500.00;

	printf("Nice to meet you %s!\n\n", player->name);
	while(game_loop(player)) {
	}
}
