/// LSU EE X70X GPU Prog / Microarch
//
 /// Initialize different scenes (add balls, boxes, tiles to scene).

#include "boxes.h"
#include "world.h"
#include "phys-obj-ball.h"
#include "phys-obj-box.h"
#include "phys-obj-tile.h"

void
World::setup_multinano()
{

  // scene setup for rolled nanotube..

  all_remove();

  const bool glued = true;
  scene_change=2;
  pCoor block_base
    (0, platform_y, 0);
 
      pVect block_diag
        (120,4,100);
      //
      // Add a new block to scene.
      //
      Box* const b = box_manager->new_box
        (block_base+ pVect(-block_diag.x*0.5,0,-block_diag.z*0.5) ,
         block_diag,color_orange);

      // Rotate it.
      //
      const float angle = 0;
      b->rotate(pVect(0,1,0),angle);

      // Maybe fix it in place if its the bottom block.
      //
      if ( glued ) b->set_read_only();

      // Increment the tower y position.
      //
      block_base += pVect(0,block_diag.y,0);

      pVect block_diag2
        (90,4,80);

      Box* const b2 = box_manager->new_box
        (block_base + pVect(-block_diag2.x*0.5,0,-block_diag2.z*0.5),
         block_diag2,color_green);

      // Rotate it.
      //
      const float angle2 = 0;
      b2->rotate(pVect(0,1,0),angle2);

      // Maybe fix it in place if its the bottom block.
      //
      if ( glued ) b2->set_read_only();
       block_base += pVect(0,block_diag2.y,0);

   
      opt_spring_constant=1000;
      const float ball_radius = 2;
      dist_bwt_atoms = 8;
      len_of_nanotube = 10;
      breadth_of_nanotube = 6;
      const float delta_theta = (2.0 * M_PI)/6;
     
      pCoor  pos_first_ball_nano(b->position.x-60,block_base.y+ 75 ,b->position.z-17);
   
      while(Clist.occ()>0){Clist.pop();}
      while(Clist2.occ()>0){Clist2.pop();}

      // Looping construct for arranging position of Zigzag Carbon Nanotube.
	  
	  for(int i = 1;i<= breadth_of_nanotube;i++)
	    
	    {
	      for (int k=1;k<=4;k++)
		{
		  for (int j = 0;j< len_of_nanotube;j++ )
		    {
		      Ball* const ball1 = new Ball(this);
		    
		     
		      ball1->position =
			pos_first_ball_nano +  pVect(0,2*dist_bwt_atoms*sinf(((delta_theta*6)/len_of_nanotube)*j),2*dist_bwt_atoms*cosf(((delta_theta*6)/len_of_nanotube)*j));
		      ball1->radius = ball_radius;
		      ball1->velocity = pVect(0,0,0);
		      ball1->omega = pVect(0,0,0);
		      // Add ball to list of simulated objects. This does not
		      // have to be done for tiles and boxes.
		      ball1->ballpos1=pCoor(0,0,0);
		      ball1->ballpos2=pCoor(0,0,0);
		      ball1->bpos1bond=false;
		      ball1->bpos2bond=false;
		      physs += ball1;
		      Clist +=ball1;
		    
		      
		    }
	     
		  if(k==1){
		    pos_first_ball_nano+=pVect(dist_bwt_atoms*sinf(delta_theta),0,dist_bwt_atoms*cosf(delta_theta));}
		  if(k==2){
		    pos_first_ball_nano+=pVect(dist_bwt_atoms,0,0);}
		  if(k==3){
		    pos_first_ball_nano+=pVect(dist_bwt_atoms*sinf(delta_theta),0,-dist_bwt_atoms*cosf(delta_theta));}
		}
	       pos_first_ball_nano+=pVect(dist_bwt_atoms,0,0);
	    }
	  

     
}

  

