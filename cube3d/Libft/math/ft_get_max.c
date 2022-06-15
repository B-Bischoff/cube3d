#include "../libft.h"

int	ft_get_max_d(int a, int b)
{
	if (a > b)
		return (a);
	else
		return (b);
}

float	ft_get_max_f(float a, float b)
{
	if (a > b)
		return (a);
	else
		return (b);
}

int	ft_get_max_3_d(int a, int b, int c)
{
	if (a > b)
	{
		if (a > c)
			return (a);
		else
			return (c);
	}
	else
	{
		if (b > c)
			return (b);
		else
			return (c);
	}
}

float	ft_get_max_3_f(float a, float b, float c)
{
	if (a > b)
	{
		if (a > c)
			return (a);
		else
			return (c);
	}
	else
	{
		if (b > c)
			return (b);
		else
			return (c);
	}
}
