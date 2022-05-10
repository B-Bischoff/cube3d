/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbischof <bbischof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 14:53:58 by bbischof          #+#    #+#             */
/*   Updated: 2022/04/22 15:37:16 by bbischof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*lst_cpy_begin;
	t_list	*lst_cpy;
	t_list	*lst_temp;

	if (!lst)
		return (NULL);
	lst_cpy = ft_lstnew((*f)(lst->content));
	if (!lst_cpy)
		return (NULL);
	lst_cpy_begin = lst_cpy;
	while (lst)
	{
		lst = lst->next;
		if (lst)
		{
			lst_temp = ft_lstnew((*f)(lst->content));
			if (!lst_temp)
			{
				ft_lstclear(&lst_cpy_begin, (*del));
				return (NULL);
			}
			ft_lstadd_back(&lst_cpy, lst_temp);
		}
	}
	return (lst_cpy_begin);
}
