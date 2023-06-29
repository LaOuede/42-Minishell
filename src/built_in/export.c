#include "../../include/minishell.h"

/* EXPORT
Definition :
	Export is used to mark variables and functions to be passed to child processes.
	Basically, a variable will be included in child process environments
	without affecting other environments.
Prototype :
	export [name[=value] ...]
*/
char	**ft_export_var(char **env, char *cmd)
{
	char	**new_env;
	int		i;
	int		j;
	int 	len_env;
	int 	len_env2 = 0;


	i = 0;
	j = 0;
	len_env = ft_get_ac(env);
	printf("len: %d\n", len_env);
	new_env = ft_calloc(len_env + 2, sizeof(char **));
	printf("len2: %d\n", len_env2);
	while(env[i])
	{
		new_env[j++] = ft_strdup(env[i++]);
		// j++;
		// i++;
	}
	printf("cmd; %s\n", cmd);
	printf("j: %d\n", j);
	new_env[j++] = ft_strdup(cmd);
	new_env[j] = NULL;
	printf("j: %d\n", j);
	ft_free_tab_char(env);
	return (new_env);
}

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
	printf("ac; %d\n", ac);
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
		printf("ft_export_var starts\n");
		ms->envp = ft_export_var(ms->envp, cmd[i]);
		printf("ft_export_var ends\n");
		//TODO do the rest

	}
}
