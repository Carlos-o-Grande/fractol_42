/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_menu.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 12:45:03 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/04/08 08:11:36 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

void	render_menu(t_fractol *s)
{
	render_rect(&s->img, (t_rect){H, 0, W - H, H, WHITE});
	usleep(10000);
	mlx_string_put(s->mlx_ptr, s->win_ptr, H + 60, 50, BLACK, "Fract'ol");
	mlx_string_put(s->mlx_ptr, s->win_ptr, H + 30, 90, BLACK, "fractal:");
	mlx_string_put(s->mlx_ptr, s->win_ptr, H + 90, 90, BLACK, name(s->type));
	if (s->type == Mandelbrot)
		render_mandelbrot_info(s);
	else if (s->type == Julia)
		render_julia_info(s);
	else if (s->type == Mandelbox)
		render_mandelbox_info(s);
	mlx_string_put(s->mlx_ptr, s->win_ptr, H + 30, H - 100, BLACK,
		"time to frame:");
	mlx_string_put(s->mlx_ptr, s->win_ptr, H + 130, H - 100, BLACK, s->m_fps);
	mlx_string_put(s->mlx_ptr, s->win_ptr, H + 60, H - 50, RED, "(H) for Help");
	if (s->help == 1)
		render_help(s);
}

void	render_mandelbrot_info(t_fractol *s)
{
	char	*smooth;

	smooth = ft_ftoa(s->smooth, 100);
	mlx_string_put(s->mlx_ptr, s->win_ptr, H + 30, 150, BLACK, "Iterations:");
	mlx_string_put(s->mlx_ptr, s->win_ptr, H + 130, 150, BLACK, s->m_iter);
	mlx_string_put(s->mlx_ptr, s->win_ptr, H + 30, 210, BLACK, "Zoom (aprox):");
	mlx_string_put(s->mlx_ptr, s->win_ptr, H + 130, 210, BLACK, s->m_zoom);
	mlx_string_put(s->mlx_ptr, s->win_ptr, H + 30, 240, BLACK, "Smoothing:");
	mlx_string_put(s->mlx_ptr, s->win_ptr, H + 130, 240, BLACK, smooth);
	free(smooth);
}

void	render_julia_info(t_fractol *s)
{
	char	*smooth;
	char	*julia_r;
	char	*julia_c;

	smooth = ft_ftoa(s->smooth, 100);
	julia_r = ft_ftoa(s->julia_r, 10000);
	julia_c = ft_ftoa(s->julia_c, 10000);
	mlx_string_put(s->mlx_ptr, s->win_ptr, H + 30, 150, BLACK, "Iterations:");
	mlx_string_put(s->mlx_ptr, s->win_ptr, H + 130, 150, BLACK, s->m_iter);
	mlx_string_put(s->mlx_ptr, s->win_ptr, H + 30, 210, BLACK, "Zoom (aprox):");
	mlx_string_put(s->mlx_ptr, s->win_ptr, H + 130, 210, BLACK, s->m_zoom);
	mlx_string_put(s->mlx_ptr, s->win_ptr, H + 30, 240, BLACK, "Smoothing:");
	mlx_string_put(s->mlx_ptr, s->win_ptr, H + 130, 240, BLACK, smooth);
	mlx_string_put(s->mlx_ptr, s->win_ptr, H + 30, 270, BLACK, "Julia R:");
	mlx_string_put(s->mlx_ptr, s->win_ptr, H + 130, 270, BLACK, julia_r);
	mlx_string_put(s->mlx_ptr, s->win_ptr, H + 30, 300, BLACK, "Julia C:");
	mlx_string_put(s->mlx_ptr, s->win_ptr, H + 130, 300, BLACK, julia_c);
	free(smooth);
	free(julia_r);
	free(julia_c);
}

void	render_mandelbox_info(t_fractol *s)
{
	char	*scale;

	scale = ft_ftoa(s->scale, 100);
	mlx_string_put(s->mlx_ptr, s->win_ptr, H + 30, 150, BLACK, "Steps:");
	mlx_string_put(s->mlx_ptr, s->win_ptr, H + 130, 150, BLACK, s->m_fill);
	mlx_string_put(s->mlx_ptr, s->win_ptr, H + 30, 180, BLACK, "Scale:");
	mlx_string_put(s->mlx_ptr, s->win_ptr, H + 130, 180, BLACK, scale);
	free(scale);
}
