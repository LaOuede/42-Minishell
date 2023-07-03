/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gle-roux <gle-roux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 08:48:10 by gle-roux          #+#    #+#             */
/*   Updated: 2023/07/03 09:43:26 by gle-roux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

/* --------------------ERROR MESSAGE--------------------- *///
# define ERR_INFILE		"Input Error : No such file or directory\n"
# define ERR_OUTFILE	"Input Error : File creation failed\n"
# define ERR_QUOTE		"Input Error : Quotation unclosed\n"
# define ERR_TOKEN		"Input Error : Invalid token combination\n" 
# define ERR_ACCESS		"Input Error : Command not found\n"

typedef struct s_jct	t_jct;
typedef struct s_ms		t_ms;

enum e_token_type
{
	ACCESS_ERR = -2,
	ERROR = -1,
	CMD = 0,
	REDIN = 1,
	REDOUT = 2,
	PIPE = 3,
	ARG = 4,
	EXPAND = 5,
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

typedef struct s_tab
{
	struct s_token	*ptr;
	int				r;
	int				c;
}	t_tab;

typedef struct s_token
{
	int				type;
	char			*str;
	int				s_quotes;
	int				d_quotes;
	int				c_brackets;
	int				nb_cmd;
	int				ws;
	int				hd;
	bool			echo;
	bool			red;
	struct s_token	*next;
}	t_token;

typedef struct s_pars
{
	struct s_token	*line;
	char			*input;
	char			**envp;
	char			**path_var;
	size_t			strlen;
	int				nb_pipe;
	int				type;
	int				s_quotes;
	int				d_quotes;
	int				c_brackets;
	int				fl_ws;
	int				hd;
	bool			fl_red;
	bool			fl_pipe;
	bool			err_infile;
	bool			err_lexer;
	bool			err_builder;
	bool			err_filler;
	bool			err_parser;
}	t_pars;

/*	--	Function Declarations for the parsing of shell commands	--	*/
/* 		Parsing functions 							*/
void	ft_parsing(t_ms *ms);
t_pars	*ft_init_pars(t_ms *ms);
void	ft_reset_node(t_pars *pars);

/* 		Lexer part functions 						*/
void	ft_char(int *i, t_ms *ms);
void	ft_char_quotes(int *i, char *str, t_ms *ms);
void	ft_check_access(t_ms *ms);
bool	ft_check_expand_brackets(char *str, t_ms *ms);
void	ft_d_quotes_token(int *i, t_ms *ms);
void	ft_envvar(int *i, char *str, t_ms *ms);
void	ft_envvar_token(int *i, char *str, t_ms *ms);
char	*ft_find_envvar(char *str, t_ms *ms);
void	ft_get_expand_brackets(int *i, char *str, t_ms *ms);
void	ft_lexer(t_ms *ms);
void	ft_metachar(char c, int *i, t_ms *ms);
void	ft_token(int *i, t_ms *ms);
void	ft_s_quotes_token(int *i, t_ms *ms);
char	*ft_stock_quotes(int *i, char *str, t_ms *ms);

/* 		Lexer utils part functions 						*/
void	ft_add_token_bottom(t_token **lst, t_token *element);
t_token	*ft_create_node(t_ms *ms, char *str, t_pars *pars);
void	ft_exit_status(t_ms *ms, int *i);
bool	ft_isenvvarchar(char c);
bool	ft_ismetachar(char c);
char	*ft_mem_alloc(t_ms *ms, char *str, int capacity);
char	*ft_stock_char(t_ms *ms, char *str, char c);
char	*ft_strjoin_char(t_ms *ms, char *s1, char s2);

/* 		Builder part functions 						*/
void	ft_args(t_ms *ms);
bool	ft_bi(t_token *node);
void	ft_builder(t_ms *ms);
void	ft_check_error_redir(t_ms *ms);
void	ft_clean_list(t_token **list);
void	ft_create_file(t_ms *ms);
void	ft_find_cmd(t_ms *ms);
void	ft_lower_cmd(char *str);
void	ft_merge(t_token *node, t_token *next);
void	ft_merge_all_red(t_ms *ms);
void	ft_merge_all_arg(t_ms *ms);
void	ft_merge_angle_brackets_in(t_pars *pars);
void	ft_merge_angle_brackets_out(t_pars *pars);
void	ft_merge_arg(t_pars *pars);
void	ft_merge_red(t_ms *ms);
void	ft_open_file(t_ms *ms);
void	ft_open_hd(t_ms *ms);
void	ft_redirection(t_ms *ms);
void	ft_swap(t_token *ptr1, t_token *ptr2);
void	ft_swap_node(t_pars *pars);
bool	ft_test_cmd(t_pars *pars, t_token *node);

/* 		Parser part functions 						*/
void	ft_filler(t_ms *ms);
void	ft_check_redir(t_ms *ms);
void	ft_check_pipe(t_ms *ms);
void	ft_init_cmdtab(t_ms *ms);
t_tab	*ft_init_tab(t_ms *ms, t_pars *pars);
void	ft_fill_tab(t_ms *ms, t_tab *tab);

/* 		Free functions 								*/
void	ft_free_lst(t_token **lst);
void	ft_free_pars(t_pars *pars);
void	ft_free_token(t_token *token);

/* 		Error functions 								*/
void	ft_error(char *err_msg);
void	ft_error_exit(char *err_msg, int exit);
void	ft_clean_up_jct(char *err_msg, t_jct *jct);
void	ft_error_parsing(char *err_msg, int step, int exit, t_ms *ms);

#endif
