// Authors: Michael Horvath
// Website: http://isometricland.net
// Updated: 2017-04-12
// This file is licensed under the terms of the CC-LGPL.
// http://www.gnu.org/licenses/lgpl-2.1.html


#declare something = 0;


#include "Transforms.inc"
// scale before translate, or both?
#switch (Camera_Mode)
	// oblique
	#case (1)
		#declare Camera_Area		= Tiles * 2 * 64;
		#declare Camera_Aspect		= 1/Camera_Aspect;
		#declare Camera_Distance	= Camera_Diagonal * Width * Tiles * Camera_Scale;
		#declare Camera_Skewed		= sin(pi/4);
		#declare Camera_Up			= -x * Camera_Area;
		#declare Camera_Right		= +z * Camera_Area * Camera_Aspect;
		#declare Camera_Location	= vnormalize(<Camera_Skewed, 1, Camera_Skewed>) * Camera_Distance;
		#declare Camera_Direction	= -Camera_Location;
		#declare Camera_Location	= Camera_Location + -x * block_dist_x/2;
		#declare Camera_LookAt		= Camera_Location + Camera_Direction;
		#declare Camera_Transform	= transform
		{
			translate	Camera_Translate
			scale		Camera_Scale
		}
		camera
		{
			orthographic
			up			Camera_Up
			right		Camera_Right
			location	Camera_Location
			direction	Camera_Direction
			transform {Camera_Transform}
		}
		#declare Camera_Location	= vtransform(Camera_Location,Camera_Transform);
		#declare Camera_LookAt		= vtransform(Camera_LookAt,Camera_Transform);
	#break
	// perspective (new)
	#case (2)
		#declare Camera_Up			= +y * Camera_Diagonal * Width * Tiles * 2 * Camera_Aspect;
		#declare Camera_Right		= +x * Camera_Diagonal * Width * Tiles * 2;
		#declare Camera_Location	= -z * Camera_Distance;
		#declare Camera_Direction	= +z * Camera_Distance;
		#declare Camera_LookAt		= Camera_Location + Camera_Direction;
		#declare Camera_Rotate		= <Camera_Horizontal,Camera_Vertical,0,>;
		#declare Camera_Transform	= transform
		{
			rotate		Camera_Rotate
			scale		Camera_Scale
			#switch (Camera_Eye)
				// do nothing
				#case (-1)
				#break
				// left eye
				#case (0)
					rotate +y * 2.5
				#break
				// right eye
				#case (1)
					rotate -y * 2.5
				#break
			#end
			translate	Camera_Translate
		}
		camera
		{
			perspective
			//orthographic
			up			Camera_Up
			right		Camera_Right
			location	Camera_Location
			direction	Camera_Direction
			transform {Camera_Transform}
		}
		#declare Camera_Location	= vtransform(Camera_Location,Camera_Transform);
		#declare Camera_LookAt		= vtransform(Camera_LookAt,Camera_Transform);
	#break
	// orthographic (new)
	#case (3)
		#declare Camera_Up			= +y * Camera_Diagonal * Width * Tiles * 2 * Camera_Aspect;
		#declare Camera_Right		= +x * Camera_Diagonal * Width * Tiles * 2;
		#declare Camera_Location	= -z * Camera_Distance;
		#declare Camera_Direction	= +z * Camera_Distance;
		#declare Camera_LookAt		= Camera_Location + Camera_Direction;
		#declare Camera_Rotate		= <Camera_Horizontal,Camera_Vertical,0,>;
		#declare Camera_Transform	= transform
		{
			rotate		Camera_Rotate
			scale		Camera_Scale
			translate	Camera_Translate
		}
		camera
		{
			orthographic
			up			Camera_Up
			right		Camera_Right
			location	Camera_Location
			direction	Camera_Direction
			transform {Camera_Transform}
		}
		#declare Camera_Location	= vtransform(Camera_Location,Camera_Transform);
		#declare Camera_LookAt		= vtransform(Camera_LookAt,Camera_Transform);
	#break
	// not sure...
	#case (4)
		#declare Camera_Up			= <+00.29007132383,+00.94193058802,-00.16919038339,>;
		#declare Camera_Right		= <-00.44470821789,-00.00000000114,-00.76243755686,>;
		#declare Camera_Location	= <-15.70614200000,+06.48226800000,+09.16094800000,>;
		#declare Camera_Direction	= <+00.81364160776,-00.33580762148,-00.47457408905,>;
		#declare Camera_LookAt		= Camera_Location + Camera_Direction;
		#declare Camera_Angle		= 50.000;
		#declare Camera_Transform	= transform
		{
			translate	Camera_Translate
			scale		Camera_Scale
		}
		camera
		{
			angle		Camera_Angle
			up			Camera_Up
			right		Camera_Right
			location	Camera_Location
			direction	Camera_Direction
			transform {Camera_Transform}
		}
		#declare Camera_Location	= vtransform(Camera_Location,Camera_Transform);
		#declare Camera_LookAt		= vtransform(Camera_LookAt,Camera_Transform);
	#break
	// cube map
	#case (5)
		#declare Camera_Up			= +y;
		#declare Camera_Right		= +x;
		#declare Camera_Location	= 0;
		#declare Camera_Direction	= +z/2;
		#declare Camera_LookAt		= Camera_Location + Camera_Direction;
		#ifndef (view_direction)
			#declare view_direction = frame_number;
		#end
		#switch (view_direction)
			#case (0)
				#declare Camera_Rotate	= <0,000,0,>;
			#break
			#case (1)
				#declare Camera_Rotate	= <0,090,0,>;
			#break
			#case (2)
				#declare Camera_Rotate	= <0,180,0,>;
			#break
			#case (3)
				#declare Camera_Rotate	= <0,270,0,>;
			#break
			#case (4)
				#declare Camera_Rotate	= <270,0,0,>;
			#break
			#case (5)
				#declare Camera_Rotate	= <090,0,0,>;
			#break
		#end
		#debug "\n"
		#debug concat("frame_number = ", str(frame_number, 0, -1), "\n")
		#debug concat("Camera_Rotate = <", vstr(3, Camera_Rotate, ",", 0, -1), ">\n")
		#debug "\n"
		#declare Camera_Transform = transform
		{
			rotate		Camera_Rotate
			translate	Camera_Location
			translate	Camera_Translate
			scale		Camera_Scale
			///////////////////////////
			rotate +z * city_rotate
		}
		camera
		{
			up			Camera_Up
			right		Camera_Right
			location	0
			direction	Camera_Direction
			transform {Camera_Transform}
		}
		#declare Camera_Location	= vtransform(Camera_Location,Camera_Transform);
		#declare Camera_LookAt		= vtransform(Camera_LookAt,Camera_Transform);
	#break
	// spherical
	#case (6)
		#declare Camera_Up			= +y;
		#declare Camera_Right		= +x;
		#declare Camera_Location	= +y*400;
		#declare Camera_Direction	= +z;
		#declare Camera_LookAt		= Camera_Location + Camera_Direction;
		#declare Camera_Transform	= transform
		{
			translate	Camera_Translate
			scale		Camera_Scale
		}
		camera
		{
			spherical
			angle		360 180
			up			Camera_Up
			right		Camera_Right
			location	Camera_Location
			look_at		Camera_LookAt
			transform {Camera_Transform}
		}
		#declare Camera_Location	= vtransform(Camera_Location,Camera_Transform);
		#declare Camera_LookAt		= vtransform(Camera_LookAt,Camera_Transform);
	#break
	// orthographic (overhead)
	#case (7)
		#declare Camera_Up			= +z * Width * 32 * Camera_Aspect;
		#declare Camera_Right		= +x * Width * 32;
		#declare Camera_Location	= +y * Camera_Distance * 2;
		#declare Camera_Direction	= -y * Camera_Distance * 2;
		#declare Camera_LookAt		= Camera_Location + Camera_Direction;
		#declare Camera_Transform	= transform
		{
			translate	Camera_Translate
			scale		Camera_Scale
		}
		camera
		{
			orthographic
			up			Camera_Up
			right		Camera_Right
			location	Camera_Location
			direction	Camera_Direction
			transform {Camera_Transform}
		}
		#declare Camera_Location	= vtransform(Camera_Location,Camera_Transform);
		#declare Camera_LookAt		= vtransform(Camera_LookAt,Camera_Transform);
	#break
	// orthographic (overhead, angled)
	#case (8)
		#declare Camera_Up			= +z * Camera_Diagonal * Width * Tiles * Camera_Aspect;
		#declare Camera_Right		= +x * Camera_Diagonal * Width * Tiles;
		#declare Camera_Location	= +y * Camera_Distance * Camera_Scale;
		#declare Camera_Direction	= -Camera_Location;
		#declare Camera_LookAt		= Camera_Location + Camera_Direction;
		#declare Camera_Rotate		= <+60,-45,+00,>;		//<+60,-45,+00,>
		#declare Camera_Transform	= transform
		{
			rotate		Camera_Rotate
			translate	Camera_Translate
			scale		Camera_Scale
		}
		camera
		{
//			orthographic
			up			Camera_Up
			right		Camera_Right
			location	Camera_Location
			direction	Camera_Direction
			transform {Camera_Transform}
		}
		#declare Camera_Location	= vtransform(Camera_Location,Camera_Transform);
		#declare Camera_LookAt		= vtransform(Camera_LookAt,Camera_Transform);
	#break
	// perspective (inside spinner habitat)
	#case (9)
		#declare Camera_Up			= +y * 420;
		#declare Camera_Right		= +x * 420 * image_width/image_height;
		#declare Camera_Direction	= +z * 420;
		#declare Camera_Location	= <0,-140,-210>;
		#declare Camera_LookAt		= Camera_Location + Camera_Direction;
		#declare Camera_Rotate		= <0,0,0>;
		#declare Camera_Transform	= transform
		{
			rotate		Camera_Rotate
			translate	Camera_Location
			rotate		+z * (sml_block_angle/2)
			rotate		+z * (street_angle/2)
			rotate		-z * (city_rotate)
			translate	+z * (hab_section_offset)
		}
		camera
		{
			perspective
			up			Camera_Up
			right		Camera_Right
			direction	Camera_Direction
			location	0
			transform {Camera_Transform}
		}
		#declare Camera_Location	= vtransform(Camera_Location,Camera_Transform);
		#declare Camera_LookAt		= vtransform(Camera_LookAt,Camera_Transform);
	#break
	// cube map (inside spinner habitat, render using square aspect ratio only!)
	#case (10)
