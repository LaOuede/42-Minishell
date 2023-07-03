#include "../../include/minishell.h"

void	ft_close_old_pipes(t_exec *exec, int i)
{
	if (i > 2 && exec->pipes[i - 1] && exec->pipes[i - 2])
	{
		if (exec->pipes[i - 2][0])
			close(exec->pipes[i - 2][0]);
		if (exec->pipes[i - 2][1])
			close(exec->pipes[i - 2][1]);
	}
}

void	ft_close_fds(t_ms *ms)
{
	if (ms->jct->fd_hd)
		close(ms->jct->fd_hd);
	if (ms->exec->input)
		close(ms->exec->input);
	if (ms->exec->output)
		close(ms->exec->output);
}

void	ft_close_all(t_ms *ms)
{
	int	i;

	i = -1;
	while (++i < ms->exec->pipes_nb)
	{
		if (ms->exec->pipes[i][0])
			close(ms->exec->pipes[i][0]);
		if (ms->exec->pipes[i][1])
			close(ms->exec->pipes[i][1]);
	}
	while (i >= 0)
	{
		if (ms->jct->fds_in[i])
			close(ms->jct->fds_in[i]);
		if (ms->jct->fds_out[i])
			close(ms->jct->fds_out[i]);
		i--;
	}
	ft_close_fds(ms);
}

int	ft_pre_redir(t_ms *ms, int i)
{
	if (ms->jct->cmd_nb > 1)
	{
		if (i > 0)
			ms->exec->input = ms->exec->pipes[i - 1][0];
		if (i < ms->exec->pipes_nb)
		{
			if (pipe(ms->exec->pipes[i]) == -1)
			{
				perror("Error! Pipe creation in pre_redir");
				return (1);
			}
			ms->exec->output = ms->exec->pipes[i][1];
		}
	}
	return (0);
}

int	ft_mem_pipes(t_ms *ms)
{
	int	i;

	if (ms->jct->cmd_nb <= 1)
		return (1);
	ms->exec->pipes_nb = ms->jct->cmd_nb - 1;
	ms->exec->pipes = ft_calloc_msh(ms->exec->pipes_nb, sizeof(int *), ms);
	if (!ms->exec->pipes)
	{
		perror("Error! Pipe memory allocation");
		return (2);
	}
	i = -1;
	while (++i < ms->exec->pipes_nb)
	{
		ms->exec->pipes[i] = ft_calloc_msh(2, sizeof(int *), ms);
		if (!ms->exec->pipes[i])
		{
			perror("Error! Pipe memory allocation");
			return (2);
		}
	}
	return (0);
}
