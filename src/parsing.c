#include "../include/minishell.h"

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
	}
	return (pars);
}

/*
Main function for parsing. Calls Lexer and Parser
and then returns a 2D arry to the executioner
*/
void	ft_parsing(t_pars *pars)
{
	printf(KYEL "-------------------- FT_PARSING" KGRN KBLD" START " RESET KYEL "--------------------\n" RESET);

	if (!*pars->input)
		return ;
	ft_lexer(pars);
	ft_lexer_debugger(pars);
	ft_rebuilder(pars);
	ft_rebuilder_debugger(pars);
	ft_extract_cmd(&pars->line, pars);
	ft_extract_cmd_debugger(pars);
	/* Free linked-list between prompt & clean up */
	ft_reset_pars(pars);
	ft_free_lst(&pars->line);
	// TODO G
	// TODO Fonction pour entrer la linked-list dans un tableau 2D
	// TODO rajouter une fonction qui check les erreurs avant l'envoi à l'exec
	// ex : if parse->s_quotes == OPEN alors retour d'erreur
	printf(KYEL "-------------------- FT_PARSING" KRED KBLD" END " RESET KYEL "--------------------\n" RESET);
}
