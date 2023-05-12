#include "../include/minishell.h"

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
	}
	return (parse);
}

void	ft_parse(t_minishell *parse)
{
	int	i = 0;
	t_token	*tmp;

	if (!*parse->input)
		return ;
	ft_tokenization(parse);
	// Print linked-list
	tmp = parse->line;
	i = 0;
	while (tmp)
	{
		printf("node[%d] nb_cmd[%d] type[%d] = %s\n", i++, tmp->nb_cmd, tmp->type, tmp->str);
		tmp = tmp->next;
	}
	free(tmp);
	// Free linked-list between prompt & clean up
	parse->nb_pipe = 1;
	parse->type = ARG;
	ft_free_lst(&parse->line);
}
