#include "../include/minishell.h"

void	ft_reset_parse(t_minishell *parse)
{
	parse->nb_pipe = 1;
	parse->type = ARG;
	parse->fl_redin = 0;
	parse->fl_redout = 0;
	parse->d_quotes_in = 0;
	parse->d_quotes_out = 0;
}

t_minishell	*ft_init_parse(void)
{
	static t_minishell	*parse;

	if (!parse)
	{
		parse = ft_calloc(1, sizeof(t_minishell));
		parse->input = NULL;
		parse->line = NULL;
		parse->nb_pipe = 1;
		parse->fl_redin = 0;
		parse->fl_redout = 0;
		parse->type = ARG;
		parse->d_quotes_in = 0;
		parse->d_quotes_out = 0;
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
		printf("node[%d] nb_cmd[%d] type[%d] = %s\n", i++, tmp->nb_cmd, tmp->type, tmp->str);
		tmp = tmp->next;
	}
	free(tmp);
	// Free linked-list between prompt & clean up
	ft_reset_parse(parse);
	ft_free_lst(&parse->line);
}