void
World::setup_debug()
{
  // Setup scene needed to debug something.

  all_remove();

  pCoor b1(-7.92045593,  -38.3105736,  46.7977409);
  pQuat q1( -0.516331136,  0.065878585,  -0.848956704,
            -0.0912945643);
  pVect d1( 3.79823494,  0.800000012,  0.884832799);

  pCoor b2(-4.63814354,  -37.6203384,  47.0100594);
  pVect d2(2,2,2);
  pQuat q2( -0.0276855193,  -0.240952447,  -0.0504386313, 0.96882993);

  Box* const bx1 = box_manager->new_box_ctr(b1,2*d1,color_green_yellow);
  bx1->orientation = q1;
  bx1->geometry_update();
  Box* const bx2 = box_manager->new_box_ctr(b2,2*d2,color_snow);
  bx2->orientation = q2;
  bx2->geometry_update();
  return;

  pCoor corner(-1,-0.9*platform_xrad,platform_zmax-14);
  Box* const b = box_manager->new_box(corner,pVect(2,4,8),color_green_yellow);
  b->read_only = false;
  const float r_short = platform_xrad - opt_ball_radius;

  //  box_manager->new_box(corner+pVect(1,3,1),pVect(2,4,8),color_snow);
  box_manager->new_box(corner+pVect(1,0.01,0.01),pVect(2,4,8),color_snow);
  return;

  if ( true )
    {
      const double sa = asin( opt_ball_radius / r_short );
      const double ca = 1.5 * M_PI;
      const double a[] = { ca - sa, ca + sa, ca };
      const double r[] =
        { r_short, r_short,
          r_short - sqrt(3) * opt_ball_radius
        };
      for ( int i=0; i<3; i++ )
        {
          Ball* const b = new Ball(this);
          b->position = pCoor( r[i] * cos(a[i]), r[i] * sin(a[i]), 45);
          b->velocity = pVect(0,0,0);
          physs += b;
        }
    }
}


