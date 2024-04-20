/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 16:01:29 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/04/10 14:47:42 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

int	end_fractol(t_fractol *s)
{
	free(s->m_smooth);
	free(s->m_julia_r);
	free(s->m_julia_c);
	mlx_destroy_image(s->mlx_ptr, s->img.image);
	mlx_destroy_window(s->mlx_ptr, s->win_ptr);
	mlx_destroy_display(s->mlx_ptr);
	free(s->mlx_ptr);
	exit(0);
}

int	setup_hooks(t_fractol *s, int type)
{
	if (type == Interactive)
	{
		mlx_hook(s->win_ptr, KeyPress, KeyPressMask, &interactive_keypress, s);
		render(s);
	}
	else
		mlx_hook(s->win_ptr, KeyPress, KeyPressMask, &handle_keypress, s);
	mlx_hook(s->win_ptr, ButtonPress, ButtonPressMask, &handle_buttons, s);
	mlx_hook(s->win_ptr, DestroyNotify, StructureNotifyMask, &end_fractol, s);
	render(s);
	mlx_loop(s->mlx_ptr);
	return (0);
}

// name of windows, type of fractal, par1, par2 of Julia
int	setup_mlx(char *name, int type, double par1, double par2)
{
	static t_fractol	s;

	s.mlx_ptr = mlx_init();
	if (!s.mlx_ptr)
		return (MLX_ERROR);
	s.win_ptr = mlx_new_window(s.mlx_ptr, W, H, name);
	if (!s.win_ptr)
	{
		free(s.win_ptr);
		return (MLX_ERROR);
	}
	s.img.image = mlx_new_image(s.mlx_ptr, W, H);
	s.img.data = mlx_get_data_addr(s.img.image, &s.img.bpp,
			&s.img.size_line, &s.img.type);
	init_shader(&s, type, par1, par2);
	setup_hooks(&s, type);
	render(&s);
	mlx_loop(s.mlx_ptr);
	return (0);
}
	// mlx_loop_hook(s.mlx_ptr, &render_loop, &s);

int	main(int argc, char *argv[])
{
	if (argc == 2)
	{
		if (!ft_strncmp(argv[1], "-fm", 4))
			setup_mlx("Mandelbrot", Mandelbrot, 0, 0);
		else if (!ft_strncmp(argv[1], "-fj", 4))
			setup_mlx("Julia", Julia, -0.8, 0.156);
		else if (!ft_strncmp(argv[1], "-fb", 4))
			setup_mlx("Mandelbox", Mandelbox, 0, 0);
		else if (!ft_strncmp(argv[1], "-fi", 4))
			setup_mlx("Interactive", Interactive, 0, 0);
		else if (!ft_strncmp(argv[1], "-h", 4))
			return (print_full_help(), 0);
	}
	if (argc == 4)
	{
		if (!ft_strncmp(argv[1], "-fj", 4))
		{
			if (check_julia_input(argv[2]) && check_julia_input(argv[3]))
				setup_mlx("Julia", Julia, ft_atof(argv[2]), ft_atof(argv[3]));
		}
	}
	print_help();
	return (0);
}
