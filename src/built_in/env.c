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

void	ft_msh_env(t_exec *exec)
{
	printf(KYEL "-------------------- FT_MSH_ENV" KGRN " START " RESET KYEL "--------------------\n" RESET);
	int	i;

	i = -1;
	if (exec->envp)
	{
		while (exec->envp[++i])
			printf("%s\n", exec->envp[i]);
		if (exec->jct->cmd_nb == 1)
			exit(EXIT_SUCCESS);
	}
	printf(KYEL "-------------------- FT_MSH_ENV" KRED " END " RESET KYEL "--------------------\n" RESET);
}
