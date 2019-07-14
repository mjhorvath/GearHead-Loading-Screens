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
	location	z * -4
	direction	z * +4
	up		y * 4
	right		x * 4 * image_width/image_height
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

#local OutRad	= 2.7;
#local InnRad	= 2.0;
#local DifRad	= OutRad - InnRad;

difference
{
	sphere	{0, +OutRad}
//	sphere	{0, +InnRad}
	box	{0, -9.0}
	scale BigScale
	texture
	{
		pigment
		{
			#local FuncBot = function {288.15 / (288.15 + -0.0065 * (f_r(x,y,z) - 0))}
			#local FuncTop = function {(9.80665 * 0.0289644) / (8.31432 * -0.0065) + 1}
			function {1.2250 * pow(FuncBot(x,y,z), FuncTop(x,y,z))}
//			#local FuncBot = function {216.65 / (216.65 + 0.001 * (f_r(x,y,z) - 20000))}
//			#local FuncTop = function {(9.80665 * 0.0289644) / (8.31432 * 0.001) + 1}
//			function {0.36391 * pow(FuncBot(x,y,z), FuncTop(x,y,z))}
//			function {f_r(x,y,z) / 8000}
			color_map
			{
				[0/3 color rgb x]
				[1/3 color rgb x]
				[1/3 color rgb y]
				[2/3 color rgb y]
				[2/3 color rgb z]
				[3/3 color rgb z]
			}
			frequency 1
//			frequency OutRad / DifRad
//			phase -mod(OutRad, DifRad) / DifRad
			scale OutRad
		}
	}
}
