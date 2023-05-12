#include "../include/minishell.h"

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

t_token	*ft_create_node(char *str)
{
	t_token	*new_node;

	new_node = ft_calloc(1, sizeof(t_token));
	new_node->type = -1;
	new_node->str = ft_strdup(str);
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
	while (parse->input[++i])
	{
		if (ft_iswhitespace(parse->input[i]) == 1)
			i++;
		if (ft_isprint(parse->input[i]) == 1)
			tmp = ft_stock_char(tmp, parse->input[i]);
		if (ft_iswhitespace(parse->input[i + 1]) == 1 || parse->input[i + 1] == '\0')
		{
			ft_add_token_bottom(&parse->line, ft_create_node(tmp));
			tmp = NULL;
		}
	}
}
