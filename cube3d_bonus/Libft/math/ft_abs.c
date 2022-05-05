#include "../libft.h"

int	ft_abs_d(int nbr)
{
	if (nbr < 0)
		return (-nbr);
	else
		return (nbr);
}

float	ft_abs_f(float nbr)
{
	if (nbr < 0.0f)
		return (-nbr);
	else
		return (nbr);
}
