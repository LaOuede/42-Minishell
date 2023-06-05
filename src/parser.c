#include "../include/minishell.h"

void	ft_clean_list_parser(t_token **list)
{
	printf(KYEL "-------------------- FT_CLEAN_LIST" KGRN " START " RESET KYEL "--------------------\n" RESET);
	t_token *sup;
	t_token	*ptr;

	if (!*list)
		return ;
	ptr = *list;
	while (ptr->next)
	{
		printf("ptr->type = %d\n", ptr->tab_type);
		printf("ptr->next->type = %d\n", ptr->next->tab_type);
		if (ptr->tab_type == ptr->next->tab_type)
		{
			sup = ptr->next;
			if (ptr->next->next)
			{
				ptr->next = ptr->next->next;
			}
			else if (!ptr->next->next)
			{
				ptr->next = NULL;
			}
			ft_free_token(sup);
		}
		else if (ptr->next)
			ptr = ptr->next;
	}
	printf(KYEL "-------------------- FT_CLEAN_LIST" KRED " END " RESET KYEL "--------------------\n" RESET);
}

void	ft_check_error(t_pars *pars)
{
	printf(KYEL "-------------------- FT_CHECK_ERROR" KGRN " START " RESET KYEL "--------------------\n" RESET);
	t_token	*ptr;

	if (!pars->line)
		return ;
	ptr = pars->line;
	while (ptr->next)
		ptr = ptr->next;
	if (ptr->type == PIPE)
	{
		ft_error("PIPE AT THE END\n");
		pars->flag_error_parser = false;
	}
	printf(KYEL "-------------------- FT_CHECK_ERROR" KRED " END " RESET KYEL "--------------------\n" RESET);
}

void	ft_print_tab(t_jct *jct)
{
	printf(KYEL "-------------------- FT_PRINT_TAB" KGRN " START " RESET KYEL "--------------------\n" RESET);
	int		row;
	int		column;
	char	***tab;

	if (!jct->tab)
		return ;
	row = -1;
	tab = jct->tab;
	while (++row < jct->cmd_nb)
	{
		column = -1;
		while (++column < 4)
			printf("[%d][%d] = %s\n", row, column, tab[row][column]);
	}
	printf(KYEL "-------------------- FT_PRINT_TAB" KRED " END " RESET KYEL "--------------------\n" RESET);
}

/* Store the nodes in a two-dimensionnal array */
void	ft_fill_tab(t_jct *jct, t_pars *pars)
{
	printf(KYEL "-------------------- FT_FILL_TAB" KGRN " START " RESET KYEL "--------------------\n" RESET);
	int		row;
	int		column;
	t_token	*ptr;

	row = -1;
	ptr = pars->line;
	printf("jct->cmd_nb = %d\n", jct->cmd_nb);
	printf("pars->nb_pipe = %d\n", pars->nb_pipe);
	while (++row < jct->cmd_nb && ptr)
	{
		column = -1;
		while (++column < 4)
		{
			printf("column = %d\n", column);
			printf("ptr->type = %d\n", ptr->type);
			if (ptr->type == 4 && column == 0)
				ptr = ptr->next;
			if (column == ptr->type)
			{
				jct->tab[row][column] = ft_strdup(ptr->str);
				printf("str = %s\n", jct->tab[row][column]);
				if (ptr->next)
					ptr = ptr->next;
			}
			else if (column != ptr->type)
			{
				if (ptr->type != 4)
					jct->tab[row][column] = NULL;
				else
				{
					while (column < 4)
						jct->tab[row][column++] = NULL;
				}
			}
		}
	}
	printf(KYEL "-------------------- FT_FILL_TAB" KRED " END " RESET KYEL "--------------------\n" RESET);
}

/* Initializes the two-dimensioonnal array. */
void	ft_init_cmdtab(t_jct *jct)
{
	int	i;
	int	j;

	jct->tab = ft_calloc(jct->cmd_nb, sizeof(char **));
	if (!jct->tab)
		ft_clean_up_jct(jct, KYEL"-> Failed to init the command tab <-"KNRM);
	i = -1;
	while (++i < jct->cmd_nb)
	{
		jct->tab[i] = ft_calloc(4, sizeof(char *));
		if (!jct->tab[i])
			ft_clean_up_jct(jct, KYEL"-> Failed to init the command tab <-"KNRM);
			j = -1;
		while (++j < 4)
		{
			jct->tab[i][j] = ft_calloc(1, sizeof(char));
			if (!jct->tab[i][j])
				ft_clean_up_jct(jct, KYEL"-> Failed to init the command tab <-"KNRM);
		}
	}
}

void	ft_cmd_type(t_token **list)
{
	t_token	*ptr;

	if (!list)
		return ;
	ptr = *list;
	while (ptr)
	{
		if (ptr->type == -1)
			ptr->tab_type = 0;
		else if (0 <= ptr->type && ptr->type <= 3)
			ptr->tab_type = 1;
		else if (ptr->type == 4)
			ptr->tab_type = -1;
		else if (ptr->type == 5 || ptr->type == 6)
			ptr->tab_type = 2;
		else if (ptr->type == 7 || ptr->type == 8)
			ptr->tab_type = 3;
		ptr = ptr->next;
	}
}

void	ft_parser(t_pars *pars, t_jct *jct)
{
	if (!pars)
		return ;
	jct->cmd_nb = pars->nb_pipe;
	//ft_cmd_type(&pars->line);
	ft_check_error(pars);
	//ft_clean_list_parser(&pars->line);
	ft_parser_debugger(pars);
	if (pars->flag_error_parser == true)
	{
		ft_init_cmdtab(jct);
		ft_fill_tab(jct, pars);
		ft_print_tab(jct);
	}
}