void
World::setup_diff_nanotube()
{

  // Scene setup for Zigzag and Armchair Nanotube.

  // Remove all existing objects from scene.
  //
  all_remove();
  scene_change=1;
  const bool glued = true;
  
  pCoor block_base
    (0, platform_y, 0);
  
  
      pVect block_diag
        (120,4,100);
      //
      // Add a new block to scene.
      //
      Box* const b = box_manager->new_box
        (block_base+ pVect(-block_diag.x*0.5,0,-block_diag.z*0.5) ,
         block_diag,color_orange);

    
      // Rotate it.
      //
      const float angle = 0;
      b->rotate(pVect(0,1,0),angle);

      // Maybe fix it in place if its the bottom block.
      //
      if ( glued ) b->set_read_only();

      // Increment the tower y position.
      //
      block_base += pVect(0,block_diag.y,0);

      pVect block_diag2
        (90,4,80);

      Box* const b2 = box_manager->new_box
        (block_base + pVect(-block_diag2.x*0.5,0,-block_diag2.z*0.5),
         block_diag2,color_green);

      // Rotate it.
      //
      const float angle2 = 0;
      b2->rotate(pVect(0,1,0),angle2);

      // Maybe fix it in place if its the bottom block.
      //
      if ( glued ) b2->set_read_only();
       block_base += pVect(0,block_diag2.y,0);

      
      const float ball_radius = 1;
      const float dist_bwt_atoms = 5;
      len_of_nanotube = 12;
      breadth_of_nanotube = 5;
      const float delta_theta = (2.0 * M_PI)/8;
      pCoor  pos_first_ball_nano(b->position.x+20,block_base.y+ 30 ,b->position.z-17);
       pCoor  pos_first_ball_nano2(b->position.x-100,block_base.y+ 30 ,b->position.z-17);
      const float cont_dis = 2*dist_bwt_atoms*cosf(delta_theta);
      const float cont_dis_1=dist_bwt_atoms*sinf(delta_theta);
      const float cont_dis_2=dist_bwt_atoms*cosf(delta_theta);
      while(Clist.occ()>0){Clist.pop();}
      while(Clist2.occ()>0){Clist2.pop();}
      // Looping construct for arranging position of Zigzag Carbon Nanotube.
	  for(int i = 1;i<= breadth_of_nanotube;i++)
	    
	    {
	      for (int k=1;k<=4;k++)
		{
		  for (int j = 0;j< len_of_nanotube;j++ )
		    {
		      Ball* const ball1 = new Ball(this);
		     
		      ball1->position =
			pos_first_ball_nano +  pVect(0,cont_dis*j,0);
		      ball1->radius = ball_radius;
		      ball1->velocity = pVect(0,0,0);
		      ball1->omega = pVect(0,0,0);
		      // Add ball to list of simulated objects. This does not
		      // have to be done for tiles and boxes.
		      ball1->ballpos1=pCoor(0,0,0);
		      ball1->ballpos2=pCoor(0,0,0);
		      ball1->bpos1bond=false;
		      ball1->bpos2bond=false;
		      physs += ball1;
		      Clist +=ball1;
		    
		      
		    }
	     
		  if(k==1){
		    pos_first_ball_nano+=pVect(cont_dis_1,-cont_dis_2,0);}
		  if(k==2){
		    pos_first_ball_nano+=pVect(dist_bwt_atoms,0,0);}
		  if(k==3){
		    pos_first_ball_nano+=pVect(cont_dis_1,cont_dis_2,0);}
		}
	       pos_first_ball_nano+=pVect(dist_bwt_atoms,0,0);
	    }
	  

	  for(int i = 1;i<= breadth_of_nanotube;i++)
	    
	    {
	      for (int k=1;k<=4;k++)
		{
		  for (int j = 0;j< len_of_nanotube;j++ )
		    {
		      Ball* const ball2 = new Ball(this);
		    
		      ball2->position =
			pos_first_ball_nano2 +  pVect(cont_dis*j,0,0);
		      ball2->radius = ball_radius;
		      ball2->velocity = pVect(0,0,0);
		      ball2->omega = pVect(0,0,0);
		      // Add ball to list of simulated objects. This does not
		      // have to be done for tiles and boxes.
		      ball2->ballpos1=pCoor(0,0,0);
		      ball2->ballpos2=pCoor(0,0,0);
		      ball2->bpos1bond=false;
		      ball2->bpos2bond=false;
		      physs += ball2;
		      Clist2 +=ball2;
		   
		    }
	      
		  if(k==1){
		    pos_first_ball_nano2+=pVect(-cont_dis_2,cont_dis_1,0);}
		  if(k==2){
		    pos_first_ball_nano2+=pVect(0,dist_bwt_atoms,0);}
		  if(k==3){
		    pos_first_ball_nano2+=pVect(cont_dis_2,cont_dis_1,0);}
		}
	       pos_first_ball_nano2+=pVect(0,dist_bwt_atoms,0);
	    }
	  
	
      
  
}

