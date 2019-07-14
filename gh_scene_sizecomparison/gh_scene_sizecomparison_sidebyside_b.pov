// Desc: Several GearHead mecha lined up in front of a ruled background.
// Auth: Michael Horvath
// Home Page: http://www.geocities.com/Area51/Quadrant/3864/gearhead.htm
// This file is licensed under the terms of the CC-LGPL.
// Dependencies:
// 1. "HIROSHT.TTF" by Jonathan Smith
// 2. "PLANK___.TTF" by Mads Rydahl

#include "colors.inc"
#include "metals.inc"
#include "glass.inc"
#include "gh_textures.inc"
#include "rand.inc"

#declare Seed =		seed(882);
#declare Included =	true;
#declare ImgScale =	4;
#declare Meters =	4;
#declare GridScale =	2;
#declare NoColors =	1;
#declare NoWeapons =	1;
#declare YRotate =	30;
#declare Width =	96;
#declare Height =	96;
#declare Subdivision =	0;
#declare Scale_LDraw =	1;

// used to convert pigments created in version 3.6 to version 3.7
#macro gamma_color_vector(in_color)
	#local out_gamma = 2.2;
	#local in_color = in_color + <0,0,0,0,0>;
	<
		pow(in_color.red,   out_gamma),
		pow(in_color.green, out_gamma),
		pow(in_color.blue,  out_gamma),
//		in_color.filter,
//		in_color.transmit
	>
#end

// used to convert pigments created in version 3.6 to version 3.7
#macro gamma_color_adjust(in_color)
	color rgb gamma_color_vector(in_color)
#end

#macro new_random_color()
	#if (NoColors = 0)
		#declare MTX = texture { pigment { color rgb gamma_color_vector(<rand(Seed),rand(Seed),rand(Seed)>) } finish { F_MetalA  } }
		#declare CTX = texture { pigment { color rgb gamma_color_vector(<rand(Seed),rand(Seed),rand(Seed)>) } finish { F_MetalA  } }
		#declare HTX = texture { pigment { color rgb gamma_color_vector(<rand(Seed),rand(Seed),rand(Seed)>) } finish { F_MetalA  } }
	#else
		#declare MTX = texture { pigment { color rgb gamma_color_vector(1) } finish { F_MetalA  } }
		#declare CTX = texture { pigment { color rgb gamma_color_vector(0) } finish { F_MetalA  } }
		#declare HTX = texture { pigment { color rgb gamma_color_vector(1/2) } finish { F_MetalA  } }
	#end
#end

#declare Plain_Gray = texture { pigment { color rgb gamma_color_vector(1/2) } finish { F_MetalA  } }
#declare Plain_LightGray = texture { pigment { color rgb gamma_color_vector(3/4) } finish { F_MetalA  } }
#declare Plain_DarkGray = texture { pigment { color rgb gamma_color_vector(1/4) } finish { F_MetalA  } }

//------------------------------------------------------------------------------
/*
global_settings
{
	radiosity
	{
		recursion_limit 1
		brightness 0.5
		count 100
		error_bound 0.5
		always_sample off
	}
	max_trace_level 256
}
*/
camera
{
	#local AspectRatio = image_height / image_width;
	orthographic
	sky		y
	up		y * ImgScale * Width * AspectRatio
	right		x * ImgScale * Width
	location	<0, ImgScale * Width * AspectRatio / 2, ImgScale * Width,>
	look_at		<0, ImgScale * Width * AspectRatio / 2, 0,>
	translate	y * -0.5 * ImgScale * Meters
}

background {color rgb 1/2}

light_source {<3000, 6000, 7000> rgb 1 parallel}

plane
{
	z, -Width * 4
	texture
	{
		pigment
		{
			gradient y
			color_map
			{
				[0.0 color rgb 1/2]
				[0.05 color rgb 1/2]
				[0.05 color rgb 1]
				[1.0 color rgb 1]
			}
			scale ImgScale * GridScale
		}
//		finish {ambient 0}
	}
}



