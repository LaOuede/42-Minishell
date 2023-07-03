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
	int	i;

	(void)cmd;
	if (cmd[1])
	{
		ft_putstr_fd("Too many args - Usage: env [no opt/args]\n", 2);
		ms->flexit = 127;
		ft_exit_free(ms, ms->flexit, 0);
	}
	i = -1;
	if (ms->envp)
		while (ms->envp[++i])
			printf("%s\n", ms->envp[i]);
}
