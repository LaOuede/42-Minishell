#include "../include/minishell.h"

// VSCode - HELL
void	ft_banner_hells(void)
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

void	ft_banner_helle(void)
{
	printf("exit\n");
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
void	ft_banner_neons(void)
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

void	ft_banner_neone(void)
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
}

void	ft_banner_start(t_ms *ms)
{
	size_t		nb;

	nb = (size_t)(&EVALUATOR);
	if (nb % 10 > 4)
	{
		ms->banner = 1;
		ft_banner_hells();
	}
	else
	{
		ms->banner = 0;
		ft_banner_neons();
	}
}

void	ft_banner_exit(t_ms *ms)
{
	if (ms->banner == 1)
		ft_banner_helle();
	else
		ft_banner_neone();
}

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
