#include "../../include/minishell.h"

void	ft_hd_parser(t_ms *ms)
{
	if (DEBUG)
		printf(KYEL "-------------------- FT_HD_PARSER" KGRN KBLD" START " RT KYEL "--------------------\n" RT);
	int	i;
	char	*tmp;

	i = 0;
	if (ms->hd->input)
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
	if (ms->hd->strlen == 0)
	{
		tmp = ft_strdup("\n");
		ft_add_token_bottom(&ms->hd->line, ft_create_node(ms, tmp, ms->hd));
		tmp = ft_freenull(tmp);
	}
	if (DEBUG)
		printf(KYEL "-------------------- FT_HD_PARSER" KRED KBLD" END " RT KYEL "--------------------\n" RT);
}

t_pars	*ft_init_hd(t_ms *ms)
{
	t_pars	*hd;

	hd = ft_calloc_msh(1, sizeof(t_pars), ms);
	hd->line = NULL;
	hd->input = NULL;
	hd->envp = ms->envp;
	hd->hd = 0;
	hd->strlen = 0;
	hd->c_brackets = 0;
	hd->err_parser = 0;
	return (hd);
}

void	ft_child_hd(char *delim, int fd_hd, t_ms *ms)
{
	if (DEBUG)
		printf(KYEL "-------------------- FT_CHILD_HD" KGRN " START " RT KYEL "--------------------\n" RT);
	ft_init_sig(HD);
	ms->hd = ft_init_hd(ms);
	while (42)
	{
		ms->hd->input = readline("> ");
		ms->hd->strlen = ft_strlen(ms->hd->input);
		ms->hd->hd++;
		if ((ft_strcmp(ms->hd->input, delim) == 0 \
			&& ms->hd->input && *ms->hd->input != '\0') || !ms->hd->input)
			break ;
		ft_hd_parser(ms);
	}
	if (DEBUG)
		DEBUG_hd(ms->hd);
	if (ms->hd->err_parser == true)
	{
		ft_error(ERR_HD);
		ft_exit_free(ms, 1, 0);
	}
	ft_merge_hd(ms->hd);
	ft_clean_list(&ms->hd->line);
	print_hd(ms->hd, fd_hd);
	close(fd_hd);
	ft_exit_free(ms, 0, 0);
}

int	ft_exec_hd(char *delim, t_ms *ms)
{
	if (DEBUG)
		printf(KYEL "-------------------- FT_CHILD_HD" KGRN " START " RT KYEL "--------------------\n" RT);
	int		fd_hd;
	pid_t	pid_hd;
	int		status;

	fd_hd = open("/tmp/here_doc", O_CREAT | O_TRUNC | O_RDWR, 0666);
	if (fd_hd < 0)
		perror("Error ! fd_hd:");
	pid_hd = fork();
	if (pid_hd == -1)
		perror("Error! pid_hd:");
	if (pid_hd == 0)
		ft_child_hd(delim, fd_hd, ms);
	waitpid (pid_hd, &status, 0);
	if (WIFEXITED(status))
		ms->flexit = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		ms->flexit = WTERMSIG(status);
	close(fd_hd);
	ms->jct->fd_hd = open("/tmp/here_doc", O_RDONLY, 0666);
	if (DEBUG)
		printf(KYEL "-------------------- FT_EXEC_HD" KRED " END " RT KYEL "--------------------\n" RT);
	return (fd_hd);
}
