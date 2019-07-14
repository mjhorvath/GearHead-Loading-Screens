#include "math.inc"

#declare Camera_Mode		= 2;				// 0 to 8; 0 = orthographic; 1 = oblique; 2 = perspective
#declare Camera_Diagonal	= cosd(45);
#declare Camera_Vertical	= 0;				//22.5;
#declare Camera_Horizontal	= 0;				//30;
#declare Camera_Scale		= 1;
#declare Camera_Aspect		= image_height/image_width;
#declare Camera_Distance	= -16;
#declare Camera_Translate	= <0,0,0,>;			//<0,0,-city_size_total.y,>


//------------------------------------------------------------------------------Global settings

//default {finish {ambient 0 diffuse 1}}
//default {finish {ambient 0.1 diffuse 0.6}}
//default {finish {ambient 0.4 diffuse 0.7}}
//#default {finish {ambient 0.1 diffuse 0.9}}
/*
global_settings
{
	ambient_light	0
	radiosity
	{
		always_sample	off
		brightness	0.5
		recursion_limit	1
		count		100
		error_bound	0.5
	}
//	max_trace_level 2
}
*/

//------------------------------------------------------------------------------Camera

#declare Camera_Up		= +y * Camera_Diagonal * 16 * Camera_Aspect;
#declare Camera_Right		= +x * Camera_Diagonal * 16;
#declare Camera_Location	= -z * Camera_Distance;
#declare Camera_Direction	= +z;
#declare Camera_LookAt		= Camera_Location + Camera_Direction;
#declare Camera_Rotate		= <Camera_Horizontal,Camera_Vertical,0,>;
camera
{
//	orthographic
	up		Camera_Up
	right		Camera_Right
	location	Camera_Location
	direction	Camera_Direction
	rotate		Camera_Rotate
	translate	Camera_Translate
//	scale		4
}
#declare Camera_Location	= Camera_Translate + vrotate(Camera_Location,Camera_Rotate);
#declare Camera_LookAt		= Camera_Translate + vrotate(Camera_LookAt,Camera_Rotate);


//------------------------------------------------------------------------------Lights
/*
light_source
{
	<-5000, 14000, -15000>/10
	color rgb <1.0, 0.9, 0.78>*2.3/2.3
//	media_interaction off
//	media_interaction on
}
*/

//------------------------------------------------------------------------------Sky
/*
sphere
{
	0, 100000
	hollow
	pigment
	{
		color rgb < 0.5, 0.6, 1.0 >/10
	}
}
*/
fog
{
	fog_type   2
	distance   5
	color      1
	fog_offset 0.1
	fog_alt    2.0
	turbulence 0.8
}

//------------------------------------------------------------------------------CSG

plane
{
	y, -16
	pigment {color rgb x}
}

sphere
{
	0, 4
	translate z * 64
}

object
{
	cylinder
	{
		y * -128, y * +128, 8
		hollow
		pigment {rgbt 1}
		interior
		{
			media
			{
				emission  1/2
				density
				{
					cylindrical
					color_map
					{
						[0 rgb 0]
						[1 rgb 1]
					}
					scale	8
//					rotate	x * 90
				}
			}
		}
		translate z * 32
	}
}

difference
{
	cylinder
	{
		-z, +z, 16
	}
	cylinder
	{
		-z*2, +z*2, 12
	}
	translate z * 16
}