//		#declare Camera_Up			= +y * 420;
//		#declare Camera_Right		= +x * 420;
//		#declare Camera_Direction	= +z * 210;
//		#declare Camera_Location	= <0,-140,-210>;
		#declare Camera_Up			= +y*2;
		#declare Camera_Right		= +x*2;
		#declare Camera_Direction	= +z*1;
		#declare Camera_Location	= <0,-city_radius*2/3,-city_length*2/4>;
		#declare Camera_LookAt		= Camera_Location + Camera_Direction;
		#switch (Camera_CubeMap)
			#case (0)
				#declare Camera_Rotate	= <0,000,0,>;
			#break
			#case (1)
				#declare Camera_Rotate	= <0,090,0,>;
			#break
			#case (2)
				#declare Camera_Rotate	= <0,180,0,>;
			#break
			#case (3)
				#declare Camera_Rotate	= <0,270,0,>;
			#break
			#case (4)
				#declare Camera_Rotate	= <270,0,0,>;
			#break
			#case (5)
				#declare Camera_Rotate	= <090,0,0,>;
			#break
		#end
		#declare Camera_Transform = transform
		{
			rotate		Camera_Rotate
			translate	Camera_Location
			rotate		+z * (hab_cap_nudge_angle)
			rotate		+z * (city_rotate)
			translate	+z * (hab_section_offset)
		}
		camera
		{
			perspective
			//orthographic
			up			Camera_Up
			right		Camera_Right
			direction	Camera_Direction
			location	0
			transform {Camera_Transform}
		}
		#declare Camera_Location	= vtransform(Camera_Location,Camera_Transform);
		#declare Camera_LookAt		= vtransform(Camera_LookAt,Camera_Transform);
	#break
	// spherical (inside spinner habitat, render using 2:1 aspect ratio)
	#case (11)
		#declare Camera_Up			= +y * 420;
		#declare Camera_Right		= +x * 420;
		#declare Camera_Direction	= +z * 210;
		#declare Camera_Location	= <0,-140,-210>;
		#declare Camera_LookAt		= Camera_Location + Camera_Direction;
		#declare Camera_Transform	= transform
		{
			translate	Camera_Location
			rotate		+z * (sml_block_angle/2)
			rotate		+z * (street_angle/2)
			rotate		-z * (city_rotate)
			translate	+z * (hab_section_offset)
		}
		camera
		{
			spherical
			angle		360 180
			up			Camera_Up
			right		Camera_Right
			direction	Camera_Direction
			location	0
			transform {Camera_Transform}
		}
		#declare Camera_Location	= vtransform(Camera_Location,Camera_Transform);
		#declare Camera_LookAt		= vtransform(Camera_LookAt,Camera_Transform);
	#break
	// orthographic (overhead, above spinner habitat, square aspect ratio)
	#case (12)
		#declare Camera_Up			= +y * 1000;
		#declare Camera_Right		= +x * 1000;
		#declare Camera_Direction	= +z * 500;
		#declare Camera_Location	= -z * 500;
		#declare Camera_LookAt		= Camera_Location + Camera_Direction;
		#declare Camera_Transform	= transform
		{
			rotate		+x * 90
//			rotate		+y * 90
			scale		3
		}
		camera
		{
			orthographic
			up			Camera_Up
			right		Camera_Right
			location	Camera_Location
			direction	Camera_Direction
			transform {Camera_Transform}
		}
		#declare Camera_Location	= vtransform(Camera_Location,Camera_Transform);
		#declare Camera_LookAt		= vtransform(Camera_LookAt,Camera_Transform);
	#break
	// cube map (inside spinner habitat, dead center, render using square aspect ratio only!)
	#case (13)
