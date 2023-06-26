#include "../../include/minishell.h"

void	ft_hd_parser(t_ms *ms)
{
	if (DEBUG)
		printf(KYEL "-------------------- FT_HD_PARSER" KGRN KBLD" START " RESET KYEL "--------------------\n" RESET);
	int	i;

	i = 0;
	while (i < (int)ms->hd->strlen)
	{
		if (DEBUG){
		printf("-> i = %d\n", (i));
		printf("-> char = %c\n", ms->hd->input[(i)]);
		}
		if ((ms->hd->input[i]) == '$')
			ft_envvar_hd(&i, ms->hd->input, ms);
		else
			ft_str_hd(&i, ms);
	}
	if (DEBUG)
		printf(KYEL "-------------------- FT_HD_PARSER" KRED KBLD" END " RESET KYEL "--------------------\n" RESET);
}

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
	hd->err_parser = 0;
	return (hd);
}

void	ft_child_hd(char *delim, int fd_hd, t_ms *ms)
{
	if (DEBUG)
		printf(KYEL "-------------------- FT_CHILD_HD" KGRN " START " RESET KYEL "--------------------\n" RESET);
	ft_init_sig(HD);
	ms->hd = ft_init_hd(ms);
	while (42)
	{
		ms->hd->input = readline("> ");
		ms->hd->strlen = ft_strlen(ms->hd->input);
		ms->hd->hd++;
		if ((ft_strncmp(ms->hd->input, delim, ms->hd->strlen) == 0 \
			&& ms->hd->input && *ms->hd->input != '\0') || !ms->hd->input)
			break ;
		ft_hd_parser(ms);
	}
	if (DEBUG)
		DEBUG_hd(ms->hd);
	if (ms->hd->err_parser == true)
	{
		ft_error(ERR_HD);
		ft_exit_free(ms, 1);
	}
	ft_merge_hd(ms->hd);
	ft_clean_list(&ms->hd->line);
	print_hd(ms->hd, fd_hd);
	ft_exit_free(ms, 0);
}

int	ft_exec_hd(char *delim, t_ms *ms)
{
	if (DEBUG)
		printf(KYEL "-------------------- FT_CHILD_HD" KGRN " START " RESET KYEL "--------------------\n" RESET);
	int		fd_hd;
	pid_t	pid_hd;
	int 	status;

	fd_hd = open("/tmp/here_doc", O_CREAT | O_TRUNC | O_RDWR, 0666);
	if (fd_hd < 0)
		perror("Error ! fd_hd:");
	pid_hd = fork();
	if (pid_hd == -1)
		perror("Error! pid_hd:");
	if (pid_hd == 0)
		ft_child_hd(delim, fd_hd, ms);
	waitpid (ms->jct->pid_hd, &status, 0);
	if (WIFEXITED(status))
		ms->flexit = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		ms->flexit = WTERMSIG(status);
	close(fd_hd);
	ms->jct->fd_hd = open("/tmp/here_doc", O_RDONLY, 0666);
	if (DEBUG)
		printf(KYEL "-------------------- FT_EXEC_HD" KRED " END " RESET KYEL "--------------------\n" RESET);
	return (fd_hd);
}
