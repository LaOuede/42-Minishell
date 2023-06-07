#include "../../include/minishell.h"

void	ft_check_pipe(t_pars *pars)
{
	printf(KYEL "-------------------- FT_CHECK_ERROR" KGRN " START " RESET KYEL "--------------------\n" RESET);
	t_token	*ptr;

	if (!pars->line)
		return ;
	ptr = pars->line;
	while (ptr->next)
		ptr = ptr->next;
	if (ptr->type == PIPE)
		ft_error_parsing(ERR_TOKEN, PARSER, pars);
	printf(KYEL "-------------------- FT_CHECK_ERROR" KRED " END " RESET KYEL "--------------------\n" RESET);
}

void	ft_check_redir(t_pars *pars)
{
	printf(KYEL "-------------------- FT_CHECK_PIPE" KGRN " START " RESET KYEL "--------------------\n" RESET);
	t_token	*ptr;
	int		len;

	if (!pars->line)
		return ;
	ptr = pars->line;
	while (ptr)
	{
		if (ptr->type == REDIN || ptr->type == REDOUT)
		{
			len = ft_strlen(ptr->str);
			if (ptr->str[len - 1] == '<' || ptr->str[len - 1] == '>')
				ft_error_parsing(ERR_TOKEN, PARSER, pars);
		}
		ptr = ptr->next;
	}
	printf(KYEL "-------------------- FT_CHECK_PIPE" KRED " END " RESET KYEL "--------------------\n" RESET);
}

void	ft_parser(t_pars *pars, t_jct *jct)
{
	if (!pars)
		return ;
	jct->cmd_nb = pars->nb_pipe;
	ft_check_redir(pars);
	ft_check_pipe(pars);
	DEBUG_parser(pars);
	if (pars->err_parser == false)
	{
		ft_init_cmdtab(jct);
		ft_fill_tab(jct, pars);
		ft_trim_cmd(jct);
		DEBUG_tab(jct);
	}
}
