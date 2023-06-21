
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

# define RED 	"\x1B[31m"
# define GRN 	"\x1B[32m"
# define BLU 	"\x1B[34m"
# define WHT 	"\x1B[37m"
# define YEL 	"\x1B[33m"
# define RESET	"\033[1;0m"

/* --------------------ERROR MESSAGE--------------------- *///
# define ERR_EXEC		"Usage error : Too many arguments.\n--> Usage : ./Minishell\n"

# define ADD 0

extern int	g_exit_status;

typedef struct s_ms
{
	struct s_minishell	*parsing;
	struct s_exec		*exec;
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

void	ft_exit(t_exec *exec);

/* 		Jct functions 							*/
t_jct	*ft_init_jct(char **envp);
void	ft_free_jct(t_jct *jct);
void	ft_free_all(t_jct *jct, t_pars *pars, t_exec *exec);

/* 		Signal functions 							*/
void	init_sig_handlers(void);
void	init_sig_exec_handlers(void);

#endif