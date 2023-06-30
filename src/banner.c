#include "../include/minishell.h"

/* void	banner(void)
{
	printf("\n");
	printf(KGRE " ███▄ ▄███▓ ██▓ ███▄    █  ██▓  ██████  ██░ ██ ▓█████  ██▓     ██▓    \n");
	printf("▓██▒▀█▀ ██▒▓██▒ ██ ▀█   █ ▓██▒▒██    ▒ ▓██░ ██▒▓█   ▀ ▓██▒    ▓██▒    \n");
	printf(KRED KBLD"▓██    ▓██░▒██▒▓██  ▀█ ██▒▒██▒░ ▓██▄   ▒██▀▀██░▒███   ▒██░    ▒██░    \n" RESET);
	printf("▒██    ▒██ ░██░▓██▒  ▐▌██▒░██░  ▒   ██▒░▓█ ░██ ▒▓█  ▄ ▒██░    ▒██░    \n");
	printf("▒██▒   ░██▒░██░▒██░   ▓██░░██░▒██████▒▒░▓█▒░██▓░▒████▒░██████▒░██████▒\n");
	printf("░ ▒░   ░  ░░▓  ░ ▒░   ▒ ▒ ░▓  ▒ ▒▓▒ ▒ ░ ▒ ░░▒░▒░░ ▒░ ░░ ▒░▓  ░░ ▒░▓  ░\n");
	printf("░ ▒░   ░  ░░▓  ░ ▒░   ▒ ▒ ░▓  ▒ ▒▓▒ ▒ ░ ▒ ░░▒░▒░░ ▒░ ░░ ▒░▓  ░░ ▒░▓  ░\n");
	printf("░  ░      ░ ▒ ░░ ░░   ░ ▒░ ▒ ░░ ░▒  ░ ░ ▒ ░▒░ ░ ░ ░  ░░ ░ ▒  ░░ ░ ▒  ░\n");
	printf("░      ░    ▒ ░   ░   ░ ░  ▒ ░░  ░  ░   ░  ░░ ░   ░     ░ ░     ░ ░   \n");
	printf("       ░    ░           ░  ░        ░   ░  ░  ░   ░  ░    ░  ░    ░  ░\n" RESET);
} */

// VSCode - YELRED
void	ft_banner_start(void)
{
	//printf(KRED BLD "\n😈😈😈 Welcome to miniꞩhell ... or should I say 🔥 MINIHELLLL 🔥 😈😈😈\n\n" RESET);
	printf("\n");
	printf(KYEL BLD"	 _____________________________  __________________            \n");
	printf(KYEL BLD"	|                              /                  |          \n");
	printf(KYEL BLD"	|               _       _     /_          _ _     |          \n");
	printf(KYEL "	|     _ __ ___ (_)_ __ (_)___/| |__   ___| | |    |        \n" RESET);
	printf(KYEL "	|    | '_ ` _ \\| | '_ \\| / _/_| '_ \\ / _ \\ | |    |          \n");
	printf(KRED "	|    | | | | | | | | | | \\_/__\\ | | |  __/ | |    |      \n" RESET);
	printf(KRED BLD"	|    |_| |_| |_|_|_| |_|_|/___/_| |_|\\___|_|_|    |   \n" RESET);
	printf(KRED BLD"	|                        /                        |   \n" RESET);
	printf(KRED BLD"	|_______________________/                         |   \n" RESET);
	printf(KRED BLD"	                                                  |   \n" RESET);
	printf("		    ...powered by " KYEL "gle-roux🐭 " RESET "&" KRED " csenand🐭" KRED BLD"  |\n" RESET);
	printf(KRED BLD"	__________________________________________________|   \n\n" RESET);
	printf("				...evaluated by " KRED BLD EVALUATOR" \n\n" RESET);
	printf(KYEL BLD"■■■■■■■■■■■■■■■■■"RESET KYEL"■■■■■■■■■■■■■■■■■"RESET KRED"■■■■■■■■■■■■■■■■■■"RESET KRED BLD"■■■■■■■■■■■■■■■■■\n\n"RESET);
}

