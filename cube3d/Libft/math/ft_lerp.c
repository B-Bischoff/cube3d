#include "../libft.h"

int	ft_lerp_d(int min, int max, float timestamp)
{
	return ((max - min) * timestamp + min);
}

float	ft_lerp_f(float min, float max, float timestamp)
{
	return ((max - min) * timestamp + min);
}

float	ft_inv_lerp_d(int min, int max, int curr)
{
	return (((float)curr - (float)min) / ((float)max - (float)min));
}

float	ft_inv_lerp_f(float min, float max, float curr)
{
	return ((curr - min) / (max - min));
}
