#include "../../include/minishell.h"

void	ft_reset_and_close(t_ms *ms)
{
	dup2(ms->exec->fd_in, STDIN_FILENO);
	dup2(ms->exec->fd_out, STDOUT_FILENO);
	ft_close_fds(ms);
}

void	ft_copy_env(t_jct *jct, char **envp)
{
	int	i;
	int	j;

	i = 0;
	while (envp[i])
		i++;
	jct->envp = ft_calloc(sizeof(char **), i + 1);
	i = -1;
	j = 0;
	while (envp[++i])
		jct->envp[j++] = ft_strdup(envp[i]);
	jct->envp[j] = NULL;
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

void	ft_reset_exec(t_ms *ms)
{
	ms->exec->input = 0;
	ms->exec->output = 0;
	ft_freenull(ms->exec->pids);
	ms->exec->pids = 0;
	ft_free_tab_int(ms->exec->pipes, ms->exec->pipes_nb);
	ms->exec->pipes = 0;
	ms->exec->pipes_nb = 0;
}

t_exec	*ft_init_exec(t_ms *ms)
{
	t_exec	*exec;

	exec = malloc(sizeof(t_exec));
	if (!exec)
		perror(NULL);
	exec->envp = ms->jct->envp;
	exec->path_var = ft_get_path(exec->envp, 0);
	exec->input = 0;
	exec->output = 0;
	exec->pids = 0;
	exec->pipes = 0;
	exec->pipes_nb = 0;
	return (exec);
}
