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
	up		y * 3/2
	right		x * 3/2 * image_width/image_height
	scale		2 * BigScale
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

difference
{
	sphere	{0, +OutRad*4/4}
	sphere	{0, +InnRad*4/4}
	box	{0, -BigScale*2}
	texture
	{
		pigment
		{
			function
			{
				max(DivRad*2-2,min(DivRad*2-1,sqrt(x*x + y*y + z*z)))
				-
				max(DivRad*2-1,min(DivRad*2-0,sqrt(x*x + y*y + z*z)))
			}
			color_map
			{
				[0/3 color rgb x]
				[1/3 color rgb x]
				[1/3 color rgb y]
				[2/3 color rgb y]
				[2/3 color rgb z]
				[3/3 color rgb z]
			}
			scale DifRad/2
		}
	}
}
