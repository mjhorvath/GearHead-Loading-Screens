// Persistence of Vision Ray Tracer Scene Description File
// File: ?.pov
// Vers: 3.6
// Desc: Basic Scene Example
// Date: mm/dd/yy
// Auth: ?
//

#version 3.6;

#include "colors.inc"

global_settings
{
	assumed_gamma 1.0
}

// ----------------------------------------

camera
{
	location	<0.0, 0.5, -4.0>
	direction	1.5*z
	right		x*image_width/image_height
	look_at		<0.0, 0.0,  0.0>
	scale		2
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
	<0, 0, 0>			// light's position (translated below)
	color rgb	<1, 1, 1>	// light's color
	translate	<-30, 30, -30>
}

// ----------------------------------------

plane
{
	y, -1
//	pigment {color rgb <0.7,0.5,0.3>}
	pigment
	{
		image_map {png "olivepink_marble.png"}
		rotate x * 90
	}
}

#local OutRad	= 2.7;
#local InnRad	= 2.0;
#local DifRad	= OutRad - InnRad;
/*
difference
{
	sphere	{0, +OutRad}
	sphere	{0, +InnRad}
	box	{0, -9.0}
	texture
	{
		pigment
		{
			onion
			color_map
			{
				[0 color rgb 0]
				[1 color rgb 1]
			}
			phase -mod(OutRad,DifRad) / DifRad
			scale DifRad
		}
		finish {ambient 1/2}
	}
}
*/
sphere
{
	0,2
	pigment
	{
//		hexagon
		image_map {png "olivepink_marble.png"}
//		rotate x * 90
//		scale <pi/2,pi/4,1>
		warp
		{
			spherical
			orientation z
		}
	}
	normal
	{
		wrinkles
		warp
		{
			spherical
			orientation y
		}
		scale 10
	}
}
