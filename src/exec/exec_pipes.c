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
		if(exec->pipes[i][0])
			close(exec->pipes[i][0]);
		if(exec->pipes[i][0])
			close(exec->pipes[i][1]);
		if (exec->input)
			close(exec->input);
		if (exec->output)
			close(exec->output);
	}
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
	int	i;

	if (exec->cmd_nb <= 1)
		return (1);
	if (ft_mem_pipes(exec) == 1)
		return (2);
	i = -1;
	while (++i < exec->pipes_nb)
	{
		if (pipe(exec->pipes[i]) == -1)
		{
			perror("Error! Pipe creation");
			return (2);
		}
	}
	// exec->pipes = ft_calloc(2, sizeof(int *));
	// exec->pipes[0] = 0;
	// exec->pipes[1] = 1;
	// if (pipe(exec->pipes) == -1)
	// {
	// 	perror("Error! pipe creation");
	// 	return (2);
	// }

	return (0);
}
