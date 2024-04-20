/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_shader.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 12:50:52 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/04/08 08:33:34 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

void	render_shader(t_fractol *s)
{
	int				x;
	int				y;
	double			real;
	double			real_i;
	static double	real_xy[H];

	y = -1;
	if (real_xy[0] == 0)
	{
		while (++y < H)
			real_xy[y] = ((-(H + H) + 4.0 * y) / H);
	}
	y = -1;
	while (++y < H)
	{
		real_i = real_xy[y] * s->zoom + s->y_shift;
		x = -1;
		while (++x < H)
		{
			real = real_xy[x] * s->zoom + s->x_shift;
			select_render(s, (t_dbl){x, y}, (t_dbl){real, real_i});
		}
	}
}

	// usleep(100000); //add if flickering
int	render(t_fractol *s)
{
	struct timeval	start;
	struct timeval	end;
	float			micros;

	if (s->win_ptr == NULL)
		return (1);
	gettimeofday(&start, NULL);
	render_shader(s);
	mlx_put_image_to_window(s->mlx_ptr, s->win_ptr, s->img.image, 0, 0);
	gettimeofday(&end, NULL);
	micros = (end.tv_usec - start.tv_usec) / 1000000.0f;
	if (micros < 0)
		micros += 1;
	s->m_fps = ft_ftoa(micros, 10000);
	ft_itoa_addr(s->iterations, s->m_iter);
	ft_itoa_addr(round((4.0 / s->zoom) / 10), s->m_zoom);
	ft_itoa_addr(s->fill, s->m_fill);
	render_menu(s);
	free(s->m_fps);
	return (0);
}
