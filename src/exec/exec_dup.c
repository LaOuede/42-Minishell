#include "../../include/minishell.h"

void	ft_free_built_in(t_ms *ms)
{
	ft_free_tab_char(ms->exec->builtin_cmd);
	ms->exec->builtin_cmd = NULL;
}

void	ft_dup_x_cmd(t_ms *ms, int i)
{
	if (i == 0)
		if (ms->jct->fd_hd)
			dup2(ms->jct->fd_hd, STDIN_FILENO);
	if (i > 0)
	{
		if (ms->exec->input)
			dup2(ms->exec->input, STDIN_FILENO);
		else if (ms->jct->fd_hd)
			dup2(ms->jct->fd_hd, STDIN_FILENO);
	}
	if (i < ms->exec->pipes_nb)
		if (ms->exec->output)
			dup2(ms->exec->output, STDOUT_FILENO);
	if (ms->jct->fds_in[i] >= 0)
		dup2(ms->jct->fds_in[i], STDIN_FILENO);
	if (ms->jct->fds_out[i])
		dup2(ms->jct->fds_out[i], STDOUT_FILENO);
}

void	ft_dup_proc(t_ms *ms, int i)
{
	if (ms->jct->cmd_nb == 1)
	{
		if (ms->jct->fds_in[i] >= 0)
			dup2(ms->jct->fds_in[i], STDIN_FILENO);
		if (ms->jct->fds_out[i])
			dup2(ms->jct->fds_out[i], STDOUT_FILENO);
		if (ms->jct->fd_hd)
			dup2(ms->jct->fd_hd, STDIN_FILENO);
	}
	else
		ft_dup_x_cmd(ms, i);
	ft_close_all(ms);
}

void	ft_dup_and_run(t_ms *ms, int i, int builtin_fts)
{
	int	j;

	if (ms->exec->pids[i] == 0)
	{
		j = -1;
		while (++j < ms->jct->cmd_nb)
			if (ms->jct->fds_in[j] < 0)
				ft_exit_free(ms, 1, 0);
		ft_dup_proc(ms, i);
		if (builtin_fts)
		{
			ms->exec->builtin->fts[builtin_fts](ms, ms->exec->builtin_cmd);
			ft_exit_free(ms, 0, 0);
		}
		ms->exec->path_var = ft_get_path(ms, ms->envp, 0);
		if (!ms->exec->path_var)
		{
			printf("Input Error : Command not found\n");
			return ;
		}
		ft_run_cmd(ms, i);
	}
	else
		ft_free_built_in(ms);
}
