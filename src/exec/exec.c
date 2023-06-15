#include "../../include/minishell.h"

void	ft_is_redirection(t_exec *exec, t_jct *jct)
{
	char	***cmds_tab;
	int		i;

	if (!jct->tab)
		return ;
	cmds_tab = jct->tab;
	printf("---		ft_is_redirection starts	---\n");
	i = 0;
	
	if (jct->fl_redirout != 0)
    {
        exec->output = dup(jct->file_out);
        close(jct->file_out);
    }
    if (exec->input)
    {
        exec->input = dup(jct->file_in);
        close(jct->file_in);
    }
	
	// while (cmds_tab[i])
	// {
	// 	if (cmds_tab[i][2])
	// 	{
	// 		exec->input = dup(jct->file_in);
	// 		close(jct->file_in);
	// 		printf("exec->input : %d\n", exec->input);
	// 	}
	// 	if (cmds_tab[i][3])
	// 	{
	// 		if(jct->fl_redirout > 0)
	// 		{
	// 			exec->output = dup(jct->file_out);
	// 			close(jct->file_out);
	// 		}
	// 		printf("exec->output : %d\n", exec->output);
	// 	}
	// 	i++;
	// }
	printf("---		ft_is_redirection ends	---\n");
}

void	ft_make_pids(t_exec *exec, t_jct *jct)
{
	int	i;
	// int	fd_in;
	// int fd_out;

	exec->pids = ft_calloc(exec->cmd_nb, sizeof(pid_t *));
	if (!exec->path_var)
		return ;
	i = -1;
	// fd_in = dup(STDIN_FILENO);
	// fd_out = dup(STDOUT_FILENO);
	while (++i < exec->cmd_nb)
	{
/* 		if (ft_check_builtin(exec, i) == true)
		{
			ft_is_builtin(exec, i);
			exit(EXIT_SUCCESS);
		} */
		exec->pids[i] = fork();
		if (exec->pids[i] == -1)
			perror("Error ! Pid creation failed:");
		// printf("--- Enter in ft_chils_proc	---\n");
		if (exec->pids[i] == 0)
		{
			//this is the child process
			ft_dup_process(exec, i);
			ft_run_cmd(exec, jct, i);
		}
		//TODO put waitpid here, maybe ?
		// printf("--- Exit ft_chils_proc	---\n");
	}
	// dup2(fd_in, STDIN_FILENO);
	// dup2(fd_out, STDOUT_FILENO);
	//TODO close all input and/or output here (including here_doc)
	if (exec->jct->fds_in[i])
		close(exec->jct->fds_in[i]);
	if (exec->jct->fds_out[i])
		close(exec->jct->fds_out[i]);
	// ft_close_pipes(exec);
}

char	*ft_cmd_path(t_exec *exec, char *cmds)
{
	char	*path;
	int		i;

	if (access(cmds, F_OK | X_OK) == 0)
		return (ft_strdup(cmds));
	path = ft_strjoin("./", cmds);
	if (access(path, F_OK | X_OK) == 0)
		return (path);
	if (path)
		free(path);
	i = -1;
	while (exec->path_var[++i])
	{
		path = ft_strjoin(exec->path_var[i], cmds);
		if (access(path, F_OK | X_OK) == 0)
			return (path);
		if (path)
			free(path);
	}
	perror("Error ! Can't find path to program");
	path = NULL;
	return (path);
}

void	ft_run_cmd(t_exec *exec, t_jct *jct, int r)
{
	char	*path;
	char	**opt;
	char	***cmds;

	cmds = jct->tab;
	// fprintf(stderr, "cmd[%d][0] = %s\n", r, cmds[r][0]);
	// fprintf(stderr, "cmd[%d][1] = %s\n", r, cmds[r][1]);
	// fprintf(stderr, "cmd[%d][2] = %s\n", r, cmds[r][2]);
	opt = ft_split(cmds[r][0], ' ');
	path = ft_cmd_path(exec, opt[0]);
	fprintf(stderr, "path = %s\n", path);
	if (!path)
		free(path);
	else if (execve(path, opt, exec->envp) < 0)
		perror("Error ! Something went wrong while executing: ");
	//TODO ft_err exit if there is an error, so the below will never be executed
}

