

#include <MLX42/MLX42.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define WIDTH 700  // largeur
#define HEIGHT 700 // hauteur

static mlx_image_t	*image;

// -----------------------------------------------------------------------------

// int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
// {
//     return (r << 24 | g << 16 | b << 8 | a);
// }

mlx_texture_t		*texture = NULL;
mlx_image_t			*player = NULL;
mlx_texture_t		*t_rainbow = NULL;
mlx_image_t			*rainbow = NULL;
mlx_texture_t		*t_floor = NULL;
mlx_image_t			*i_floor = NULL;
mlx_texture_t		*t_wall = NULL;
mlx_image_t			*wall = NULL;
mlx_texture_t		*t_unicorn = NULL;
mlx_image_t			*unicorn = NULL;


void	mlx_load_textures(void *param)
{
	mlx_t	*mlx;
	int		i;
	int		j;

	mlx = param;
	t_floor = mlx_load_png("./floor_small.png");
	t_rainbow = mlx_load_png("./rainbow_small.png");
	texture = mlx_load_png("./player_small.png");
	t_wall = mlx_load_png("./wall_small.png");
	t_unicorn = mlx_load_png("./the_door_small.png");

	if (!texture)
	{
		printf("impossible de charger l'image player\n");
		mlx_close_window(mlx);
		exit(EXIT_FAILURE);
	}
	i_floor = mlx_texture_to_image(mlx, t_floor);
	player = mlx_texture_to_image(mlx, texture);
	rainbow = mlx_texture_to_image(mlx, t_rainbow);
	wall = mlx_texture_to_image(mlx, t_wall);
	unicorn = mlx_texture_to_image(mlx, t_unicorn);

	if (!player)
	{
		printf("impossible de convertir la texture en image\n");
		mlx_delete_texture(texture);
		mlx_close_window(mlx);
		exit(EXIT_FAILURE);
	}
	i = 0;
	j = 0;
	while (j < 7) // parcourir tout mon map **
	{
		i = 0;
		while (i < 7)
		{
			mlx_image_to_window(mlx, i_floor, i * 100, j * 100);
			i++;
		}
		j++;
	}
	mlx_image_to_window(mlx, wall, 300, 300);
	mlx_image_to_window(mlx, wall, 400, 300);
	
	
	mlx_image_to_window(mlx, rainbow, 0, 0);
	mlx_image_to_window(mlx, rainbow, 100, 0);
	
	mlx_image_to_window(mlx, rainbow, 400, 200);
	if (mlx_image_to_window(mlx, player, 100, 100) == -1)
	{
		printf("Erreur: Impossible d'afficher l'image\n");
		mlx_delete_texture(texture);
		mlx_close_window(mlx);
		exit(EXIT_FAILURE);
	}
	mlx_image_to_window(mlx, unicorn, 200, 230);

	printf("Image chargée avec succès!\n");
}

void	ft_hook(void *param)
{
	mlx_t	*mlx;
	static int move = 0;
	static double last_press_time = 0;
	//double current_time = mlx_get_time();
	//const double delay = 0.1;

	mlx = param;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_get_time() - last_press_time >= 0.15)
	{
		// double temps = mlx_get_time();
		// printf("%10.2f\n", temps);
		if (mlx_is_key_down(mlx, MLX_KEY_UP))
		{
			player->instances[0].y -= 100;
			move++;
			printf("Moves =%d", move);
		}
		if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
		{
			player->instances[0].y += 100;
			move++;
			printf("Moves =%d", move);
		}
		if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		{
			player->instances[0].x -= 100;
			move++;
			printf("Moves =%d", move);
		}	
		if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		{
			player->instances[0].x += 100;
			move++;
			printf("Moves =%d", move);
		}
		last_press_time = mlx_get_time();
		// if (moved)
		// {
		// 	move++;
		// 	last_press_time = mlx_get_time();
		// }
	}
}


// -----------------------------------------------------------------------------

int32_t	main(void)
{
	mlx_t *mlx;

	// Gotta error check this stuff
	if (!(mlx = mlx_init(WIDTH, HEIGHT, "so_long", true)))
	{
		puts(mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}

	mlx_load_textures(mlx);
	mlx_loop_hook(mlx, ft_hook, mlx);
	
	mlx_loop(mlx);
	mlx_delete_image(mlx, player); // et rainbow et floot et unicorn>>>
	mlx_delete_texture(texture); // et rainbow et floot et unicorn>>>
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}