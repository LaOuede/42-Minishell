#include "../../include/minishell.h"

void ft_pre_redir(t_exec *exec, int i)
{
	printf("---		ft_pre_redir starts\n");
	printf("---		i = %d \n", i);
	if (exec->cmd_nb > 1) // s'il y a plus qu'une cmd, donc des pipes
	{
		printf("\n--- 1er if statement \n");
		if (i > 0 && exec->pipes[i - 1][0]) //if there is a prev pipe, input will be the entry of the piep
			exec->input = exec->pipes[i - 1][0];
		printf("\n--- 2nd if statement \n");
		if (i < exec->pipes_nb) //if there is a pipe out, the output is the pipe
		{
			printf("\n--- Entered in 2nd if statement \n");
			exec->output = exec->pipes[i][1];
		}
	}
	if (exec->jct->fds_in[i])
		exec->input = exec->jct->fds_in[i];
	if (exec->jct->fds_out[i])
		exec->output = exec->jct->fds_out[i];
	printf("---		ft_pre_redir ends\n");
}

void	ft_make_pids(t_exec *exec, t_jct *jct)
{
	int	i;

	exec->pids = ft_calloc(exec->cmd_nb, sizeof(pid_t *));
	if (!exec->path_var)
		return ;
	i = -1;
	while (++i < exec->cmd_nb)
	{
		// printf("--- Enter while loop		---\n");
/* 		if (ft_check_builtin(exec, i) == true)
		{
			ft_is_builtin(exec, i);
			exit(EXIT_SUCCESS);
		} */
		ft_pre_redir(exec, i);
		exec->pids[i] = fork();
		if (exec->pids[i] == -1)
			perror("Error ! Pid creation failed:");
		// printf("--- Enter in ft_chils_proc	---\n");
		if (exec->pids[i] == 0)
		{
			//this is the child process
			ft_dup_proc(exec, i);
			ft_run_cmd(exec, jct, i);
		}
		// printf("--- Exit ft_chils_proc	---\n");
	}
	// printf("--- Exit while loop	---\n");
	ft_close_fds(exec);
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
	perror("Error ! Can't find path to program");
	path = NULL;
	return (path);
}

void	ft_run_cmd(t_exec *exec, t_jct *jct, int r)
{
	char	*path;
	char	**opt;
	char	***cmds;

	cmds = jct->tab;
	// fprintf(stderr, "cmd[%d][0] = %s\n", r, cmds[r][0]);
	// fprintf(stderr, "cmd[%d][1] = %s\n", r, cmds[r][1]);
	// fprintf(stderr, "cmd[%d][2] = %s\n", r, cmds[r][2]);
	opt = ft_split(cmds[r][0], ' ');
	path = ft_cmd_path(exec, opt[0]);
	fprintf(stderr, "path = %s\n", path);
	if (!path)
		free(path);
	else if (execve(path, opt, exec->envp) < 0)
		perror("Error ! Something went wrong while executing: ");
	//TODO ft_err exit if there is an error, so the below will never be executed
}

void	ft_dup_proc(t_exec *exec, int i)
{
	if (exec->cmd_nb == 1) // if 1 cmd and no pipes (so one cmd only)
	{
		fprintf(stderr, "\n---	1 cmd ONLY\n");
		if(exec->jct->tab[i][1]) //cas ou il y a une redirection in dans la cmd
			dup2(exec->jct->fds_in[i], STDIN_FILENO);
		if(exec->jct->tab[i][2]) //cas ou il y a une redirection out dans la cmd
			dup2(exec->jct->fds_out[i], STDOUT_FILENO);
	}
	if (exec->cmd_nb > 1) // s'il y a plus qu'une cmd, donc des pipes
	{
		if (i > 0 && exec->pipes[i - 1][0])
		{
			if(exec->input)
				dup2(exec->input, STDIN_FILENO);
			close(exec->input);
		}
		if (i < exec->pipes_nb)
		{
			if(exec->output)
				dup2(exec->output, STDOUT_FILENO);
			close(exec->output);
		}
	}
	ft_close_fds(exec);
}

void	ft_exec(t_exec *exec, t_jct *jct)
{
	int	i;
	int	status;

	if (ft_create_pipes(exec) == 2)
		return ;
	ft_make_pids(exec, jct);
	i = -1;
	while (++i < exec->cmd_nb)
		waitpid(exec->pids[i], &status, 0);
	//TODO clarifier le 2nd arg de waitpid
}
