// Caption: Several GearHead mecha lined up in front of a ruled background.
// Authors: Michael Horvath, many model designers
// Website: http://isometricland.net
// Created: ????-??-??
// Updated: 2021-03-25
// This file is licensed under the terms of the CC-LGPL.

#version 3.8;

#include "colors.inc"
#include "metals.inc"
#include "glass.inc"
#include "transforms.inc"
#include "gh_textures.inc"
#include "rand.inc"

#declare Seed		= seed(882);
#declare Included	= true;
#declare ImgScale	= 4;
#declare Meters		= 4;
#declare GridScale	= 2;
#declare NoColors	= 1;
#declare NoWeapons	= 1;
#declare YRotate	= 30;
#declare Width		= 24 * Meters;
#declare Height		= 24 * Meters;
#declare Subdivision =	0;
#declare Scale_LDraw =	1;
#declare AspectRatio = image_height / image_width;
//#declare Font1Name = "HIROSHT.TTF";		// by Jonathan Smith
//#declare Font1Name = "AwesomeSouthKorea-Lw54.ttf";
#declare Font1Name = "aAnnyeongHaseyo.ttf";
#declare Font2Name = "PLANK__.TTF";			// by Mads Rydahl
#declare Font3Name = "arial.ttf";
#declare GridColor = 5/8;
#declare FontColor = 0;
#declare BackColor = 6/8;
#declare FontSize = 2.5 * Meters;


//------------------------------------------------------------------------------

global_settings
{
	#if (1 = 1)
		ambient_light	0
		radiosity
		{
			pretrace_start	0.08
			pretrace_end	0.02
			count			20
			error_bound		1
			recursion_limit	1
			normal			on
			brightness		0.3
			always_sample	no
			gray_threshold	0.8
			media			on
		}
	#else
		ambient_light	0.3
	#end
	charset			utf8
	assumed_gamma	1
	max_trace_level	8		// default is 5
}

camera
{
	orthographic
	up			+y * ImgScale * Width * AspectRatio
	right		-x * ImgScale * Width
	direction	-z
	location	<0, ImgScale * Width * AspectRatio / 2, ImgScale * Width>
	translate	+y * -0.5 * ImgScale * Meters
}


background {color srgb BackColor}

light_source
{
	<3000, 6000, 7000>
	rgb 2
	parallel
	point_at 0
}

plane
{
	-z, Width * Meters
	texture
	{
		pigment
		{
			gradient y
			color_map
			{
				[0.00 color srgb GridColor]
				[0.05 color srgb GridColor]
				[0.05 color srgb BackColor]
				[1.00 color srgb BackColor]
			}
			scale ImgScale * GridScale
		}
		finish {emission 1 diffuse 0}
	}
}


//------------------------------------------------------------------------------

#macro new_random_color()
	#local numA = 1;
	#local numB = 1-numA;
	#if (!NoColors)
		#declare MTX = texture { pigment { color srgb <rand(Seed)*numA+numB,rand(Seed)*numA+numB,rand(Seed)*numA+numB> } finish { F_MetalA } }
		#declare CTX = texture { pigment { color srgb <rand(Seed)*numA+numB,rand(Seed)*numA+numB,rand(Seed)*numA+numB> } finish { F_MetalA } }
		#declare HTX = texture { pigment { color srgb <rand(Seed)*numA+numB,rand(Seed)*numA+numB,rand(Seed)*numA+numB> } finish { F_MetalA } }
		#declare WTX = texture { pigment { color srgb <rand(Seed)*numA+numB,rand(Seed)*numA+numB,rand(Seed)*numA+numB> } finish { F_MetalA } }
		#declare GTX = texture { pigment { color srgb <rand(Seed)*numA+numB,rand(Seed)*numA+numB,rand(Seed)*numA+numB> } finish { F_MetalA } }
	#else
		#declare MTX = texture { pigment { color srgb 4/4 } finish { F_MetalA } }
		#declare CTX = texture { pigment { color srgb 0/4 } finish { F_MetalA } }
		#declare HTX = texture { pigment { color srgb 1/2 } finish { F_MetalA } }
		#declare WTX = texture { pigment { color srgb 1/4 } finish { F_MetalA } }
		#declare GTX = texture { pigment { color srgb 2/4 } finish { F_MetalA } }
	#end
