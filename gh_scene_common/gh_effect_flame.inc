#local Scale_All = 1;
#local Tiles = 1/8 * Scale_All;
#include "GearHead.inc"

global_settings {max_trace_level 50}

#local Flame_Obj = sphere
{
	0, 2.0 scale <1,0.1,1> translate 0.5*y scale Scale_All
	pigment {color rgb <0.85,0.45,0.15>}
}

// Rune's Particle System
// Sample animation scene file
// 
// Suggested command line settings (for 25 frames per second):
// +kff50 +kf2 +kc
   
   
// Include particle system include file
// ************************************
   
   #include "particle.inc"
   
// Clock settings
// **************
   
   #local particle_start  = 0.0;
   #local particle_end    = 2.0;
   #local particle_cyclic = on;
   #local particle_steps  = 100;
   
// General particle settings
// *************************
   
   #local particle_frequency = 40;
   #local particle_life      = 0.7;
   #local particle_lifeturb  = 0.3;
   #local particle_seed      = 123;
   //#local particle_maxnumber = 100;
   
// Environment settings
// ********************
   
   #local particle_drag      = 0.0;
   #local particle_transfer  = 0.0;
   
   #macro particle_gravity  (Clock,Point) 40*y #end
   #macro particle_wind     (Clock,Point) <0,0,0> #end
   
// Emitter settings
// ****************
   
   #macro particle_emitter  (Clock) <0,0,0> #end
   #macro particle_emitting (Clock) on      #end
   #macro particle_emitvect (Clock) <0,0,0> #end
   #macro particle_emitturb (Clock) 1.5     #end
   #macro particle_emitobj  (Clock) Flame_Obj #end
   #macro particle_emitobjn (Clock) 0.0     #end
   
// Collision settings
// ******************
   
// (Collision settings not used)
   
// Call particle system
// ********************
   
   particle_system ("fire")
   
// Load system
// ***********
   
   #include "fire.inc"
   
   #local fire_method     = 1;
   #local fire_color      = <0.85,0.45,0.15>;
   #local fire_intensity  = 2.0;
   #local fire_highlight  = 2.0;
   #local fire_samples    = 5;
   #local fire_turbulence = 1.0;
   #local fire_size       = 1.2 * Scale_All;
   #local fire_stretch    = 0.1;
   
   fire_create("fire")
   
// Scene setup
// ***********
  

   light_source {
      fire_center, color 0.25*fire_light*<1.0,0.7,0.4>
      fade_power 2 fade_distance 10
      area_light 5*x, 5*z, 5, 5 jitter adaptive 0 circular orient
   }
   