void
World::setup_nanotube(int dist, int len, int breadth)
{

  // Scene setup for testing lateral compression mechanism of Carbon Nanotube.
  
   // Remove all existing objects from scene.
  //
  all_remove();

  const bool glued = true;
  scene_change=3;
  pCoor block_base
    (0, platform_y, 0);
  
 
      pVect block_diag
        (120,4,100);
      //
      // Add a new block to scene.
      //
      Box* const b = box_manager->new_box
        (block_base+ pVect(-block_diag.x*0.5,0,-block_diag.z*0.5) ,
         block_diag,color_orange);

      
      // Rotate it.
      //
      const float angle = 0;
      b->rotate(pVect(0,1,0),angle);

      // Maybe fix it in place if its the bottom block.
      //
      if ( glued ) b->set_read_only();

      // Increment the tower y position.
      //
      block_base += pVect(0,block_diag.y,0);

      pVect block_diag2
        (90,4,80);

      Box* const b2 = box_manager->new_box
        (block_base + pVect(-block_diag2.x*0.5,0,-block_diag2.z*0.5),
         block_diag2,color_green);

      // Rotate it.
      //
      const float angle2 = 0;
      b2->rotate(pVect(0,1,0),angle2);

      // Maybe fix it in place if its the bottom block.
      //
      if ( glued ) b2->set_read_only();
       block_base += pVect(0,block_diag2.y,0);

      pVect block_diag3
        (20,40,60);

      Box* const b3 = box_manager->new_box
        (block_base + pVect(-block_diag2.x*0.5,0,-block_diag3.z*0.5),
         block_diag3,color_blue);

   
      // Rotate it.
      //
      const float angle3 = 0;
      b3->rotate(pVect(0,1,0),angle3);

      // Maybe fix it in place if its the bottom block.
      if ( glued ) b3->set_read_only();

      //block_base += pVect(0,block_diag3.y,0);

      pVect block_diag4
        (20,40,60);

      Box* const b4 = box_manager->new_box
        (block_base + pVect(block_diag2.x*0.5-block_diag4.x,0,-block_diag4.z*0.5),
         block_diag4,color_blue);

      
      // Rotate it.
      //
      const float angle4 = 0;
      b4->rotate(pVect(0,1,0),angle4);

      // Maybe fix it in place if its the bottom block.
      if ( glued ) b4->set_read_only();

            
      opt_spring_constant=500;
      const float ball_radius = 1;
      dist_bwt_atoms = dist;
      len_of_nanotube = len;
      breadth_of_nanotube = breadth;
      const float delta_theta = (2.0 * M_PI)/6;
     
      
      pCoor  pos_first_ball_nano(b->position.x-50,block_base.y+ 75 ,b->position.z-17);
      
      
      while(Clist.occ()>0){Clist.pop();}
      while(Clist2.occ()>0){Clist2.pop();}
      // Looping construct for arranging position of Zigzag Carbon Nanotube in a circular fashion.
	  for(int i = 1;i<= breadth_of_nanotube;i++)
	    
	    {
	      for (int k=1;k<=4;k++)
		{
		  for (int j = 0;j< len_of_nanotube;j++ )
		    {
		      Ball* const ball1 = new Ball(this);
		    
		      ball1->position =
			pos_first_ball_nano +  pVect(0,2*dist_bwt_atoms*sinf(((delta_theta*6)/len_of_nanotube)*j),2*dist_bwt_atoms*cosf(((delta_theta*6)/len_of_nanotube)*j));
		      ball1->radius = ball_radius;
		      ball1->velocity = pVect(0,0,0);
		      ball1->omega = pVect(0,0,0);
		      // Add ball to list of simulated objects. This does not
		      // have to be done for tiles and boxes.
		      ball1->ballpos1=pCoor(0,0,0);
		      ball1->ballpos2=pCoor(0,0,0);
		      ball1->bpos1bond=false;
		      ball1->bpos2bond=false;
		      physs += ball1;
		      Clist +=ball1;
		      
		    }
	    
		  if(k==1){
		    pos_first_ball_nano+=pVect(dist_bwt_atoms*sinf(delta_theta),0,dist_bwt_atoms*cosf(delta_theta));}
		  if(k==2){
		    pos_first_ball_nano+=pVect(dist_bwt_atoms,0,0);}
		  if(k==3){
		    pos_first_ball_nano+=pVect(dist_bwt_atoms*sinf(delta_theta),0,-dist_bwt_atoms*cosf(delta_theta));}
		}
	       pos_first_ball_nano+=pVect(dist_bwt_atoms,0,0);
	    }
	  

	  
	  // AFM probe for compressing the carbon nanotube. 

	  pVect block_diag5
	    (20,4,40);

	  Box* const b5 = box_manager->new_box
	    (block_base + pVect(-block_diag5.x*0.5,150,-block_diag5.z*0.5),
	     block_diag5,color_purple);

      
	  // Rotate it.
	  //
	  const float angle5 = 0;
	  b5->rotate(pVect(0,1,0),angle5);

	  // Maybe fix it in place if its the bottom block.
	  //
	  //	 if ( glued ) b5->set_read_only();

	  block_base += pVect(0,block_diag5.y,0);
}

