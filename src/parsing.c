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
		printf("*" KBLU KBLD " -> P_brackets[%d]                                           " RESET KBLU "*\n", tmp->p_brackets);
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
	pars->input = NULL;
	pars->line = NULL;
	pars->strlen = 0;
	pars->nb_pipe = 1;
	pars->type = ARG;
	pars->d_quotes = 0;
	pars->s_quotes = 0;
	pars->p_brackets = 0;
	pars->c_brackets = 0;
	pars->flag_whitespace = 0;
	pars->flag_error_lexer = false;
	pars->flag_error_rebuilder = false;
	pars->flag_error_parser = false;
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
		pars->p_brackets = 0;
		pars->c_brackets = 0;
		pars->flag_whitespace = 0;
		pars->flag_error_lexer = false;
		pars->flag_error_rebuilder = false;
		pars->flag_error_parser = false;
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
	if (pars->flag_error_lexer == false)
	{
		ft_rebuilder(pars);
		ft_rebuilder_debugger(pars);
		ft_extract_cmd_debugger(pars);
		ft_parser(pars, jct);
	}
	/* Free linked-list between prompt & clean up */
	ft_reset_pars(pars);
	ft_free_lst(&pars->line);
	// TODO rajouter une fonction qui check les erreurs avant l'envoi à l'exec
	// ex : if parse->s_quotes == OPEN alors retour d'erreur
	// TODO Fonction pour entrer la linked-list dans un tableau 2D
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

Lexer almost done. Parser here I come!

10) Transfer linked-list into 2D table
11) Parse commands
12) Shoot error message when a parsing error is found
13) Handle memory wise girl !!
12) Check everything to make a list of what's missing.
15) Clean the code!
*/