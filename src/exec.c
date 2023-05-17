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
		// printf("--- Enter in ft_chils_proc	---\n");
		if (exec->pids[i] == 0)
			ft_child_process(exec, i);
		// printf("--- Exit ft_chils_proc	---\n");
	}
	// close(exec->input);
	// close(exec->output);
	ft_close_pipes(exec);
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

	cmds = ft_split(exec->readline[exec->index], ' ');
	// int j = -1;
	// while(exec->readline[++j])
	// 	printf("exec->readline[%d] : %s\n", j, exec->readline[j]);
	// j = -1;
	// while(cmds[++j])
	// 	printf("cmds[%d] : %s\n", j, cmds[j]);
	path = ft_cmd_path(exec, cmds[0]);
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
	if (exec->cmd_nb == 1)
		ft_run_cmd(exec);
	else
	{
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
		// close(exec->input);
		// close(exec->output);
		ft_close_pipes(exec);
		ft_run_cmd(exec);
	}
}

void	ft_exec(t_exec *exec)
{
	int	i;
	
	// printf("\n--- ft_create_pipes : Pipe creation starts ---\n");
	ft_create_pipes(exec);
	// printf("--- ft_create_pipes : Pipe creation ends ---\n\n");

	// printf("--- ft_make_pids : PIDs creation starts	---\n");
	ft_make_pids(exec);
	// printf("--- ft_make_pids : PIDs creation ends	---\n\n");
	i = -1;
	while (++i < exec->cmd_nb)
		waitpid(exec->pids[i], NULL, 0);
	//TODO clarifier le 2nd arg de waitpid
	// ft_free_data(exec);
}