void	ft_dup_process(t_exec *exec, int i)
{
	fprintf(stderr, "exec->cmd = %d\n", exec->cmd_nb);
	fprintf(stderr, "jct->fl_redirout : %d\n", exec->jct->fl_redirout);
	if (exec->cmd_nb == 1) //cas avc une seule cmd SANS pipe
	{
		if (exec->jct->tab[i][1]) //cas avc une seule cmd SANS pipe MAIS avec une redirection in
			dup2(exec->jct->fds_in[i], STDIN_FILENO); //cas redrection in avec une seule cmd
		if (exec->jct->tab[i][2]) //cas avc une seule cmd SANS pipe MAIS avec une redirection out
			dup2(exec->jct->fds_out[i], STDOUT_FILENO); //cas redrection out avec une seule cmd
	}
	if (exec->cmd_nb > 1) //cas avc plus qu'une seule cmd (donc il y a forcement pipes[i][0] et pipes[i][1] créés dans ft_create_pipes)
	{
		if (exec->jct->tab[i][2]) //cas avc plus qu'une cmd AVEC pipe ET avec une redirection out
			dup2(exec->jct->fds_out[i], exec->pipes[1]);
		else
		{
			dup2(exec->pipes[0], STDIN_FILENO);
			dup2(exec->pipes[1], STDOUT_FILENO);
		}
	}
	//TODO close all input and/or output here (including here_doc)
	if (exec->jct->fds_in[i])
		close(exec->jct->fds_in[i]);
	if (exec->jct->fds_out[i])
		close(exec->jct->fds_out[i]);
	// ft_close_pipes(exec);
}

// void	ft_dup_process(t_exec *exec, int i)
// {
// 	fprintf(stderr, "exec->cmd = %d\n", exec->cmd_nb);
// 	fprintf(stderr, "jct->fl_redirout : %d\n", exec->jct->fl_redirout);
	
// 	if (exec->jct->tab[i][1])
// 	{
// 		if (exec->jct->fds_in[i])
// 		{
// 			fprintf(stderr, "Dup2 exec->input\n");
// 			fprintf(stderr, "exec->jct->fds_in[%d] = %d\n", i, exec->jct->fds_in[i]);
// 			dup2(exec->jct->fds_in[i], STDIN_FILENO);
// 		}
// 		// dup2(exec->pipes[i][1], STDOUT_FILENO);
// 	}
// 	else
// 		dup2(0, STDIN_FILENO);
// 	if (exec->jct->tab[i][2])
// 	{
// 		if (exec->jct->fds_out[i])
// 		{
// 			fprintf(stderr, "Dup2 exec->output\n");
// 			fprintf(stderr, "exec->jct->fds_out[%d] = %d\n", i, exec->jct->fds_out[i]);
// 			dup2(exec->jct->fds_out[i], STDOUT_FILENO);
// 		}
// 		// dup2(exec->pipes[i][1], STDOUT_FILENO);
// 	}
// 	else
// 		dup2(1, STDOUT_FILENO);
// 	//TODO close all input and/or output here (including here_doc)
// 	if (exec->jct->fds_in[i])
// 		close(exec->jct->fds_in[i]);
// 	if (exec->jct->fds_out[i])
// 		close(exec->jct->fds_out[i]);
// 	ft_close_pipes(exec);
// }

void	ft_exec(t_exec *exec, t_jct *jct)
{
	int	i;
	int	status;

	// ft_is_redirection(exec, jct);
	if (ft_create_pipes(exec) == 2)
		return ;
	ft_make_pids(exec, jct);
	i = -1;
	while (++i < exec->cmd_nb)
		waitpid(exec->pids[i], &status, 0);
	//TODO clarifier le 2nd arg de waitpid
}

// void	ft_exec_jct(t_exec *exec, t_jct *jct)
// {
// 	int	i;
// 	int status;

// 	ft_is_redirection(exec, jct);
// 	ft_create_pipes(exec);
// 	ft_make_pids_jct(exec, jct);
// 	i = -1;
// 	while (++i < exec->cmd_nb)
// 		waitpid(exec->pids[i], &status, 0);
// 	//TODO clarifier le 2nd arg de waitpid
// 	// ft_free_data(exec);
// }