#include "../../include/minishell.h"

/* EXPORT
Definition :
	Export is used to mark variables and functions to be passed to child processes.
	Basically, a variable will be included in child process environments
	without affecting other environments.
Prototype :
	export [name[=value] ...]
*/

// int		ft_find_index_var(t_ms *ms, char *cmd)
// {
// 	int i;

// 	i = 0;
// 	while(ms->envp[i])
// 	{
// 		if (ft_strncmp())
// 		i++;
// 	}
// }

char	**ft_export_var(t_ms *ms, char **env, char *cmd)
{
	char	**new_env;
	int		i;
	int		j;
	int		len_env;
	int		len_env2 = 0;


	i = 0;
	j = 0;
	len_env = ft_get_ac(env);
	printf("len: %d\n", len_env);
	new_env = ft_calloc_msh(len_env + 2, sizeof(char *), ms);
	printf("len2: %d\n", len_env2);
	while(env[i])
		new_env[j++] = ft_strdup(env[i++]);
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
	{
		printf("export: %s not a valid identifier\n", cmd);
		return (false);
	}
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
			if (ms->jct->cmd_nb == 1)
				return ;
			else
				ft_exit_free(ms, 1, 0);
		}
		printf("ft_export_var starts\n");
		ms->envp = ft_export_var(ms, ms->envp, cmd[i]);
		printf("ft_export_var ends\n");
		//TODO do the rest
	}
}
