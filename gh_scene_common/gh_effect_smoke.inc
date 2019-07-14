//#local Tiles = 1/12;
//#include "GearHead.inc"

// Rune's Particle System
// Sample animation scene file
// 
// Suggested command line settings (for 25 frames per second):
// +kff500 +ki-0.5 +kf1.5 -kc
   
   #local ShowCloud  = yes;
   #local ShowSmoke  = yes;//
   #local ShowDust   = no;
   #local ShowDebris = yes;
   
   #local exp_test = yes; // show solid spheres instead of ones with fire and smoke textures
   
   #local FocusSpline =
   spline {
      natural_spline
      -0.50,<0,0,5>,
      +0.10,<0,0,8>,
      +0.50,<0,0,1>,
      +0.80,<0,0,1>,
      +1.30,<0,0,0>,
   }
   
   #local FlashSpline =
   spline {
      linear_spline
      0.00,0.00,
      0.03,1.00,
      0.10,0.30,
   }
   light_source {
      <0,1.5,-0.2>,
      color <1.0,0.4,0.1>*25*FlashSpline(clock)
      fade_power 2 fade_distance 1
      shadowless
   }
   
   global_settings {max_trace_level 50}
   
   #local BuildingAndGround = plane {y,0 pigment {gamma_color_adjust(<1,1,1>)}}

   #local camera_location = Camera_Location;
   
//   object {BuildingAndGround}
   
// Include particle system include file
// ************************************
   
   #include "particle.inc"
   
// ...and particle element include file.
   #include "expl.inc"
   
   
// FIRST PARTICLE SYSTEM - EXPLOSION A
// ***********************************
   
// Clock options
// *************
   
   #local particle_start  = 0;
   #local particle_end    = 1.0;
   #local particle_cyclic = on;
   #local particle_steps  = 50;
   
// General particle options
// ************************
   
   #local particle_frequency = 150;
   #local particle_life      = 0.5;
   #local particle_lifeturb  = 0.5;
   #local particle_seed      = 234;
   //#local particle_maxnumber = 100;
   
// Environment options
// *******************
   
   #local particle_drag      = 0.3;
   #local particle_transfer  = 0.0;
   
   #macro particle_gravity  (Clock,Point) 200*y #end
   #macro particle_wind     (Clock,Point) 5*x #end
   
// Emitter options
// ***************
   
   #macro particle_emitter  (Clock) <0,0,0> #end
   #macro particle_emitting (Clock) (Clock<0.05) #end
   #macro particle_emitvect (Clock) <0,0,0> #end
   #macro particle_emitturb (Clock) 30.0     #end
   //#macro particle_emitobj  (Clock) object {} #end
   
// Collision options
// *****************
   
   #local particle_blockobj     = BuildingAndGround
   #local particle_bounce       = 1.0;
   #local particle_bounceturb   = 0.0;
   #local particle_friction     = 0.0;
   #local particle_bounceoffset = 0.01;
   //#macro particle_killobj    (Clock) object {}    #end
   
// Particle element macro (optional)
// *********************************
   
   #local exp_size       = 4.0;
   #local exp_opacity    = 1.0;
   #local exp_emission   = 3.5;		//2.5
   #local exp_smokeshade = 0.2;		//0.4
   #local exp_smokeglow  = 2.5;		//1.5
   #local exp_smokestart = 0.14;
   #local exp_fireend    = 0.23;
   #local exp_ambient    = 0.5;
   
   #macro particle_element() exp_element() #end
   
// Call particle system
// ********************
#declare Layer1 = union
   {
   #if (ShowCloud)
      particle_system ("explosion_a")
   #end
   }
   
   
