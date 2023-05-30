#include "../include/minishell.h"

void	ft_extract_cmd(t_token **list, t_pars *pars)
{
	printf(KYEL "-------------------- FT_EXTRACT_CMD" KGRN " START " RESET KYEL "--------------------\n" RESET);
	t_token	*ptr;
	char	*tmp;
	int		i;
	int		start;
	int		len;
	int		flag;

	ptr = *list;
	tmp = NULL;
	flag = 42;
	while (ptr)
	{
		if (0 <= ptr->type && ptr->type <= 3 && flag == 42)
		{
			i = 0;
			start = -1;
			printf("flag = %d\n", flag);
			while (ft_isprint(ptr->str[i]) == 1 && ft_iswhitespace(ptr->str[i]) == 0)
				i++;
			printf("i = %d\n", i);
			if (ptr->str[i + 1] != '\0')
			{
				tmp = ft_calloc(i + 1, sizeof(char));
				while (++start < i)
				{
					tmp[start] = ptr->str[start];
					printf("char = %c\n", tmp[start]);
				}
				if (ft_iswhitespace(ptr->str[i]) == 1)
					i++;
				start = i;
				while (ptr->str[start])
					start++;
				len = start;
				start = i;
				printf("tmp = %s\n", tmp);
				ptr->str = ft_substr(ptr->str, start, len);
				printf("ptr->str = %s\n", ptr->str);
				if (ptr->prev == NULL)
				{
					ft_add_token_top(&pars->line, ft_create_node(tmp, pars));
					flag = 0;
				}
				else
				{
					ft_insert_token(&pars->line, ptr->prev, ptr, ft_create_node(tmp, pars));
					flag = 0;
				}
				ft_freenull(tmp);
				printf("flag = %d\n", flag);
			}
			else
				ptr->type = CMD;
		}
		if (ptr->type == PIPE)
			flag = 42;
		ptr = ptr->next;
	}
	printf(KYEL "-------------------- FT_EXTRACT_CMD" KRED " END " RESET KYEL "--------------------\n" RESET);
}