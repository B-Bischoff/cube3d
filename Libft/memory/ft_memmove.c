/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbischof <bbischof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 11:35:44 by bbischof          #+#    #+#             */
/*   Updated: 2022/04/22 15:37:16 by bbischof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*ptr_d;
	const char	*ptr_s;

	ptr_d = dst;
	ptr_s = src;
	if (ptr_d > ptr_s)
	{
		while (len-- > 0)
			ptr_d[len] = ptr_s[len];
	}
	else
		return (ft_memcpy(ptr_d, ptr_s, len));
	return (dst);
}