//------------------------------------------------------------------------------

new_random_color()
#include "btr_maanji.pov"
union
{
	object
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
	text
	{
		ttf "HIROSHT.TTF" "Maanji" 0.1, 0
		rotate y * 180
		scale Meters * 2
		translate y * (-Meters * 2 + 0.125 * GridScale * ImgScale)
		translate x * 18
	}
	translate x * +(Width * 0 + Width/2)
	translate y * (Height * 0)
	#debug "Maanji is done.\n"
}

new_random_color()
#include "btr_radcliff.pov"
union
{
	object
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
	text
	{
		ttf "HIROSHT.TTF" "Radcliff" 0.1, 0
		rotate y * 180
		scale Meters * 2
		translate y * (-Meters * 2 + 0.125 * GridScale * ImgScale)
		translate x * 26
	}
	translate x * +(Width * 1 + Width/2)
	translate y * (Height * 0)
	#debug "Radcliff is done.\n"
}

new_random_color()
#include "btr_vadel.pov"
union
{
	object
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
	text
	{
		ttf "HIROSHT.TTF" "Vadel" 0.1, 0
		rotate y * 180
		scale Meters * 2
		translate y * (-Meters * 2 + 0.125 * GridScale * ImgScale)
		translate x * 16
	
	}
	translate x * -(Width * 1 + Width/2)
	translate y * (Height * 1)
	#debug "Vadel is done.\n"
}

new_random_color()
#include "ara_kojedo.pov"
union
{
	object
	{
		ara_kojedo_
		translate <18.42348,0,-364.0902> * -1
		scale 1/470
		// edit below
		scale 11 * Meters
		rotate y * YRotate
	}
	text
	{
		ttf "HIROSHT.TTF" "Kojedo" 0.1, 0
		rotate y * 180
		scale Meters * 2
		translate y * (-Meters * 2 + 0.125 * GridScale * ImgScale)
		translate x * 19
	}
	translate x * +(Width * 0 + Width/2)
	translate y * (Height * 1)
	#debug "Kojedo is done.\n"
}

new_random_color()
#include "btr_ovaknight.pov"
union
{
	object
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
		scale 19 * Meters
		rotate y * YRotate
	}
	text
	{
		ttf "HIROSHT.TTF" "OvaKnight" 0.1, 0
		rotate y * 180
		scale Meters * 2
		translate y * (-Meters * 2 + 0.125 * GridScale * ImgScale)
		translate x * 28
	}
	translate x * -(Width * 0 + Width/2)
	translate y * (Height * 0)
	#debug "Ovaknight is done.\n"
}

new_random_color()
#include "btr_condor.pov"
union
{
	object
	{
		Condor__e_dot_mpd #if (version >= 3.1) material #else texture #end { Color7 }
		rotate x * 180
		scale 1/465
		//edit below
		scale 15 * Meters
		rotate y * YRotate
	}
	text
	{
		ttf "HIROSHT.TTF" "Condor" 0.1, 0
		rotate y * 180
		scale Meters * 2
		translate y * (-Meters * 2 + 0.125 * GridScale * ImgScale)
		translate x * 22
	}
	translate x * -(Width * 1 + Width/2)
	translate y * (Height * 0)
	#debug "Condor is done.\n"
}

new_random_color()
#include "btr_jos.pov"
union
{
	object
	{
		object01
		matrix <1.000000, 0.000000, 0.000000,
		0.000000, 1.000000, 0.000000,
		0.000000, 0.000000, 1.000000,
		0.000000, 0.000000, 0.000000>
		translate <0.000000, 0.000000, 0.000000>
		scale <1.000000, 1.000000, 1.000000>
		scale 1/140
		//edit below
		scale 17 * Meters
		rotate y * YRotate
	}
	text
	{
		ttf "HIROSHT.TTF" "Jos" 0.1, 0
		rotate y * 180
		scale Meters * 2
		translate y * (-Meters * 2 + 0.125 * GridScale * ImgScale)
		translate x * 9
	}
	translate x * -(Width * 0 + Width/2)
	translate y * (Height * 1)
	#debug "Jos is done.\n"
}

