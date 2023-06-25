#include "../../include/minishell.h"

/*
Fill the char ***array with nodes of the linked-list.
***FROM***
Input : cat supp.txt >outfile | cat -e | ls < infile | echo -n Minihell
***TO***
--------------------------------------------------------------
-                           TAB                              -
--------------------------------------------------------------
[0][0] = cat supp.txt
[0][1] = (null)
[0][2] = > outfile
--------------------------------------------------------------
[1][0] = cat -e
[1][1] = (null)
[1][2] = (null)
--------------------------------------------------------------
[2][0] = ls
[2][1] = < infile
[2][2] = (null)
--------------------------------------------------------------
[3][0] = cat -n Minihell
[3][1] = (null)
[3][2] = (null)
--------------------------------------------------------------
*/
void	ft_fill_tab(t_ms *ms, t_tab *tab)
{
	if(DEBUG){
	printf(KYEL "-------------------- FT_FILL_TAB" KGRN " START " RESET KYEL "--------------------\n" RESET);
	printf("ms->jct->cmd_nb = %d\n", ms->jct->cmd_nb);
	printf("ms->pars->nb_pipe = %d\n", ms->pars->nb_pipe);
	}
	while (++tab->r < ms->jct->cmd_nb && tab->ptr)
	{
		tab->c = -1;
		while (++tab->c < 3)
		{
			if (DEBUG){
			printf("c = %d\n", tab->c);
			printf("tab-> ptr->type = %d\n", tab->ptr->type);
			}
			if (tab->ptr->type == PIPE && tab->c == 0)
				tab->ptr = tab->ptr->next;
			if (tab->c == tab->ptr->type)
			{
				ms->jct->tab[tab->r][tab->c] = ft_strdup(tab->ptr->str);
				if (DEBUG)
					printf("str = %s\n", ms->jct->tab[tab->r][tab->c]);
				if (tab->ptr->next)
					tab->ptr = tab->ptr->next;
			}
			else if (tab->c != tab->ptr->type)
			{
				if (tab->ptr->type == ACCESS_ERR && tab->c == 0)
				{
					ms->jct->tab[tab->r][tab->c] = ft_strdup(tab->ptr->str);
					if (tab->ptr->next)
						tab->ptr = tab->ptr->next;
				}
				else if (tab->ptr->type != PIPE)
					ms->jct->tab[tab->r][tab->c] = NULL;
				else
					while (tab->c < 3)
						ms->jct->tab[tab->r][tab->c++] = NULL;
			}
		}
	}
	if (DEBUG)
		printf(KYEL "-------------------- FT_FILL_TAB" KRED " END " RESET KYEL "--------------------\n" RESET);
	// Ct_debug(0, "-------------------- FT_FILL_TAB END --------------------", "log.txt");
}

/* Allocate memory for the char ***array. */
void	ft_init_cmdtab(t_ms *ms)
{
	int	i;

	ms->jct->tab = ft_calloc(ms->jct->cmd_nb + 1, sizeof(char **));
	if (!ms->jct->tab)
	{
		ft_free_3tab(ms->jct);
		return ;
	}
	i = -1;
	while (++i < ms->jct->cmd_nb)
	{
		ms->jct->tab[i] = ft_calloc(3, sizeof(char *));
		if (!ms->jct->tab[i])
		{
			ft_free_3tab(ms->jct);
			return ;
		}
	}
}

/*
1) Check for PIPE token at the start of the linked-list
2) Check for double-pipe
3) Check for PIPE token at the end of the linked-list
*/
void	ft_check_pipe(t_ms *ms)
{
	if (DEBUG)
		printf(KYEL "-------------------- FT_CHECK_PIPE" KGRN " START " RESET KYEL "--------------------\n" RESET);
	t_token	*ptr;

	ptr = ms->pars->line;
	if (ptr->type == PIPE)
		ft_error_parsing(ERR_TOKEN, PARSER, 2, ms);
	while (ptr->next)
	{
		if (DEBUG){
		printf("str = %s\n", ptr->str);
		printf("str next = %s\n", ptr->next->str);
		}
		if (ptr->type == PIPE && ptr->next->type == PIPE)
		{
			ft_error_parsing(ERR_TOKEN, PARSER, 2, ms);
			break ;
		}
		else
			ptr = ptr->next;
	}
	if (ptr->next == NULL && ptr->type == PIPE)
		ft_error_parsing(ERR_TOKEN, PARSER, 2, ms);
	if (DEBUG)
		printf(KYEL "-------------------- FT_CHECK_PIPE" KRED " END " RESET KYEL "--------------------\n" RESET);
}

/*
Check for REDIN or REDOUT token at the end of the linked-list.
*/
void	ft_check_redir(t_ms *ms)
{
	if (DEBUG)
		printf(KYEL "-------------------- FT_CHECK_REDIR" KGRN " START " RESET KYEL "--------------------\n" RESET);
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
		printf(KYEL "-------------------- FT_CHECK_REDIR" KRED " END " RESET KYEL "--------------------\n" RESET);
}

/*
Parsing Part III
1) Check for any invalid token (redirection or pipe).
2) Initialize the char ***array and allocate memory
3) Fill the tab
*/
void	ft_parser(t_ms *ms)
{
	t_tab	*tab;

	tab = NULL;
	ft_check_redir(ms);
	ft_check_pipe(ms);
	if (DEBUG)
		DEBUG_parser(ms->pars);
	if (ms->pars->err_parser == false)
	{
		ms->jct->cmd_nb = ms->pars->nb_pipe;
		if (DEBUG)
			printf("ms->jct->cmd_nb = %d\n", ms->jct->cmd_nb);
		ft_init_cmdtab(ms);
		tab = ft_init_tab(ms->pars);
		ft_fill_tab(ms, tab);
		free(tab);
		if (DEBUG)
			DEBUG_tab(ms->jct);
	}
}
