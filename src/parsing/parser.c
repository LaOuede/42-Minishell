#include "../../include/minishell.h"

/* Store the nodes in a two-dimensionnal array */
void	ft_fill_tab(t_jct *jct, t_pars *pars)
{
	printf(KYEL "-------------------- FT_FILL_TAB" KGRN " START " RESET KYEL "--------------------\n" RESET);
	int		row;
	int		column;
	t_token	*ptr;

	row = -1;
	ptr = pars->line;
	jct->file_out = dup(pars->file_out);
	jct->file_in = dup(pars->file_in);
	close(pars->file_in);
	close(pars->file_out);
	printf("jct->file_out : %d\n", jct->file_out);
	printf("pars->file_out : %d\n", pars->file_out);
	printf("jct->file_in : %d\n", jct->file_in);
	printf("pars->file_in : %d\n", pars->file_in);
	printf("jct->cmd_nb = %d\n", jct->cmd_nb);
	printf("pars->nb_pipe = %d\n", pars->nb_pipe);
	while (++row < jct->cmd_nb && ptr)
	{
		column = -1;
		while (++column < 4)
		{
			printf("column = %d\n", column);
			printf("ptr->type = %d\n", ptr->type);
			if (ptr->type == PIPE && column == 0)
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
				if (ptr->type != PIPE)
					jct->tab[row][column] = NULL;
				else
					while (column < 4)
						jct->tab[row][column++] = NULL;
			}
		}
	}
	printf(KYEL "-------------------- FT_FILL_TAB" KRED " END " RESET KYEL "--------------------\n" RESET);
}

/* Initializes the two-dimensionnal array. */
void	ft_init_cmdtab(t_jct *jct)
{
	int	i;

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
	}
}

void	ft_check_pipe_tail(t_pars *pars)
{
	printf(KYEL "-------------------- FT_CHECK_PIPE_TAIL" KGRN " START " RESET KYEL "--------------------\n" RESET);
	t_token	*ptr;

	ptr = pars->line;
	while (ptr->next)
		ptr = ptr->next;
	if (ptr->type == PIPE)
		ft_error_parsing(ERR_TOKEN, PARSER, pars);
	printf(KYEL "-------------------- FT_CHECK_PIPE_TAIL" KRED " END " RESET KYEL "--------------------\n" RESET);
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
				ft_error_parsing(ERR_TOKEN, PARSER, pars);
		}
		ptr = ptr->next;
	}
	printf(KYEL "-------------------- FT_CHECK_REDIR" KRED " END " RESET KYEL "--------------------\n" RESET);
}

void	ft_parser(t_pars *pars, t_jct *jct)
{
	if (!pars)
		return ;
	jct->cmd_nb = pars->nb_pipe;
	ft_check_redir(pars);
	ft_check_pipe_tail(pars);
	DEBUG_parser(pars);
	if (pars->err_parser == false)
	{
		ft_init_cmdtab(jct);
		ft_fill_tab(jct, pars);
		DEBUG_tab(jct);
	}
}
