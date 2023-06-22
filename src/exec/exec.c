#include "../../include/minishell.h"

void	ft_make_pids(t_exec *exec)
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
/* 		{
		if (ft_check_builtin(exec, i) == true)
			ft_is_builtin(exec, i);
			exit(EXIT_SUCCESS);
		} */
		if (ft_pre_redir(exec, i) == 1)
			exit(127); //TODO mettre le vrai exit status
		exec->pids[i] = fork();
		if (exec->pids[i] == -1)
			perror("Error ! Pid creation failed:");
		if (exec->pids[i] == 0)
		{
			ft_dup_proc(exec, i);
			ft_run_cmd(exec, i);
		}
	}
	ft_reset_and_close(exec);
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

void	ft_run_cmd(t_exec *exec, int r)
{
	char	*path;
	char	**opt;

	opt = ft_split(exec->jct->tab[r][0], ' ');
	path = ft_cmd_path(exec, opt[0]);
	if (!path)
	{
		ft_free_tab_char(opt);
		exit(127);
	}
	if (execve(path, opt, exec->envp) < 0)
	{
		perror("Error ! Something went wrong while executing");
		free(path);
		ft_free_tab_char(opt);
		exit(127);
	}
}

void	ft_dup_proc(t_exec *exec, int i)
{
	if (exec->cmd_nb == 1) // if 1 cmd and no pipes (so one cmd only)
	{
		if (exec->jct->tab[i][1])
			dup2(exec->jct->fds_in[i], STDIN_FILENO);
		if (exec->jct->tab[i][2])
			dup2(exec->jct->fds_out[i], STDOUT_FILENO);
	}
	else // s'il y a plus qu'une cmd, donc des pipes
	{
		if (i > 0)
			if (exec->input)
				dup2(exec->input, STDIN_FILENO);
		if (i < exec->pipes_nb)
			if (exec->output)
				dup2(exec->output, STDOUT_FILENO);
		if (exec->jct->tab[i][1])
			dup2(exec->jct->fds_in[i], STDIN_FILENO);
		if (exec->jct->tab[i][2])
			dup2(exec->jct->fds_out[i], STDOUT_FILENO);
	}
	ft_close_fds(exec);
}

void	ft_exec(t_exec *exec)
{
	int	i;

	if (ft_mem_pipes(exec) == 2)
		return ;
	ft_make_pids(exec);
	i = -1;
	while (++i < exec->cmd_nb)
		waitpid(exec->pids[i], NULL, 0);
	//TODO clarifier le 2nd arg de waitpid
}
