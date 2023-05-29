#include "../include/minishell.h"

void	ft_extract_cmd(t_token **list, t_pars *pars)
{
	printf(KYEL "-------------------- FT_EXTRACT_CMD" KGRN " START " RESET KYEL "--------------------\n" RESET);
	t_token	*ptr;
	char	*tmp;
	int		i;
	int		start;
	int		len;

	i = 0;
	ptr = *list;
	printf("str = %s\n", ptr->str);
	if (0 <= ptr->type && ptr->type <= 3)
	{
		while (ft_isprint(ptr->str[i]) == 1 && ft_iswhitespace(ptr->str[i]) == 0)
			i++;
		tmp = ft_calloc(i + 1, sizeof(char));
		if (ft_iswhitespace(ptr->str[i]) == 1)
			i++;
		start = i;
		while (ptr->str[start])
			start++;
		len = start;
		start = i;
		while (i-- > 0)
			tmp[i] = ptr->str[i];
		printf("tmp = %s\n", tmp);
		ptr->str = ft_substr(ptr->str, start, len);
		printf("ptr->str = %s\n", ptr->str);
		ft_add_token_top(&pars->line, ft_create_node(tmp, pars));
		ft_freenull(tmp);
	}
	printf(KYEL "-------------------- FT_EXTRACT_CMD" KRED " END " RESET KYEL "--------------------\n" RESET);
}