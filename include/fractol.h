/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 12:31:01 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/04/10 14:49:27 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# include <math.h>
# include <sys/time.h>
# include "../libs/libft/include/libft.h"
# include "../libs/minilibx-linux/mlx.h"
# include "../libs/minilibx-linux/mlx_int.h"

# define MLX_ERROR		1
# define W				1000
# define H				800

# define RED			0xFF0000
# define YELLOW			0xFFFF00
# define GREEN			0x00FF00
# define CYAN			0x00FFFF
# define BLUE			0x0000FF
# define MAGENTA		0xFF00FF
# define WHITE			0xFFFFFF
# define ALPHA_WHITE	0xAAAAAAAA
# define BLACK			0x000000
// # define FONT	"-*-helvetica-bold-r-*--20-*-*-*-*-*-*-*"
// # define FONT	"-misc-fixed-bold-*-normal-*-15-*-*-*-*-*-*-*"

typedef enum e_shader
{
	Simple,
	Escape,
	Demostration,
	Smooth,
	Dark,
}	t_shader;

typedef enum e_type
{
	Mandelbrot,
	Julia,
	Mandelbox,
	Interactive,
}	t_type;

typedef struct s_rect
{
	int	x;
	int	y;
	int	width;
	int	height;
	int	color;
}	t_rect;

// x = a, y = b || x < y || a < b
typedef struct s_dbl
{
	double		x;
	double		y;
}	t_dbl;

typedef struct s_int
{
	int		x;
	int		y;
}	t_int;

typedef struct s_vec3
{
	float		x;
	float		y;
	float		z;
}	t_vec3;

typedef struct s_pixel
{
	int		r;
	int		g;
	int		b;
	int		rgb;
	double	len;
	float	smooth;
}	t_pixel;

typedef struct s_upixel
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
	double			len;
	float			smooth;
}	t_upixel;

typedef struct s_fractol
{
	t_xvar	*mlx_ptr;
	void	*win_ptr;
	char	*name;
	t_img	img;
	t_pixel	rgb;
	int		cur_img;
	int		type;
	int		shader;
	int		help;
	t_dbl	x_plane;
	t_dbl	y_plane;
	double	x_shift;
	double	y_shift;
	double	orbit;
	double	sqr_z;
	double	julia_r;
	double	julia_c;
	int		julia_preset;
	int		iterations;
	int		fill;
	double	zoom;
	float	smooth;
	float	scale;
	char	*m_fps;
	char	*m_julia_r;
	char	*m_julia_c;
	char	*m_smooth;
	char	m_iter[5];
	char	m_fill[3];
	char	m_zoom[12];
	char	m_scale[6];
}	t_fractol;

//	fractol.c
int		setup_mlx(char *name, int type, double par1, double par2);
int		setup_hooks(t_fractol *s, int type);
int		end_fractol(t_fractol *s);

//	aux.c
void	init_shader(t_fractol *s, int type, double par1, double par2);
void	change_julia_values(t_fractol *s, int preset);
double	map(double value, t_dbl orig, t_dbl dest);
bool	check_julia_input(char *arg);

//	help.c
void	render_help(t_fractol *s);
void	print_help(void);
void	print_full_help(void);
char	*help_text(int idx);
char	*name(int idx);

//	hooks.c
int		handle_keypress(int keysym, t_fractol *s);
int		fractal_keypress(int keysym, t_fractol *s);
int		interactive_keypress(int keysym, t_fractol *s);
int		handle_buttons(int button, int x, int y, t_fractol *s);

//	mandelbox.c
t_dbl	mandelbox(t_fractol *s, double real, double real_i);
t_vec3	mandelbox_fold(t_fractol *s, t_vec3 z);
void	mandelbox_render(t_fractol *s, t_dbl pos, t_dbl pix);

//	mlx_aux.c
void	pixel_put(t_img *img, int x, int y, int color);
void	pixel_put_alpha(t_img *img, int x, int y, int color);
int		render_rect(t_img *img, t_rect rect);

//	render_menu.c
void	render_menu(t_fractol *s);
void	render_mandelbrot_info(t_fractol *s);
void	render_julia_info(t_fractol *s);
void	render_mandelbox_info(t_fractol *s);

//	render_select.c
void	select_render(t_fractol *s, t_dbl pos, t_dbl c);
void	render_mandelbrot(t_fractol *s, t_dbl pos, t_dbl c);
void	render_julia(t_fractol *s, t_dbl pos, t_dbl c);
void	render_mandelbox(t_fractol *s, t_dbl pos, t_dbl c);

//	render_shader.c
void	render_shader(t_fractol *s);
int		render(t_fractol *s);

//	mandelbrot.c
double	mandelbrot(t_fractol *s, double real, double real_i);
t_dbl	mandelbrot_csqr(t_fractol *s, double real, double real_i);
t_dbl	mandelbrot_escape(t_fractol *s, double real, double real_i);

//	julia.c
double	julia(t_fractol *s, double real, double real_i);
t_dbl	julia_csqr(t_fractol *s, double real, double real_i);
t_dbl	julia_escape(t_fractol *s, double real, double real_i);

//	shaders.c
void	simple_render(t_fractol *s, t_dbl pos, double n);
void	escape_shader(t_fractol *s, t_dbl pos, t_dbl i_csqr);
void	demo_shader(t_fractol *s, t_dbl pos, t_dbl i_csqr);
void	smooth_shader(t_fractol *s, t_dbl pos, t_dbl i_csqr);
void	shader_dark(t_fractol *s, t_dbl pos, double n);

#endif