#end

#declare Plain_Gray			= texture { pigment { color srgb 1/2 } finish { F_MetalA  } }
#declare Plain_LightGray	= texture { pigment { color srgb 3/4 } finish { F_MetalA  } }
#declare Plain_DarkGray		= texture { pigment { color srgb 1/4 } finish { F_MetalA  } }


//------------------------------------------------------------------------------

new_random_color()
#include "btr_maanji.pov"
#declare mecha_object = object
{
	object01
	matrix <1.000000, 0.000000, 0.000000,
	0.000000, 1.000000, 0.000000,
	0.000000, 0.000000, 1.000000,
	0.000000, 0.000000, 0.000000>
	translate <0.000000, 0.000000, 0.000000>
	scale <1.000000, 1.000000, 1.000000>
	translate y * -4.65
	scale 1/115
	//edit below
	scale 18 * Meters
	rotate y * YRotate
}
#declare text_object = text
{
	ttf Font1Name "Maanji" 0.1, 0
	pigment {color srgb FontColor}
	finish {emission 1 diffuse 0}
	rotate y * 180
	scale FontSize
	translate y * (-Meters * 2 + GridScale * ImgScale * Meters/32)
}
union
{
	object {mecha_object}
	object {text_object Center_Trans(text_object, x)}
	translate +x * (Width * 0 + Width/2)
	translate +y * (Height * 0)
	#debug "Maanji is done.\n"
}

new_random_color()
#include "btr_radcliff.pov"
#declare mecha_object = object
{
	object01
	matrix <1.000000, 0.000000, 0.000000,
	0.000000, 1.000000, 0.000000,
	0.000000, 0.000000, 1.000000,
	0.000000, 0.000000, 0.000000>
	translate <0.000000, 0.000000, 0.000000>
	scale <1.000000, 1.000000, 1.000000>
	scale 1/115
	//edit below
	scale 16 * Meters
	rotate y * YRotate
}
#declare text_object = text
{
	ttf Font1Name "Radcliff" 0.1, 0
	pigment {color srgb FontColor}
	finish {emission 1 diffuse 0}
	rotate y * 180
	scale FontSize
	translate y * (-Meters * 2 + GridScale * ImgScale * Meters/32)
}
union
{
	object {mecha_object}
	object {text_object Center_Trans(text_object, x)}
	translate +x * (Width * 1 + Width/2)
	translate +y * (Height * 0)
	#debug "Radcliff is done.\n"
}

new_random_color()
#include "btr_vadel.pov"
#declare mecha_object = object
{
	object01
	matrix <0.707112, 0.000000, -0.707101,
	0.000000, 1.000000, 0.000000,
	0.707101, 0.000000, 0.707112,
	0.000000, 0.000000, 0.000000>
	translate <0.000000, 0.000000, 0.000000>
	scale <1.000000, 1.000000, 1.000000>
	rotate y * -45
	scale 1/75
	//edit below
	scale 16 * Meters
	rotate y * YRotate
}
#declare text_object = text
{
	ttf Font1Name "Vadel" 0.1, 0
	pigment {color srgb FontColor}
	finish {emission 1 diffuse 0}
	rotate y * 180
	scale FontSize
	translate y * (-Meters * 2 + GridScale * ImgScale * Meters/32)
}
union
{
	object {mecha_object}
	object {text_object Center_Trans(text_object, x)}
	translate -x * (Width * 1 + Width/2)
	translate +y * (Height * 1)
	#debug "Vadel is done.\n"
}

new_random_color()
#include "ara_kojedo.pov"
#declare mecha_object = object
{
	ara_kojedo_
	translate <18.42348,0,-364.0902> * -1
	scale 1/375
	// edit below
	scale 10 * Meters
	rotate y * YRotate
}
#declare text_object = text
{
	ttf Font1Name "Kojedo" 0.1, 0
	pigment {color srgb FontColor}
	finish {emission 1 diffuse 0}
	rotate y * 180
	scale FontSize
	translate y * (-Meters * 2 + GridScale * ImgScale * Meters/32)
}
union
{
	object {mecha_object}
	object {text_object Center_Trans(text_object, x)}
	translate +x * (Width * 0 + Width/2)
	translate +y * (Height * 1)
	#debug "Kojedo is done.\n"
}

