#include "cube3d.h"

void	add_text_pix(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->rays_nb)
	{
		int lineHeight = (double)(data->win_height / data->rays[i].perp_length);

    	double step = 1.0 * data->text[0].long_img / (lineHeight * 2);

      	//calculate lowest and highest pixel to fill in current stripe
      	int drawStart = (data->win_height >> 1) - lineHeight;
		if (drawStart < 0) drawStart = 0;

    	int drawEnd = (data->win_height >> 1) + lineHeight;
		if (drawEnd >= data->win_height) drawEnd = data->win_height - 1;
	
    	double texPos = (double)(drawStart - (data->win_height >> 1) + lineHeight) * step;

		for (int y = drawStart; y < drawEnd; y++)
    	{
			if (y >= 0 && y < data->win_width)
			{
	    		int texY = (int)texPos & (data->text[0].long_img - 1);
	    		texPos += step;

				data->rays[i].text_buf[0][y] = get_text_pix(&data->text[0], (int)(data->rays[i].wall_x * (double)data->text[0].long_img), texY);
				// data->rays[i].text_buf[1][y] = get_text_pix(&data->text[0], (int)(data->rays[i].wall_x_2 * (double)data->text[0].long_img), texY);
				// data->rays[i].text_buf[0][y] = ((i + 1) <<16) + ((i + 1)<<8) +  (i + 1);
				// data->rays[i].text_buf[1][y] = ((i + 1) <<16) + ((i + 1)<<8) +  (i + 1);	
			}
		}
		i++;
	}
}
