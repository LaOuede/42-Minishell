#include "../include/minishell.h"

void	ft_reset_parse(t_minishell *parse)
{
	parse->nb_pipe = 1;
	parse->type = ARG;
	parse->fl_redin = 0;
	parse->fl_redout = 0;
	parse->s_quotes = 0;
	parse->s_quotes = 0;
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
		parse->nb_pipe = 1;
		parse->fl_redin = 0;
		parse->fl_redout = 0;
		parse->type = ARG;
		parse->d_quotes = 0;
		parse->s_quotes = 0;
	}
	return (parse);
}

void	ft_parse(t_minishell *parse)
{
	t_token	*tmp;

	if (!*parse->input)
		return ;
	ft_tokenization(parse);
	// Print linked-list
	int	i = 0;
	tmp = parse->line;
	while (tmp)
	{
		printf("node[%d] nb_cmd[%d] type[%d] Quote [%d] Str = %s\n", i++, tmp->nb_cmd, tmp->type, tmp->d_quotes, tmp->str);
		tmp = tmp->next;
	}
	free(tmp);
	// Free linked-list between prompt & clean up
	ft_reset_parse(parse);
	ft_free_lst(&parse->line);
	// TODO Fonction pour entrer la linked-list dans un tableau 2D
	// TODO rajouter une fonction qui check les erreurs avant l'envoi à l'exec
	// ex : if parse->s_quotes == OPEN alors retour d'erreur
}
