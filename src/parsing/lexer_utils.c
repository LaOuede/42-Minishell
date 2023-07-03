/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gle-roux <gle-roux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 08:48:10 by gle-roux          #+#    #+#             */
/*   Updated: 2023/07/03 09:42:21 by gle-roux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_token	*ft_create_node(t_ms *ms, char *str, t_pars *pars)
{
	t_token	*new_node;

	new_node = ft_calloc_msh(1, sizeof(t_token), ms);
	new_node->type = pars->type;
	new_node->str = ft_strdup(str);
	new_node->s_quotes = pars->s_quotes;
	new_node->d_quotes = pars->d_quotes;
	new_node->c_brackets = pars->c_brackets;
	new_node->nb_cmd = pars->nb_pipe;
	new_node->ws = pars->fl_ws;
	new_node->hd = pars->hd;
	new_node->echo = false;
	new_node->red = false;
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
		new_node->next = NULL;
		return ;
	}
	last = *lst;
	while (last->next != NULL)
		last = last->next;
	last->next = new_node;
}

char	*ft_mem_alloc(t_ms *ms, char *str, int capacity)
{
	int		i;
	char	*new;

	new = ft_calloc_msh(sizeof(new), (capacity * 2), ms);
	if (!new)
		return (NULL);
	i = 0;
	while (str[i])
	{
		new[i] = str[i];
		i++;
	}
	free(str);
	return (new);
}

char	*ft_stock_char(t_ms *ms, char *str, char c)
{
	static int	i = 0;
	static int	size = 0;
	static int	capacity = 2;

	if (!str)
	{
		i = 0;
		size = 0;
		capacity = 2;
		str = ft_calloc_msh(sizeof(str), capacity, ms);
	}
	str[i++] = c;
	if (size++ == capacity)
	{
		str = ft_mem_alloc(ms, str, capacity);
		capacity *= 2;
	}
	return (str);
}

char	*ft_strjoin_char(t_ms *ms, char *s1, char s2)
{
	char	*s3;
	size_t	len;

	len = (ft_strlen(s1));
	s3 = ft_calloc_msh((len + 2), sizeof(char), ms);
	if (!s3)
		return (0);
	len = 0;
	while (s1[len])
	{
		s3[len] = s1[len];
		len++;
	}
	s3[len] = s2;
	s1 = ft_freenull(s1);
	return (s3);
}
