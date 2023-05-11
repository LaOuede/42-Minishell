#include "../include/minishell.h"

/*
** Simple main that prints a message (printf) on the terminal
** Infinite loop pour attendre le user input
*/
int main()
{
	printf("\n😈😈😈 Welcome to minishell ... or should say "RED"MINIHELLLLLLLLLL 😈😈😈\n\n"WHT);
	while(1)
		readline("Minishell > ");
		// Recuperer ce que le user met en input pour faire le parsing de la ligne de cmd
	return (0);
}