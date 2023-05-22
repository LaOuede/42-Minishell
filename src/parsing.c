#include "../include/minishell.h"

void	ft_reset_parse(t_minishell *parse)
{
	parse->nb_pipe = 1;
	parse->type = ARG;
	parse->fl_redin = 0;
	parse->fl_redout = 0;
	parse->d_quotes = 0;
	parse->s_quotes = 0;
	parse->p_brackets = 0;
	parse->c_brackets = 0;
	parse->flag = 0;
	parse->flag_whitespace = 0;
	parse->strlen = 0;
}

t_minishell	*ft_init_parse(char **envp)
{
	static t_minishell	*parse;

	if (!parse)
	{
		parse = ft_calloc(1, sizeof(t_minishell));
		parse->input = NULL;
		parse->line = NULL;
		parse->envp = envp;
		parse->strlen = 0;
		parse->nb_pipe = 1;
		parse->fl_redin = 0;
		parse->fl_redout = 0;
		parse->type = ARG;
		parse->d_quotes = 0;
		parse->s_quotes = 0;
		parse->p_brackets = 0;
		parse->c_brackets = 0;
		parse->flag = 0;
		parse->flag_whitespace = 0;
	}
	return (parse);
}

void	ft_parse(t_minishell *parse)
{
	t_token	*tmp;

	if (!*parse->input)
		return ;
	printf(KYEL "-------------------- FT_PARSING -------------------- \n" RESET);
	ft_lexer(parse);
	//ft_expansion_quotes(parse->line, parse);
	/* Print linked-list */
	int	i = 0;
	tmp = parse->line;
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
	/* Free linked-list between prompt & clean up */
	ft_reset_parse(parse);
	ft_free_lst(&parse->line);
	// TODO Fonction pour entrer la linked-list dans un tableau 2D
	// TODO rajouter une fonction qui check les erreurs avant l'envoi à l'exec
	// ex : if parse->s_quotes == OPEN alors retour d'erreur
}
