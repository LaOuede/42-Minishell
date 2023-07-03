#include "../../include/minishell.h"

int	ft_get_ac(char **cmd)
{
	int	j;

	j = 0;
	while (cmd[j])
		j++;
	return (j);
}

void	ft_print_err(t_ms *ms, char *cmd)
{
	printf("export: %s not a valid identifier\n", cmd);
	ms->flexit = EXIT_FAILURE;
}

int	ft_find_index_var(t_ms *ms, char *cmd)
{
	int	i;
	int	len;

	if (!cmd || !ft_strchr(cmd, '='))
		return (0);
	len = 0;
	while (cmd[len] != '=' && cmd[len])
		len++;
	i = 0;
	while (ms->envp[i])
	{
		if (!ft_strncmp(ms->envp[i], cmd, len + 1))
			return (i);
		i++;
	}
	return (0);
}

char	*ft_getenv(t_ms *ms, char *home)
{
	int		index;
	char	**path_var;
	char	*tmp;

	tmp = NULL;
	path_var = NULL;
	if (!ms->envp)
		return (NULL);
	index = ft_isexist(ms, home);
	if (index < 0)
		return (NULL);
	path_var = ft_split(ms->envp[index], '=');
	if (path_var[1])
	{
		tmp = ft_strdup(path_var[1]);
		ft_free_tab_char(path_var);
		return (tmp);
	}
	else
	{
		ft_free_tab_char(path_var);
		return (NULL);
	}
}
