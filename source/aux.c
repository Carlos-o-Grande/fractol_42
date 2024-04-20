/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 12:42:47 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/04/12 15:11:21 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

void	init_shader(t_fractol *s, int type, double par1, double par2)
{
	s->iterations = 100;
	s->orbit = 4;
	s->zoom = 1.0;
	s->type = type;
	if (s->type == Mandelbox)
		s->zoom *= 3;
	s->shader = Simple;
	s->fill = 5;
	s->scale = 2.0;
	s->x_plane = (t_dbl){-2, 2};
	s->y_plane = (t_dbl){-2, 2};
	s->x_shift = 0.0;
	s->y_shift = 0.0;
	s->smooth = 0.05;
	s->julia_r = par1;
	s->julia_c = par2 * -1;
	s->julia_preset = 5;
	if (type == Interactive)
	{
		s->help = 1;
		s->julia_r = -0.8;
		s->julia_c = 0.156 * -1;
	}
}

void	change_julia_values(t_fractol *s, int preset)
{
	const t_dbl	values[6] = {
	{-0.4, 0.6},
	{-0.4, -0.6},
	{0.285, 0.01},
	{-0.70176, -0.3842},
	{-0.835, 0.2321},
	{-0.8, 0.156}};

	if (preset > 5)
		s->julia_preset = 0;
	s->julia_r = values[s->julia_preset].x;
	s->julia_c = values[s->julia_preset].y * -1;
}

// double map(double value,
// double o_low, double o_high, double d_low, double d_high)
// return (value - o_low) / (o_high - o_low) * (d_high - d_low) + d_low;
double	map(double value, t_dbl orig, t_dbl dest)
{
	return ((value - orig.x) / (orig.y - orig.x) * (dest.y - dest.x) + dest.x);
}

bool	check_julia_input(char *arg)
{
	bool	dot;
	float	test;

	dot = false;
	test = ft_atof(arg);
	while (ft_isspace(*arg))
		arg++;
	if (*arg == '-' || *arg == '+')
		arg++;
	while (*arg)
	{
		if (!ft_isdigit(*arg) && *arg != '.')
			return (false);
		if (*arg == '.' && !dot)
			dot = true;
		else if (*arg == '.' && dot)
			return (false);
		arg++;
	}
	if (isnan(test) || isinf(test))
		return (false);
	return (true);
}
