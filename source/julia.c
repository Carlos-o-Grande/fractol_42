/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 13:49:34 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/04/12 15:07:15 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

double	julia(t_fractol *s, double real, double real_i)
{
	double	c_sqr;
	double	zx;
	double	zy;
	int		i;

	i = 0;
	zx = real;
	zy = real_i;
	while (i < s->iterations)
	{
		if (zx * zx + zy * zy > 4)
			break ;
		c_sqr = (2.0 * zx * zy) + s->julia_c;
		zx = (zx * zx - zy * zy) + s->julia_r;
		zy = c_sqr;
		i++;
	}
	return (i);
}

t_dbl	julia_csqr(t_fractol *s, double real, double real_i)
{
	double	c_sqr;
	double	zx;
	double	zy;
	int		i;

	i = 0;
	zx = real;
	zy = real_i;
	while (i < s->iterations)
	{
		if (zx * zx + zy * zy > 4)
			break ;
		c_sqr = (2.0 * zx * zy) + s->julia_c;
		zx = (zx * zx - zy * zy) + s->julia_r;
		zy = c_sqr;
		i++;
	}
	return ((t_dbl){i, zx * zx + zy * zy});
}

t_dbl	julia_escape(t_fractol *s, double real, double real_i)
{
	double	c_sqr;
	double	zx;
	double	zy;
	int		i;

	i = 0;
	zx = real;
	zy = real_i;
	while (i < s->iterations)
	{
		c_sqr = (2.0 * zx * zy) + s->julia_c;
		zx = (zx * zx - zy * zy) + s->julia_r;
		zy = c_sqr;
		i++;
		if (sqrt(zx * zx + zy * zy) > 11.0f)
			break ;
	}
	return ((t_dbl){i, zx * zx + zy * zy});
}
