// Persistence of Vision Ray Tracer Scene Description File
// File: ?.pov
// Vers: 3.6
// Desc: Basic Scene Example
// Date: mm/dd/yy
// Auth: ?
//

#version 3.6;

#include "stdinc.inc"

global_settings
{
	assumed_gamma 1.0
}

#local BigScale = 22000;

// ----------------------------------------

camera
{
	location	z * -3
	direction	z * +3
	up		y * 2
	right		x * 2 * image_width/image_height
	scale		2 * BigScale
//	rotate		x * 30
//	rotate		y * 45
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
//	translate	<-30, 30, -30>
	translate	<0, 0, -30>
	scale BigScale
}

// ----------------------------------------

plane
{
	y, -1
	pigment {color rgb <0.7,0.5,0.3>}
	scale BigScale
}

#local OutRad =	BigScale;
#local InnRad =	BigScale * 10/13;
#local DifRad =	OutRad - InnRad;
#local DivRad =	OutRad / DifRad;
#local MulSgn = -1;
#declare Seed =		seed(22231);

difference
{
	box {-BigScale, +BigScale}
	plane {z, 0}
	texture
	{
		pigment
		{
			planar
			color_map
			{
				[099/100 rgb 0]
				[100/100 rgb 1]
			}

			warp
			{
				black_hole	0, 1
				inverse
				falloff		1
				strength	4
			}

			warp
			{
				turbulence <1/4,1/4,1/4,>
			}

			scale BigScale
		}
	}
}