//		#declare Camera_Up			= +y * 420;
//		#declare Camera_Right		= +x * 420;
//		#declare Camera_Direction	= +z * 210;
//		#declare Camera_Location	= <0,0,-city_length/2>;
		#declare Camera_Up			= +y * city_length;
		#declare Camera_Right		= +x * city_length;
		#declare Camera_Direction	= +z * city_length/2;
		#declare Camera_Location	= <0,0,0>;
		#declare Camera_LookAt		= Camera_Location + Camera_Direction;
		#switch (Camera_CubeMap)
			#case (0)
				#declare Camera_Rotate	= <0,000,0,>;
			#break
			#case (1)
				#declare Camera_Rotate	= <0,090,0,>;
			#break
			#case (2)
				#declare Camera_Rotate	= <0,180,0,>;
			#break
			#case (3)
				#declare Camera_Rotate	= <0,270,0,>;
			#break
			#case (4)
				#declare Camera_Rotate	= <270,0,0,>;
			#break
			#case (5)
				#declare Camera_Rotate	= <090,0,0,>;
			#break
		#end
		#declare Camera_Transform = transform
		{
			rotate		Camera_Rotate
			translate	Camera_Location
			rotate		+z * (hab_cap_nudge_angle)
			rotate		+z * (city_rotate)
			translate	+z * (hab_section_offset)
		}
		camera
		{
			perspective
			up			Camera_Up
			right		Camera_Right
			direction	Camera_Direction
			location	0
			transform {Camera_Transform}
		}
		#declare Camera_Location	= vtransform(Camera_Location,Camera_Transform);
		#declare Camera_LookAt		= vtransform(Camera_LookAt,Camera_Transform);
	#break
#end