// SECOND PARTICLE SYSTEM - EXPLOSION B
// ************************************
   
   #local particle_frequency = 60;
   #macro particle_emitting (Clock) on #end
   //#macro particle_emitvect (Clock) <0,0,0> #end
   #macro particle_emitturb (Clock) max(7+5,20-20*Clock) #end
   
   #local exp_size       = 2.5;//2.5
   #local exp_opacity    = 1.0;//1.0
   #local exp_emission   = 3.5;		//2.5
   #local exp_smokeshade = 0.2;		//0.4
   #local exp_smokeglow  = 2.5;		//1.5
   #local exp_smokestart = 0.14;//0.14
   #local exp_fireend    = 0.23;//0.23
   
   #macro particle_element() exp_element() #end
   
// Call particle system
// ********************
#declare Layer2 = union
   {
   #if (ShowSmoke)
      particle_system ("explosion_b")
   #end
   }
   
// THIRD PARTICLE SYSTEM - DUST
// ****************************
   
   #local particle_frequency = 150;
   #local particle_life      = 2.5*1.5;
   
   #macro particle_emitter  (Clock) <0,0.7,0> #end
   #macro particle_emitting (Clock) (Clock<0.05) #end
   //#macro particle_emitvect (Clock) <0,0,0> #end
   #macro particle_emitturb (Clock) 35 #end
   
   #macro particle_gravity  (Clock,Point) -10*y #end
   
   #local particle_blockobj    = plane{y,0}
   
   #local exp_size       = 6.0;
   #local exp_opacity    = 0.3;
   #local exp_emission   = 0.0;
   #local exp_smokeshade = 1.0;
   #local exp_smokeglow  = 0.0;
   #local exp_smokestart = 0.00;
   #local exp_fireend    = 0.00;
   
   #macro particle_element() exp_element() #end
   
// Call particle system
// ********************

#declare Layer3 = union
   {
   #if (ShowDust)
      particle_system ("dust")
   #end
   }
   
// FOURTH PARTICLE SYSTEM - DEBRIS
// *******************************
   
// Clock options
// *************
   
   #local particle_start  = 0.0;
   #local particle_end    = 2.0;
   #local particle_cyclic = off;
   #local particle_steps  = 50;
   
// General particle options
// ************************
   
   #local particle_frequency = 5000;
   #local particle_life      = 2.0;
   #local particle_lifeturb  = 0.5;
   #local particle_seed      = 243;
   #local particle_maxnumber = 250;
   
// Environment options
// *******************
   
   #local particle_drag      = 0.0;
   #local particle_transfer  = 0.0;
   
   #macro particle_gravity  (Clock,Point) -150*y #end
   #macro particle_wind     (Clock,Point) <0,0,0> #end
   
// Emitter options
// ***************
   
   #macro particle_emitter  (Clock) <0,1.3,-0.1> #end
   #macro particle_emitting (Clock) (Clock<0.05) #end
   #macro particle_emitvect (Clock) <0,0,-30>  #end
   #macro particle_emitturb (Clock) 35         #end
   //#macro particle_emitobj  (Clock) object {} #end
   
// Collision options
// *****************
   
   #local particle_blockobj    = BuildingAndGround
   #local particle_bounce       = 0.2;
   #local particle_bounceturb   = 0.0;
   #local particle_friction     = 1.0;
   #local particle_bounceoffset = 0.01;
   //#macro particle_killobj    (Clock) object {}    #end
   
// Particle element macro (optional)
// *********************************
   
   #macro particle_element ()
      #local Seed = seed(p_random*1000);
      box {
         -1, 1 scale <0.04,0.04,0.10>*(0.5+1.0*rand(Seed))
         pigment {gamma_color_adjust((<0.70,0.95,1.00>+<0.30,0.05,0.00>*rand(Seed))*(0.2+0.5*rand(Seed)))}
         finish {ambient 0.7 diffuse 0.3}
         rotate (p_rotate+p_location.z*(rand(Seed)-0.5))*360*y
         translate p_location
      }
   #end
   
// Call particle system
// ********************
   #declare Layer4 = union
   {
   #if (ShowDebris)
      particle_system ("debris")
   #end
   }
   
   