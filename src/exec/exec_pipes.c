#include "../../include/minishell.h"

void	ft_close_fds(t_exec *exec)
{
	int	i;

	i = -1;
	while (++i < exec->pipes_nb)
	{
		if (exec->jct->fds_in[i])
			close(exec->jct->fds_in[i]);
		if (exec->jct->fds_out[i])
			close(exec->jct->fds_out[i]);
		if (exec->pipes[i][0])
			close(exec->pipes[i][0]);
		if (exec->pipes[i][1])
			close(exec->pipes[i][1]);
	}
	if (exec->fd_in)
		close(exec->fd_in);
	if (exec->fd_out)
		close(exec->fd_out);
	if (exec->jct->fd_hd)
		close(exec->jct->fd_hd);
	if (exec->input)
		close(exec->input);
	if (exec->output)
		close(exec->output);
}

int	ft_pre_redir(t_exec *exec, int i)
{
	printf("---		ft_pre_redir starts\n");
	printf("---		i = %d \n", i);
	printf("---		exec->jct->fd_hd = %d \n", exec->jct->fd_hd);
	if (exec->cmd_nb > 1) // s'il y a plus qu'une cmd, donc des pipes
	{
		printf("\n--- 1er if statement \n");
		//if there is a prev pipe, input will be the entry of the pipe
		if (i > 0)
			exec->input = exec->pipes[i - 1][0];
		printf("\n--- 2nd if statement \n");
		//if there is a pipe out, the output is the pipe
		if (i < exec->pipes_nb)
		{
			if (pipe(exec->pipes[i]) == -1)
			{
				perror("Error! Pipe creation");
				return (1);
			}	
			exec->output = exec->pipes[i][1];
		}
	}
	if (exec->jct->fd_hd)
	{
		dup2(exec->jct->fd_hd, STDIN_FILENO);
		// close(exec->jct->fd_hd); //TODO to test
		exec->jct->fd_hd = 0;
	}
	if (exec->jct->fds_in[i])
		exec->input = exec->jct->fds_in[i];
	if (exec->jct->fds_out[i])
		exec->output = exec->jct->fds_out[i];
	printf("---		ft_pre_redir ends\n");
	return (0);
}

int	ft_mem_pipes(t_exec *exec)
{
	int	i;

	// printf("\n--- Pipes calloc starts ---\n");
	exec->pipes = ft_calloc(exec->pipes_nb, sizeof(int *));
	if (!exec->pipes)
	{
		perror("Error! Pipe memory allocation");
		return (1);
	}
	i = -1;
	while (++i < exec->pipes_nb)
	{
		exec->pipes[i] = ft_calloc(2, sizeof(int *));
		if (!exec->pipes[i])
		{
			perror("Error! Pipe memory allocation");
			return (1);
		}
	}
	// printf("\n--- Pipe calloc ends		---\n");
	return (0);
}

int	ft_create_pipes(t_exec *exec)
{
	// int	i;

	if (exec->cmd_nb <= 1)
		return (1);
	if (ft_mem_pipes(exec) == 1)
		return (2);
	// i = -1;
	// while (++i < exec->pipes_nb)
	// {
	// 	if (pipe(exec->pipes[i]) == -1)
	// 	{
	// 		perror("Error! Pipe creation");
	// 		return (2);
	// 	}
	// }
	return (0);
}
