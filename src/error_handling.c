#include "../include/minishell.h"

/*
This function :
	- return an error message to the user,
	- close fd if necessary.
*/
void	ft_error_parsing(char *err_msg, int step, t_pars *pars)
{
	if (err_msg)
		write(STDERR_FILENO, err_msg, ft_strlen(err_msg));
	if (step == 1)
		pars->err_lexer = true;
	else if (step == 2)
		pars->err_rebuilder = true;
	else
		pars->err_parser = true;
}

void	ft_error(char *err_msg)
{
	if (err_msg)
		write(STDERR_FILENO, err_msg, ft_strlen(err_msg));
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
		ft_error(err_msg);
}
