#include "../include/minishell.h"

void	ft_parser_debugger(t_pars *pars)
{
	t_token	*tmp;
	int		i = 0;

	tmp = pars->line;
	while (tmp)
	{
		printf(KGRE "**************************************************************\n");
		printf("*" KGRE KBLD "                          NODE[%d]                           " RESET KGRE "*\n", i++);
		printf("*" KGRE KBLD " -> Type[%d]                                                 " RESET KGRE "*\n", tmp->tab_type);
		printf(KGRE KBLD " -> Str = " RESET KBLD "%s" RESET KGRE "\n", tmp->str);
		printf(KGRE "**************************************************************\n" RESET);
		tmp = tmp->next;
	}
	ft_free_lst(&tmp);
}

void	ft_extract_cmd_debugger(t_pars *pars)
{
	t_token	*tmp;
	int		i = 0;

	tmp = pars->line;
	while (tmp)
	{
		printf(KMAG "**************************************************************\n");
		printf("*" KMAG KBLD "                          NODE[%d]                           " RESET KMAG "*\n", i++);
		printf("*" KMAG KBLD " -> Type[%d]                                                 " RESET KMAG "*\n", tmp->type);
		printf(KMAG KBLD " -> Str = " RESET KBLD "%s" RESET KMAG "\n", tmp->str);
		printf(KMAG "**************************************************************\n" RESET);
		tmp = tmp->next;
	}
	ft_free_lst(&tmp);
}

void	ft_rebuilder_debugger(t_pars *pars)
{
	t_token	*tmp;
	int		i = 0;

	tmp = pars->line;
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

void	ft_lexer_debugger(t_pars *pars)
{
	t_token	*tmp;
	int		i = 0;

	tmp = pars->line;
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

void	ft_reset_pars(t_pars *pars)
{
	ft_free_lst(&pars->line);
	pars->input = NULL;
	pars->line = NULL;
	pars->strlen = 0;
	pars->nb_pipe = 1;
	pars->type = ARG;
	pars->d_quotes = 0;
	pars->s_quotes = 0;
	pars->c_brackets = 0;
	pars->flag_whitespace = 0;
	pars->err_lexer = false;
	pars->err_rebuilder = false;
	pars->err_parser = false;
}

t_pars	*ft_init_pars(char **envp)
{
	static t_pars	*pars;

	if (!pars)
	{
		pars = ft_calloc(1, sizeof(t_pars));
		pars->input = NULL;
		pars->line = NULL;
		pars->envp = envp;
		pars->strlen = 0;
		pars->nb_pipe = 1;
		pars->type = ARG;
		pars->d_quotes = 0;
		pars->s_quotes = 0;
		pars->c_brackets = 0;
		pars->flag_whitespace = 0;
		pars->err_lexer = false;
		pars->err_rebuilder = false;
		pars->err_parser = false;
	}
	return (pars);
}

/*
Main function for parsing. Calls Lexer and Parser
and then returns a 2D arry to the executioner
*/
void	ft_parsing(t_pars *pars, t_jct *jct)
{
	printf(KYEL "-------------------- FT_PARSING" KGRN KBLD" START " RESET KYEL "--------------------\n" RESET);

	if (!*pars->input)
		return ;
	ft_lexer(pars);
	ft_lexer_debugger(pars);
	if (pars->line && pars->err_lexer == false)
	{
		ft_rebuilder(pars);
		ft_rebuilder_debugger(pars);
		ft_extract_cmd_debugger(pars);
		if (pars->err_rebuilder == false)
			ft_parser(pars, jct);
	}
	printf("err_lexer = %d\n", pars->err_lexer);
	printf("err_rebuilder = %d\n", pars->err_rebuilder);
	printf("err_parser = %d\n", pars->err_parser);
	if (pars->err_lexer == true || pars->err_rebuilder == true || pars->err_parser == true)
		jct->err_pars = true;
	printf("err_pars = %d\n", jct->err_pars);
	ft_reset_pars(pars);
	printf(KYEL "-------------------- FT_PARSING" KRED KBLD" END " RESET KYEL "--------------------\n" RESET);
}

/* TODO
1) DONE - No need to handle curly_brackets and parenthesis_brackets you fool!! 
So need to suppress functions
2) DONE - Also need to deal better with $ expansion. watch out for $ and $$...
   DONE - Need to deal with ${}
3) DONE - Check if whitespace flag is working. If not, handle it! ==> I think it's ok
4) DONE - Deal with double quotes and only after that deal with $ inside
5) DONE - Cleaning up the code a little bit (Need to redo this one!)
7) DONE - Re-construct the arguments (seems ok so far)
8) DONE - Clean up the linked-list (Remove empty node added)
9) DONE - Linked-list divided in cmd (CMD - ARG - REDIN - REDOUT)
10) DONE - Transfer linked-list into 2D table
11) DONE - Parse commands & Shoot error message when a parsing error is found

12) Handle memory wise girl !!
13) Check everything to make a list of what's missing.
14) Clean the code!

Rajouter flag de fin de parsing pour exec (add variable dans struct jct)
check : echo "$USER" <in "salut" salut no good although echo "$USER" <in salut salut is good
pb with EXPAND TYPE...
strtrim cmd
*/