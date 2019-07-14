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
	location	z * -3
	direction	z * +3
	up		y * 2
	right		x * 2 * image_width/image_height
	scale		2 * BigScale
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
	<0,0,0,>,		// light's position (translated below)
	<1,1,1,>		// light's color
//	parallel
//	translate	<-30,+30,-30,>
	translate	<+00,+00,-30,>
	scale BigScale
}

// ----------------------------------------

plane
{
	y, -1
	pigment {color rgb x}
	scale BigScale
}


#local CenterX = +0;	// (a)
#local CenterY = -1;	// (a)
#local CenterZ = +0;	// (a)
#local Radius = log(vlength(<CenterX,CenterY,CenterZ,>)+1) / log(2);	// (b)
#local Temp_fnc1 = function
{
	1 - min(1, sqrt(x*x + y*y + z*z)/Radius)	// (c)
}
#local Temp_fnc3 = function
{
	Temp_fnc1(x-CenterX,y-CenterY,z-CenterZ)	// (d)
}

box
{
	<-BigScale,-BigScale,0,>, +BigScale
	texture
	{
		pigment
		{
			function {Temp_fnc3(x,y,z)}
			pigment_map
			{
				[0 color rgb 0]
				[1 color rgb 1]
			}
			scale BigScale
		}
	}
}