#include "../../include/minishell.h"

void	ft_free_jct(t_jct *jct)
{
	if (jct)
	{
		if (jct->tab)
			ft_free_3tab(jct);
		if (jct->fds_in)
			free(jct->fds_in);
		if (jct->fds_out)
			free(jct->fds_out);
		ft_freenull(jct);
	}
}

void	ft_reset_jct(t_jct *jct)
{
	free(jct->fds_in);
	jct->fds_in = NULL;
	free(jct->fds_out);
	jct->fds_out = NULL;
	ft_free_3tab(jct);
	jct->tab = NULL;
	jct->fd_hd = 0;
	jct->cmd_nb = -1;
	jct->echo = false;
	jct->err_pars = false;
	jct->flag_var = false;
}

/*
Initialization of the junction structure.
This structure holds all important data needed both in parsing and execution.
*/
t_jct	*ft_init_jct(t_ms *ms, char **envp)
{
	t_jct	*jct;

	(void)envp;
	jct = ft_calloc_msh(1, sizeof(t_jct), ms);
	jct->fds_in = NULL;
	jct->fds_out = NULL;
	jct->tab = NULL;
	jct->fd_hd = 0;
	jct->cmd_nb = -1;
	jct->echo = false;
	jct->err_pars = false;
	jct->flag_var = false;
	return (jct);
}
