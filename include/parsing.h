#ifndef PARSING_H
# define PARSING_H

# include <stdbool.h>

enum e_metac
{
	ARG = -1,
	PIPE = 0,
	REDIN = 1,
	REDOUT = 2,
	D_QUOTES = 3,
	S_QUOTE = 4,
};

// prototype de la liste chainee token
typedef struct s_token
{
	int				type; // cmd ou arg, ou flag ou operateur
	char			*str;
	int				nb_cmd;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

// Parsing main structure prototype... incomplete
typedef struct s_minishell
{
	struct s_token	*line;
	char			*input;
	bool			fl_redin;
	bool			fl_redout;
	int				nb_pipe;
	int				type;
	int				d_quotes_in;
	int				d_quotes_out;
}	t_minishell;

/* 		Lexer part functions 						*/
void		ft_add_token_bottom(t_token **lst, t_token *element);
void		ft_clean_up(t_minishell *parse);
t_token		*ft_create_node(char *str, t_minishell *parse);
void		ft_free_lst(t_token **lst);
t_minishell	*ft_init_parse(void);
void		ft_parse(t_minishell *parse);
void		ft_quotes_token(int *i, t_minishell *parse);
char		*ft_stock_char(char *str, char c);
void		ft_tokenization(t_minishell *parse);

#endif
