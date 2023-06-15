#include "../include/minishell.h"

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
	printf("--------------------------------------------------------------\n"RESET);
	while (++row < jct->cmd_nb)
	{
		column = -1;
		while (++column < 3)
			printf(KMAG KBLD"[%d][%d] = %s\n"RESET, row, column, tab[row][column]);
	}
}
void	DEBUG_parser(t_pars *pars)
{
	t_token	*tmp;
	int		i = 0;

	tmp = pars->line;
	printf(KGRE KBLD"--------------------------------------------------------------\n");
	printf("-			DEBUG_parser			     -\n");
	printf("--------------------------------------------------------------\n"RESET);
	while (tmp)
	{
		printf(KGRE "**************************************************************\n");
		printf("*" KGRE KBLD "                          NODE[%d]                           " RESET KGRE "*\n", i++);
		printf("*" KGRE KBLD " -> Type[%d]                                                 " RESET KGRE "*\n", tmp->type);
		printf(KGRE KBLD " -> Str = " RESET KBLD "%s" RESET KGRE "\n", tmp->str);
		printf(KGRE "**************************************************************\n" RESET);
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
	printf("--------------------------------------------------------------\n"RESET);
	while (tmp)
	{
		printf(KGRN "**************************************************************\n");
		printf("*" KGRN KBLD "                          NODE[%d]                           " RESET KGRN "*\n", i++);
		printf("*" KGRN KBLD " -> Type[%d]                                                 " RESET KGRN "*\n", tmp->type);
		printf(KGRN KBLD " -> Str = " RESET KBLD "%s" RESET KGRN "\n", tmp->str);
		printf(KGRN "**************************************************************\n" RESET);
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
	printf("--------------------------------------------------------------\n"RESET);
	while (tmp)
	{
		printf(KBLU "**************************************************************\n");
		printf("*" KBLU KBLD "                          NODE[%d]                           " RESET KBLU "*\n", i++);
		printf("*" KBLU KBLD " -> Cmd[%d]                                                  " RESET KBLU "*\n", tmp->nb_cmd);
		printf("*" KBLU KBLD " -> Type[%d]                                                 " RESET KBLU "*\n", tmp->type);
		printf("*" KBLU KBLD " -> D_Quotes[%d]                                             " RESET KBLU "*\n", tmp->d_quotes);
		printf("*" KBLU KBLD " -> S_Quotes[%d]                                             " RESET KBLU "*\n", tmp->s_quotes);
		printf("*" KBLU KBLD " -> C_brackets[%d]                                           " RESET KBLU "*\n", tmp->c_brackets);
		printf("*" KBLU KBLD " -> Whitespace[%d]                                           " RESET KBLU "*\n", tmp->ws);
		printf("*" KBLU KBLD " -> Str =          " RESET KBLD "%s" RESET KBLU "\n", tmp->str);
		printf(KBLU "**************************************************************\n" RESET);
		tmp = tmp->next;
	}
	ft_free_lst(&tmp);
}