/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 12:45:03 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/04/08 09:01:41 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

int	handle_keypress(int keysym, t_fractol *s)
{
	if (keysym == XK_Escape)
		end_fractol(s);
	if (keysym == XK_r)
		init_shader(s, s->type, s->julia_r, s->julia_c);
	if (keysym == XK_Up || keysym == XK_w)
		s->y_shift += map((double)60, (t_dbl){0, H}, s->y_plane) / 4 * s->zoom;
	if (keysym == XK_Down || keysym == XK_s)
		s->y_shift -= map((double)60, (t_dbl){0, H}, s->y_plane) / 4 * s->zoom;
	if (keysym == XK_Left || keysym == XK_a)
		s->x_shift += map((double)60, (t_dbl){0, H}, s->x_plane) / 4 * s->zoom;
	if (keysym == XK_Right || keysym == XK_d)
		s->x_shift -= map((double)60, (t_dbl){0, H}, s->x_plane) / 4 * s->zoom;
	if (keysym == XK_h)
	{
		if (s->help == 1)
		{
			if (s->type == Interactive)
				render_rect(&s->img, (t_rect){0, 0, H, H, BLACK});
			return (s->help = 0, render(s));
		}
		return (s->help = 1, render(s));
	}
	fractal_keypress(keysym, s);
	return (0);
}

int	fractal_keypress(int keysym, t_fractol *s)
{
	if (s->type == Mandelbox)
	{
		if (keysym == XK_i)
			s->fill++;
		if (keysym == XK_k)
			s->fill--;
		if (keysym == XK_o)
			s->scale += 0.1;
		if (keysym == XK_l)
			s->scale -= 0.1;
	}
	else
	{
		if (keysym == XK_i)
			s->iterations += 10;
		if (keysym == XK_k)
			s->iterations -= 10;
		if (keysym == XK_o)
			s->smooth += 0.01;
		if (keysym == XK_l)
			s->smooth -= 0.01;
		if (keysym == XK_j)
			change_julia_values(s, ++s->julia_preset);
	}
	return (render(s), 0);
}

int	interactive_keypress(int keysym, t_fractol *s)
{
	static int	first_run;

	if (keysym == XK_t)
	{
		if (s->type == Interactive && !first_run++)
			s->type = Mandelbrot;
		else if (s->type == Mandelbox)
		{
			s->type = Mandelbrot;
			s->zoom /= 3;
		}
		else
			s->type++;
		if (s->type == Mandelbox)
			s->zoom *= 3;
	}
	if (keysym == XK_y)
	{
		if (s->shader == Dark)
			s->shader = Simple;
		else
			s->shader++;
	}
	handle_keypress(keysym, s);
	return (0);
}

int	handle_buttons(int button, int x, int y, t_fractol *s)
{
	static t_dbl	pos;
	bool			mouse_moved;

	mouse_moved = true;
	if (pos.x != x || pos.y != y)
	{
		mouse_moved = true;
		pos = (t_dbl){x, y};
	}
	if (button == Button1 && x < H)
	{
		s->y_shift += map((double)y, (t_dbl){0, H}, s->y_plane) / 1 * s->zoom;
		s->x_shift += map((double)x, (t_dbl){0, H}, s->x_plane) / 1 * s->zoom;
	}
	if (button == Button5)
		s->zoom *= 1.05;
	if (button == Button4)
		s->zoom *= 0.95;
	if ((button == Button5 || button == Button4) && mouse_moved)
	{
		s->x_shift += map((double)x, (t_dbl){0, H}, s->x_plane) / 4 * s->zoom;
		s->y_shift += map((double)y, (t_dbl){0, H}, s->y_plane) / 4 * s->zoom;
	}
	render(s);
	return (0);
}
