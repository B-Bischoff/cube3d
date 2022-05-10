/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbischof <bbischof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 12:13:49 by bbischof          #+#    #+#             */
/*   Updated: 2022/04/22 15:37:16 by bbischof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*temp_lst;

	if (lst)
	{
		while (*lst)
		{
			temp_lst = (*lst)->next;
			ft_lstdelone((*lst), (*del));
			*(lst) = temp_lst;
		}
	}
}
