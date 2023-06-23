#include "../../include/minishell.h"

void	ft_close_fds(t_ms *ms)
{
	int	i;

	i = -1;
	while (++i < ms->exec->pipes_nb)
	{
		if (ms->jct->fds_in[i])
			close(ms->jct->fds_in[i]);
		if (ms->jct->fds_out[i])
			close(ms->jct->fds_out[i]);
		if (ms->exec->pipes[i][0])
			close(ms->exec->pipes[i][0]);
		if (ms->exec->pipes[i][1])
			close(ms->exec->pipes[i][1]);
	}
	if (ms->exec->fd_in)
		close(ms->exec->fd_in);
	if (ms->exec->fd_out)
		close(ms->exec->fd_out);
	if (ms->jct->fd_hd)
		close(ms->jct->fd_hd);
	if (ms->exec->input)
		close(ms->exec->input);
	if (ms->exec->output)
		close(ms->exec->output);
}

int	ft_pre_redir(t_ms *ms, int i)
{
	printf("---	ft_pre_redir starts\n\n");
	// printf("---	i = %d \n", i);
	// printf("---	exec->jct->fd_hd = %d \n", exec->jct->fd_hd);
	// printf("---	BEFORE if, exec->jct->fds_in[%d]: %d\n", i,  exec->jct->fds_in[i]);
	// printf("---	BEFORE if, exec->input: %d\n", exec->input);
	printf("ms->jct->cmd_nb = %d\n", ms->jct->cmd_nb);
	if (ms->jct->cmd_nb > 1) // s'il y a plus qu'une cmd, donc des pipes
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
	printf("ms->jct->fd_hd = %d\n", ms->jct->fd_hd);
	if (ms->jct->fd_hd)
	{
		dup2(ms->jct->fd_hd, STDIN_FILENO);
		close(ms->jct->fd_hd); //TODO to test
		ms->jct->fd_hd = 0;
	}
	printf("\n---	ft_pre_redir ends\n\n");
	return (0);
}

int	ft_mem_pipes(t_ms *ms)
{
	int	i;

	if (ms->jct->cmd_nb <= 1)
		return (1);
	// printf("\n--- Pipes calloc starts ---\n");
	ms->exec->pipes_nb = ms->jct->cmd_nb - 1;
	printf("ms->jct->cmd_nb = %d\n", ms->jct->cmd_nb);
	printf("ms->exec->pipes_nb = %d\n", ms->exec->pipes_nb);
	ms->exec->pipes = ft_calloc(ms->exec->pipes_nb, sizeof(int *));
	if (!ms->exec->pipes)
	{
		perror("Error! Pipe memory allocation");
		return (2);
	}
	i = -1;
	while (++i < ms->exec->pipes_nb)
	{
		ms->exec->pipes[i] = ft_calloc(2, sizeof(int *));
		if (!ms->exec->pipes[i])
		{
			perror("Error! Pipe memory allocation");
			return (2);
		}
	}
	// printf("\n--- Pipe calloc ends		---\n");
	return (0);
}
