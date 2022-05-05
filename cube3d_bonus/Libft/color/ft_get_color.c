#include "../libft.h"

int	get_r(int color)
{
	return ((color >> 16) & 0xFF);
}

int	get_g(int color)
{
	return ((color >> 8) & 0xFF);
}

int	get_b(int color)
{
	return (color & 0xFF);
}

int	get_t(int color)
{
	return ((color >> 24) & 0xFF);
}

int	create_rgbt(int r, int g, int b, int t)
{
	return (t << 24 | r << 16 | g << 8 | b);
}
