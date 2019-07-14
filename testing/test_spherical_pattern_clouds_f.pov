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
	<0, 0, 0>			// light's position (translated below)
	<1, 1, 1>	// light's color
//	translate	<-30, 30, -30>
	translate	<0, 0, -30>
	scale BigScale
}

// ----------------------------------------

plane
{
	y, -1
	pigment {color rgb 3/4}
	scale BigScale
}

#local OutRad =	BigScale;
#local InnRad =	BigScale * 10/13;
#local DifRad =	OutRad - InnRad;
#local DivRad =	OutRad / DifRad;
#local MulSgn = -1;
#declare Seed =		seed(22231);


#local Temp_fnc1 = function
{
	1 - min(1, sqrt(x*x + y*y + z*z))
}
#local Temp_fnc3 = function
{
	Temp_fnc1(x,log(max(y + 1,0.000000000001)) / log(2),z)
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
/*
			#local iCount = 0;
			#while (iCount < 20)
				#local hole_coo = <rand(Seed),rand(Seed),rand(Seed),>*2-1;
				warp
				{
					black_hole	hole_coo, 1-abs(hole_coo.y)
					inverse
					falloff		1
					strength	1
				}
				#local iCount = iCount + 1;
			#end
*/
			warp
			{
				turbulence	<1/4,1/64,1/4,>
				octaves		4
				lambda		2
				omega		1/2
			}

			scale BigScale
		}
	}
}