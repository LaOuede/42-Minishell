#include "../../include/minishell.h"

void	ft_dup_and_run(t_ms *ms, int i, int builtin_fts)
{
	if (ms->exec->pids[i] == 0)
	{
		ft_dup_proc(ms, i);
		if(builtin_fts)
		{
			ms->exec->builtin->fts[builtin_fts](ms, ms->exec->builtin_cmd);
			exit(0);
		}
		ft_run_cmd(ms, i);
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
		if (ms->jct->fd_hd)
			dup2(ms->jct->fd_hd, STDIN_FILENO);
	}
	else // s'il y a plus qu'une cmd, donc des pipes
	{
		// if (i == 0)
		// 	if (ms->jct->fd_hd){
		// 		// ms->jct->fd_hd = open("/tmp/here_doc", O_RDONLY, 0666);
		// 		fprintf(stderr, "fd_hd: %d\n", ms->jct->fd_hd);
		// 		fprintf(stderr, "dup2: %d\n", dup2(ms->jct->fd_hd, STDIN_FILENO));
		// 	}
		if (i > 0)
		{
			if (ms->jct->fd_hd)
				dup2(ms->jct->fd_hd, STDIN_FILENO);
			else if (ms->exec->input)
				dup2(ms->exec->input, STDIN_FILENO);
		}
		if (i < ms->exec->pipes_nb)
			if (ms->exec->output)
				dup2(ms->exec->output, STDOUT_FILENO);
		if (ms->jct->tab[i][1])
			dup2(ms->jct->fds_in[i], STDIN_FILENO);
		if (ms->jct->tab[i][2])
			dup2(ms->jct->fds_out[i], STDOUT_FILENO);
	}
	ft_close_all(ms);
}

void	ft_make_pids(t_ms *ms)
{
	int	i;
	int builtin_fts;

	if (!ms->exec->path_var)
		return ;
	ms->exec->pids = ft_calloc(ms->jct->cmd_nb, sizeof(pid_t *));
	i = -1;
	while (++i < ms->jct->cmd_nb)
	{
		if(DEBUG)
			printf("--- Enter while loop		---\n");
		if (ms->jct->tab[i][0])
		{
			builtin_fts = ft_is_builtin(ms, i);
			//TODO if we do the below, redir doesn't because it's not in a child
			// if (ms->jct->cmd_nb == 1 && builtin_fts)
			// {
			// 	ms->exec->builtin->fts[builtin_fts](ms, ms->exec->builtin_cmd);
			// 	return ;
			// }
			if (ft_pre_redir(ms, i) == 1)
				exit(127); //TODO mettre le vrai exit status
			ms->exec->pids[i] = fork();
			if (ms->exec->pids[i] == -1)
				perror("Error! PID creation failed:");
			ft_close_old_pipes(ms->exec, i);
			ft_dup_and_run(ms, i, builtin_fts);
		}
	}
	ft_close_all(ms);
	if(DEBUG)
		printf("--- Exit while loop	---\n");
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