void
World::setup_nanotube_2(int dist, int len, int breadth)
{

  // Scene setup for testing Vertical compression mechanism of Carbon Nanotube.

  // Remove all existing objects from scene.
  //
  all_remove();

  const bool glued = true;
  scene_change=4;
  pCoor block_base
    (0, platform_y, 0);
  
  
      pVect block_diag
        (120,4,100);
      //
      // Add a new block to scene.
      //
      Box* const b = box_manager->new_box
        (block_base+ pVect(-block_diag.x*0.5,0,-block_diag.z*0.5) ,
         block_diag,color_orange);

     
      // Rotate it.
      //
      const float angle = 0;
      b->rotate(pVect(0,1,0),angle);

      // Maybe fix it in place if its the bottom block.
      //
      if ( glued ) b->set_read_only();

      // Increment the tower y position.
      //
      block_base += pVect(0,block_diag.y,0);

      pVect block_diag2
        (90,4,80);

      Box* const b2 = box_manager->new_box
        (block_base + pVect(-block_diag2.x*0.5,0,-block_diag2.z*0.5),
         block_diag2,color_green);

      
      // Rotate it.
      //
      const float angle2 = 0;
      b2->rotate(pVect(0,1,0),angle2);

      // Maybe fix it in place if its the bottom block.
      //
      if ( glued ) b2->set_read_only();

       block_base += pVect(0,block_diag2.y,0);
     

      opt_spring_constant=900;
      const float ball_radius = 1;
      dist_bwt_atoms = dist;
      len_of_nanotube = len;
      breadth_of_nanotube = breadth;
      const float delta_theta = (2.0 * M_PI)/6;
      
      const float cont_dis_1=dist_bwt_atoms*sinf(delta_theta);
      const float cont_dis_2=dist_bwt_atoms*cosf(delta_theta);

      pCoor  pos_first_ball_nano(b->position.x+10,block_base.y+ 75 ,b->position.z+3);
     
      
      while(Clist.occ()>0){Clist.pop();}
      while(Clist2.occ()>0){Clist2.pop();}
	  
      // Looping construct for arranging position of Zigzag Carbon Nanotube in a circular fashion.

	  for(int i = 1;i<= breadth_of_nanotube;i++)
	    
	    {
	      for (int k=1;k<=4;k++)
		{
		  for (int j = 0;j< len_of_nanotube;j++ )
		    {
		      Ball* const ball1 = new Ball(this);
		  
		     
		      ball1->position =
			pos_first_ball_nano +  pVect(2*dist_bwt_atoms*cosf(((delta_theta*6)/len_of_nanotube)*j),0,2*dist_bwt_atoms*sinf(((delta_theta*6)/len_of_nanotube)*j));
		      ball1->radius = ball_radius;
		      ball1->velocity = pVect(0,0,0);
		      ball1->omega = pVect(0,0,0);
		     
		      ball1->ballpos1=pCoor(0,0,0);
		      ball1->ballpos2=pCoor(0,0,0);
		      ball1->bpos1bond=false;
		      ball1->bpos2bond=false;
		      physs += ball1;
		      Clist +=ball1;
     
		    }
		  if(k==1){
		    pos_first_ball_nano+=pVect(-cont_dis_2,cont_dis_1,0);}
		  if(k==2){
		    pos_first_ball_nano+=pVect(0,dist_bwt_atoms,0);}
		  if(k==3){
		    pos_first_ball_nano+=pVect(cont_dis_2,cont_dis_1,0);}
		}
	      pos_first_ball_nano+=pVect(0,dist_bwt_atoms,0);
	    }
	  
	 
     
	  // AFM probe for compressing the carbon nanotube. 

	  pVect block_diag3
	    (60,4,60);

	  Box* const b3 = box_manager->new_box
	    (block_base + pVect(-block_diag3.x*0.5,220,-block_diag3.z*0.5),
	     block_diag3,color_purple);

      
	  // Rotate it.
	  //
	  const float angle3 = 0;
	  b3->rotate(pVect(0,1,0),angle3);

	  // Maybe fix it in place if its the bottom block.
	  //
	  //	 if ( glued ) b3->set_read_only();

	  block_base += pVect(0,block_diag3.y,0);
}


