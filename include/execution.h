#ifndef EXECUTION_H
# define EXECUTION_H

# include <stdlib.h>
# include "minishell.h"

# define BLD "\x1B[1m"

# define PIPE_NO 0
# define PIPE_IN 1
# define PIPE_OUT 2
# define PIPE_IN_OUT 3

typedef struct s_jct	t_jct;

/*
**	Structure that holds all infomration needed for the execution
*/
typedef struct s_exec
{
	//to keep
	char			**envp;
	char			**path_var;
	int				input;
	int				fd_in;
	int				fd_out;
	int				output;
	pid_t			*pids;
	int				**pipes;
	struct s_jct	*jct;
	int				cmd_nb;
	int				pipes_nb;
}			t_exec;

/*	--	Function Declarations for the execution of shell commands	--	*/
t_exec	*ft_init_exec(char **envp, t_jct *jct);
void	ft_dup_proc(t_exec *exec, int i);
void 	ft_pre_redir(t_exec *exec, int i);
void	ft_close_fds(t_exec *exec);
int		ft_create_pipes(t_exec *exec);
char	*ft_free_2char(char **tab);
void	ft_free_3tab(t_jct *jct);
void	ft_free_exec(t_exec *exec);
void	ft_exec(t_exec *exec, t_jct *jct);
void	ft_copy_env(t_exec *exec, char **envp);
char	*ft_cmd_path(t_exec *exec, char *cmds);
void	ft_free_3tab(t_jct *jct);
void	ft_run_cmd(t_exec *exec, t_jct *jct, int i);
// void	exec_hd(t_pars *pars, char *delim, int i);
int		exec_hd(char *delim);

/*	--	Debug fct	--	*/
// void	ft_print_debug(t_exec *exec);

#endif