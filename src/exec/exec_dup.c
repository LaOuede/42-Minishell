#include "../../include/minishell.h"

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
	if (ms->jct->cmd_nb == 1) // if 1 cmd and no pipes (so one cmd only)
	{
		if (ms->jct->fds_in[i] >= 0)
			dup2(ms->jct->fds_in[i], STDIN_FILENO);
		if (ms->jct->fds_out[i])
			dup2(ms->jct->fds_out[i], STDOUT_FILENO);
		if (ms->jct->fd_hd)
			dup2(ms->jct->fd_hd, STDIN_FILENO);
	}
	else // s'il y a plus qu'une cmd, donc des pipes
		ft_dup_x_cmd(ms, i);
	ft_close_all(ms);
}

//  git commit -am "Built_in & Execution | few add ons (cd ~, ft_get_ac, comments in ft_msh_unset, free if no env in ft_get_path, fix hang in ft_dup_proc"

void	ft_dup_and_run(t_ms *ms, int i, int builtin_fts)
{
	if (ms->exec->pids[i] == 0)
	{
		ft_dup_proc(ms, i);
		if (builtin_fts)
		{
			ms->exec->builtin->fts[builtin_fts](ms, ms->exec->builtin_cmd);
			exit(0);
		}
		ms->exec->path_var = ft_get_path(ms->envp, 0);
		if (!ms->exec->path_var)
		{
			printf("Input Error : Command not found\n");
			return ;
		}
		if (ms->jct->fds_in[i] < 0)
			exit(1);
		ft_run_cmd(ms, i);
	}
}