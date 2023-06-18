#include "../../include/minishell.h"

void	ft_child_hd(char *delim, t_pars *pars, int i)
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
		ft_putstr_fd(tmp, pars->jct->fds_in[i]);
		ft_freenull(tmp);
	}
}

void	exec_hd(t_pars *pars, char *delim, int i)
{
	pars->jct->fds_in[i] = open("/tmp/here_doc", O_CREAT | O_TRUNC | O_RDWR, 0644);
	if (pars->jct->fds_in[i] < 0)
		perror("Error ! pars->jct->fds_in:");
	ft_child_hd(delim, pars, i);
	close(pars->jct->fds_in[i]);
	pars->jct->fds_in[i] = open("/tmp/here_doc", O_RDONLY, 0644);
}
