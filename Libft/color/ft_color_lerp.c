#include "../libft.h"

int	color_lerp(int color1, int color2, float timestamp)
{
	int	r;
	int	g;
	int	b;

	if (timestamp > 1.0f)
		timestamp = 1.0f;
	r = ft_lerp_d(get_r(color1), get_r(color2), timestamp);
	g = ft_lerp_d(get_g(color1), get_g(color2), timestamp);
	b = ft_lerp_d(get_b(color1), get_b(color2), timestamp);
	return (create_rgbt(r, g, b, 1));
}
