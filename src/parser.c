#include "../include/minishell.h"

/* void	ft_check_redir(t_pars *pars)
{
	printf(KYEL "-------------------- FT_CHECK_INFILE" KGRN " START " RESET KYEL "--------------------\n" RESET);
	t_token	*ptr;
	int		i;
	char	*tmp;

	if (!pars->line)
		return ;
	ptr = pars->line;
	while (ptr)
	{
		i = 0;
		if (ptr->type == REDIN)
		{
			while (ptr->str[i])
			{
				if (ft_iswhitespace(ptr->str[i]) == 1 || ptr->str[i] == '<')
					i++;
				else
		}
		ptr = ptr->next;
	}
	printf(KYEL "-------------------- FT_CHECK_INFILE" KRED " END " RESET KYEL "--------------------\n" RESET);
} */

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
	//int	j;

	jct->tab = ft_calloc(jct->cmd_nb + 1, sizeof(char **));
	if (!jct->tab)
	{
		ft_free_3tab(jct);
		return ;
	}
	i = -1;
	while (++i < jct->cmd_nb)
	{
		jct->tab[i] = ft_calloc(4, sizeof(char *));
		if (!jct->tab[i])
		{
			ft_free_3tab(jct);
			return ;
		}
/* 			j = -1;
		while (++j < 4)
		{
			jct->tab[i][j] = ft_calloc(1, sizeof(char));
			if (!jct->tab[i][j])
			{
				ft_free_3tab(jct);
				return ;
			}
		} */
	}
}

void	ft_parser(t_pars *pars, t_jct *jct)
{
	if (!pars)
		return ;
	jct->cmd_nb = pars->nb_pipe;
	ft_check_redir(pars);
	//ft_check_infile(pars);
	ft_check_pipe(pars);
	ft_parser_debugger(pars);
	if (pars->flag_error_parser == true)
	{
		ft_init_cmdtab(jct);
		ft_fill_tab(jct, pars);
		ft_print_tab(jct);
	}
}
