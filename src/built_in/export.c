#include "../../include/minishell.h"

/* EXPORT
Definition :
	Export is used to mark variables and functions to be passed to child processes.
	Basically, a variable will be included in child process environments
	without affecting other environments.
Prototype :
	export [name[=value] ...]
*/
bool	ft_valid_ex(char *cmd)
{
	if ((!ft_isalpha(cmd[0]) && cmd[0] != '_') || !ft_strchr(cmd, '='))
		return (false);
	// free(cmd);
	return (true);
}

void	ft_msh_export(t_ms *ms, char **cmd)
{
	int	ac;
	int i;
	ac = ft_get_ac(cmd);

	i = 0;
	if (ac == 1)
		while ((ms->envp[++i]))
			printf("declare -x %s\n", ms->envp[i]);
	i = 0;
	while (cmd[++i])
	{
		if (!ft_valid_ex(cmd[i]))
		{
			if (ms->exec->cmd_nb == 1)
				ft_exit_free(ms, 1);
			else
			{
				ft_free_all(ms);
				return ;
			}
		}
		//TODO do the rest
	}
}
