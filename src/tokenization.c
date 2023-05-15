#include "../include/minishell.h"

// Special char = whitespaces, pipe, < >, $
void	ft_deal_metac(char c, int *index, t_minishell *parse)
{
	if (ft_iswhitespace(c == 1))
		(*index) += 1;
	else if (c == 34)
		ft_d_quotes_token(index, parse);
	else if (c == 39)
		ft_s_quotes_token(index, parse);
	else if (c == '|')
		ft_pipes_token(index, parse);
	else if (c == '<')
	{
		parse->type = REDIN;
		parse->fl_redin = 1;
	}
	else if (c == '>')
	{
		parse->type = REDOUT;
		parse->fl_redout = 1;
	}
}

int	ft_ismetac(char c)
{
	if (ft_iswhitespace(c) == 1)
		return (1);
	if (c == '|' || c == '<' || c == '>' || c == 34 || c == 39)
		return (1);
	return (0);
}

char	*ft_mem_alloc(char *str, int capacity)
{
	int		i;
	char	*new;

	new = ft_calloc(sizeof(new), (capacity * 2));
	if (!new)
		return (0);
	i = 0;
	while (str[i])
	{
		new[i] = str[i];
		i++;
	}
	free(str);
	return (new);
}

char	*ft_stock_char(char *str, char c)
{
	static int	i = 0;
	static int	size = 0;
	static int	capacity = 2;

	if (!str)
	{
		i = 0;
		size = 0;
		capacity = 2;
		str = ft_calloc(sizeof(str), capacity);
	}
	str[i++] = c;
	if (size++ == capacity)
	{
		str = ft_mem_alloc(str, capacity);
		capacity *= 2;
	}
	return (str);
}

t_token	*ft_create_node(char *str, t_minishell *parse)
{
	t_token	*new_node;

	new_node = ft_calloc(1, sizeof(t_token));
	new_node->type = parse->type;
	new_node->str = ft_strdup(str);
	new_node->nb_cmd = parse->nb_pipe;
	new_node->prev = NULL;
	new_node->next = NULL;
	return (new_node);
}

void	ft_add_token_bottom(t_token **lst, t_token *new_node)
{
	t_token	*last;

	if (!new_node)
		return ;
	if (*lst == NULL)
	{
		*lst = new_node;
		new_node->prev = NULL;
		return ;
	}
	last = *lst;
	while (last->next != NULL)
		last = last->next;
	last->next = new_node;
	new_node->prev = last;
}

void	ft_tokenization(t_minishell *parse)
{
	int		i;
	char	*tmp;

	i = -1;
	tmp = NULL;
	// TODO add gate for pipe, simple-quotes and double-quotes
	while (parse->input[++i])
	{
		if (ft_ismetac(parse->input[i]) == 1)
			ft_deal_metac(parse->input[i], &i, parse);
		if (ft_isprint(parse->input[i]) == 1 && parse->input[i] != 32 )
			tmp = ft_stock_char(tmp, parse->input[i]);
		if ((ft_iswhitespace(parse->input[i + 1]) == 1 || parse->input[i + 1] == '\0' || ft_ismetac(parse->input[i + 1]) == 1) && tmp != NULL)
		{
			ft_add_token_bottom(&parse->line, ft_create_node(tmp, parse));
			tmp = NULL;
		}
	}
}
