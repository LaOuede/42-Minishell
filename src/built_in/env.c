#include "../../include/minishell.h"

/* ENV
Definition :
	The env command allows you to display your current environment
	or run a specified command in a changed environment.
	If no flags or parameters are specified, the env command displays
	your current environment, showing one Name=Value pair per line.
Prototype :
	env
*/

void	ft_msh_env(t_ms *ms, char **cmd)
{
	(void)cmd;
	printf(KYEL "-------------------- FT_MSH_ENV" KGRN " START " RESET KYEL "--------------------\n" RESET);
	int	i;

	//TODO mettre protection si pas de env
	i = -1;
	if (ms->exec->envp)
	{
		while (ms->exec->envp[++i])
			printf("%s\n", ms->exec->envp[i]);
		if (ms->jct->cmd_nb > 1)
			exit(EXIT_SUCCESS);
	}
	printf(KYEL "-------------------- FT_MSH_ENV" KRED " END " RESET KYEL "--------------------\n" RESET);
}