void	ft_banner_exit(void)
{
	printf("\n");
	printf(KYEL BLD"	 _________________________________________________            \n"RESET);
	printf(KYEL BLD"	|                                                 |          \n"RESET);
	printf(KYEL"	|                           _ _                   |          \n"RESET);
	printf(KYEL"	|                 _____   _(_) |_                 |        \n" RESET);
	printf(KRED"	|                / _ \\ \\_/ / | __|                |          \n"RESET);
	printf(KRED"	|               |  __/> _ <| | |_                 |   \n" RESET);
	printf(KRED BLD"	|                \\___/_/ \\_\\_|\\__|                |   \n" RESET);
	printf(KRED BLD"	|                                                 |   \n" RESET);
	printf(KRED BLD"	|_________________________________________________|   \n" RESET);
	printf("\n\n");
}

// VSCode NEON
/* void	ft_banner_start(void)
{
	printf("\n");
	printf(KCYN"	 _____________________________  __________________            \n"RESET);
	printf(KCYN"	|                              /                  |          \n"RESET);
	printf(KMAG"	|               _       _     /_          _ _     |          \n"RESET);
	printf(KMAG"	|     _ __ ___ (_)_ __ (_)___/| |__   ___| | |    |        \n" RESET);
	printf(KMAG BLD"	|    | '_ ` _ \\| | '_ \\| / _/_| '_ \\ / _ \\ | |    |          \n"RESET);
	printf(KMAG BLD"	|    | | | | | | | | | | \\_/__\\ | | |  __/ | |    |      \n" RESET);
	printf(KBLU BLD"	|    |_| |_| |_|_|_| |_|_|/___/_| |_|\\___|_|_|    |   \n" RESET);
	printf(KBLU BLD"	|                        /                        |   \n" RESET);
	printf(KBLU BLD"	|_______________________/                         |   \n" RESET);
	printf(KBLU BLD"	                                                  |   \n" RESET);
	printf("		    ...powered by " KMAG "gle-roux🐭 " RESET "&" KCYN " csenand🐭" KGRE"  |\n" RESET);
	printf(KGRE BLD"	__________________________________________________|   \n\n" RESET);
	printf("				...evaluated by " KBLU BLD EVALUATOR" \n\n" RESET);
	printf(KCYN"■■■■■■■■■■■■■■■■■"RESET KMAG"■■■■■■■■■■■■■■■■■"RESET KMAG BLD"■■■■■■■■■■■■■■■■■■"RESET KBLU BLD"■■■■■■■■■■■■■■■■■\n\n"RESET);
}

void	ft_banner_exit(void)
{
	printf("\n");
	printf(KCYN"	 _________________________________________________            \n"RESET);
	printf(KCYN"	|                                                 |          \n"RESET);
	printf(KMAG"	|                           _ _                   |          \n"RESET);
	printf(KMAG"	|                 _____   _(_) |_                 |        \n" RESET);
	printf(KMAG BLD"	|                / _ \\ \\_/ / | __|                |          \n"RESET);
	printf(KMAG BLD"	|               |  __/> _ <| | |_                 |   \n" RESET);
	printf(KBLU BLD"	|                \\___/_/ \\_\\_|\\__|                |   \n" RESET);
	printf(KBLU BLD"	|                                                 |   \n" RESET);
	printf(KBLU BLD"	|_________________________________________________|   \n" RESET);
	printf("\n\n");
} */

