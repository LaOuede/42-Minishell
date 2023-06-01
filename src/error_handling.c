#include "../include/minishell.h"

/*
This function :
	- return an error message to the user,
	- close fd if necessary.
*/
void	ft_error(char *err_msg, int fd)
{
	if (err_msg)
		write(STDERR_FILENO, err_msg, ft_strlen(err_msg));
	if (fd)
		close (fd);
	exit(EXIT_FAILURE);
}

void	ft_clean_up(t_pars *pars)
{
	if (pars)
	{
		if (pars->input)
			free(pars->input);
		free(pars);
	}
}

void	ft_clean_up_jct(t_jct *jct, char *err_msg)
{
	if (jct)
	{
		if (jct->tab)
			ft_free_tab_char(*jct->tab);
		free(jct);
	}
	if (err_msg)
		ft_error(err_msg, 2);
	if (!err_msg)
		exit(EXIT_SUCCESS);
	exit(EXIT_SUCCESS);
}
