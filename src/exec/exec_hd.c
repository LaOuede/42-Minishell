#include "../../include/minishell.h"

void	ft_child_hd(char *delim, t_pars *pars)
{
	char *tmp;

	while(1)
	{
		ft_putstr_fd("> ", 1);
		tmp = get_next_line(0);
		if((ft_strncmp(tmp, delim, ft_strlen(delim))) == 0)
		{
			if (ft_strncmp(tmp + ft_strlen(delim), "\n", 2) == 0)
			{
				ft_freenull(tmp);
				// printf("\n");
				break;
			}
		}
		ft_putstr_fd(tmp, pars->file_in);
		ft_freenull(tmp);
	}
	//TODO put here all free ft required
	// exit(0);
}

// int	exec_hd(char *delim)
// {
// 	int		fd_hd[2];
// 	char	*line;
// 	int		pid_hd;

// 	if (pipe(fd_hd) < 0)
// 	{
// 		perror("Error ! Pipe_hd failed:");
// 		return (-1);
// 	}
// 	line = NULL;
// 	pid_hd = fork();
// 	if (pid_hd == -1)
// 		perror("Error ! Pid_hd failed:");
// 	if (pid_hd == 0)
// 		ft_child_hd(delim, line, fd_hd);
// 	close(fd_hd[1]);
// 	printf("before waitpid\n");
// 	waitpid(pid_hd, NULL, 0);
// 	printf("after waitpid\n");
// 	return(fd_hd[0]);
// }

void	exec_hd(t_pars *pars, char *delim)
{
	pars->file_in = open("/tmp/here_doc", O_CREAT | O_TRUNC | O_RDWR, 0644);
	if (pars->file_in < 0)
		perror("Error ! pars->file_in:");
	ft_child_hd(delim, pars);
	close(pars->file_in);
	pars->file_in = open("/tmp/here_doc", O_RDONLY, 0644);
}