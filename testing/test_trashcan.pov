// Persistence of Vision Ray Tracer Scene Description File
// File: ?.pov
// Vers: 3.6
// Desc: Basic Scene Example
// Date: mm/dd/yy
// Auth: ?
//

#version 3.6;

#include "colors.inc"
#include "math.inc"

global_settings
{
	assumed_gamma 1.0
}
default {finish {ambient 0 diffuse 1}}

// ----------------------------------------

camera
{
	orthographic
	location	z*-12
	direction	z
	up		y
	right		x*image_width/image_height
	scale		25
	rotate		x * 30
	rotate		y * 30
}

sky_sphere
{
	pigment
	{
		gradient y
		color_map
		{
			[0.0 rgb <0.6,0.7,1.0>]
			[0.7 rgb <0.0,0.1,0.8>]
		}
	}
}
/*
light_source
{
	<0, 0, 0>            // light's position (translated below)
	color rgb <1, 1, 1>/1  // light's color
	translate <-30, 30, -30>
}

light_source
{
	<0, 0, 0>            // light's position (translated below)
	color rgb <1, 1, 1>/1  // light's color
	translate <-30, 30, +30>
}
*/
// ----------------------------------------

union
{
	difference
	{
		cone {y/2, 12/16, y*5/2, 16/16}
		cone {y/1, 11/16, y*6/2, 15/16}
	}
	cylinder {0, y*5/2, 1/8	translate <-1,0,0>}
	cylinder {0, y*5/2, 1/8	translate <+1,0,0>}
	cylinder {0, y*5/2, 1/8	translate <0,0,+1>}
	cylinder {0, y*5/2, 1/8	translate <0,0,-1>}
	pigment {color rgb y}
}
