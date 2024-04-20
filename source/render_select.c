/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_select.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 12:50:52 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/04/07 17:00:26 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

void	select_render(t_fractol *s, t_dbl pos, t_dbl c)
{
	if (s->type == Mandelbrot)
		render_mandelbrot(s, pos, c);
	if (s->type == Julia)
		render_julia(s, pos, c);
	if (s->type == Mandelbox)
		render_mandelbox(s, pos, c);
}

void	render_mandelbrot(t_fractol *s, t_dbl pos, t_dbl c)
{
	if (s->shader == Simple)
		simple_render(s, (t_dbl){pos.x, pos.y}, mandelbrot(s, c.x, c.y));
	if (s->shader == Escape)
		escape_shader(s, (t_dbl){pos.x, pos.y}, mandelbrot_escape(s, c.x, c.y));
	if (s->shader == Demostration)
		demo_shader(s, (t_dbl){pos.x, pos.y}, mandelbrot_csqr(s, c.x, c.y));
	if (s->shader == Smooth)
		smooth_shader(s, (t_dbl){pos.x, pos.y}, mandelbrot_csqr(s, c.x, c.y));
	if (s->shader == Dark)
		shader_dark(s, (t_dbl){pos.x, pos.y}, mandelbrot(s, c.x, c.y));
}

void	render_julia(t_fractol *s, t_dbl pos, t_dbl c)
{
	if (s->shader == Simple)
		simple_render(s, (t_dbl){pos.x, pos.y}, julia(s, c.x, c.y));
	if (s->shader == Escape)
		escape_shader(s, (t_dbl){pos.x, pos.y}, julia_escape(s, c.x, c.y));
	if (s->shader == Demostration)
		demo_shader(s, (t_dbl){pos.x, pos.y}, julia_csqr(s, c.x, c.y));
	if (s->shader == Smooth)
		smooth_shader(s, (t_dbl){pos.x, pos.y}, julia_csqr(s, c.x, c.y));
	if (s->shader == Dark)
		shader_dark(s, (t_dbl){pos.x, pos.y}, julia(s, c.x, c.y));
}

void	render_mandelbox(t_fractol *s, t_dbl pos, t_dbl c)
{
	mandelbox_render(s, (t_dbl){pos.x, pos.y}, mandelbox(s, c.x, c.y));
}
