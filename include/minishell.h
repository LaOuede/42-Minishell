
#ifndef MINISHELL_H
# define MINISHELL_H

# define READLINE_LIBRARY
# include <fcntl.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "../libs/libft/includes/libft.h"
# include "readline.h"
# include "parsing.h"
# include "builtins.h"
# include "execution.h"
# include "history.h"
// # include "../C_tools/C_tool.h" //TODO to remove later

# define RED 	"\x1B[31m"
# define GRN 	"\x1B[32m"
# define BLU 	"\x1B[34m"
# define WHT 	"\x1B[37m"
# define YEL 	"\x1B[33m"
# define RESET	"\033[1;0m"

/* --------------------ERROR MESSAGE--------------------- *///
# define ERR_EXEC	"Usage error : too many arguments.\n--> Usage : ./Minishell\n"
# define ERR_EXI1	"Usage error : exit: too many arguments\n"
# define ERR_EXI2	"Usage error : exit: numeric argument required\n"

# define DEBUG 0
# define MAIN 42
# define EXEC 666
# define HD 7
# define CHILD 1

typedef struct s_ms
{
	struct s_pars	*pars;
	struct s_exec	*exec;
	struct s_jct	*jct;
	struct s_pars	*hd;
	int				flexit;
}	t_ms;

//	Struct prototype to make the junction between the parsing and the execution
typedef struct s_jct
{
	int		*fds_in;
	int		*fds_out;
	char	***tab;
	char	**envp;
	int		cmd_nb;
	int		fd_hd;
	bool	err_pars;
	//TODO do we still need those 3 variables ?
	int		file_in;
	int		file_out;
	int		fl_redirout;
}			t_jct;

t_ms	*ft_init_ms(char **envp);
void	ft_exit_free(t_ms *ms, int flexit);

/* 		Jct functions 							*/
t_jct	*ft_init_jct(char **envp);
void	ft_free_jct(t_jct *jct);
void	ft_free_child(t_ms *ms);
void	ft_free_all(t_ms *ms);
void	ft_reset_jct(t_jct *jct);

/* 		Signal functions 						*/
void	ft_init_sig(int phase);

/* 		hd parsing functions 					*/
void	ft_hd_parser(t_ms *ms);
void	ft_str_hd(int *i, t_ms *ms);
void	ft_envvar_hd(int *i, char *str, t_ms *ms);
bool	ft_check_expand_brackets_hd(char *str, t_ms *ms);
void	ft_get_expand_brackets_hd(int *i, char *str, t_ms *ms);
void	ft_envvar_token_hd(int *i, char *str, t_ms *ms);
void	DEBUG_hd(t_pars *hd);
void	ft_reset_pars(t_pars *pars);
void	print_hd(t_pars *hd, int fd_hd);
void	ft_merge_hd(t_pars *hd);

#endif