
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

extern t_jct	*g_jct;

typedef struct s_ms
{
	struct s_minishell	*parsing;
	struct s_exec		*exec;
}	t_ms;

//	Struct prototype to make the junction between the parsing and the execution
typedef struct s_jct
{
	char	***tab;
	int		pipe_nb;
	int		cmd_nb;
	int		file_out;
	int		file_in;
	int		exit_status;
	int		fl_redirout;
	int		*fds;
	bool	err_pars;
}			t_jct;

/* 		Jct functions 							*/
void	ft_free_jct(void);

/* 		Signal functions 							*/
void	sig_handler(int sig);

#endif