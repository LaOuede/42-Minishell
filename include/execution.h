#ifndef EXECUTION_H
# define EXECUTION_H

# include <stdlib.h>
# include "minishell.h"

# define BLD "\x1B[1m"

/*
**	Structure that holds all infomration needed for the execution
*/
typedef struct s_exec
{
	char 	*line;
	char	**av;
	char	**readline;
	char	**envp;
	char	**path_var;
	int		input;
	char 	*input_file_name;
	int		output;
	char 	*output_file_name;
	int		index;
	int		pipes_nb;
	int		pipes_op;
	int		cmd_nb;
	int		**pipes;
	pid_t	*pids;
	int		fl_pipe_op;
	int		fl_redirin;
	int		fl_redirout;
}			t_exec;

/*
**	Function Declarations for the execution of shell commands
*/
t_exec	*ft_init_exec(int ac, char **av, char **envp);
void	ft_dup_process(t_exec *exec, int i);
void	ft_close_pipes(t_exec *exec);
void	ft_create_pipes(t_exec *exec);
void	ft_err(char *msg, t_exec *exec);
void	ft_free_exec(t_exec *exec);
void	ft_exec(t_exec *exec);
void	ft_copy_env(t_exec *exec, char **envp);
void	ft_is_operator(t_exec *exec);

/*	--	Temp fct, to delete once the parsing is ready	--	*/
void	ft_cmd_nb(t_exec *exec);

/*	--	Debug fct	--	*/
void	ft_print_debug(t_exec *exec);

#endif