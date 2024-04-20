/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 13:49:34 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/04/07 19:08:19 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

double	mandelbrot(t_fractol *s, double real, double real_i)
{
	double	c_sqr;
	double	zx;
	double	zy;
	int		i;

	i = 0;
	zx = 0.0;
	zy = 0.0;
	c_sqr = real * real + real_i * real_i;
	if (256.0 * c_sqr * c_sqr - 96.0 * c_sqr + 32.0 * real - 3.0 < 0.0
		|| 16.0 * (c_sqr + 2.0 * real + 1.0) - 1.0 < 0.0)
		return (0);
	while (i < s->iterations)
	{
		if (zx * zx + zy * zy > 4)
			break ;
		c_sqr = (2.0 * zx * zy) + real_i ;
		zx = (zx * zx - zy * zy) + real;
		zy = c_sqr;
		i++;
	}
	return (i);
}

t_dbl	mandelbrot_csqr(t_fractol *s, double real, double real_i)
{
	double	c_sqr;
	double	zx;
	double	zy;
	int		i;

	i = 0;
	zx = 0.0;
	zy = 0.0;
	c_sqr = real * real + real_i * real_i;
	if (256.0 * c_sqr * c_sqr - 96.0 * c_sqr + 32.0 * real - 3.0 < 0.0)
		return ((t_dbl){0, c_sqr});
	if (16.0 * (c_sqr + 2.0 * real + 1.0) - 1.0 < 0.0)
		return ((t_dbl){999, c_sqr});
	while (i < s->iterations)
	{
		c_sqr = (2.0 * zx * zy) + real_i ;
		zx = (zx * zx - zy * zy) + real;
		zy = c_sqr;
		i++;
		if (zx * zx + zy * zy > 4)
			break ;
	}
	return ((t_dbl){i, zx * zx + zy * zy});
}

t_dbl	mandelbrot_escape(t_fractol *s, double real, double real_i)
{
	double	c_sqr;
	double	zx;
	double	zy;
	int		i;

	i = 0;
	zx = 0.0;
	zy = 0.0;
	c_sqr = real * real + real_i * real_i;
	if (256.0 * c_sqr * c_sqr - 96.0 * c_sqr + 32.0 * real - 3.0 < 0.0
		|| 16.0 * (c_sqr + 2.0 * real + 1.0) - 1.0 < 0.0)
		return ((t_dbl){0, c_sqr});
	while (i < s->iterations)
	{
		c_sqr = (2.0 * zx * zy) + real_i;
		zx = (zx * zx - zy * zy) + real;
		zy = c_sqr;
		i++;
		if (sqrt(zx * zx + zy * zy) > 11.0f)
			break ;
	}
	return ((t_dbl){i, zx * zx + zy * zy});
}
