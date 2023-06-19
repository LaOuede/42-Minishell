#include "../../include/minishell.h"

void	ft_copy_env(t_exec *exec, char **envp)
{
	int	i;
	int	j;

	i = 0;
	while (envp[i])
		i++;
	exec->envp = ft_calloc(sizeof(char **), i + 1);
	i = -1;
	j = 0;
	while (envp[++i])
		exec->envp[j++] = ft_strdup(envp[i]);
	exec->envp[j] = NULL;
}

char	*ft_free_2char(char **tab)
{
	int	i;

	i = -1;
	while (++i < 3)
		free(tab[i]);
	free(tab);
	return (0);
}

void	ft_free_3tab(t_jct *jct)
{
	int		i;
	char	***tmp;

	if (!jct->tab)
		return ;
	tmp = jct->tab;
	i = -1;
	while (++i < jct->cmd_nb)
		ft_free_2char(tmp[i]);
	free(tmp);
	jct->tab = NULL;
}

void	ft_free_exec(t_exec *exec)
{
	if (exec->envp)
		ft_free_tab_char(exec->envp);
	if (exec->path_var)
		ft_free_tab_char(exec->path_var);
	if (exec->pipes)
		ft_free_tab_int(exec->pipes, exec->pipes_nb);
	if (exec->pids)
		ft_freenull(exec->pids);
	// ft_freenull(exec);
}

int	ft_path_var_qty(char **path_var)
{
	int	i;

	i = 0;
	while (path_var[i])
		i++;
	return (i);
}

char	**ft_get_path(char **envp, int i)
{
	char	**path_var;
	char	**new_path_var;

	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (!envp[i])
	{
		new_path_var = ft_calloc(1, sizeof(char *));
		new_path_var[0] = ft_calloc(1, sizeof(char));
		return (new_path_var);
	}
	path_var = ft_split(&envp[i][5], ':');
	if (!path_var)
		return (NULL);
	new_path_var = ft_calloc(ft_path_var_qty(path_var) + 1, sizeof(char *));
	if (!new_path_var)
		return (NULL);
	i = -1;
	while (path_var[++i])
	{
		new_path_var[i] = ft_strjoin(path_var[i], "/");
		free(path_var[i]);
	}
	free(path_var);
	return (new_path_var);
}

t_exec	*ft_init_exec(char **envp, t_jct *jct)
{
	static t_exec	*exec;

	exec = malloc(sizeof(t_exec));
	if (!exec)
		perror(NULL);
	exec->envp = NULL;
	ft_copy_env(exec, envp);
	exec->path_var = ft_get_path(exec->envp, 0);
	exec->jct = ft_init_jct();
	exec->input = 0;
	exec->output = 0;
	exec->pids = 0;
	exec->pipes = 0;
	exec->cmd_nb = jct->cmd_nb;
	exec->pipes_nb = exec->cmd_nb - 1;
	return (exec);
}
