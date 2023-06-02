#include "../include/minishell.h"

void	ft_make_pids_jct(t_exec *exec, t_jct *jct)
{
	int	i;
	
	exec->pids = ft_calloc(exec->cmd_nb, sizeof(pid_t *));
	if (!exec->path_var)
		return ;
	i = -1;
	while (++i < exec->cmd_nb)
	{
		exec->pids[i] = fork();
		if (exec->pids[i] == -1)
			ft_err("Something went wrong during pid process:", exec);
		// printf("--- Enter in ft_chils_proc	---\n");
		if (exec->pids[i] == 0)
		{
			//this is the child process
			ft_dup_process(exec, i);
			ft_run_cmd_jct(exec, jct);
		}	

		// printf("--- Exit ft_chils_proc	---\n");
	}
	if(exec->fl_redirin == 1)
		close(exec->input);
	if(exec->fl_redirout == 1)
		close(exec->output);
	ft_close_pipes(exec);
}

void	ft_run_cmd_jct(t_exec *exec, t_jct *jct)
{
	char	*path;
	char	***cmds;
	int		i;
	int		r;

	cmds = jct->tab;
	r = -1;
	while (cmds[++r])
	{
		path = ft_cmd_path(exec, cmds[r][0]);
		fprintf(stderr, "path = %s\n", path);
		if (!path)
			free(path);
		else if (execve(path, *cmds, exec->envp) < 0)
			ft_err("Error ! Something went wrong while executing: ", exec);
	}
	//TODO ft_err exit if there is an error, so the below will never be executed
	i = 0;
	while (exec->path_var[i])
		free(exec->path_var[i++]);
	free(exec->path_var);
	exec->path_var = NULL;
}

void	ft_exec_jct(t_exec *exec, t_jct *jct)
{
	int	i;
	int status;
	
	//TODO remove the below
	exec->fl_redirin = 0;
	exec->fl_redirout = 0;
	exec->input  = open("Makefile", O_RDONLY);
	if (exec->input == -1)
				ft_err("Error exec->file", exec);
	exec->input  = open("supp.txt", O_RDONLY);
	if (exec->input == -1)
				ft_err("Error exec->file", exec);
	exec->output = open("out", O_RDWR | O_CREAT | O_TRUNC, 0644);
	//TODO remove the above

	ft_create_pipes(exec);
	ft_make_pids_jct(exec, jct);
	i = -1;
	while (++i < exec->cmd_nb)
		waitpid(exec->pids[i], &status, 0);
	//TODO clarifier le 2nd arg de waitpid
	// ft_free_data(exec);
}