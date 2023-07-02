#include "../../include/minishell.h"

/*
1) Check for PIPE token at the start of the linked-list
2) Check for double-pipe
3) Check for PIPE token at the end of the linked-list
*/
void	ft_check_pipe(t_ms *ms)
{
	if (DEBUG)
		printf(KYEL "-------------------- FT_CHECK_PIPE" KGRN " START " RT KYEL "--------------------\n" RT);
	t_token	*ptr;

	ptr = ms->pars->line;
	if (ptr->type == PIPE)
	{
		ms->pars->fl_pipe = true;
		ft_error_parsing(ERR_TOKEN, PARSER, 2, ms);
	}
	while (ptr->next)
	{
		if (DEBUG)
		{
			printf("str = %s\n", ptr->str);
			printf("str next = %s\n", ptr->next->str);
		}
		if (ms->pars->fl_pipe == false && ptr->type == PIPE && ptr->next->type == PIPE)
		{
			ms->pars->fl_pipe = true;
			ft_error_parsing(ERR_TOKEN, PARSER, 2, ms);
			break ;
		}
		else
			ptr = ptr->next;
	}
	if (ms->pars->fl_pipe == false && ptr->next == NULL && ptr->type == PIPE)
		ft_error_parsing(ERR_TOKEN, PARSER, 2, ms);
	if (DEBUG)
		printf(KYEL "-------------------- FT_CHECK_PIPE" KRED " END " RT KYEL "--------------------\n" RT);
}

/*
Check for REDIN or REDOUT token at the end of the linked-list.
*/
void	ft_check_redir(t_ms *ms)
{
	if (DEBUG)
		printf(KYEL "-------------------- FT_CHECK_REDIR" KGRN " START " RT KYEL "--------------------\n" RT);
	t_token	*ptr;
	int		len;

	ptr = ms->pars->line;
	while (ptr)
	{
		if (ptr->type == REDIN || ptr->type == REDOUT)
		{
			len = ft_strlen(ptr->str);
			if (ptr->str[len - 1] == '<' || ptr->str[len - 1] == '>')
				ft_error_parsing(ERR_TOKEN, PARSER, 2, ms);
		}
		ptr = ptr->next;
	}
	if (DEBUG)
		printf(KYEL "-------------------- FT_CHECK_REDIR" KRED " END " RT KYEL "--------------------\n" RT);
}

/*
Parsing Part III
1) Check for any invalid token (redirection or pipe).
2) Initialize the char ***array and allocate memory
3) Fill the tab
*/
void	ft_filler(t_ms *ms)
{
	t_tab	*tab;

	tab = NULL;
	ft_check_redir(ms);
	ft_check_pipe(ms);
	if (DEBUG)
		DEBUG_filler(ms->pars);
	if (ms->pars->err_filler == false)
	{
		ms->jct->cmd_nb = ms->pars->nb_pipe;
		if (DEBUG)
			printf("ms->jct->cmd_nb = %d\n", ms->jct->cmd_nb);
		ft_init_cmdtab(ms);
		tab = ft_init_tab(ms, ms->pars);
		ft_fill_tab(ms, tab);
		free(tab);
		if (DEBUG)
			DEBUG_tab(ms->jct);
	}
}
