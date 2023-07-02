#include "../../include/minishell.h"

// VSCode - HELL
void	ft_banner_helle(void)
{
	printf("exit\n");
	printf(KYEL BLD"	 _____________________________________________\n"RT);
	printf(KYEL BLD"	|                                             |\n"RT);
	printf(KYEL"	|                         _ _                 |\n"RT);
	printf(KYEL"	|               _____   _(_) |_               |\n" RT);
	printf(KRED"	|              / _ \\ \\_/ / | __|              |\n"RT);
	printf(KRED"	|             |  __/> _ <| | |_               |\n" RT);
	printf(KRED BLD"	|              \\___/_/ \\_\\_|\\__|              |\n" RT);
	printf(KRED BLD"	|                                             |\n" RT);
	printf(KRED BLD"	|_____________________________________________|\n" RT);
	printf("\n\n");
}

void	ft_banner_neone(void)
{
	printf("exit\n");
	printf(KCYN"	 _____________________________________________\n"RT);
	printf(KCYN"	|                                             |\n"RT);
	printf(KMAG"	|                         _ _                 |\n"RT);
	printf(KMAG"	|               _____   _(_) |_               |\n" RT);
	printf(KMAG BLD"	|              / _ \\ \\_/ / | __|              |\n"RT);
	printf(KMAG BLD"	|             |  __/> _ <| | |_               |\n" RT);
	printf(KBLU BLD"	|              \\___/_/ \\_\\_|\\__|              |\n" RT);
	printf(KBLU BLD"	|                                             |\n" RT);
	printf(KBLU BLD"	|_____________________________________________|\n" RT);
	printf("\n\n");
}

void	ft_banner_exit(t_ms *ms)
{
	if (ms->banner == 1)
		ft_banner_helle();
	else
		ft_banner_neone();
}
