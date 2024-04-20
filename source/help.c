/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 15:57:19 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/04/12 16:47:50 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

// mo, to, lo are offsets for menu, text and lines
void	render_help(t_fractol *s)
{
	int	mo;
	int	to;
	int	lo;
	int	i;

	mo = (H - 500) / 2;
	to = mo + 50;
	i = 0;
	render_rect(&s->img, (t_rect){mo, mo, 500, 500, ALPHA_WHITE});
	mlx_string_put(s->mlx_ptr, s->win_ptr, (H / 2) - 20, to, BLACK, "HELP");
	while (help_text(i) != NULL)
	{
		lo = to + 30 + (i * 20);
		mlx_string_put(s->mlx_ptr, s->win_ptr, to, lo, BLACK, help_text(i));
		i++;
	}
}

void	print_help(void)
{
	ft_printf(
		"Usage: fractol [OPTION]\n"
		"  -fm			render Mandelbrot\n"
		"  -fj			render Julia with default values\n"
		"  -fj \e[3;35mfloat float\e[0m	define values for Julia\n"
		"  -fb			render Mandelbox fractal (bonus)\n"
		"  -fi			render Fractol in interactive mode\n"
		"\e[1;35m  -h			show complete help text\e[0m\n\n"
		"Fractol key usage\n"
		"  MOVE			WASD, or arrow keys\n"
		"  ZOOM			RF, or mouse whell to zoom\n"
		"  RESET			R to reset view to default values\n"
		"  HELP			H to view help screen\n"
		"  CENTER		click to center view\n"
		);
}

void	print_full_help(void)
{
	print_help();
	ft_printf(
		"\nMandelbrot / Julia\n"
		"  ITERATIONS		IK to increase/decrease\n"
		"  SMOOTH		OL to increase/decrease. Not available for all.\n\n"
		"Julia best results between  -2.0, 0.60 for 1st value\n"
		"                        and -1.3, 1.30 for 2nd value\n"
		"  NOTE: NOT include i, NOT invert sign, program will handle that\n"
		"                   i.e. 0.4i should be 0.4; -0.4i should be -0.4\n"
		"  PRESETS		J to change Julia preset values\n\n"
		"Mandelbox (bonus fractal)\n"
		"  STEPS			I K to increase/decrease\n"
		"  SCALE			O L to increase/decrease.\n\n"
		"INTERACTIVE MODE\n"
		"			T change fractal type\n"
		"			Y change shader\n"
		"			R to reset fractal to default values\n\n"
		"NOTE: increasing ZOOM or ITERATIONS will also increase render time.\n"
		"      The program will probably zoom forever, however after limit\n"
		"      of double is reached, no further quality is possible.\n"
		"\ncjoao-de@42lisboa\n"
		);
}

char	*help_text(int idx)
{
	const char	*text[] = {
		"movement:",
		"(WASD or arrow keys) to move image",
		"mouse wheel to ZOOM",
		"click to recenter",
		" ",
		"Mandelbrot and Julia",
		"(I, K) for  Iterations,   (O, L) for Depth",
		"Julia values must be between -2.0 and 2.0",
		"Press (J) to change Julia preset values",
		" ",
		"Mandelbox (bonus)",
		"(I, K) for  Steps,   (O, L) for scale",
		" ",
		"Interactive mode (-fi)",
		"(T) for next fractal",
		"(Y) for next shader",
		"(R) to reset to default values",
		"press (H) to close this help menu",
		" ",
		"Increasing iterations will make image generation take mooooooore time",
		NULL};

	return ((char *)text[idx]);
}

char	*name(int idx)
{
	const char	*shadername[] = {
		"Mandelbrot",
		"Julia",
		"Mandelbox",
		"Interactive",
		NULL};

	return ((char *)shadername[idx]);
}
