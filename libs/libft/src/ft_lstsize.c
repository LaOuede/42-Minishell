/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
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
	Count the number of elements in the list
Declaration :
	int ft_lstsize(t_list *lst)
Parameters :
	lst - the beginning of the list
Return Value :
	The size of the list
*/
int	ft_lstsize(t_list *lst)
{
	int		size;
	t_list	*ptr;

	size = 0;
	ptr = lst;
	if (!lst)
		return (0);
	while (ptr->next != NULL)
	{
		size++;
		ptr = ptr->next;
	}
	if (ptr->next == NULL)
		size++;
	return (size);
}
