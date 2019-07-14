// Desc: GearHead models with a ruled background
// Auth: Michael Horvath
// Home Page: http://www.geocities.com/Area51/Quadrant/3864/gearhead.htm
// This file is licensed under the terms of the CC-LGPL.
// Dependencies:
// 1. "HIROSHT.TTF" by Jonathan Smith
// 2. "PLANK___.TTF" by Mads Rydahl
// +KFI0 +KFF10 +KC
// +k0.5

#version 3.6

#include "colors.inc"
#include "metals.inc"
#include "glass.inc"
#include "transforms.inc"
#include "gh_textures.inc"

#declare Included =	1;
#declare NoWeapons =	1;
#declare Width =	96;
#declare Subdivision =	0;
#declare Scale_LDraw =	1;
#declare MechaNum =	frame_number;
#declare RotateY =	0;
#declare Mecha_Size =	1;
#declare Seed =		seed(8829464);
#declare NoColors =	1;
#declare MTX = texture { pigment { color rgb <rand(Seed),rand(Seed),rand(Seed)> } finish { F_MetalA } }
#declare CTX = texture { pigment { color rgb <rand(Seed),rand(Seed),rand(Seed)> } finish { F_MetalA } }
#declare HTX = texture { pigment { color rgb <rand(Seed),rand(Seed),rand(Seed)> } finish { F_MetalA } }


//------------------------------------------------------------------------------

#switch (MechaNum)
	#case (0)
		#include "btr_maanji.pov"
		#local Mecha_Name = "Maanji";
		#local Mecha_Object = object
		{
			object01
			matrix		<1.000000, 0.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 0.000000>
			translate	<0.000000, 0.000000, 0.000000>
			scale		<1.000000, 1.000000, 1.000000>
			translate	+y * (6.4 - 10 - 2/3)
			scale		1/2
		}
	#break
	#case (1)
		#include "btr_radcliff.pov"
		#local Mecha_Name = "Radcliff";
		#local Mecha_Object = object
		{
			object01
			matrix		<-0.000009, 0.000000, -1.000009, 0.000000, 1.000000, 0.000000, 1.000009, 0.000000, -0.000009, 0.000000, 0.000000, 0.000000>
			translate	<0.000000, 0.000000, 0.000000>
			scale		<1.000000, 1.000000, 1.000000>
			scale		1/2
			rotate		-y * 90
		}
	#break
	#case (2)
		#include "btr_vadel.pov"
		#local Mecha_Name = "Vadel";
		#local Mecha_Object = object
		{
			object01
			matrix		<0.707112, 0.000000, -0.707101, 0.000000, 1.000000, 0.000000, 0.707101, 0.000000, 0.707112, 0.000000, 0.000000, 0.000000>
			translate	<0.000000, 0.000000, 0.000000>
			scale		<1.000000, 1.000000, 1.000000>
			scale		3/4
			rotate		-y * 45
		}
	#break
	#case (3)
		#include "btr_condor.pov"
		#local Mecha_Name = "Condor";
		#local Mecha_Object = object
		{
			Condor__e_dot_mpd #if (version >= 3.1) material #else texture #end { Color7 }
			scale		1/10
			//scale		1/2	// ideal scale
			rotate		+x * 180
		}
	#break
	#case (4)
		#include "btr_jos.pov"
		#local Mecha_Name = "Jos";
		#local Mecha_Object = object
		{
			object01
			matrix		<1.000000, 0.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 0.000000>
			translate	<0.000000, 0.000000, 0.000000>
			scale		<1.000000, 1.000000, 1.000000>
			scale		1/2
		}
	#break
	#case (5)
		#include "btr_ovaknight.pov"
		#local Mecha_Size = 1.25;
		#local Mecha_Name = "Ovaknight";
		#local Mecha_Object = object
		{
			object01
			matrix		<0.707112, 0.000000, -0.707101, 0.000000, 1.000000, 0.000000, 0.707101, 0.000000, 0.707112, 0.000000, 0.000000, 0.000000>
			translate	<0.000000, 0.000000, 0.000000>
			scale		<1.000000, 1.000000, 1.000000>
			scale		3/4
			rotate		-y * 45
		}
	#break
	#case (6)
		// Assembled object that is contained in ara_kojedo_POV_geom.inc
		#include "ara_kojedo.pov"
		#local Mecha_Name = "Kojedo";
		#local Mecha_Object = object
		{
			ara_kojedo_
			translate	<18.42348,0,-364.0902> * -1
			scale		1/2
			// edit below
			scale		1/4
		}
	#break
	#case (7)
		#include "ghu_doombuggy.pov"
		#declare Mecha_Size = 0.5;
		#declare Mecha_Name = "Doombuggy";
		#declare Mecha_Object = object
		{
			APC
			texture {ACP_Texture}
			scale		1/2
			rotate		+y * 90
			rotate		+y * 45
		}
	#break
	#case (8)
		#include "ghu_renegade.pov"
		#declare Mecha_Size = 0.5;
		#declare Mecha_Name = "Renegade";
		#declare Mecha_Object = object
		{
			RedrockRacer__b_dot_mpd #if (version >= 3.1) material #else texture #end { Color7 }
			scale		1/10
			scale		1/2
			rotate		+x * 180
			rotate		+y * 45
		}
	#break
	#case (9)
		#include "gca_rover.pov"
		#declare Mecha_Size = 0.5;
		#declare Mecha_Name = "Rover";
		#declare Mecha_Object = object
		{
			BUGGY__b_dot_mpd #if (version >= 3.1) material #else texture #end { Color7 }
			scale		1/10
			scale		1/2
			rotate		+x * 180
			rotate		+y * 45
		}
	#break
	#case (10)
		#include "btr_trailblazer.pov"
		#declare Mecha_Name = "Trailblazer";
		#declare Mecha_Object = object
		{
			object01
			matrix		<0.707112, 0.000000, -0.707101, 0.000000, 1.000000, 0.000000, 0.707101, 0.000000, 0.707112, 0.000000, 0.000000, 0.000000>
			translate	<0.000000, 0.000000, 0.000000>
			scale		<1.000000, 1.000000, 1.000000>
			rotate		y * -45
		}
	#break
