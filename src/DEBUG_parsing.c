#include "../include/minishell.h"

void	DEBUG_hd(t_pars *hd)
{
	t_token	*tmp;

	tmp = hd->line;
	printf(KRED KBLD"--------------------------------------------------------------\n");
	printf("-			DEBUG_hd			     -\n");
	printf("--------------------------------------------------------------\n"RT);
	while (tmp)
	{
		printf(KRED KBLD"**************************************************************\n");
		printf("*" KRED KBLD " -> Str =          " RT KBLD "%s" RT KRED BLD"\n", tmp->str);
		printf("*" KRED KBLD " -> Type = %d                                                " RT KRED BLD"*\n", tmp->hd);
		printf(KRED KBLD"**************************************************************\n" RT);
		tmp = tmp->next;
	}
	ft_free_lst(&tmp);
}

void	DEBUG_tab(t_jct *jct)
{
	int		row;
	int		column;
	char	***tab;

	if (!jct->tab)
		return ;
	row = -1;
	tab = jct->tab;
	printf(KMAG KBLD"--------------------------------------------------------------\n");
	printf("-			DEBUG_tab			     -\n");
	printf("--------------------------------------------------------------\n"RT);
	while (++row < jct->cmd_nb)
	{
		column = -1;
		while (++column < 3)
			printf(KMAG KBLD"[%d][%d] = %s\n"RT, row, column, tab[row][column]);
		printf(KMAG KBLD"--------------------------------------------------------------\n"RT);
	}
}

void	DEBUG_filler(t_pars *pars)
{
	t_token	*tmp;
	int		i = 0;

	tmp = pars->line;
	printf(KGRE KBLD"--------------------------------------------------------------\n");
	printf("-			DEBUG_filler			     -\n");
	printf("--------------------------------------------------------------\n"RT);
	while (tmp)
	{
		printf(KGRE "**************************************************************\n");
		printf("*" KGRE KBLD "                          NODE[%d]                           " RT KGRE "*\n", i++);
		printf("*" KGRE KBLD " -> Type[%d]                                                 " RT KGRE "*\n", tmp->type);
		printf(KGRE KBLD " -> Str = " RT KBLD "%s" RT KGRE "\n", tmp->str);
		printf(KGRE "**************************************************************\n" RT);
		tmp = tmp->next;
	}
	ft_free_lst(&tmp);
}

void	DEBUG_builder(t_pars *pars)
{
	t_token	*tmp;
	int		i = 0;

	tmp = pars->line;
	printf(KGRN KBLD"--------------------------------------------------------------\n");
	printf("-			DEBUG_build			     -\n");
	printf("--------------------------------------------------------------\n"RT);
	while (tmp)
	{
		printf(KGRN "**************************************************************\n");
		printf("*" KGRN KBLD "                          NODE[%d]                           " RT KGRN "*\n", i++);
		printf("*" KGRN KBLD " -> Type[%d]                                                 " RT KGRN "*\n", tmp->type);
		printf(KGRN KBLD " -> Str = " RT KBLD "%s" RT KGRN "\n", tmp->str);
		printf(KGRN "**************************************************************\n" RT);
		tmp = tmp->next;
	}
	ft_free_lst(&tmp);
}

void	DEBUG_lexer(t_pars *pars)
{
	t_token	*tmp;
	int		i = 0;

	tmp = pars->line;
	printf(KBLU KBLD"--------------------------------------------------------------\n");
	printf("-			DEBUG_lexer			     -\n");
	printf("--------------------------------------------------------------\n"RT);
	while (tmp)
	{
		printf(KBLU "**************************************************************\n");
		printf("*" KBLU KBLD "                          NODE[%d]                           " RT KBLU "*\n", i++);
		printf("*" KBLU KBLD " -> Cmd[%d]                                                  " RT KBLU "*\n", tmp->nb_cmd);
		printf("*" KBLU KBLD " -> Type[%d]                                                 " RT KBLU "*\n", tmp->type);
		printf("*" KBLU KBLD " -> D_Quotes[%d]                                             " RT KBLU "*\n", tmp->d_quotes);
		printf("*" KBLU KBLD " -> S_Quotes[%d]                                             " RT KBLU "*\n", tmp->s_quotes);
		printf("*" KBLU KBLD " -> C_brackets[%d]                                           " RT KBLU "*\n", tmp->c_brackets);
		printf("*" KBLU KBLD " -> Whitespace[%d]                                           " RT KBLU "*\n", tmp->ws);
		printf("*" KBLU KBLD " -> Str =          " RT KBLD "%s" RT KBLU "\n", tmp->str);
		printf(KBLU "**************************************************************\n" RT);
		tmp = tmp->next;
	}
	ft_free_lst(&tmp);
}