#include "../include/minishell.h"

void	ft_make_pids(t_exec *exec)
{
	int	i;

	exec->pids = ft_calloc(exec->cmd_nb, sizeof(pid_t *));
	if (!exec->path_var)
		return ;
	i = -1;
	while (++i < exec->cmd_nb)
	{
		exec->pids[i] = fork();
		if (exec->pids[i] == -1)
			ft_err("Something went wrong during pid process:", exec);
		if (exec->pids[i] == 0)
			ft_child_process(exec, i);
	}
	if (exec->pipes)
	{
		close(exec->input);
		close(exec->output);
		ft_close_pipes(exec);
	}
}

char	*ft_cmd_path(t_exec *exec, char *cmds)
{
	char	*path;
	int		i;

	if (access(cmds, X_OK | F_OK) == 0)
		return (ft_strdup(cmds));
	path = ft_strjoin("./", cmds);
	if (access(path, X_OK | F_OK) == 0)
		return (path);
	if (path)
		free(path);
	i = -1;
	while (exec->path_var[++i])
	{
		path = ft_strjoin(exec->path_var[i], cmds);
		if (access(path, X_OK | F_OK) == 0)
			return (path);
		if (path)
			free(path);
	}
	ft_err("Error ! Can't find path to program", exec);
	path = NULL;
	return (path);
}

void	ft_run_cmd(t_exec *exec)
{
	char	*path;
	char	**cmds;
	int		i;

	cmds = exec->readline; 
	path = ft_cmd_path(exec, cmds[0]);
	printf("execve will be executed");
	if (!path)
		free(path);
	else if (execve(path, cmds, exec->envp) < 0)
		ft_err("Error ! Something went wrong while executing: ", exec);
	i = 0;
	while (exec->path_var[i])
		free(exec->path_var[i++]);
	free(exec->path_var[i++]);
	free(exec->path_var);
	exec->path_var = NULL;
}

void	ft_child_process(t_exec *exec, int i)
{
	exec->index = i;
	if (exec->index == 0)
	{
		if (exec->input == -1)
		{
			ft_close_pipes(exec);
			close(exec->input);
			close(exec->output);
			ft_err("Couldn't open the input file", exec);
		}
		dup2(exec->input, STDIN_FILENO);
	}
	else
		dup2(exec->pipes[i - 1][0], STDIN_FILENO);
	if (exec->index == exec->cmd_nb - 1)
		dup2(exec->output, STDOUT_FILENO);
	else
		dup2(exec->pipes[i][1], STDOUT_FILENO);
	close(exec->input);
	close(exec->output);
	ft_close_pipes(exec);
	ft_run_cmd(exec);
}

void	ft_exec(t_exec *exec)
{
	ft_create_pipes(exec);
	ft_make_pids(exec);
}