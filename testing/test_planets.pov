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
#include "shapes.inc"
#include "shapesq.inc"

#declare city_radius = 10;
#declare city_circum = pi * city_radius * 2;
#declare city_use_mesh = 1;
#include "CG_PRIMITIVES.INC"

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
	scale		32
//	rotate		x * 30
//	rotate		y * 30
//	translate	y * -8
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

cylinder
{
	-x*256,+x*256, 1/2
	pigment {color rgb x}
//	translate -y * city_radius
}
cylinder
{
	-y*256,+y*256, 1/2
	pigment {color rgb y}
//	translate -y * city_radius
}
cylinder
{
	-z*256,+z*256, 1/2
	pigment {color rgb z}
//	translate -y * city_radius
}
plane
{
	y, 0
	pigment {color rgbt <1,0,1,3/4>}
}


// ----------------------------------------

sphere
{
	0,8
	texture
	{
		pigment
		{
			image_map
			{
				png		"EarthMapAtmos_2500x1250.png"
				map_type	1
			}
		}
	}
	texture
	{
		pigment
		{
			image_map
			{
				png		"EarthClouds_2500x1250.png"
				map_type	1
			}
		}
	}
	texture
	{
		pigment
		{
			image_map
			{
				png		"EarthNight_2500x1250.png"
				map_type	1
			}
		}
		finish {ambient 1}
	}
}