#include "../../include/minishell.h"

/* EXPORT
Definition :
	Export is used to mark variables and functions to be passed to child processes.
	Basically, a variable will be included in child process environments
	without affecting other environments.
Prototype :
	export [name[=value] ...]
*/

char	*ft_replace_var(t_ms *ms, char *cmd, int index_var)
{
	char	*new_envp;

	new_envp = ft_strdup(cmd);
	free(ms->envp[index_var]);
	return (new_envp);
}

char	**ft_export_var(t_ms *ms, char **env, char *cmd)
{
	int		i;
	int		j;
	int		len_env;
	char	**new_envp_env;

	i = 0;
	j = 0;
	len_env = ft_get_ac(env);
	new_envp_env = ft_calloc_msh(len_env + 2, sizeof(char *), ms);
	while (env[i])
		new_envp_env[j++] = ft_strdup(env[i++]);
	new_envp_env[j++] = ft_strdup(cmd);
	new_envp_env[j] = NULL;
	ft_free_tab_char(env);
	return (new_envp_env);
}

bool	ft_valid_ex(t_ms *ms, char *cmd)
{
	int		i;
	char	**var;

	var = NULL;
	if (cmd[0] == '=')
		return (ft_print_err(ms, cmd), false);
	var = ft_split(cmd, '=');
	i = -1;
	while (var[0][++i])
	{
		if (!ft_strchr(cmd, '='))
		{
			ft_free_tab_char(var);
			return (false);
		}
		if (!ft_1st_part_valid(ms, var[0]))
		{
			ft_print_err(ms, cmd);
			ft_free_tab_char(var);
			return (false);
		}
	}
	ft_free_tab_char(var);
	return (true);
}

void	ft_export_loop(t_ms *ms, char **cmd, int i)
{
	int		index_var;
	char	*tmp;

	tmp = NULL;
	if (ft_valid_ex(ms, cmd[i]))
	{
		index_var = ft_find_index_var(ms, cmd[i]);
		if (index_var < 0)
			return ;
		tmp = ft_trim_arg(cmd[i]);
		if (index_var > 0)
			ms->envp[index_var] = ft_replace_var(ms, tmp, index_var);
		else
			ms->envp = ft_export_var(ms, ms->envp, tmp);
		tmp = ft_freenull(tmp);
	}
}

void	ft_msh_export(t_ms *ms, char **cmd)
{
	int		i;
	int		ac;

	ac = ft_get_ac(cmd);
	i = 0;
	if (ac <= 1)
		while ((ms->envp[++i]))
			printf("declare -x %s\n", ms->envp[i]);
	i = 0;
	while (++i < ac)
		ft_export_loop(ms, cmd, i);
}
