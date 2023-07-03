/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwenolaleroux <gwenolaleroux@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 08:48:10 by gle-roux          #+#    #+#             */
/*   Updated: 2023/02/09 21:31:19 by gwenolalero      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

/*
Library :
	#include "libft.h"
Description :
	Delete and free the memory of the element passed in parameter, and of all
	the elements that follow, using 'del' and free(3).
	Finally, the initial pointer must be set to NULL.
Declaration :
	void ft_lstclear(t_list **lst, void (*del)(void*))
Parameters :
	lst - The address of the pointer to an element.
	del - The address of the function to delete the content of the element.
Return Value :
	None.
*/
void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*ptr;

	if (!lst || !del)
		return ;
	ptr = *lst;
	while (*lst != NULL)
	{
		ptr = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = ptr;
	}
}
