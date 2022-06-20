/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbischof <bbischof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 12:27:29 by bbischof          #+#    #+#             */
/*   Updated: 2022/04/22 15:37:16 by bbischof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static char	*return_empty_string(void);

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*dst;
	int		i;

	if (!s || start > (unsigned int)(ft_strlen((char *) s)))
		return (return_empty_string());
	if (ft_strlen((char *)s + start) + 1 <= (int)len)
		dst = malloc(sizeof(char) * ft_strlen((char *)s + start + 1));
	else
		dst = malloc(sizeof(char) * len + 1);
	if (dst == NULL)
		return (NULL);
	i = 0;
	while (s[i + start] && i <= (int)len)
	{
		dst[i] = s[i + start];
		i++;
	}
	if (i <= (int)len)
		dst[i] = '\0';
	else
		dst[i - 1] = '\0';
	return (dst);
}

static char	*return_empty_string(void)
{
	char	*str;

	str = malloc(sizeof(char));
	if (str == NULL)
		return (NULL);
	str[0] = '\0';
	return (str);
}