#end

#include "cha_m_citizen.pov"
object
{
	object01
	matrix		<0.707112, 0.000000, -0.707101, 0.000000, 1.000000, 0.000000, 0.707101, 0.000000, 0.707112, 0.000000, 0.000000, 0.000000>
	translate	<0.000000, 0.000000, 0.000000>
	scale		<1.000000, 1.000000, 1.000000>
	scale		1/16
	scale		Scale_LDraw
	rotate		-y * 45
	rotate		+y * RotateY
	translate	+x * Mecha_Size * Width / 3
	translate	+z * Mecha_Size * Width / 2
}


//------------------------------------------------------------------------------

#local iCount = 0;
#if (Mecha_Size = 1/2)
	#local iMax = 08;
#end
#if (Mecha_Size = 1/1)
	#local iMax = 17;
#end
#if (Mecha_Size = 5/4)
	#local iMax = 22;
#end
#while (iCount < iMax)
	text
	{
		ttf "arial.ttf" str(iCount, 0, 0) 0.1, 0
		rotate		+y * 180
		scale		+4
		translate	+y * (iCount * 4 + 0.5)
		translate	-z * Mecha_Size * Width / 2
		translate	+x * Mecha_Size * (Width / 2 - 0.5)
		pigment		{color rgb 1/2}
		no_shadow
		no_reflection
	}
	#local iCount = iCount + 1;
#end

#declare H1_Object = text
{
	ttf "PLANK___.TTF" "GearHead 2" 0.1, 0
	rotate		+y * 180
	translate	-y * 1/2
	scale		+8 * Mecha_Size
	translate	-z * Mecha_Size * Width / 2
	translate	+y * Mecha_Size * 16 * 4
	no_shadow
	no_reflection
}

#declare H2_Object = text
{
	ttf "PLANK___.TTF" "Just a minute..." 0.1, 0
	rotate		+y * 180
	translate	-y * 1/2
	scale		+4 * Mecha_Size
	translate	-z * Mecha_Size * Width / 2
	translate	+y * Mecha_Size * 14.5 * 4
	no_shadow
	no_reflection
}

object
{
	H1_Object
	Center_Trans(H1_Object, x)
}

object
{
	H2_Object
}

object
{
	Mecha_Object
	scale	Scale_LDraw
	rotate	+y * RotateY
}

#declare Label_Object = text
{
	ttf "HIROSHT.TTF" Mecha_Name 0.1, 0
	rotate		+y * 180
	translate	-y * 1/2
	scale		+4 * Mecha_Size
	no_shadow
	no_reflection
}

object
{
	Label_Object
	Center_Trans(Label_Object, x)
	translate	-x * Mecha_Size * Width / 4
	translate	+z * Mecha_Size * Width / 2
	translate	+y * Mecha_Size * (0.5 * 4 + 0.5)
}

//------------------------------------------------------------------------------

camera
{
	#local Camera_Distance = Mecha_Size * Width;
	#local Camera_Aspect = image_height/image_width;
	orthographic
	up		+y * Camera_Distance * Camera_Aspect
	right		-x * Camera_Distance
	location	+z * Camera_Distance
	direction	-z
	translate	+y * Camera_Distance * Camera_Aspect / 2
	translate	-y * Mecha_Size * 0.5 * 4
}

background	{color rgb 1/2}

light_source	{<+3000, +6000, +7000,> rgb 1 parallel}

plane
{
	z, -Width * Mecha_Size
	texture
	{
		pigment
		{
			gradient y
			color_map
			{
				[0.00 color rgb 1/2]
				[0.05 * Mecha_Size color rgb 1/2]
				[0.05 * Mecha_Size color rgb 1/1]
				[1.00 color rgb 1/1]
			}
			scale 4
		}
	}
}
