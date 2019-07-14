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

#local BigScale = 1000;

// ----------------------------------------

camera
{
	location	z * -4
	direction	z * +4
	up		y * 2
	right		x * 2 * image_width/image_height
	scale		BigScale
//	rotate		x * 15
//	rotate		y * 30
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
	<0, 0, 0>,			// light's position (translated below)
	<1, 1, 1>		// light's color
//	parallel
//	translate	<-30, 30, -30>
	translate	<0, 0, -30>
	scale BigScale
}

// ----------------------------------------

plane
{
	y, -1
	pigment {color rgb x}
	scale BigScale
}


#local Temp_fnc1 = function
{
	sqrt(x*x + y*y + z*z)
}
#local Temp_fnc2 = function
{
	max(0,1 - min(1, sqrt(x*x + y*y + z*z)))
}
#local Temp_fnc3 = function
{
	log(sqrt(x*x + y*y + z*z)) / log(2)/1
}
#local Temp_fnc4 = function
{
	Temp_fnc2(x/200+2,y/200,z/200)
	*
	Temp_fnc3(x/200-2,y/200,z/200)
}
#local Temp_fnc5 = function
{
	Temp_fnc1(x/100+1,y/100,z/100)
	+
	Temp_fnc2(x/100-1,y/100,z/100)
}

box
{
	<-BigScale,-BigScale,0,>, +BigScale
	texture
	{
		pigment
		{
			function {Temp_fnc5(x,y,z)}
			pigment_map
			{
				[0 color rgb 0]
				[1 color rgb 1]
			}
		}
	}
}