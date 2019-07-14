// Persistence of Vision Ray Tracer Scene Description File
// File: ?.pov
// Vers: 3.6
// Desc: Basic Scene Example
// Date: mm/dd/yy
// Auth: ?
//

#version 3.7;

#include "colors.inc"
#include "glass.inc"
#include "functions.inc"
#include "shapes.inc"

global_settings
{
	assumed_gamma 1.0
}

// ----------------------------------------

camera
{
	location  <0, 0, -1>
	direction 1.5*z
	right     x*image_width/image_height
	look_at   <0.0, 0.0,  0.0>
	rotate x * 90
//	rotate y * 45
	scale 16
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
	color rgb <1, 1, 1>  // light's color
	translate <-30, 30, -30>
}

// ----------------------------------------

#declare test_function_1 = function (x,y,z)
{
	pow(y,2) + pow(x,2) - z
}

#declare test_function_2 = function (x,y,z)
{
	pow(z, 1/2)*10
}

#declare para_pigment = pigment
{
	function {test_function_2(x,y,z)}
	color_map
	{
		[0.00 rgb 0]
		[0.01 rgb 0]
		[0.01 rgb 1]
		[0.99 rgb 1]
		[0.99 rgb 0]
		[1.00 rgb 0]
	}
}


// ----------------------------------------

#local p_radius = 5;
intersection
{
	object
	{
		Paraboloid_Z
	}
	plane {+y, 0}
	pigment {para_pigment scale 1/4}
	scale p_radius
	translate -z * 3
}

#for (t_cnt, 0, 5, 0.1)
	#local x_new = p_radius/4 * t_cnt * 2;
	#local z_new = p_radius/4 * pow(t_cnt, 2);
	sphere
	{
		<+x_new,0,z_new>, 1/10
		pigment {color rgb x}
		translate -z * 3
	}
#end