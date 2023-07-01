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
typedef struct s_ms		t_ms;

typedef struct s_builtin
{
	void					(*fts[8])(t_ms *, char **);
}							t_builtin;

/*
**	Structure that holds all infomration needed for the execution
*/
typedef struct s_exec
{
	struct s_jct	*jct;
	char			**envp;
	char			**path_var;
	int				input;
	int				output;
	pid_t			*pids;
	int				**pipes;
	int				pipes_nb;
	t_builtin		*builtin;
	char			**builtin_cmd;
	int				builtin_fts;
}			t_exec;

/*	--	Function Declarations for the execution of shell commands	--	*/
t_exec	*ft_init_exec(t_ms *ms);
void	ft_dup_proc(t_ms *ms, int i);
int		ft_pre_redir(t_ms *ms, int i);
void	ft_close_all(t_ms *ms);
void	ft_close_fds(t_ms *ms);
int		ft_mem_pipes(t_ms *ms);
char	*ft_free_2char(char **tab);
void	ft_free_3tab(t_jct *jct);
void	ft_free_exec(t_exec *exec);
void	ft_exec(t_ms *ms);
void	ft_copy_env(t_ms *ms, char **envp);
char	*ft_cmd_path(t_exec *exec, char *cmds);
void	ft_free_3tab(t_jct *jct);
void	ft_run_cmd(t_ms *ms, int i);
int		ft_exec_hd(char *delim, t_ms *ms);
void	ft_close_old_pipes(t_exec *exec, int i);
void	ft_dup_and_run(t_ms *ms, int i, int builtin_fts);
void	ft_dup_x_cmd(t_ms *ms, int i);

char		**ft_get_path(t_ms *ms, char **envp, int i);
t_builtin	*ft_get_builtin(void);

void	ft_reset_exec(t_ms *ms);

#endif