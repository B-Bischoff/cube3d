/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbischof <bbischof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 13:40:34 by azanane           #+#    #+#             */
/*   Updated: 2022/05/09 16:02:17 by bbischof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	exists_in_garbage(void *ptr, t_list *garbage);

void	*calloc_garbage(size_t count, size_t size, t_list **garbage)
{
	void	*ptr;
	t_list	*new_elem;

	ptr = ft_calloc(count, size);
	if (ptr == NULL)
		return (NULL);
	new_elem = ft_lstnew(ptr);
	if (new_elem == NULL)
		return (NULL);
	ft_lstadd_back(garbage, new_elem);
	return (ptr);
}

void	add_to_garbage(void *ptr, t_list **garbage)
{
	t_list	*new_elem;

	if (ptr == NULL || exists_in_garbage(ptr, *garbage))
		return ;
	new_elem = ft_lstnew(ptr);
	if (new_elem == NULL)
		return ;
	ft_lstadd_back(garbage, new_elem);
}

void	add_array_to_garbage(void **array, t_list **garbage)
{
	t_list	*new_elem;
	int		i;

	if (array == NULL)
		return ;
	i = 0;
	if (!exists_in_garbage(array, *garbage))
		add_to_garbage(array, garbage);
	while (array[i])
	{
		if (!exists_in_garbage(array[i], *garbage))
		{
			new_elem = ft_lstnew(array[i]);
			if (new_elem == NULL)
				return ;
			ft_lstadd_back(garbage, new_elem);
		}
		i++;
	}
}

int	exists_in_garbage(void *ptr, t_list *garbage)
{
	if (garbage == NULL || ptr == NULL)
		return (0);
	while (garbage)
	{
		if (ptr == garbage->content)
			return (1);
		garbage = garbage->next;
	}
	return (0);
}
