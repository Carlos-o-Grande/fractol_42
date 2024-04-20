/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shaders.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 12:50:52 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/04/10 13:40:07 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

void	simple_render(t_fractol *s, t_dbl pos, double n)
{
	t_pixel	pixel;

	n = (int)n;
	if (n == 0)
		return (pixel_put (&s->img, pos.x, pos.y, BLACK));
	else if (n == s->iterations)
		return (pixel_put (&s->img, pos.x, pos.y, BLACK));
	pixel.r = (int)((n / 255 * 100) * 30);
	pixel.g = (int)((n / 255 * 100) * 30);
	pixel.b = (int)((n / 255 * 100) * 10);
	pixel.rgb = (pixel.r << 16) | (pixel.g << 8) | pixel.b;
	pixel_put (&s->img, pos.x, pos.y, pixel.rgb);
}

void	escape_shader(t_fractol *s, t_dbl pos, t_dbl i_csqr)
{
	t_pixel	pixel;
	float	mu;

	if (i_csqr.x == s->iterations || i_csqr.x == 0)
		return (pixel_put (&s->img, pos.x, pos.y, BLACK));
	mu = i_csqr.x - (log(log(sqrt(i_csqr.y)))) / log (2.0);
	pixel.r = (int)map(mu, (t_dbl){0, 8}, (t_dbl){0, 255});
	pixel.g = (int)map(mu, (t_dbl){0, 68}, (t_dbl){0, 255});
	pixel.b = (int)map(mu, (t_dbl){0, 40}, (t_dbl){0, 255});
	pixel.rgb = (pixel.r << 16) | (pixel.g << 8) | pixel.b;
	pixel_put (&s->img, pos.x, pos.y, pixel.rgb);
}

void	demo_shader(t_fractol *s, t_dbl pos, t_dbl i_csqr)
{
	if (i_csqr.x == 0)
		return (pixel_put(&s->img, pos.x, pos.y, BLUE));
	if (i_csqr.x == 999)
		return (pixel_put(&s->img, pos.x, pos.y, RED));
	if (i_csqr.x == s->iterations)
		return (pixel_put(&s->img, pos.x, pos.y, BLACK));
	return (pixel_put(&s->img, pos.x, pos.y, WHITE));
}

void	smooth_shader(t_fractol *s, t_dbl pos, t_dbl i_csqr)
{
	double	sn;
	double	hue;
	t_pixel	pixel;

	s->rgb.len = sqrt(i_csqr.y);
	if (i_csqr.x == s->iterations || i_csqr.x == 0 || i_csqr.x == 999)
		return (pixel_put (&s->img, pos.x, pos.y, BLACK));
	sn = i_csqr.x - log2(log2(i_csqr.y)) + 4.0;
	hue = sn / s->iterations;
	pixel.rgb = map(hue, (t_dbl){0, 1}, (t_dbl){0, 255});
	pixel.r = (0.5 + 0.5 * cos(3.0 + pixel.rgb * s->smooth + 0.0)) * 255;
	pixel.g = (0.5 + 0.5 * cos(3.0 + pixel.rgb * s->smooth + 0.6)) * 255;
	pixel.b = (0.5 + 0.5 * cos(3.0 + pixel.rgb * s->smooth + 1.0)) * 255;
	pixel.rgb = (pixel.r << 16) | (pixel.g << 8) | pixel.b;
	pixel_put (&s->img, pos.x, pos.y, pixel.rgb);
}

void	shader_dark(t_fractol *s, t_dbl pos, double n)
{
	double	log_iter;
	t_pixel	pixel;
	double	coeff;

	coeff = 1;
	if (n == s->iterations)
		return (pixel_put (&s->img, pos.x, pos.y, BLACK));
	if (n == 0)
		coeff = 20000;
	log_iter = log(n + 1) / log(s->iterations * coeff);
	pixel.r = (int)(255 * pow(log_iter, 5.0));
	pixel.g = (int)(255 * pow(log_iter, 3.0));
	pixel.b = (int)(255 * pow(log_iter, 3.0));
	pixel.rgb = (pixel.r << 16) | (pixel.g << 8) | pixel.b;
	pixel_put (&s->img, pos.x, pos.y, pixel.rgb);
}
