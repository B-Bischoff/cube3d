#include "cube3d.h"

void	add_text_pix(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->rays_nb)
	{
		int lineHeight = (int)(data->win_height / data->rays[i].perp_length);

		// int lineHeight = (double)(1.0f / (double)data->rays[i].perp_length);
		// dprintf(1, "%lf\n", line_height);
		// lineHeight *= (double)data->win_height;

    	double step = 1.0 * data->text[0].long_img / (lineHeight * 2);

      	//calculate lowest and highest pixel to fill in current stripe
      	int drawStart = data->win_height / 2 - lineHeight;
		if (drawStart < 0) drawStart = 0;

    	int drawEnd = data->win_height / 2 + lineHeight;
		if (drawEnd >= data->win_height) drawEnd = data->win_height - 1;
	
    	double texPos = (drawStart - data->win_height / 2 + lineHeight / 2) * step;
		
		for (int y = drawStart; y < drawEnd; y++)
    	{

    		int texY = (int)texPos & (data->text[0].long_img - 1);
    		texPos += step;

			// data->rays[i].text_buf[y] = get_text_pix(&data->text[0], data->rays[i].wall_x, texY);
			// dprintf(2, "wall x %f | y text %lf\n", data->rays[i].wall_x, texPos);
			
			data->rays[i].text_buf[y] = get_text_pix(&data->text[0], data->rays[i].wall_x * data->text[0].lar_img, texY);
		}
		i++;
	}

}
