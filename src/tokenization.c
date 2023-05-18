#include "../include/minishell.h"
//TODO : gérer les parenthèses et les curly brackets

// Special char = whitespaces, pipe, < >, $
void	ft_deal_metac(char c, int *index, t_minishell *parse)
{
	printf("META CHAR\n");
	printf("char = %c\n", parse->input[(*index)]);
	if (ft_iswhitespace(c == 1))
		(*index) += 1;
	else if (c == 34 && !parse->d_quotes)
		ft_d_quotes_token(index, parse);
	else if (c == 39)
		ft_s_quotes_token(index, parse);
	else if (c == '|')
		ft_pipes_token(index, parse);
	else if (c == '<' && parse->input[(*index) + 1] == '<')
		ft_appenred_token(index, parse);
	else if (c == '<')
		ft_redirin_token(index, parse);
	else if (c == '>' && parse->input[(*index) + 1] == '>')
		ft_heredoc_token(index, parse);
	else if (c == '>')
		ft_redirout_token(index, parse);
	else if (c == '$')
		ft_envvar_token(index, parse);
	else if (c == '(' || c == ')' || c == '{' || c == '}')
		ft_brackets_token(index, parse);
	else
		return ;
}

int	ft_ismetac(char c)
{
	if (ft_iswhitespace(c) == 1)
		return (1);
	if (c == '|' || c == '<' || c == '>' || c == 34 || c == 39
		|| c == '$' || c == '(' || c == ')' || c == '{' || c == '}')
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

char	*ft_strjoin_char(const char *s1, const char s2)
{
	size_t	i;
	char	*s3;
	size_t	len;

	len = (ft_strlen(s1) + 1);
	s3 = ft_calloc((len + 1), sizeof(char));
	if (!s3)
		return (0);
	len = 0;
	while (s1[len])
	{
		s3[len] = s1[len];
		len++;
	}
	i = 0;
	s3[len + i] = s2;
	free((char *)s1);
	return (s3);
}

t_token	*ft_create_node(char *str, t_minishell *parse)
{
	t_token	*new_node;

	new_node = ft_calloc(1, sizeof(t_token));
	new_node->type = parse->type;
	new_node->str = ft_strdup(str);
	new_node->nb_cmd = parse->nb_pipe;
	new_node->s_quotes = parse->s_quotes;
	new_node->d_quotes = parse->d_quotes;
	new_node->p_brackets = parse->p_brackets;
	new_node->c_brackets = parse->c_brackets;
	new_node->ws = parse->fl_ws;
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
	printf("TOKENIZATION\n");
	// TODO add gate for pipe, simple-quotes and double-quotes
	while (parse->input[++i])
	{
		if (ft_ismetac(parse->input[i]) == 1)
			ft_deal_metac(parse->input[i], &i, parse);
		if (ft_isprint(parse->input[i]) == 1 && parse->input[i] != 32 && !parse->flag)
		//if (ft_isprint(parse->input[i]) == 1 && ft_ismetac(parse->input[i]) == 0 && !parse->flag)
			tmp = ft_stock_char(tmp, parse->input[i]);
		if (ft_ismetac(parse->input[i]) == 1)
			ft_deal_metac(parse->input[i], &i, parse);
		printf("char tokenization = %c\n", parse->input[(i)]);
		printf("tmp = %s\n", tmp);
		// TODO Add flag pour les espaces entre les arguments
		if ((ft_iswhitespace(parse->input[i + 1]) == 1 || parse->input[i + 1] == '\0' || ft_ismetac(parse->input[i + 1]) == 1) && tmp != NULL)
		{
			if ((parse->input[i]) != 34 && (parse->input[i]) != 39)
			ft_add_token_bottom(&parse->line, ft_create_node(tmp, parse));
			tmp = NULL;
		}
	}
}

void	ft_deal_char(char c, int *i, t_minishell *parse)
{
	char	*tmp;

	tmp = NULL;
	(void)c;
	printf("DEAL CHAR\n");
	while (ft_iswhitespace(parse->input[(*i)]) == 1)
	{
		printf("white space\n");
		parse->fl_ws = 42;
		(*i)++;
	}
	while (parse->input[(*i)] && ft_ismetac(parse->input[(*i)]) == 0)
	{
		printf("char DEAL CHAR = %c\n", parse->input[(*i)]);
		tmp = ft_stock_char(tmp, parse->input[(*i)]);
		(*i)++;
	}
	if (tmp)
	{
		ft_add_token_bottom(&parse->line, ft_create_node(tmp, parse));
		tmp = NULL;
	}
	printf("i DEAL CHAR = %d\n", (*i));
	printf("char fin DEAL CHAR = %c\n", parse->input[(*i)]);
}

void	ft_deal_metac2(char c, int *i, t_minishell *parse)
{
	printf("META CHAR2\n");
	printf("char META CHAR2 = %c\n", parse->input[(*i)]);
	printf("i META CHAR = %d\n", (*i));
	if (c == '|')
		ft_pipes_token(i, parse);
	else if (c == '<' && parse->input[(*i) + 1] == '<')
		ft_appenred_token(i, parse);
	else if (c == '<')
		ft_redirin_token(i, parse);
	else if (c == '>' && parse->input[(*i) + 1] == '>')
		ft_heredoc_token(i, parse);
	else if (c == '>')
		ft_redirout_token(i, parse);
	else if (c == '(' || c == ')' || c == '{' || c == '}')
		ft_brackets_token(i, parse);
	else if (c == '$')
		ft_envvar_token(i, parse);
	else if (c == 34)
		ft_d_quotes_token(i, parse);
	else if (c == 39)
		ft_s_quotes_token(i, parse);
}

int	ft_ismetac2(char c)
{
	if (c == '|' || c == '<' || c == '>' || c == 34 || c == 39
		|| c == '$' || c == '(' || c == ')' || c == '{' || c == '}')
		return (1);
	return (0);
}

// TODO REfaire la fonction au 
void	ft_lexer(t_minishell *parse)
{
	int	i;
	int	len;

	i = 0;
	printf("LEXER\n");
	len = ft_strlen(parse->input);
	printf("len = %d\n", len);
	while (i < len)
	{
		printf("char lexer = %c\n", parse->input[(i)]);
		if (ft_ismetac2(parse->input[i]) == 1)
			ft_deal_metac2(parse->input[i], &i, parse);
		else
			ft_deal_char(parse->input[i], &i, parse);
		printf("i LEXER = %d\n", i);
	}
}
