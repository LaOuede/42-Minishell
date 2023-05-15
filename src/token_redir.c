#include "../include/minishell.h"

void	ft_redirin_token(int *i, t_minishell *parse)
{
	char	*tmp;

	tmp = NULL;
	tmp = ft_stock_char(tmp, parse->input[(*i)]);
	parse->type = REDIN;
	parse->fl_redin = 1;
	ft_add_token_bottom(&parse->line, ft_create_node(tmp, parse));
	(*i)++;
	parse->type = ARG;
}

void	ft_redirout_token(int *i, t_minishell *parse)
{
	char	*tmp;

	tmp = NULL;
	tmp = ft_stock_char(tmp, parse->input[(*i)]);
	parse->type = REDOUT;
	parse->fl_redout = 1;
	ft_add_token_bottom(&parse->line, ft_create_node(tmp, parse));
	(*i)++;
	parse->type = ARG;
}

void	ft_appenred_token(int *i, t_minishell *parse)
{
	char	*tmp;

	tmp = NULL;
	while (parse->input[(*i)] == '<')
	{
		tmp = ft_stock_char(tmp, parse->input[(*i)]);
		(*i)++;
	}
	parse->type = APPRED;
	ft_add_token_bottom(&parse->line, ft_create_node(tmp, parse));
	(*i)++;
	parse->type = ARG;
}

void	ft_heredoc_token(int *i, t_minishell *parse)
{
	char	*tmp;

	tmp = NULL;
	while (parse->input[(*i)] == '>')
	{
		tmp = ft_stock_char(tmp, parse->input[(*i)]);
		(*i)++;
	}
	parse->type = HEREDOC;
	ft_add_token_bottom(&parse->line, ft_create_node(tmp, parse));
	(*i)++;
	parse->type = ARG;
}
