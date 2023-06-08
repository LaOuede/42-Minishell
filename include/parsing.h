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

/* --------------------ERROR MESSAGE--------------------- *///
# define ERR_INFILE		"Input Error : No such file or directory\n"
# define ERR_OUTFILE	"Input Error : File creation failed\n"
# define ERR_QUOTE		"Input Error : Quotation unclosed\n"
# define ERR_TOKEN		"Input Error : Invalid token combination\n"

typedef struct s_jct	t_jct;

enum e_token_type
{
	ERROR = -1,
	CMD = 0,
	ARG = 1,
	REDIN = 2,
	REDOUT = 3,
	PIPE = 4,
	EXPAND = 5,
	//TODO add token_type for here_doc
};

enum e_gate
{
	OPEN = 1,
	CLOSE = 2,
};

enum e_step
{
	LEXER = 1,
	REBUILDER = 2,
	PARSER = 3,
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
	int				file_out;
	int				file_in;
	bool			err_lexer;
	bool			err_rebuilder;
	bool			err_parser;
}	t_pars;

/* 		Debug functions 							*/
void	DEBUG_builder(t_pars *pars);
void	DEBUG_lexer(t_pars *pars);
void	DEBUG_parser(t_pars *pars);
void	DEBUG_tab(t_jct *jct);

/* 		Parsing functions 							*/
void	ft_parsing(t_pars *pars, t_jct *jct);
t_pars	*ft_init_pars(char **envp);
void	ft_reset_node(t_pars *pars);
void	ft_reset_pars(t_pars *pars);

/* 		Lexer part functions 						*/
void	ft_char(int *i, t_pars *pars);
bool	ft_check_expand_brackets(char *str, t_pars *pars);
void	ft_d_quotes_token(int *i, t_pars *pars);
void	ft_envvar(int *i, t_pars *pars);
void	ft_envvar_token(int *i, t_pars *pars);
char	*ft_find_envvar(char *str, t_pars *pars);
char	*ft_get_before(char *str, int *i);
void	ft_get_expand_brackets(int *i, t_pars *pars);
char	*ft_get_expand_brackets_quotes(int *i, char *str, t_pars *pars);
void	*ft_get_expansion(char *str, int *i, t_pars *pars);
bool	ft_isenvvarchar(char c);
bool	ft_ismetachar(char c);
void	ft_lexer(t_pars *pars);
void	ft_metachar(char c, int *i, t_pars *pars);
void	ft_pipe_token(int *i, t_pars *pars);
char	*ft_quotes_expansion(char *str, t_pars *pars);
void	ft_redin_token(int *i, t_pars *pars);
void	ft_redout_token(int *i, t_pars *pars);
void	ft_s_quotes_token(int *i, t_pars *pars);
char	*ft_stock_quotes(int *i, char *str, t_pars *pars);

/* 		Lexer utils part functions 						*/
void	ft_add_token_bottom(t_token **lst, t_token *element);
t_token	*ft_create_node(char *str, t_pars *pars);
char	*ft_mem_alloc(char *str, int capacity);
char	*ft_stock_char(char *str, char c);
char	*ft_strjoin_char(char *s1, char s2);
char	*ft_strjoin_free(char *str1, char *str2);

/* 		Builder part functions 						*/
void	ft_args(t_pars *pars);
void	ft_builder(t_pars *pars);
void	ft_clean_list(t_token **list);
void	ft_check_error_pipe(t_pars *pars);
void	ft_check_error_redir(t_pars *pars);
void	ft_create_file(t_token *node, t_pars *pars);
// void	ft_create_file(t_token *node, t_pars *pars, t_jct *jct);
void	ft_find_arg(t_pars *pars);
void	ft_find_cmd(t_pars *pars);
void	ft_find_redin(t_pars *pars);
void	ft_find_redout(t_pars *pars);
void	ft_finish(t_pars *pars);
void	ft_merge_allredin(t_pars *pars);
void	ft_merge_allredout(t_pars *pars);
void	ft_merge_arg(t_pars *pars);
void	ft_merge_in(t_pars *pars);
void	ft_merge_out(t_pars *pars);
void	ft_merge_pipe(t_pars *pars);
void	ft_merge_red(t_pars *pars);
void	ft_open_file(t_token *node, t_pars *pars);
void	ft_pipe(t_pars *pars);
void	ft_redirection(t_pars *pars);
void	ft_swap_node(t_pars *pars);

/* 		Parser part functions 						*/
void	ft_parser(t_pars *pars, t_jct *jct);
void	ft_check_pipe(t_pars *pars);
void	ft_check_redir(t_pars *pars);
void	ft_fill_tab(t_jct *jct, t_pars *pars);
void	ft_init_cmdtab(t_jct *jct);
char	*ft_trim(char *str, char c);
void	ft_trim_cmd(t_jct *jct);


/* 		Free functions 								*/
void	ft_free_lst(t_token **lst);
void	ft_free_pars(t_pars *pars);
void	ft_free_token(t_token *token);

/* 		Error functions 								*/
void	ft_error(char *err_msg);
void	ft_clean_up(t_pars *pars);
void	ft_clean_up_jct(t_jct *jct, char *err_msg);
void	ft_error_parsing(char *err_msg, int step, t_pars *pars);

#endif
