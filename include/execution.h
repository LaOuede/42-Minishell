#ifndef EXECUTION_H
# define EXECUTION_H

# include <stdlib.h>

/*
**	Structure that holds all infomration needed for the execution
*/
typedef struct s_exec
{
	char	**av;
	char	**envp;
	char	**cmd_paths;
	int		input;
	int		output;
	int		index;
	int		pipes_nb;
	int		cmd_nb;
	int		**pipes;
	pid_t	*pids;
}			t_exec;

/*
**	Function Declarations for the execution of shell commands
*/
t_exec	*ft_init_exec(int ac, char **av, char **envp);
void	ft_err(char *msg, t_exec *exec);
void	ft_free_exec(t_exec *exec);
void	ft_exec(t_exec *exec);

#endif