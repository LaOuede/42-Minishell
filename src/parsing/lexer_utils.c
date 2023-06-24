#include "../../include/minishell.h"

t_token	*ft_create_node(char *str, t_pars *pars)
{
	t_token	*new_node;

	new_node = ft_calloc(1, sizeof(t_token));
	new_node->type = pars->type;
	new_node->str = ft_strdup(str);
	new_node->s_quotes = pars->s_quotes;
	new_node->d_quotes = pars->d_quotes;
	new_node->c_brackets = pars->c_brackets;
	new_node->nb_cmd = pars->nb_pipe;
	new_node->ws = pars->flag_whitespace;
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

char	*ft_mem_alloc(char *str, int capacity)
{
	int		i;
	char	*new;

	new = ft_calloc(sizeof(new), (capacity * 2));
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

char	*ft_strjoin_char(char *s1, char s2)
{
	if (DEBUG)
		printf(KYEL "-------------------- FT_STRJOIN_CHAR" KGRN KBLD" START " RESET KYEL "--------------------\n" RESET);
	char	*s3;
	size_t	len;

	len = (ft_strlen(s1));
	s3 = ft_calloc((len + 2), sizeof(char));
	if (!s3)
		return (0);
	len = 0;
	while (s1[len])
	{
		if (DEBUG)
			printf("char = %c\n", s1[len]);
		s3[len] = s1[len];
		len++;
	}
	if (DEBUG)
		printf("len = %zu\n", len);
	s3[len] = s2;
	if (DEBUG)
		printf("s3 = %s\n", s3);
	ft_freenull(s1);
	if (DEBUG)
		printf(KYEL "-------------------- FT_STRJOIN_CHAR" KRED KBLD" END " RESET KYEL "--------------------\n" RESET);
	return (s3);
}
