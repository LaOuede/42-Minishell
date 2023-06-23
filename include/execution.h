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

typedef struct s_builtin
{
	void					(*operation_funcs[8])();
}							t_builtin;

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
	t_builtin		*builtin;
	int				cmd_nb;
	int				pipes_nb;
}			t_exec;

/*	--	Function Declarations for the execution of shell commands	--	*/
t_exec	*ft_init_exec(t_jct *jct);
void	ft_dup_proc(t_exec *exec, int i);
// void 	ft_pre_redir(t_exec *exec, int i);
int		ft_pre_redir(t_exec *exec, int i);
void	ft_close_fds(t_exec *exec);
// void	ft_close_fds(t_exec *exec, int i);
// int		ft_create_pipes(t_exec *exec);
int		ft_mem_pipes(t_exec *exec);
char	*ft_free_2char(char **tab);
void	ft_free_3tab(t_jct *jct);
void	ft_free_exec(t_exec *exec);
void	ft_exec(t_exec *exec);
void	ft_copy_env(t_jct *jct, char **envp);
char	*ft_cmd_path(t_exec *exec, char *cmds);
void	ft_free_3tab(t_jct *jct);
void	ft_run_cmd(t_exec *exec, int i);
// void	exec_hd(t_pars *pars, char *delim, int i);
int		ft_exec_hd(char *delim, t_pars *pars);
void	ft_reset_and_close(t_exec *exec);
void	ft_close_old_pipes(t_exec *exec, int i);

/*	--	Debug fct	--	*/
// void	ft_print_debug(t_exec *exec);

char	**ft_get_path(char **envp, int i);
t_builtin	*ft_get_builtin(void);

#endif