/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbox.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 12:50:52 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/04/07 20:15:31 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

t_dbl	mandelbox(t_fractol *s, double real, double real_i)
{
	double	c_sqr;
	t_dbl	z;
	t_vec3	b;
	float	dist;
	int		i;

	z.x = real;
	z.y = real_i;
	dist = 1.0;
	i = 0;
	while (i < s->fill)
	{
		b = mandelbox_fold(s, (t_vec3){z.x, z.y, dist});
		z.x = b.x;
		z.y = b.y;
		dist = b.z;
		z.x = s->scale * z.x + real;
		z.y = s->scale * z.y + real_i;
		dist = s->scale + 1.0;
		i++;
	}
	c_sqr = z.x * z.x + z.y * z.y;
	return ((t_dbl){sqrt(c_sqr), dist});
}

static float	fold_helper(float val, float scale)
{
	if (val > 1)
		return (scale - val);
	else if (val < -1)
		return (-scale - val);
	return (val);
}

t_vec3	mandelbox_fold(t_fractol *s, t_vec3 z)
{
	double	c_sqr;
	double	inv_c_sqr;

	z.x = fold_helper(z.x, s->scale);
	z.y = fold_helper(z.y, s->scale);
	c_sqr = z.x * z.x + z.y * z.y;
	if (c_sqr < 0.5)
	{
		z.x *= 2.0;
		z.y *= 2.0;
		z.z *= 2.0;
	}
	else if (c_sqr < 1)
	{
		inv_c_sqr = 1.0 / c_sqr;
		z.x *= inv_c_sqr;
		z.y *= inv_c_sqr;
		z.z *= inv_c_sqr;
	}
	return ((t_vec3){z.x, z.y, z.z});
}

void	mandelbox_render(t_fractol *s, t_dbl pos, t_dbl pix)
{
	t_pixel	pixel;
	int		val;

	if (pix.x < pix.y)
	{
		val = (int)map(pix.x / pix.y, (t_dbl){0, 2}, (t_dbl){0, 255});
		pixel.r = val;
		pixel.g = val;
		pixel.b = val;
		pixel.rgb = (pixel.r << 16) | (pixel.g << 8) | pixel.b;
		pixel_put (&s->img, pos.x, pos.y, pixel.rgb);
	}
	else if (pix.x > pix.y)
	{
		val = (int)map(pix.x / pix.y, (t_dbl){0, 2}, (t_dbl){0, 255});
		pixel.r = 2;
		pixel.g = 2;
		pixel.b = 2;
		pixel.rgb = (pixel.r << 16) | (pixel.g << 8) | pixel.b;
		pixel_put (&s->img, pos.x, pos.y, pixel.rgb);
	}
}
