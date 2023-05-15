#ifndef EXECUTION_H
# define EXECUTION_H

# include <stdlib.h>
# include "minishell.h"

/*
**	Function Declarations for the execution of shell commands
*/
t_exec	*ft_init_exec(int ac, char **av, char **envp);
void	ft_child_process(t_ms *ms, t_exec *exec, int i);
void	ft_close_pipes(t_exec *exec);
int		ft_create_pipes(t_exec *exec);
void	ft_err(char *msg, t_exec *exec);
void	ft_free_exec(t_exec *exec);
void	ft_exec(t_exec *exec);

#endif