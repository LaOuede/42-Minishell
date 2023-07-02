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
	return(new_envp);
}

char	**ft_export_var(t_ms *ms, char **env, char *cmd)
{
	char	**new_envp_env;
	int		i;
	int		j;
	int		len_env;

	i = 0;
	j = 0;
	len_env = ft_get_ac(env);
	new_envp_env = ft_calloc_msh(len_env + 2, sizeof(char *), ms);
	while(env[i])
		new_envp_env[j++] = ft_strdup(env[i++]);
	new_envp_env[j++] = ft_strdup(cmd);
	new_envp_env[j] = NULL;
	ft_free_tab_char(env);
	return (new_envp_env);
}

int		ft_find_index_var(t_ms *ms, char *cmd)
{
	int	i;
	int	len;

	if (!cmd || !ft_strchr(cmd, '='))
		return (0);
	len = 0;
	while(cmd[len] != '=' && cmd[len])
		len++;
	i = 0;
	while(ms->envp[i])
	{
		if(!ft_strncmp(ms->envp[i], cmd, len + 1))
			return (i);
		i++;
	}
	return (0);
}

bool	ft_valid_ex(t_ms *ms, char *cmd) 
{
	int		i;
	char	**var;

	if (cmd[0] == '=')
	{
		printf("export: %s not a valid identifier\n", cmd);
		ms->flexit = EXIT_FAILURE;
		return (false);
	}
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
			printf("export: %s not a valid identifier\n", cmd);
			ms->flexit = EXIT_FAILURE;
			ft_free_tab_char(var);
			return (false);
		}
	}
	ft_free_tab_char(var);
	return (true);
}

void	ft_msh_export(t_ms *ms, char **cmd)
{
	int		ac;
	int 	i;
	int		index_var;
	char	*tmp;

	ac = ft_get_ac(cmd);
	i = 0;
	if (ac <= 1)
		while ((ms->envp[++i]))
			printf("declare -x %s\n", ms->envp[i]);
	i = 1;
	tmp = NULL;
	while (i < ac)
	{
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
		i++;
	}
}
