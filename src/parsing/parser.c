#include "../../include/minishell.h"

/* Store the nodes in a two-dimensionnal array */
void	ft_fill_tab(t_pars *pars, t_tab *tab)
{
	printf(KYEL "-------------------- FT_FILL_TAB" KGRN " START " RESET KYEL "--------------------\n" RESET);
	// g_jct ->fl_redirout = pars->fl_redirout;
	// printf("pars->fl_redirout : %d\n", pars->fl_redirout);
	// printf("g_jct->fl_redirout : %d\n", g_jct->fl_redirout);
	// g_jct->file_out = dup(pars->file_out);
	// close(pars->file_out);
	// g_jct->file_in = dup(pars->file_in);
	// close(pars->file_in);
	// printf("g_jct->file_out : %d\n", g_jct->file_out);
	// printf("pars->file_out : %d\n", pars->file_out);
	// printf("g_jct->file_in : %d\n", g_jct->file_in);
	// printf("pars->file_in : %d\n", pars->file_in);
	printf("pars->jct->cmd_nb = %d\n", pars->jct->cmd_nb);
	printf("pars->nb_pipe = %d\n", pars->nb_pipe);
	while (++tab->row < pars->jct->cmd_nb && tab->ptr)
	{
		tab->column = -1;
		while (++tab->column < 3)
		{
			printf("column = %d\n", tab->column);
			printf("ptr->type = %d\n", tab->ptr->type);
			if (tab->ptr->type == PIPE && tab->column == 0)
				tab->ptr = tab->ptr->next;
			if (tab->column == tab->ptr->type)
			{
				pars->jct->tab[tab->row][tab->column] = ft_strdup(tab->ptr->str);
				printf("str = %s\n", pars->jct->tab[tab->row][tab->column]);
				if (tab->ptr->next)
					tab->ptr = tab->ptr->next;
			}
			else if (tab->column != tab->ptr->type)
			{
				if (tab->ptr->type != PIPE)
					pars->jct->tab[tab->row][tab->column] = NULL;
				else
					while (tab->column < 3)
						pars->jct->tab[tab->row][tab->column++] = NULL;
			}
		}
	}
	printf(KYEL "-------------------- FT_FILL_TAB" KRED " END " RESET KYEL "--------------------\n" RESET);
}

/* Initializes the two-dimensionnal array. */
void	ft_init_cmdtab(t_pars *pars)
{
	int	i;

	pars->jct->tab = ft_calloc(pars->jct->cmd_nb + 1, sizeof(char **));
	if (!pars->jct->tab)
	{
		ft_free_3tab(pars->jct);
		return ;
	}
	i = -1;
	while (++i < pars->jct->cmd_nb)
	{
		pars->jct->tab[i] = ft_calloc(3, sizeof(char *));
		if (!pars->jct->tab[i])
		{
			ft_free_3tab(pars->jct);
			return ;
		}
	}
}

void	ft_check_pipe(t_pars *pars)
{
	printf(KYEL "-------------------- FT_CHECK_PIPE" KGRN " START " RESET KYEL "--------------------\n" RESET);
	t_token	*ptr;

	ptr = pars->line;
	if (ptr->type == PIPE)
		ft_error_parsing(ERR_TOKEN, PARSER, 2, pars);
	while (ptr->next)
	{
		printf("str = %s\n", ptr->str);
		printf("str next = %s\n", ptr->next->str);
		if (ptr->type == PIPE && ptr->next->type == PIPE)
		{
			ft_error_parsing(ERR_TOKEN, PARSER, 2, pars);
			break ;
		}
		else
			ptr = ptr->next;
	}
	if (ptr->next == NULL && ptr->type == PIPE)
		ft_error_parsing(ERR_TOKEN, PARSER, 2, pars);
	printf(KYEL "-------------------- FT_CHECK_PIPE" KRED " END " RESET KYEL "--------------------\n" RESET);
}

void	ft_check_redir(t_pars *pars)
{
	printf(KYEL "-------------------- FT_CHECK_REDIR" KGRN " START " RESET KYEL "--------------------\n" RESET);
	t_token	*ptr;
	int		len;

	ptr = pars->line;
	while (ptr)
	{
		if (ptr->type == REDIN || ptr->type == REDOUT)
		{
			len = ft_strlen(ptr->str);
			if (ptr->str[len - 1] == '<' || ptr->str[len - 1] == '>')
				ft_error_parsing(ERR_TOKEN, PARSER, 2, pars);
		}
		ptr = ptr->next;
	}
	printf(KYEL "-------------------- FT_CHECK_REDIR" KRED " END " RESET KYEL "--------------------\n" RESET);
}

void	ft_parser(t_pars *pars)
{
	t_tab	*tab;

	tab = NULL;
	ft_check_redir(pars);
	ft_check_pipe(pars);
	DEBUG_parser(pars);
	if (pars->err_parser == false)
	{
		pars->jct->cmd_nb = pars->nb_pipe;
		ft_init_cmdtab(pars);
		tab = ft_init_tab(pars);
		ft_fill_tab(pars, tab);
		free(tab);
		DEBUG_tab(pars->jct);
	}
}
