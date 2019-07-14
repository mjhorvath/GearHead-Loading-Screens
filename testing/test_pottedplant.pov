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

// ----------------------------------------

#declare TexQual = 1;
#macro gamma_color_adjust(in_color)
	#local out_gamma = 2.2;
	#local in_color = in_color + <0,0,0,0,0>;
	<
		pow(in_color.red, out_gamma),
		pow(in_color.green, out_gamma),
		pow(in_color.blue, out_gamma),
		in_color.filter,
		in_color.transmit
	>
#end
#include "gh_deciduous_tree.inc"
union
{
	object
	{
		TREE
		scale <2,4,2>
		translate	y*1/8
	}
	difference
	{
		sphere {y*1, 8/8}
		sphere {y*1, 7/8}
		plane {-y,-1}
	}
	intersection
	{
		sphere {y*1, 7/8}
		plane {y, 7/8}
		pigment {color rgbft gamma_color_adjust(<.2,.2,.2>)}
	}
	cylinder {0, y/2, 1/8	translate <-1,0,-1>/2}
	cylinder {0, y/2, 1/8	translate <-1,0,+1>/2}
	cylinder {0, y/2, 1/8	translate <+1,0,+1>/2}
	cylinder {0, y/2, 1/8	translate <+1,0,-1>/2}
	bounded_by {cylinder {0, y*5, 2}}
	texture
	{
		pigment {rgbft gamma_color_adjust(<0,.4,0>)}
		finish {metallic}
	}
}
