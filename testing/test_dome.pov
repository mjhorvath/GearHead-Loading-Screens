// Persistence of Vision Ray Tracer Scene Description File
// File: ?.pov
// Vers: 3.6
// Desc: Basic Scene Example
// Date: mm/dd/yy
// Auth: ?
//

#version 3.6;

#include "colors.inc"
#include "glass.inc"

global_settings {
  assumed_gamma 1.0
}

// ----------------------------------------

camera {
  location  <0.0, 0.5, -4.0>
  direction 1.5*z
  right     x*image_width/image_height
  look_at   <0.0, 0.0,  0.0>
scale 32
}

sky_sphere {
  pigment {
    gradient y
    color_map {
      [0.0 rgb <0.6,0.7,1.0>]
      [0.7 rgb <0.0,0.1,0.8>]
    }
  }
}

light_source {
  <0, 0, 0>            // light's position (translated below)
  color rgb <1, 1, 1>  // light's color
  translate <-30, 30, -30>
}

// ----------------------------------------

plane {
  y, 0
  pigment { color rgbt <0.7,0.5,0.3,1/2> }
}

// ----------------------------------------

#declare dome_radius		= 32;
#declare Seed			= seed(8829464);
#declare Included		= 1;				// tells any included files that they are being included.
#macro gamma_color_adjust(in_color)
	#local out_gamma = 2.2;
	#local in_color = in_color + <0,0,0,0,0>;
	color rgbft
	<
		pow(in_color.red, out_gamma),
		pow(in_color.green, out_gamma),
		pow(in_color.blue, out_gamma),
		in_color.filter,
		in_color.transmit
	>
#end

// ----------------------------------------

		// grass setup
		#include "grasspatch.inc"
		#local someseed			= seed(2345);
		#local xseed			= seed(422);
		#local zseed			= seed(369);
		#local Patch_Tranlation		= <0,0,0>;
		#local Use_Blade_Distance	= true;
		#local PlotPoints		= false;
		#local Blade_Density		= 4;		// per unit length. Square this to know how many will be in each unit squared of landscape
		#local Patch_Shape		= 0;		// Circular
		#local Spread_Correction	= 0.9;
		#local Blade_Height_Minimum	= 1/2;		// Blade_Heights are in standard POV units
		#local Blade_Height_Maximum	= 1;
		#local Blade_Detail		= 10;
		#local Max_Blade_Angle		= 15;
		#local Min_Blade_Angle		= 0;
		#local Blade_Scale		= 0.5;
		#local Blade_Width		= 0.1;
		#local Max_Blade_Detail		= 20;
		#local Min_Blade_Detail		= 5;
		#local Max_Detail_Distance	= 1;
		#local Min_Detail_Distance	= 10;
		#local Blade_Tex = texture			// And of course the texture. This is the default:
		{
			pigment {gamma_color_adjust(<64/255,104/255,72/255,> * 2)}
		}

		// dome setup
		#local N			= 2;
		#local Half			= 1;
		#local Method			= 1;
		#local Disc			= 0;
		#local R_Ten			= 0.01 / N;
		#local R_Hen			= 0.01 / N;
		#include "sphere.inc"
		#local RibTexture		= texture {pigment {gamma_color_adjust(<1,1,1>)}}
		#local PaneTexture		= texture{T_Glass3}
		#local DirtTexture		= texture
		{
			pigment
			{
				wrinkles
				color_map
				{
					[0 gamma_color_adjust(1/4*<1,1,1>)]
					[1 gamma_color_adjust(0/4*<1,1,1>)]
				}
			}
		}
		#local dome_object = union
		{
			object {Ten				texture {RibTexture}}
			object {Hen				texture {RibTexture}}
			object {Men				texture {PaneTexture}}
			cylinder {-y/16,0,1		texture {RibTexture}}
			cylinder {0,+y/128,1	texture {DirtTexture}}
			union
			{
				PlantPatch()
				scale	1/2 * 0.9
				scale	y * 2
				rotate	y * rand(Seed) * 360
			}
		}

// ----------------------------------------

object
{
	dome_object
	scale dome_radius
}
