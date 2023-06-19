#include "../../include/minishell.h"

void	ft_make_pids(t_exec *exec, t_jct *jct)
{
	int	i;

	exec->pids = ft_calloc(exec->cmd_nb, sizeof(pid_t *));
	if (!exec->path_var)
		return ;
	exec->fd_in = dup(STDIN_FILENO);
	exec->fd_out = dup(STDOUT_FILENO);
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
	dup2(exec->fd_in, STDIN_FILENO);
	dup2(exec->fd_out, STDOUT_FILENO);
	ft_close_fds(exec);
	// printf("--- Exit while loop	---\n");
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
		//cas ou il y a une redirection in dans la cmd
		if (exec->jct->tab[i][1])
			dup2(exec->jct->fds_in[i], STDIN_FILENO);
		//cas ou il y a une redirection out dans la cmd
		if (exec->jct->tab[i][2])
			dup2(exec->jct->fds_out[i], STDOUT_FILENO);
	}
	if (exec->cmd_nb > 1) // s'il y a plus qu'une cmd, donc des pipes
	{
		if (i > 0 && exec->pipes[i - 1][0])
		{
			if (exec->input)
				dup2(exec->input, STDIN_FILENO);
			close(exec->input);
		}
		if (i < exec->pipes_nb)
		{
			if (exec->output)
				dup2(exec->output, STDOUT_FILENO);
			close(exec->output);
		}
	}
	ft_close_fds(exec);
}

void	ft_exec(t_exec *exec, t_jct *jct)
{
	int	i;

	if (ft_create_pipes(exec) == 2)
		return ;
	ft_make_pids(exec, jct);
	i = -1;
	while (++i < exec->cmd_nb)
		waitpid(exec->pids[i], NULL, 0);
	//TODO clarifier le 2nd arg de waitpid
}
