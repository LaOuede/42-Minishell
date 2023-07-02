#include "../../include/minishell.h"

// VSCode - HELL
void	ft_banner_hells(void)
{
	printf("\n");
	printf(KYEL BLD"	 _____________________________________________\n");
	printf(KYEL BLD"	|                            /                |\n");
	printf(KYEL BLD"	|             _       _     /_          _ _   |\n");
	printf(KYEL "	|   _ __ ___ (_)_ __ (_)___/| |__   ___| | |  |\n" RT);
	printf(KYEL "	|  | '_ ` _ \\| | '_ \\| / _/_| '_ \\ / _ \\ | |  |\n");
	printf(KRED "	|  | | | | | | | | | | \\_/__\\ | | |  __/ | |  |\n" RT);
	printf(KRED BLD"	|  |_| |_| |_|_|_| |_|_|/___/_| |_|\\___|_|_|  |\n" RT);
	printf(KRED BLD"	|                      /                      |\n" RT);
	printf(KRED BLD"	|_____________________/                       |\n" RT);
	printf(KRED BLD"	                                              |\n" RT);
	printf("		...powered by " KYEL "gle-roux🐭 " RT "&"\
		KRED " csenand🐭" KRED BLD"  |\n" RT);
	printf(KRED BLD"	______________________________________________|\n\n" RT);
	printf("			...evaluated by " KRED BLD EVALUATOR" \n\n" RT);
	printf(KYEL BLD"■■■■■■■■■■■■■■■"RT KYEL"■■■■■■■■■■■■■■■■"\
	RT KRED"■■■■■■■■■■■■■■■■■"RT KRED BLD"■■■■■■■■■■■■■■■\n\n"RT);
}

// VSCode NEON
void	ft_banner_neons(void)
{
	printf("\n");
	printf(KCYN"	 _____________________________________________\n");
	printf(KCYN"	|                            /                |\n");
	printf(KMAG"	|             _       _     /_          _ _   |\n");
	printf(KMAG "	|   _ __ ___ (_)_ __ (_)___/| |__   ___| | |  |\n" RT);
	printf(KMAG BLD"	|  | '_ ` _ \\| | '_ \\| / _/_| '_ \\ / _ \\ | |  |\n");
	printf(KMAG BLD"	|  | | | | | | | | | | \\_/__\\ | | |  __/ | |  |\n" RT);
	printf(KBLU BLD"	|  |_| |_| |_|_|_| |_|_|/___/_| |_|\\___|_|_|  |\n" RT);
	printf(KBLU BLD"	|                      /                      |\n" RT);
	printf(KBLU BLD"	|_____________________/                       |\n" RT);
	printf(KBLU BLD"	                                              |\n" RT);
	printf("		...powered by " KMAG "gle-roux🐭 " RT "&"\
		KCYN " csenand🐭" KBLU BLD"  |\n" RT);
	printf(KBLU BLD"	______________________________________________|\n\n" RT);
	printf("			...evaluated by " KBLU BLD EVALUATOR" \n\n" RT);
	printf(KCYN"■■■■■■■■■■■■■■■"RT KMAG"■■■■■■■■■■■■■■■■"\
	RT KMAG BLD"■■■■■■■■■■■■■■■■■"RT KBLU BLD"■■■■■■■■■■■■■■■\n\n"RT);
	printf("\n");
}

/* void	ft_banner_neons(void)
{
	printf(KBLU BLD"	|                        / \
		                       |   \n" RT);
	printf(KBLU BLD"	|_______________________/  \
		                      |   \n" RT);
	printf(KBLU BLD"	                            \
		                      |   \n" RT);
	printf("		    ...powered by " KMAG "gle-roux🐭 "\
		 RT "&" KCYN " csenand🐭" KGRE"  |\n" RT);
	printf(KGRE BLD"	______________________________\
		____________________|   \n\n" RT);
	printf("				...evaluated by " \
		KBLU BLD EVALUATOR" \n\n" RT);
	printf(KCYN"■■■■■■■■■■■■■■■■■"RT KMAG"■■■■■■■■■■■■■■■■■"RT \
		KMAG BLD"■■■■■■■■■■■■■■■■■■"RT KBLU BLD"■■■■■■■■■■■■■■■■■\n\n"RT);
} */

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