new_random_color()
#include "btr_ovaknight.pov"
#declare mecha_object = object
{
	object01
	matrix <0.707112, 0.000000, -0.707101,
	0.000000, 1.000000, 0.000000,
	0.707101, 0.000000, 0.707112,
	0.000000, 0.000000, 0.000000>
	translate <0.000000, 0.000000, 0.000000>
	scale <1.000000, 1.000000, 1.000000>
	rotate y * -45
	scale 1/100
	//edit below
	scale 20 * Meters
	rotate y * YRotate
}
#declare text_object = text
{
	ttf Font1Name "OvaKnight" 0.1, 0
	pigment {color srgb FontColor}
	finish {emission 1 diffuse 0}
	rotate y * 180
	scale FontSize
	translate y * (-Meters * 2 + GridScale * ImgScale * Meters/32)
}
union
{
	object {mecha_object}
	object {text_object Center_Trans(text_object, x)}
	translate -x * (Width * 0 + Width/2)
	translate +y * (Height * 0)
	#debug "Ovaknight is done.\n"
}

new_random_color()
#include "btr_condor.pov"
#declare mecha_object = object
{
	Condor__e_dot_mpd #if (version >= 3.1) material #else texture #end { Color7 }
	rotate x * 180
	scale 1/465
	//edit below
	scale 16 * Meters
	rotate y * YRotate
}
#declare text_object = text
{
	ttf Font1Name "Condor" 0.1, 0
	pigment {color srgb FontColor}
	finish {emission 1 diffuse 0}
	rotate y * 180
	scale FontSize
	translate y * (-Meters * 2 + GridScale * ImgScale * Meters/32)
}
union
{
	object {mecha_object}
	object {text_object Center_Trans(text_object, x)}
	translate -x * (Width * 1 + Width/2)
	translate +y * (Height * 0)
	#debug "Condor is done.\n"
}

new_random_color()
#include "btr_jos.pov"
#declare mecha_object = object
{
	object01
	matrix <1.000000, 0.000000, 0.000000,
	0.000000, 1.000000, 0.000000,
	0.000000, 0.000000, 1.000000,
	0.000000, 0.000000, 0.000000>
	translate <0.000000, 0.000000, 0.000000>
	scale <1.000000, 1.000000, 1.000000>
	scale 1/122
	//edit below
	scale 16 * Meters
	rotate y * YRotate
}
#declare text_object = text
{
	ttf Font1Name "Jos" 0.1, 0
	pigment {color srgb FontColor}
	finish {emission 1 diffuse 0}
	rotate y * 180
	scale FontSize
	translate y * (-Meters * 2 + GridScale * ImgScale * Meters/32)
}
union
{
	object {mecha_object}
	object {text_object Center_Trans(text_object, x)}
	translate -x * (Width * 0 + Width/2)
	translate +y * (Height * 1)
	#debug "Jos is done.\n"
}

new_random_color()
#include "btr_trailblazer.pov"
#declare mecha_object = object
{
	object01
	matrix <0.707112, 0.000000, -0.707101,
	0.000000, 1.000000, 0.000000,
	0.707101, 0.000000, 0.707112,
	0.000000, 0.000000, 0.000000>
	translate <0.000000, 0.000000, 0.000000>
	scale <1.000000, 1.000000, 1.000000>
	rotate y * -45
	scale 1/63
	//edit below
	scale 13 * Meters
	rotate y * YRotate
}
#declare text_object = text
{
	ttf Font1Name "Trailblazer" 0.1, 0
	pigment {color srgb FontColor}
	finish {emission 1 diffuse 0}
	rotate y * 180
	scale FontSize
	translate y * (-Meters * 2 + GridScale * ImgScale * Meters/32)
}
union
{
	object {mecha_object}
	object {text_object Center_Trans(text_object, x)}
	translate +x * (Width * 1 + Width/2)
	translate +y * (Height * 1)
	#debug "Trailblazer is done.\n"
}

