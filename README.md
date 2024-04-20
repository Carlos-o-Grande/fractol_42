# Fract'ol

Usage: fractol [OPTION]
  -fm                   render Mandelbrot
  -fj                   render Julia with default values
  -fj float float       define values for Julia
  -fb                   render Mandelbox fractal (bonus)
  -fi                   render Fractol in interactive mode
  -h                    show complete help text

Fractol key usage
  MOVE                  WASD, or arrow keys
  ZOOM                  RF, or mouse whell to zoom
  CENTER                click on new view center
  RESET                 R to reset view to default values
  HELP                  H to view help screen

Mandelbrot / Julia
  ITERATIONS            IK to increase/decrease
  SMOOTH                OL to increase/decrease. Not available for all.

Mandelbox (bonus fractal)
  STEPS                 IK to increase/decrease
  SCALE                 OL to increase/decrease.

INTERACTIVE MODE
                        T change fractal type
                        G circle color pallete (not available for all)

NOTE: increasing ZOOM or ITERACTIONS will also increase render time.
      The program will probably zoom forever, however after limit
      of double is reached, no further quality is possible.

cjoao-de@42lisboa


// todo clean include file
// todo copy keypress references
