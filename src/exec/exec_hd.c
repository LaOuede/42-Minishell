#include "../../include/minishell.h"

t_pars	*ft_init_hd(t_ms *ms)
{
	t_pars	*hd;

	hd = ft_calloc(1, sizeof(t_pars));
	hd->line = NULL;
	hd->input = NULL;
	hd->envp = ms->jct->envp;
	hd->hd = 0;
	hd->strlen = 0;
	hd->c_brackets = 0;
	hd->flag_whitespace = 0;
	return (hd);
}

void	ft_child_hd(char *delim, int fd_hd, t_ms *ms)
{
	(void)delim;
	ft_init_sig(HD);
	ms->hd = ft_init_hd(ms);
	while (42)
	{
		ms->hd->input = readline("> ");
		ms->hd->strlen = ft_strlen(ms->hd->input);
		ms->hd->hd++;
		if (ft_strncmp(ms->hd->input, delim, ms->hd->strlen) == 0)
			break ;
		ft_hd_parser(ms);
		ft_freenull(ms->hd->input);
	}
	if (DEBUG)
		DEBUG_hd(ms->hd);
	ft_merge_hd(ms->hd);
	ft_clean_list(&ms->hd->line);
	print_hd(ms->hd, fd_hd);
	ft_free_all(ms);
	exit(0);
}

int	ft_exec_hd(char *delim, t_ms *ms)
{
	int		fd_hd;
	pid_t	pid_hd;
	int		status;

	fd_hd = open("/tmp/here_doc", O_CREAT | O_TRUNC | O_RDWR, 0644);
	if (fd_hd < 0)
		perror("Error ! fd_hd:");
	pid_hd = fork();
	if (pid_hd == -1)
		perror("Error! pid_hd:");
	if (pid_hd == 0)
		ft_child_hd(delim, fd_hd, ms);
	waitpid (pid_hd, &status, 0);
/* 	if (WIFEXITED(status))
		ms->flexit = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		ms->flexit = WTERMSIG(status); */
	close(fd_hd);
	fd_hd = open("/tmp/here_doc", O_RDONLY, 0644);
	return (fd_hd);
}
