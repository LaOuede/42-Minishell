#ifndef EXECUTION_H
# define EXECUTION_H

# include <stdlib.h>
# include "minishell.h"

# define BLD "\x1B[1m"

typedef struct s_jct	t_jct;

/*
**	Structure that holds all infomration needed for the execution
*/
typedef struct s_exec
{
	//to keep
	char	**envp;
	char	**path_var;
	int		input;
	char 	*file_in;
	int		output;
	char 	*file_out;
	int		index;
	int		fl_redirin;
	int		fl_redirout;
	int		fl_hd_out;
	int		fl_hd_in;
	pid_t	*pids;
	int		**pipes;
	//to delete - will be in t_jct
	int		cmd_nb;
	int		pipes_nb;
	//to delete - obselete
	char 	*line;
	char	**readline;
	char	**av;
	int		pipes_op;
	int		fl_pipe_op; 
}			t_exec;

/*	--	Function Declarations for the execution of shell commands	--	*/
t_exec	*ft_init_exec(char **envp, t_jct *jct);
// void	ft_dup_process(t_exec *exec, int i);
void	ft_dup_process(t_exec *exec, int i);
void	ft_close_pipes(t_exec *exec);
int		ft_create_pipes(t_exec *exec);
void	ft_free_exec(t_exec *exec);
void	ft_exec(t_exec *exec, t_jct *jct);
void	ft_copy_env(t_exec *exec, char **envp);
char	*ft_cmd_path(t_exec *exec, char *cmds);
void	ft_free_3tab(t_jct *jct);
void	ft_run_cmd(t_exec *exec, t_jct *jct, int i);
void	exec_hd(t_pars *pars, char *delim);

/*	--	Debug fct	--	*/
void	ft_print_debug(t_exec *exec);

#endif