new_random_color()
#include "btr_trailblazer.pov"
union
{
	object
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
	text
	{
		ttf "HIROSHT.TTF" "Trailblazer" 0.1, 0
		rotate y * 180
		scale Meters * 2
		translate y * (-Meters * 2 + 0.125 * GridScale * ImgScale)
		translate x * 34
	}
	translate x * +(Width * 1 + Width/2)
	translate y * (Height * 1)
	#debug "Trailblazer is done.\n"
}

new_random_color()
#include "ghu_doombuggy.pov"
union
{
	object
	{
		APC
		texture {ACP_Texture}
		rotate y * 90
		scale 1/23
		//edit below
		scale 3 * Meters
		rotate y * YRotate
	}
	text
	{
		ttf "HIROSHT.TTF" "Doom Buggy" 0.1, 0
		rotate y * 180
		scale Meters * 2
		translate y * (-Meters * 2 + 0.125 * GridScale * ImgScale)
		translate x * 34
	}
	translate x * +(Width * 0 + Width/2)
	translate y * (Height * 2)
	#debug "Doombuggy is done.\n"
}

new_random_color()
#include "ghu_renegade.pov"
union
{
	object
	{
		RedrockRacer__b_dot_mpd #if (version >= 3.1) material #else texture #end { Color7 }
		scale 1/10
		scale 1/2
		scale Scale_LDraw
		rotate x * 180
//		rotate y * -45
		rotate y * YRotate
	}
	text
	{
		ttf "HIROSHT.TTF" "Renegade" 0.1, 0
		rotate y * 180
		scale Meters * 2
		translate y * (-Meters * 2 + 0.125 * GridScale * ImgScale)
		translate x * 28
	}
	translate x * +(Width * 1 + Width/2)
	translate y * (Height * 2)
	#debug "Renegade is done.\n"
}

new_random_color()
#include "gca_rover.pov"
union
{
	object
	{
		BUGGY__b_dot_mpd #if (version >= 3.1) material #else texture #end { Color7 }
		scale 1/10
		scale 1/2
		scale Scale_LDraw
		rotate x * 180
//		rotate y * -45
		rotate y * YRotate
	}
	text
	{
		ttf "HIROSHT.TTF" "Rover" 0.1, 0
		rotate y * 180
		scale Meters * 2
		translate y * (-Meters * 2 + 0.125 * GridScale * ImgScale)
		translate x * 17
	}
	translate x * -(Width * 0 + Width/2)
	translate y * (Height * 2)
	#debug "Rover is done.\n"
}

new_random_color()
#include "cha_m_citizen.pov"
union
{
	object
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
	text
	{
		ttf "HIROSHT.TTF" "Citizen" 0.1, 0
		rotate y * 180
		scale Meters * 2
		translate y * (-Meters * 2 + 0.125 * GridScale * ImgScale)
		translate x * 20
	}
	translate x * -(Width * 1 + Width/2)
	translate y * (Height * 2)
	#debug "Citizen is done.\n"
}

new_random_color()
union
{
	#local jCount = 0;
	#while (jCount < 3)
		#local iCount = 0;
		#while (iCount < 11)
			text
			{
				ttf "arial.ttf" str(iCount * GridScale * ImgScale / Meters,0,0) 0.1, 0
				rotate y * 180
				translate y * (iCount + 0.125)
				scale GridScale
				translate x * (Width / 2 - 0.125)
				scale ImgScale
				pigment {color rgb 1/2}
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
	ttf "PLANK___.TTF" "GearHead 2" 0.1, 0
	rotate y * 180
	scale 32
	translate x * (120)
	translate y * (240)
}

text
{
	ttf "PLANK___.TTF" "Just a minute..." 0.1, 0
	rotate y * 180
	scale 16
	translate x * (0)
	translate y * (224)
}
