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
	char 	*input_file_name;
	int		output;
	char 	*output_file_name;
	int		index;
	int		fl_redirin;
	int		fl_redirout;
	int		fl_hdr;
	int		fl_hdl;
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
void	ft_dup_process(t_exec *exec, int i);
void	ft_close_pipes(t_exec *exec);
void	ft_create_pipes(t_exec *exec);
void	ft_err(char *msg, t_exec *exec);
void	ft_free_exec(t_exec *exec);
void	ft_exec_jct(t_exec *exec, t_jct *jct);
void	ft_exec(t_exec *exec);
void	ft_copy_env(t_exec *exec, char **envp);
void	ft_is_operator(t_exec *exec);
char	*ft_cmd_path(t_exec *exec, char *cmds);
void	ft_free_3tab(t_jct *jct);

/*	--	Temp fct, to delete once the parsing is ready	--	*/
void	ft_cmd_nb(t_exec *exec);
void	ft_run_cmd_jct(t_exec *exec, t_jct *jct, int i);
void	ft_run_cmd(t_exec *exec);

/*	--	Debug fct	--	*/
void	ft_print_debug(t_exec *exec);

#endif