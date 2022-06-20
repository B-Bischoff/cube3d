/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbischof <bbischof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 12:24:33 by bbischof          #+#    #+#             */
/*   Updated: 2022/04/22 15:37:16 by bbischof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static void	ft_putnbr(int n, int fd);

void	ft_putnbr_fd(int n, int fd)
{
	long	n_cpy;

	n_cpy = n;
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		n_cpy = (long)n * -1;
	}
	if (n_cpy > 9)
	{
		ft_putnbr_fd(n_cpy / 10, fd);
		ft_putnbr(n_cpy % 10, fd);
	}
	else
		ft_putnbr(n_cpy, fd);
}

static void	ft_putnbr(int n, int fd)
{
	char	c;

	c = n + 48;
	write(fd, &c, 1);
}
