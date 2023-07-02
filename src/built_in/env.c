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
	if (DEBUG)
		printf(KYEL "-------------------- FT_MSH_ENV" KGRN " START " RT KYEL "--------------------\n" RT);
	int	i;

	if (cmd[1])
	{
		ft_putstr_fd("Too many args - Usage: env [no opt/args]\n", 2);
		exit(127);
	}
	i = -1;
	if (ms->envp)
		while (ms->envp[++i])
			printf("%s\n", ms->envp[i]);
	if (DEBUG)
		printf(KYEL "-------------------- FT_MSH_ENV" KRED " END " RT KYEL "--------------------\n" RT);
}
