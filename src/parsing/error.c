#include "../../include/minishell.h"

void	ft_error_parsing(char *err_msg, int step, int exit, t_ms *ms)
{
	if (err_msg)
		write(STDERR_FILENO, err_msg, ft_strlen(err_msg));
	if (step == 1)
	{
		ms->pars->err_lexer = true;
		ms->flexit = exit;
	}
	else if (step == 2)
	{
		ms->pars->err_builder = true;
		ms->flexit = exit;
	}
	else
	{
		ms->pars->err_parser = true;
		ms->flexit = exit;
	}
	if (DEBUG)
		printf("exit_status = %d\n", ms->flexit);
}

void	ft_error(char *err_msg)
{
	if (err_msg)
		write(STDERR_FILENO, err_msg, ft_strlen(err_msg));
}

void	ft_clean_up_jct(char *err_msg, t_jct *jct)
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
