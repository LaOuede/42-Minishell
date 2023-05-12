#ifndef PARSING_H
# define PARSING_H

// prototype de la liste chainee token
typedef struct s_token
{
	int				type; // cmd ou arg, ou flag ou operateur
	char			*str;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

// Parsing main structure prototype... incomplete
typedef struct s_minishell
{
	struct s_token	*line;
	char			*input;
}	t_minishell;

/* 		Lexer part functions 						*/
void		ft_add_token_bottom(t_token **lst, t_token *element);
void		ft_clean_up(t_minishell *parse);
t_token		*ft_create_node(char *str);
void		ft_free_lst(t_token **lst);
t_minishell	*ft_init_parse(void);
void		ft_parse(t_minishell *parse);
void		ft_tokenization(t_minishell *parse);

#endif
