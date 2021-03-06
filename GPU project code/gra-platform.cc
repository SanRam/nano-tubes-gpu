/// LSU EE X70X GPU Prog / Microarch
//
 /// Code for Half-Cylinder Platform

#include "boxes.h"
#include "world.h"
#include "phys-obj-ball.h"
#include "phys-obj-box.h"
#include "phys-obj-tile.h"

void
World::platform_update()
{
  /// Set up Platform

  const bool curved = opt_platform_curved;
  const float platform_delta_z = platform_zmax - platform_zmin;
  const int tile_count = int(max(1.0,platform_delta_z * 0.15));
  const float zdelta = platform_delta_z / tile_count;
  const float platform_delta_x = platform_xmax - platform_xmin;

  PStack<pVect> p_tile_coords;
  PStack<pVect> p1_tile_coords;
  PStack<pVect> p_tile_norms;
  PStack<pVect> p1_tile_norms;
  PStack<float> p_tex_coords, p1_tex_coords;
  platform_pi_xwidth_inv = M_PI / platform_delta_x;

  const int tess_bits = 2;
  const int tess_mask = 1 << tess_bits;
  const int th_tile_count = 19 << tess_bits;
  const double delta_theta = M_PI / th_tile_count;
  delta_theta_inv = 1.0 / delta_theta;
  tile_size_inv = 1 / zdelta;
  platform_xmid = 0.5 * ( platform_xmax + platform_xmin );
  platform_xrad = 0.5 * platform_delta_x;
  platform_xrad_inv = 1 / platform_xrad;
  platform_y = -platform_xrad;
  const double delta_x = platform_delta_x / th_tile_count;

  const float trdelta = ( trmax - trmin ) / tess_mask;

  for ( int i = 0; i < th_tile_count; i++ )
    {
      const double theta0 = i * delta_theta;
      const double theta1 = theta0 + delta_theta;
      bool even = i & tess_mask;
      const float x0c = platform_xmid - platform_xrad * cos(theta0);
      const float x1c = platform_xmid - platform_xrad * cos(theta1);
      const float y0c = -0.01 - platform_xrad * sin(theta0);
      const float y1c = -0.01 - platform_xrad * sin(theta1);
      pVect norm0c( cos(theta0), sin(theta0), 0);
      pVect norm1c( cos(theta1), sin(theta1), 0);

      const float x0 = curved ? x0c : platform_xmin + i * delta_x;
      const float x1 = curved ? x1c : x0 + delta_x;
      const float y0 = curved ? y0c : platform_y;
      const float y1 = curved ? y1c : platform_y;
      pVect norm0 = curved ? norm0c : pVect(0,1,0);
      pVect norm1 = curved ? norm1c : pVect(0,1,0);

      const float trma = trmax - trdelta * ( i & ( tess_mask - 1 ) );
      const float trmi = trma - trdelta;

      for ( float z = platform_zmin; z + 0.001 < platform_zmax; z += zdelta )
        {
          PStack<pVect>& t_coords = even ? p_tile_coords : p1_tile_coords;
          PStack<pVect>& t_norms = even ? p_tile_norms : p1_tile_norms;
          PStack<float>& tex_coords = even ? p_tex_coords : p1_tex_coords;
          tex_coords += trma; tex_coords += tsmax;
          t_coords += pVect(x0,y0,z);
          t_norms += norm0;  t_norms += norm0;
          tex_coords += trma; tex_coords += tsmin;
          t_coords += pVect(x0,y0,z+zdelta);
          tex_coords += trmi; tex_coords += tsmin;
          t_coords += pVect(x1,y1,z+zdelta);
          t_norms += norm1;  t_norms += norm1;
          tex_coords += trmi; tex_coords += tsmax;
          t_coords += pVect(x1,y1,z);
          even = !even;
        }
    }

  platform_even_vtx_cnt = p_tile_coords.occ();
  platform_odd_vtx_cnt = p1_tile_coords.occ();

  while ( pVect* const v = p1_tile_coords.iterate() ) p_tile_coords += *v;
  while ( pVect* const v = p1_tile_norms.iterate() ) p_tile_norms += *v;
  while ( float* const v = p1_tex_coords.iterate() ) p_tex_coords += *v;

  platform_tile_norms.re_take(p_tile_norms);
  platform_tile_norms.to_gpu();
  platform_tile_coords.re_take(p_tile_coords);
  platform_tile_coords.to_gpu();
  platform_tex_coords.re_take(p_tex_coords);
  platform_tex_coords.to_gpu();
}
