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
	direction 1*z
	right     x*image_width/image_height
	look_at   <0.0, 0.0, 0.0>
	scale 256
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
/*
light_source
{
	<0, 0, 0>            // light's position (translated below)
	color rgb <1, 1, 1>  // light's color
	translate <-30, 30, -30>
}
*/
// ----------------------------------------

#declare LampsNumber = 12;
#declare LampLength = 400;
#declare LampColor = <1.303795,1.164882,0.971169>;
#declare MinorRadius = 2;
#declare MajorRadius = MinorRadius + 6;
#declare BoundRadius = MinorRadius + MajorRadius;
#declare Frequency = pi/MinorRadius;
#declare LCorner = <-BoundRadius, -LampLength/2, -BoundRadius>;
#declare RCorner = <+BoundRadius, +LampLength/2, +BoundRadius>;
#declare LampFunction = function {f_helix1(x,y,z, 1, Frequency, MinorRadius, MajorRadius, 1, 1, 0)}
#declare LampDensity = function {max(0, LampFunction(x,y,z))}
#declare LampMaterial = material
{
	texture
	{
		pigment {color rgb LampColor filter 1}
//		finish
//		{
//			ambient		rgb <0,0,0>
//			diffuse		0.6
//			emission	rgb <0,0,0>
//			phong		0.3
//		}
	}
	interior
	{
		ior 1
		media
		{
			method       3
			samples      500,500
			confidence   0.9
			variance     0.0078125
			jitter       0
			aa_level     4
			aa_threshold 0.1
			emission     rgb LampColor/LampsNumber
			density
			{
				function {LampDensity(x,y,z)}
				color_map
				{
					[0.00 color rgb 1]
					[1.00 color rgb 0]
				}
			}
		}
	}
}


#declare LampBulb = isosurface
{
	function {LampFunction(x,y,z)}
		//P0= number of helixes
		//P1= frequency
		//P2= minor radius
		//P3= major radius
		//P4= Y scale cross section
		//P5= cross section
		//P6= cross section rotation (¡)
		//P0 is set to 1 to get only a single helix. Non integer may cause unexpected results. (not used if f_helix2)
		//P1, P2 and P3 are renamed to reflect their functions.
		//P4 elongate the section along the Y axis. Set to 1 to leave the shape unchanged. (not used if f_helix2)
		//P5 is set to 1 whitch correspond to a circular section.
		//0 = square section.
		//1 = circular section
		//2 = losange section (I don't get it that a square rotated 45° could be called "diamond")
		//>2 = concave losange section, may become degenarate if larger than 3.
		//For a circular section, P6 have no effect. It rotate the section shape when it's not circular.
	contained_by {box {LCorner, RCorner}}
	max_gradient 1.5
	material {LampMaterial}
	hollow
}

light_source
{
	0, LampColor
	area_light
	+y * LampLength, +x, LampsNumber, 1
	looks_like {LampBulb}
}

//object {LampBulb}
