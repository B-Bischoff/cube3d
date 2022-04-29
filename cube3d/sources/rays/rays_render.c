#include "cube3d.h"

void	rays_render(t_data *data)
{
	int slice_width;

	slice_width = data->win_width / data->rays_nb;

	for (int i = 0; i < data->rays_nb; i++)
	{
		t_ray *ray = &data->rays[i];

		if (ray->length == -1)
			continue;

		// float line_height = (float)data->win_height / (float)(ray->perp_length);
		double line_height;
		
		line_height = 1.0f / ray->perp_length;
		// dprintf(1, "%lf\n", line_height);
		line_height *= (double)data->win_height;
		if (line_height > 500)
			line_height = data->win_height;
		// line_height *= .5f;

		// dprintf(1, "i %d | hit point y %f x %f | length %lf | perp %lf | ", i, ray->hit_point.y, ray->hit_point.x, ray->length, ray->perp_length);
		// dprintf(1, "height %lf %d\n", line_height, (int)line_height);
		// dprintf(1, "i %d | perp %lf | length %lf | %lf\n", i, ray->perp_length, ray->length, ray->length / ray->perp_length);

		float j = ft_inv_lerp_f(10.0f, 75.0f, line_height);

		int color;
		if (ray->side_hit == 0)
			color = color_lerp(DARK_GRAY, RED, j);
		else if (ray->side_hit == 1)
			color = color_lerp(DARK_GRAY, BLUE, j);
		else if (ray->side_hit == 2)
			color = color_lerp(DARK_GRAY, YELLOW, j);
		else
			color = color_lerp(DARK_GRAY, GREEN, j);
		
		t_vector2_d tl = {i * slice_width, data->win_height / 2 - line_height};
		t_vector2_d br = {i * slice_width + slice_width, data->win_height / 2 + line_height};
		draw_rect_filled_color(data, tl, br, color);

	}
}
