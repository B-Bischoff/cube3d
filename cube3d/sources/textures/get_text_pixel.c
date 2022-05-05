#include "cube3d.h"

int	get_text_pix(t_text *text, int x, int y)
{
	int	color;
	// char	*str;

	if (text == NULL)
	{
		// dprintf(1, "Invalid texture pointer\n");
		return (0);
	}
	if (x < 0 || x > text->lar_img || y < 0 || y > text->long_img)
	{
		// dprintf(1, "Invalid texture coordinate\n");
		return (0);
	}
	color = (*(int *)(text->text_adr + (x * text->bit / 8) + (y * text->size_line)));

	// str = &text->text_adr[y * text->size_line + x * (text->bit / 8)];
	// color.str[0] = str[0];
	// color.str[1] = str[1];
	// color.str[2] = str[2];
	// color.str[3] = str[3];

	return (color);
}