void
World::benchmark_setup(int tiers)
{
  // Set up an arrangement of balls intended for performance measurement.

  cuda_at_balls_change();

  for ( Phys *phys; phys_live_iterate(phys); )
    { physs.iterate_yank(); delete phys; }

  const bool opt_multisize = false;

  // Note that number of balls determined by ball size.
  opt_ball_radius = opt_multisize ? 2.5 : 1.08;

  const float delta_x = opt_ball_radius * 2.1;
  const float delta_z = opt_ball_radius * 3 * 4;
  const float hdeltaz = delta_z / 2;
  const float hdeltax = delta_x / 2;
  const float delta_y = 2.1 * opt_ball_radius;
  const float ymax = delta_y * tiers - 0.001;

  const int balls_per_sheet = 30.0 * tiers * 2 * platform_xrad / delta_x;


  opt_drop_boxes = opt_drip = false;
  opt_spray_on = false;
  opt_verify = false;
  opt_mirror = false;
  opt_shadows = false;
#if 0
  const float platform_zwid = platform_zmax - platform_zmin;
  int ball_amt = 30000;
  while ( ball_amt > 0 )
    {
      const float z = platform_xmin + platform_zwid * drand48();
      const float x = platform_xmin + 2.0 * drand48() * platform_xrad;
      const float y = 2 * opt_ball_radius + drand48() * ymax;
      const pCoor pos(x,y,z);
      const double rad_min = 0.6;
      const float rad = max(rad_min,opt_ball_radius * pow(drand48(),1));
      if ( !sphere_empty(pos,rad) ) continue;
      ball_amt--;
      Ball* const b = new Ball(this);
      b->set_radius(rad);
      b->velocity = pVect(0,0,0);
      b->position = pos;
      physs += b;
    }
  return;
#endif

  //  const int balls_per_sheet = 30.0 * tiers * 2 * platform_xrad / delta_x;;

  opt_drop_boxes = opt_drip = false;
  opt_spray_on = false;
  opt_verify = false;
  opt_mirror = false;
  //  opt_shadows = false;
  //  opt_friction_coeff = 2.0;
  //  opt_friction_coeff = 0.01;
  opt_ball_density = 0.07;

  if ( opt_multisize )
    {
      for ( float z = platform_zmin + hdeltaz; z < platform_zmax; z+= delta_z )
        {
          for ( int i=0; i<balls_per_sheet; i++ )
            {
              const float x = platform_xmin + 2.0 * drand48() * platform_xrad;
              const float y = 2 * opt_ball_radius + drand48() * ymax;
              const pCoor pos(x,y,z);
              const double rad_min = 0.6;
              const float rad = max(rad_min,opt_ball_radius * pow(drand48(),1));
              if ( !sphere_empty(pos,rad) ) continue;
              Ball* const b = new Ball(this);
              b->set_radius(rad);
              b->velocity = pVect(0,0,0);
              b->position = pos;
              physs += b;
            }
        }
    }
  else
    {
      for ( float z = platform_zmin + hdeltaz; z < platform_zmax; z+= delta_z )
        for ( float x = platform_xmin + hdeltax;
              x < platform_xmax; x += delta_x )
          for ( float y = 0; y < ymax; y+= delta_y )
            {
              Ball* const b = new Ball(this);
              b->velocity.z = 0;
              b->position = pCoor(x,y,z);
              physs += b;
            }
    }
  variables_update();
  opt_elasticity = 0.1 / 16;
  opt_ball_density = 0.9;
  opt_ball_radius = 3.0;
}
