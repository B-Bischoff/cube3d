#include "cube3d.h"

int		load_texture(t_data *data, t_text *texture, char *texture_path)
{
	texture->text = mlx_xpm_file_to_image(data->mlx, texture_path, &texture->width_img, &texture->height_img);
	if (texture->text == NULL)
		dprintf(1, "NUUUULL\n");
	// Check null pointer
	texture->text_adr = mlx_get_data_addr(texture->text, &texture->bit, &texture->size_line, &texture->endian);
	// Check null pointer
	return (0);
}

void	initialize_text(t_data *data)
{
	data->textures = malloc(sizeof(t_text) * 6);
	load_texture(data, &data->textures[0], "../assets/barrel.xpm");
	load_texture(data, &data->textures[1], "../assets/pillar.xpm");

	// Animated sprites
	load_texture(data, &data->textures[2], "../assets/mguard/mguard_w1_1.xpm");
	load_texture(data, &data->textures[3], "../assets/mguard/mguard_w2_1.xpm");
	load_texture(data, &data->textures[4], "../assets/mguard/mguard_w3_1.xpm");
	load_texture(data, &data->textures[5], "../assets/mguard/mguard_w4_1.xpm");

}

int main(int argc, char *argv[])
{
	t_data	data;

	if (parsing(&data, argc, argv) == 1)
		exit (1);
	if (ft_mlx_init(&data) == 1)
		exit (1);
	if (ft_init_vision(&data) == 1)
		exit (1);

	initialize_text(&data);
	sprites_init(&data);

	mlx_mouse_hide();
	data.mouse_pos.x = data.win_width / 2;
	data.mouse_pos.y = data.win_height / 2;
	data.mouse_move.x = 0;
	data.mouse_move.y = 0;
	mlx_mouse_move(data.mlx_win, data.win_width / 2, data.win_height / 2);	

	ft_mlx_hooks_and_loop(&data);

	free_all(&data);
	exit (0);
}
