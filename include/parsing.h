#ifndef PARSING_H
# define PARSING_H

# include <stdbool.h>

/* --------------------COLORS--------------------- */
# define KNRM "\x1B[m"
# define KBLD "\x1B[1m"
# define KGRE "\x1B[2m"
# define KITA "\x1B[3m"
# define KUND "\x1B[4m"
# define KRST "\x1B[5m"
# define KRED "\x1B[31m"
# define KGRN "\x1B[32m"
# define KYEL "\x1B[33m"
# define KBLU "\x1B[34m"
# define KMAG "\x1B[35m"
# define KCYN "\x1B[36m"
# define KWHT "\x1B[37m"

//TODO add bracket type in function
enum e_token_type
{
	ERROR = -2,
	CMD = -1,
	ARG = 0,
	D_QUOTES = 1,
	S_QUOTES = 2,
	EXPAND = 3,
	PIPE = 4,
	REDIN = 5,
	APPRED = 6,
	REDOUT = 7,
	HEREDOC = 8,
};

enum e_gate
{
	OPEN = 1,
	CLOSE = 2,
};

// prototype de la liste chainee token
typedef struct s_token
{
	int				type; // cmd ou arg, ou flag ou operateur
	int				tab_type;
	char			*str;
	int				s_quotes;
	int				d_quotes;
	int				c_brackets;
	int				p_brackets;
	int				nb_cmd;
	int				ws;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

// Parsing main structure prototype... incomplete
typedef struct s_pars
{
	struct s_token	*line;
	char			*input;
	char			**envp;
	size_t			strlen;
	int				nb_pipe;
	int				type;
	int				s_quotes;
	int				d_quotes;
	int				c_brackets;
	int				p_brackets;
	int				flag_whitespace;
}	t_pars;
//TODO mieux gérer flag de brackets

/* 		Lexer part functions 						*/
void		ft_add_token_bottom(t_token **lst, t_token *element);
void		ft_add_token_top(t_token **lst, t_token *new_node);
void		ft_appenred_token(int *i, t_pars *pars);
void		ft_brackets_token(int *i, t_pars *pars);
void		ft_char(char c, int *i, t_pars *pars);
void		ft_clean_up(t_pars *pars);
t_token		*ft_create_node(char *str, t_pars *pars);
void		ft_d_quotes_token(int *i, t_pars *pars);
void		ft_envvar(int *i, t_pars *pars);
void		ft_envvar_token(int *i, t_pars *pars);
char		*ft_envvar_brackets_token(int *i, t_pars *pars, char *str);
//char		*ft_envvar_quotes_token(int *i, t_pars *pars, char *str);
char		*ft_envvar_quotes_token(char *str, t_pars *pars);
//void		ft_envvar_quotes_token(char *str, t_pars *pars);
void		ft_expansion_quotes(t_pars *pars);
void		ft_extract_cmd(t_token **list, t_pars *pars);
t_token		*ft_find_head(t_token **last);
void		ft_free_lst(t_token **lst);
void		ft_free_token(t_token *token);
void		ft_heredoc_token(int *i, t_pars *pars);
t_pars		*ft_init_pars(char **envp);
void		ft_insert_token(t_token **lst, t_token *prev, t_token *current, t_token *new_node);
bool		ft_isenvvarchar(char c);
bool		ft_ismetachar(char c);
void		ft_lexer(t_pars *pars);
void		ft_metachar(char c, int *i, t_pars *pars);
void		ft_parsing(t_pars *pars);
void		ft_pipe_token(int *i, t_pars *pars);
void		ft_rebuilder(t_pars *pars);
void		ft_redin_token(int *i, t_pars *pars);
void		ft_redout_token(int *i, t_pars *pars);
void		ft_remove_empty(t_token **list);
void		ft_reset_node(t_pars *pars);
void		ft_s_quotes_token(int *i, t_pars *pars);
char		*ft_stock_char(char *str, char c);
char		*ft_strjoin_char(const char *s1, const char s2);
char		*ft_strjoin_free(char *str1, char *str2);
void		ft_swap_node(t_token *swap1, t_token *swap2);
void		ft_add_token(t_token **lst, t_token *new_node);
char		*ft_quotes_expansion(char *str, t_pars *pars);
char		*ft_find_envvar(char *str, t_pars *pars);
void		ft_get_expand_brackets(int *i, t_pars *pars);
bool		ft_check_expand_brackets(char *str, t_pars *pars);
void		ft_get_expand_brackets_quotes(int *i, char *str, t_pars *pars);
void		ft_clean_list(t_token **list);
void		ft_parser(t_pars *pars);
void		ft_parser_debugger(t_pars *pars);

#endif
