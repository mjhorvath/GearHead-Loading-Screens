// Example of constraining media to an isosurface built on
// the helix1 function.
//
#version 3.7;
global_settings
{
	assumed_gamma 1
	ambient_light srgb <1,1,1>
}
#include "functions.inc"
#include "colors.inc"
background {color rgb 3/4}
camera
{
	perspective
	location <2.7,2.7,-4.001>*2
	sky <0,1,0>
	angle 35
	right x*(image_width/image_height)
	look_at <0,0,0>
}
light_source {<50,150,-250>, srgbft <1,1,1,0,0>}




//	P0 : Number of helixes - e.g. 2 for a double helix 
//	P1 : Period - is related to the number of turns per unit length 
//	P2 : Minor radius (major radius > minor radius) 
//	P3 : Major radius 
//	P4 : Shape parameter. If this is greater than 1 then the tube becomes fatter in the y direction 
//	P5 : Cross section type 
//	P6 : Cross section rotation angle (degrees) 
#declare F_Helix1 = function
{
	f_helix1(x,y,z,1,pi*2,0.1,0.9,1,1,0)
}
#declare FnDensity = function
{
    max(0,F_Helix1(x,y,z))
}
#declare Material0 = material
{
	texture
	{
		pigment { color srgbft <1,1,1,1,0> }
		finish
		{
			ambient srgb <0,0,0>
			diffuse 0.6
			emission srgb <0,0,0>
			phong 0.3
		}
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
			emission     rgbft <1,1,1,0,0>
			density
			{
				function { FnDensity(x,y,z) }
				color_map
				{
					[0.00 color rgb 1]
					[1.00 color rgb 0]
				}
			}
		}
	}
}
object
{
	isosurface
	{
		function { F_Helix1(x,y,z) }
		contained_by { box { <-1,-1,-1>,<1,1,1> } }
		threshold		0
		accuracy		0.001
		max_gradient	4.1
		all_intersections
	}
	material { Material0 }
	hollow
}

//---


cylinder {0,x,0.01 pigment {color rgb x}}
cylinder {0,y,0.01 pigment {color rgb y}}
cylinder {0,z,0.01 pigment {color rgb z}}