/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbischof <bbischof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 13:39:42 by bbischof          #+#    #+#             */
/*   Updated: 2022/05/26 10:07:25 by bbischof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static void	get_word_init(char *quote, int *i, char *str)
{
	*quote = 0;
	*i = 0;
	while (str[*i] && str[*i] == ' ')
		*i += 1;
}

// Return the first word found in str from start
char	*ft_get_word(char *str)
{
	int		i;
	int		j;
	char	quote;
	char	*new_str;

	j = 0;
	get_word_init(&quote, &i, str);
	new_str = ft_calloc(ft_strlen(str + i) + 1, sizeof(char));
	if (new_str == NULL)
		return (NULL);
	while (str[i] && str[i] != ' ')
		new_str[j++] = str[i++];
	new_str[j] = '\0';
	return (new_str);
}
