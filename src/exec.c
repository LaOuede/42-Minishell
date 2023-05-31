#include "../include/minishell.h"

void	ft_run_cmd(t_exec *exec);

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
		{
			//this is the child process
			ft_dup_process(exec, i);
			ft_run_cmd(exec);
		}	

		// printf("--- Exit ft_chils_proc	---\n");
	}
	if(exec->fl_redirin == 1)
		close(exec->input);
	if(exec->fl_redirout == 1)
		close(exec->output);
	ft_close_pipes(exec);
}

char	*ft_cmd_path(t_exec *exec, char *cmds)
{
	char	*path;
	int		i;

	if (access(cmds, F_OK | X_OK) == 0)
		return (ft_strdup(cmds));
	path = ft_strjoin("./", cmds);
	if (access(path, F_OK | X_OK) == 0)
		return (path);
	if (path)
		free(path);
	i = -1;
	while (exec->path_var[++i])
	{
		path = ft_strjoin(exec->path_var[i], cmds);
		if (access(path, F_OK | X_OK) == 0)
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
	// char	*cmds[1] = {"ls"};
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
	//TODO ft_err exit if there is an error, so the below will never be executed
	i = 0;
	while (exec->path_var[i])
		free(exec->path_var[i++]);
	free(exec->path_var[i++]);
	free(exec->path_var);
	exec->path_var = NULL;
}

void	ft_dup_process(t_exec *exec, int i)
{
	exec->index = i;
	if (exec->index == 0)
	{
		if (exec->fl_redirin == 1)
			dup2(exec->input, STDIN_FILENO);
		else
			dup2(0, STDIN_FILENO);
	}
	else
		dup2(exec->pipes[i - 1][0], STDIN_FILENO);
	if (exec->index == exec->cmd_nb - 1)
	{
		if(exec->fl_redirout == 1)
			dup2(exec->output, STDOUT_FILENO);
		dup2(1, STDOUT_FILENO);
	}
	else
		dup2(exec->pipes[i][1], STDOUT_FILENO);
	ft_close_pipes(exec);
}

void	ft_exec(t_exec *exec)
{
	int	i;
	int status;
	
	//TODO remove the below
	exec->fl_redirin = 1;
	exec->fl_redirout = 1;
	exec->input  = open("Makefile", O_RDONLY);
	if (exec->input == -1)
				ft_err("Error exec->file", exec);
	exec->input  = open("supp.txt", O_RDONLY);
	if (exec->input == -1)
				ft_err("Error exec->file", exec);
	exec->output = open("out", O_RDWR | O_CREAT | O_TRUNC, 0644);
	//TODO remove the above

	ft_create_pipes(exec);
	ft_make_pids(exec);
	i = -1;
	while (++i < exec->cmd_nb)
		waitpid(exec->pids[i], &status, 0);
	//TODO clarifier le 2nd arg de waitpid
	// ft_free_data(exec);
}

/*
void	ft_exec(t_exec *exec)
{
	int	i;
	int status;
	
	printf("\n--- ft_create_pipes : Pipe creation starts ---\n");
	ft_create_pipes(exec);
	printf("--- ft_create_pipes : Pipe creation ends ---\n\n");

	printf("--- ft_make_pids : PIDs creation starts	---\n");
	ft_make_pids(exec);
	printf("--- ft_make_pids : PIDs creation ends	---\n\n");
	i = -1;
	while (++i < exec->cmd_nb)
		waitpid(exec->pids[i], &status, 0);
	//TODO clarifier le 2nd arg de waitpid
	// ft_free_data(exec);
}
*/