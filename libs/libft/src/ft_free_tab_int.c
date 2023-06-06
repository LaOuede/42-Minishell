/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_tab_int.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csenand <csenand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 13:51:24 by gwenolalero       #+#    #+#             */
/*   Updated: 2023/06/06 09:46:42 by csenand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_free_tab_int(int **tab, size_t len)
{
	while (len-- > 0)
		ft_freenull(tab[len]);
	ft_freenull(tab);
	return (0);
}
