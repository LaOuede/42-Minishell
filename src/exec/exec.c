#include "../../include/minishell.h"

void	ft_make_pids(t_ms *ms)
{
	int	i;

	if (!ms->exec->path_var)
		return ;
	ms->exec->pids = ft_calloc(ms->jct->cmd_nb, sizeof(pid_t *));
	ms->exec->fd_in = dup(STDIN_FILENO);
	ms->exec->fd_out = dup(STDOUT_FILENO);
	i = -1;
	while (++i < ms->jct->cmd_nb)
	{
		// printf("--- Enter while loop		---\n");
		// if (ft_is_builtin(ms->exec, i))
		// {
		// 	ft_is_builtin(ms->exec, i);
		// 	exit(EXIT_SUCCESS);
		// }
		if (ft_pre_redir(ms, i) == 1)
			exit(127); //TODO mettre le vrai exit status
		ms->exec->pids[i] = fork();
		if (ms->exec->pids[i] == -1)
			perror("Error ! Pid creation failed:");
		ft_close_old_pipes(ms->exec, i);
		if (ms->exec->pids[i] == 0)
		{
			ft_dup_proc(ms, i);
			ft_run_cmd(ms, i);
		}
	}
	ft_reset_and_close(ms);
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
		ft_freenull(path);
	i = -1;
	while (exec->path_var[++i])
	{
		path = ft_strjoin(exec->path_var[i], cmds);
		if (access(path, F_OK | X_OK) == 0)
			return (path);
		if (path)
			ft_freenull(path);
	}
	perror("Error ! Can't find path to program");
	path = NULL;
	return (path);
}

void	ft_run_cmd(t_ms *ms, int r)
{
	char	*path;
	char	**opt;
	char	**envp;

	opt = ft_split(ms->jct->tab[r][0], ' ');
	path = ft_cmd_path(ms->exec, opt[0]);
	envp = ms->jct->envp;
	if (!path)
	{
		ft_free_tab_char(opt);
		ft_free_all(ms);
		exit(127);
	}
	ft_free_child(ms);
	if (execve(path, opt, envp) < 0)
	{
		perror("Error ! Something went wrong while executing");
		free(path);
		ft_free_tab_char(opt);
		ft_free_all(ms);
		exit(127);
	}
}

void	ft_dup_proc(t_ms *ms, int i)
{
	if (ms->jct->cmd_nb == 1) // if 1 cmd and no pipes (so one cmd only)
	{
		if (ms->jct->tab[i][1])
			dup2(ms->jct->fds_in[i], STDIN_FILENO);
		if (ms->jct->tab[i][2])
			dup2(ms->jct->fds_out[i], STDOUT_FILENO);
	}
	else // s'il y a plus qu'une cmd, donc des pipes
	{
		if (i > 0)
			if (ms->exec->input)
				dup2(ms->exec->input, STDIN_FILENO);
		if (i < ms->exec->pipes_nb)
			if (ms->exec->output)
				dup2(ms->exec->output, STDOUT_FILENO);
		if (ms->jct->tab[i][1])
			dup2(ms->jct->fds_in[i], STDIN_FILENO);
		if (ms->jct->tab[i][2])
			dup2(ms->jct->fds_out[i], STDOUT_FILENO);
	}
	ft_close_fds(ms);
}

void	ft_exec(t_ms *ms)
{
	int	i;
	int	status;

	ft_init_sig(EXEC);
	if (ft_mem_pipes(ms) == 2)
		return ;
	ft_make_pids(ms);
	i = -1;
	while (++i < ms->jct->cmd_nb)
	{
		waitpid(ms->exec->pids[i], &status, 0);
		if (WIFEXITED(status))
			ms->flexit = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			ms->flexit = WTERMSIG(status);
	}
	ft_reset_exec(ms);
	//TODO clarifier le 2nd arg de waitpid
}
