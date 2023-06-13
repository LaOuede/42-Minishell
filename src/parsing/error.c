#include "../../include/minishell.h"

void	ft_exit_status(t_pars *pars)
{
	printf("%d\n", g_jct->exit_status);
	g_jct->exit_status = 0;
	pars->EXIT_STATUS = true;
}

void	ft_error_parsing(char *err_msg, int step, int exit, t_pars *pars)
{
	if (err_msg)
		write(STDERR_FILENO, err_msg, ft_strlen(err_msg));
	if (step == 1)
	{
		pars->err_lexer = true;
		g_jct->exit_status = exit;
	}
	else if (step == 2)
	{
		pars->err_rebuilder = true;
		g_jct->exit_status = exit;
	}
	else
	{
		pars->err_parser = true;
		g_jct->exit_status = exit;
	}
	printf("exit_status = %d\n", g_jct->exit_status);
}

void	ft_error(char *err_msg)
{
	if (err_msg)
		write(STDERR_FILENO, err_msg, ft_strlen(err_msg));
}

void	ft_clean_up_jct(char *err_msg)
{
	if (g_jct)
	{
		if (g_jct->tab)
			ft_free_tab_char(*g_jct->tab);
		free(g_jct);
	}
	if (err_msg)
		ft_error(err_msg);
}
