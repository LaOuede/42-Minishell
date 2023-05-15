#ifndef PARSING_H
# define PARSING_H

# include <stdbool.h>

enum e_metac
{
	ARG = 0,
	PIPE = 1,
	REDIN = 2,
	REDOUT = 3,
	D_QUOTES = 4,
	S_QUOTES = 5,
	APPRED = 6,
	HEREDOC = 7,
};

enum e_gate
{
	OPEN = 1,
	CLOSED = 2,
};

// prototype de la liste chainee token
typedef struct s_token
{
	int				type; // cmd ou arg, ou flag ou operateur
	char			*str;
	int				s_quotes;
	int				d_quotes;
	int				nb_cmd;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

// Parsing main structure prototype... incomplete
typedef struct s_minishell
{
	struct s_token	*line;
	char			*input;
	char			**envp;
	bool			fl_redin;
	bool			fl_redout;
	int				nb_pipe;
	int				type;
	int				s_quotes;
	int				d_quotes;
}	t_minishell;

/* 		Lexer part functions 						*/
void		ft_add_token_bottom(t_token **lst, t_token *element);
void		ft_appenred_token(int *i, t_minishell *parse);
void		ft_clean_up(t_minishell *parse);
t_token		*ft_create_node(char *str, t_minishell *parse);
void		ft_d_quotes_token(int *i, t_minishell *parse);
void		ft_envvar_token(int *i, t_minishell *parse);
void		ft_free_lst(t_token **lst);
void		ft_heredoc_token(int *i, t_minishell *parse);
t_minishell	*ft_init_parse(char **envp);
int			ft_ismetac(char c);
void		ft_parse(t_minishell *parse);
void		ft_pipes_token(int *i, t_minishell *parse);
void		ft_redirin_token(int *i, t_minishell *parse);
void		ft_redirout_token(int *i, t_minishell *parse);
void		ft_s_quotes_token(int *i, t_minishell *parse);
char		*ft_stock_char(char *str, char c);
void		ft_tokenization(t_minishell *parse);

#endif
