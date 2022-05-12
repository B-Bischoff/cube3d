#include "cube3d.h"

void	add_text_pix(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->rays_nb)
	{
		int line_height = (double)(data->win_height / data->rays[i].perp_length);

    	double step = 1.0 * data->text[0].height_img / (line_height);

      	int draw_start = (data->win_height >> 1) - line_height / 2;
		if (draw_start < 0) draw_start = 0;

    	int draw_end = (data->win_height >> 1) + line_height / 2;
		if (draw_end >= data->win_height) draw_end = data->win_height - 1;
	
    	double tex_pos = (double)(draw_start - (data->win_height >> 1) + (line_height >> 1)) * step;

		for (int y = draw_start; y < draw_end; y++)
    	{
			if (y >= 0 && y < data->win_width)
			{
	    		int tex_y = (int)tex_pos;
	    		tex_pos += step;
			
				data->rays[i].text_buf[y] = get_text_pix(&data->text[0], data->rays[i].tex_x, tex_y);
			}
		}
		i++;
	}
}