new_random_color()
#include "ghu_doombuggy.pov"
#declare mecha_object = object
{
	APC
	texture {ACP_Texture}
	rotate y * 90
	scale 1/23
	//edit below
	scale 3 * Meters
	rotate y * YRotate
}
#declare text_object = text
{
	ttf Font1Name "Doom Buggy" 0.1, 0
	pigment {color srgb FontColor}
	finish {emission 1 diffuse 0}
	rotate y * 180
	scale FontSize
	translate y * (-Meters * 2 + GridScale * ImgScale * Meters/32)
}
union
{
	object {mecha_object}
	object {text_object Center_Trans(text_object, x)}
	translate +x * (Width * 0 + Width/2)
	translate +y * (Height * 2)
	#debug "Doombuggy is done.\n"
}

new_random_color()
#include "ghu_renegade.pov"
#declare mecha_object = object
{
	RedrockRacer__b_dot_mpd
	scale 1/10
	scale 1/2
	scale Scale_LDraw
	rotate x * 180
//	rotate y * -45
	rotate y * YRotate
}
#declare text_object = text
{
	ttf Font1Name "Renegade" 0.1, 0
	pigment {color srgb FontColor}
	finish {emission 1 diffuse 0}
	rotate y * 180
	scale FontSize
	translate y * (-Meters * 2 + GridScale * ImgScale * Meters/32)
}
union
{
	object {mecha_object}
	object {text_object Center_Trans(text_object, x)}
	translate +x * (Width * 1 + Width/2)
	translate +y * (Height * 2)
	#debug "Renegade is done.\n"
}

new_random_color()
#include "gca_rover.pov"
#declare mecha_object = object
{
	BUGGY__b_dot_mpd
	scale Scale_LDraw
	scale 1/10
	scale 1/2
	rotate x * 180
//	rotate y * -45
	rotate y * YRotate
}
#declare text_object = text
{
	ttf Font1Name "Rover" 0.1, 0
	pigment {color srgb FontColor}
	finish {emission 1 diffuse 0}
	rotate y * 180
	scale FontSize
	translate y * (-Meters * 2 + GridScale * ImgScale * Meters/32)
}
union
{
	object {mecha_object}
	object {text_object Center_Trans(text_object, x)}
	translate -x * (Width * 0 + Width/2)
	translate +y * (Height * 2)
	#debug "Rover is done.\n"
}

new_random_color()
#include "cha_m_citizen.pov"
#declare mecha_object = object
{
	object01
	matrix <0.707112, 0.000000, -0.707101,
	0.000000, 1.000000, 0.000000,
	0.707101, 0.000000, 0.707112,
	0.000000, 0.000000, 0.000000>
	translate <0.000000, 0.000000, 0.000000>
	scale <1.000000, 1.000000, 1.000000>
	scale 1/16
	rotate y * -45
	rotate y * YRotate
}
#declare text_object = text
{
	ttf Font1Name "Citizen" 0.1, 0
	pigment {color srgb FontColor}
	finish {emission 1 diffuse 0}
	rotate y * 180
	scale FontSize
	translate y * (-Meters * 2 + GridScale * ImgScale * Meters/32)
}
union
{
	object {mecha_object}
	object {text_object Center_Trans(text_object, x)}
	translate -x * (Width * 1 + Width/2)
	translate +y * (Height * 2)
	#debug "Citizen is done.\n"
}


//------------------------------------------------------------------------------

union
{
	#local jCount = 0;
	#while (jCount < 3)
		#local iCount = 0;
		#while (iCount < 11)
			text
			{
				ttf Font3Name str(iCount * GridScale * ImgScale / Meters,0,0) 0.1, 0
				pigment {color srgb GridColor}
				finish {emission 1 diffuse 0}
				rotate y * 180
				translate y * (iCount + Meters/32)
				scale GridScale
				translate x * (Width / 2 - Meters/32)
				scale ImgScale
				no_shadow
				translate y * (Height * jCount)
			}
			#local iCount = iCount + 1;
		#end
		#local jCount = jCount + 1;
	#end
}

text
{
	ttf Font2Name "GearHead 2" 0.1, 0
	pigment {color srgb FontColor}
	finish {emission 1 diffuse 0}
	rotate y * 180
	scale 8 * Meters
	translate x * (30 * Meters)
	translate y * (60 * Meters)
}

text
{
	ttf Font2Name "Just a minute..." 0.1, 0
	pigment {color srgb FontColor}
	finish {emission 1 diffuse 0}
	rotate y * 180
	scale 4 * Meters
	translate x * ( 0 * Meters)
	translate y * (56 * Meters)
}