//VSCode BLUE
/* void	ft_banner_start(void)
{
	//printf(KRED BLD "\n😈😈😈 Welcome to miniꞩhell ... or should I say 🔥 MINIHELLLL 🔥 😈😈😈\n\n" RESET);
	printf("\n");
	printf(KGRE"	 _____________________________  __________________            \n"RESET);
	printf(KGRE"	|                              /                  |          \n"RESET);
	printf(KCYN"	|               _       _     /_          _ _     |          \n"RESET);
	printf(KCYN"	|     _ __ ___ (_)_ __ (_)___/| |__   ___| | |    |        \n" RESET);
	printf(KCYN BLD"	|    | '_ ` _ \\| | '_ \\| / _/_| '_ \\ / _ \\ | |    |          \n"RESET);
	printf(KCYN BLD"	|    | | | | | | | | | | \\_/__\\ | | |  __/ | |    |      \n" RESET);
	printf(KBLU"	|    |_| |_| |_|_|_| |_|_|/___/_| |_|\\___|_|_|    |   \n" RESET);
	printf(KBLU"	|                        /                        |   \n" RESET);
	printf(KBLU"	|_______________________/                         |   \n" RESET);
	printf(KBLU BLD"	                                                  |   \n" RESET);
	printf("		    ...powered by " KCYN "gle-roux🐭 " RESET "&" KBLU " csenand🐭" KBLU BLD"  |\n" RESET);
	printf(KBLU BLD"	__________________________________________________|   \n\n" RESET);
	printf("				...evaluated by " KBLU BLD EVALUATOR" \n\n" RESET);
	printf(KGRE BLD"■■■■■■■■■■■■■■■■■"RESET KCYN"■■■■■■■■■■■■■■■■■"RESET KBLU"■■■■■■■■■■■■■■■■■■"RESET KBLU BLD"■■■■■■■■■■■■■■■■■\n\n"RESET);
}

void	ft_banner_exit(void)
{
	printf("\n");
	printf(KGRE"	 _________________________________________________            \n"RESET);
	printf(KGRE"	|                                                 |          \n"RESET);
	printf(KCYN"	|                           _ _                   |          \n"RESET);
	printf(KCYN"	|                 _____   _(_) |_                 |        \n" RESET);
	printf(KCYN BLD"	|                / _ \\ \\_/ / | __|                |          \n"RESET);
	printf(KBLU"	|               |  __/> _ <| | |_                 |   \n" RESET);
	printf(KBLU"	|                \\___/_/ \\_\\_|\\__|                |   \n" RESET);
	printf(KBLU BLD"	|                                                 |   \n" RESET);
	printf(KBLU BLD"	|_________________________________________________|   \n" RESET);
	printf("\n\n");
} */

// TERMINAL
/* void	banner(void)
{
	//printf(KRED BLD "\n😈😈😈 Welcome to miniꞩhell ... or should I say 🔥 MINIHELLLL 🔥 😈😈😈\n\n" RESET);
	printf(KYEL"\n");
	printf(KYEL"	 _____________________________  __________________            \n"RESET);
	printf(KYEL"	|                              /                  |          \n"RESET);
	printf(KYEL BLD"	|               _       _     /_          _ _     |          \n"RESET);
	printf(KYEL BLD"	|     _ __ ___ (_)_ __ (_)___/| |__   ___| | |    |        \n" RESET);
	printf(KRED BLD"	|    | '_ ` _ \\| | '_ \\| / _/_| '_ \\ / _ \\ | |    |          \n"RESET);
	printf(KRED BLD"	|    | | | | | | | | | | \\_/__\\ | | |  __/ | |    |      \n" RESET);
	printf(KRED BLD"	|    |_| |_| |_|_|_| |_|_|/___/_| |_|\\___|_|_|    |   \n" RESET);
	printf(KRED"	|                        /                        |   \n" RESET);
	printf(KRED"	|_______________________/                         |   \n" RESET);
	printf(KRED"	                                                  |   \n" RESET);
	printf("		    ...powered by " KYEL "gle-roux🐭 " RESET "&" KRED " csenand🐭" KRED"  |\n" RESET);
	printf(KRED"	__________________________________________________|   \n\n" RESET);
	printf("				...evaluated by " KRED BLD "USER \n\n" RESET);
	printf(KYEL BLD"■■■■■■■■■■■■■■■■■"RESET KYEL"■■■■■■■■■■■■■■■■■"RESET KRED"■■■■■■■■■■■■■■■■■■"RESET KRED BLD"■■■■■■■■■■■■■■■■■\n\n"RESET);

} */
