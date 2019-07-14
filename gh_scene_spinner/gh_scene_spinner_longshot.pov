// Desc: Several GearHead mecha battling it out in a city setting.
// Auth: Michael Horvath
// Home Page: http://isometricland.com
// This file is licensed under the terms of the CC-LGPL.
// Dependencies:
// 1. CITY GENERATOR INCLUDE FILE by Chris Colefax
// 2. Rune's particle system
// need to migrate all includes to the GearHead directory
// raumschiff needs a bounding box

//+KFI0 +KFF5 +KC +KI0 +KF0
//+KFI5 +KFF5 +KC
//+K0 +KC

#version 3.6

#include "CIE.inc"		// http://www.ignorancia.org/en/index.php?page=Lightsys
#include "lightsys.inc"		// http://www.ignorancia.org/en/index.php?page=Lightsys
#include "math.inc"
#include "shapes.inc"
#include "finish.inc"
#include "metals.inc"
#include "colors.inc"

// inter-scene variables
#declare pov_version		= 1;				// 0 = 3.6; 1 = 3.7; 3.7 also has gamma adjustments in INI file
#declare Seed			= seed(8829464);
#declare Tiles			= 1;				// the default size of the scene, measured in tiles. Use this to zoom in/out.
#declare Sprite_Height		= 128;				// changes the camera's position. 0 for mecha, 1 for walls & terrain.
#declare Width			= 8;				// the default width of a tile.
#declare Subdivision		= 0;				// turn on/off mesh subdivision. This requires a special exe available on the Net.
#declare Included		= 1;				// tells any included files that they are being included.
#declare TexQual		= 1;
#declare Minimal		= 0;				// a minimal render with lots turned off

// toggles
#declare NoColors		= 0;
#declare NoCity			= 0;
#declare NoSmoke		= 1;					// not used
#declare NoMecha		= 0;
#declare NoMissiles		= 1;					// not used
#declare NoBullets		= 1;					// not used
#declare NoTrees		= 1;					// not used
#declare NoRadiosity		= 1;
#declare NoLights		= 0;					// not used
#declare NoSky			= 0;					// not used
#declare NoShell		= 0;					// boolean, toggle outer shell, spokes and endcaps
#declare NoLamp			= 0;
#declare NoCars			= 0;
#declare NoStreet		= 0;
#declare NoDomes		= 0;
#declare NewTrain		= 1;					// boolean, use maglev instead of streetcars
#declare AlwaysReflect		= 0;
#declare debug_progress		= 1;					// boolean, see CityGen docs

#if (Minimal)
	#declare NoSmoke		= 1;					// not used
	#declare NoMecha		= 0;
	#declare NoMissiles		= 1;					// not used
	#declare NoBullets		= 1;					// not used
	#declare NoTrees		= 1;					// not used
	#declare NoRadiosity		= 1;
	#declare NoLights		= 0;					// not used
	#declare NoSky			= 0;					// not used
	#declare NoShell		= 0;					// boolean, toggle outer shell, spokes and endcaps
	#declare NoLamp			= 1;
	#declare NoCars			= 1;
	#declare NoStreet		= 1;
	#declare NoDomes		= 1;
	#declare AlwaysReflect		= 0;
#end

// citygen variables
#declare glass_hollow		= false;				// boolean
#declare glass_thin		= false;				// boolean
#declare bound_fit		= true;	
#declare city_night		= false;
#declare city_right_hand_drive	= false;
#declare city_default_objects	= false;
#declare city_use_mesh		= false;
#declare city_all_mesh		= false;
#declare city_tileable		= true;
#declare city_units		= 1;					// should not be used anywhere directly
#declare city_storey_height	= city_units * 4;			// for reference, people are roughly city_units * 2 units tall
#declare city_ped_density	= 1/64/city_units;			// is this being used?? it should be!
#declare city_radius		= city_units * 4096;
#declare city_circum		= city_radius * 2 * pi;
#declare city_grass_height	= city_units / 4;			// too thin and it gets clipped by the pavement
#declare city_tree_height	= city_units * 12;
#declare Lightsys_Scene_Scale	= city_units * 100;
#declare total_lanes		= (NewTrain ? 2 : 3);			// in both directions, including half lanes for bikes (minimum 2)
#declare nominal_traffic_width	= city_units * (NewTrain ? 6 : 12);
#declare nominal_building_width	= city_units * 64;
#declare buildings_per_block	= <4,4,0,>;
#declare city_block_count	= <8,8,0,>;
#declare traffic_spacing	= city_units * 128;
#declare traffic_width		= nominal_traffic_width/total_lanes;
#declare traffic_lanes		= floor(total_lanes/2);			// in each direction...
#declare pavement_width		= city_units * 2;
#declare building_gap		= pavement_width * 2;
#declare building_width		= nominal_building_width - pavement_width * 2;
#declare min_building_height	= city_units * 32;
#declare max_building_height	= city_units * 64;
#declare building_height_turb	= 1;
#declare street_height		= 0;					// to do, may conflict with citygen...
#declare street_width		= nominal_traffic_width;
#declare rail_ped_thick		= city_units * 2/3;			// rail pedestal leg
#declare rail_width		= street_width/2;
#declare rail_height		= city_units * 4;
#declare rail_thick		= city_units/4;
#declare rail_plat_width	= street_width * 4/3;
#declare rail_cars_number	= 1;					// odd values only
#declare shell_radius		= city_units * 272;
#declare dome_radius		= city_units * 64;
#declare panel_distance		= city_units * 72;
#declare panel_width		= city_units * 128;
#declare panel_length		= city_units * 512;
#declare panel_thick		= city_units/2;
#declare dock_length		= city_units * 256;
#declare city_rotate		= 0;					// degrees

// scene variables
#local light_color		= Light_Color(Daylight(5500),2.3);

// scene variables (mostly)
#local city_sections		= 1;					// integer
#local block_dist_x		= nominal_traffic_width + nominal_building_width * buildings_per_block.x;	// float, ignores city_tileable
#local block_dist_z		= nominal_traffic_width + nominal_building_width * buildings_per_block.y;	// float, ignores city_tileable
#local city_length		= block_dist_z * city_block_count.y * city_sections		// city blocks
				+ 2 * (nominal_traffic_width + nominal_building_width);		// end border grass
#local total_length		= city_length + dock_length;
#debug concat("\ncity_length = ",str(city_length,0,0),"\n\n")
#local spoke_total		= 5;					// integer, the number of radial city sections
#local spoke_angle		= 360/spoke_total;			// float, the angle separating each section (should be hidden)
#local slice_total		= 25;					// integer, the number of radial city blocks, needs to be divisible by spoke_total
#local slice_angle		= 360/slice_total;			// float, the angle between each block (should be hidden)
//#declare city_circum		= block_dist_x * slice_total;		// float, the circumference of the spinner colony
//#declare city_radius		= city_circum/2/pi;			// float, the radius of the spinner colony
#local cap_thickness		= city_units * 4;			// float, the thickness of the spinner shell
#local lamp_radius		= city_units * 4;			// float, the radius of the fusion lamp
#local cap_zscale		= 1/2;					// float, makes the endcaps ellipsoidal instead of spherical
#local light_lumens		= 2.3;					// float
#local light_temp		= Daylight(5002.78);			// float?
#local nominal_slice_total 	= (Minimal ? slice_total : slice_total);		// integer, can't remember what this was for
#local planet_distance		= 385000000/10000;			// meters
#local planet_radius		=   6371000/10000;			// meters
#local sun_distance		= 149600000/10000;			// kilometers
#local sun_radius		=    695500/10000;			// kilometers
#local lamp_length		= city_length;
#if (TexQual = 1)
	#local lamp_number = floor(lamp_length/32);
#else
	#local lamp_number = floor(lamp_length/64);
#end

#declare Camera_Mode		= 3;				// 0 to 8; 0 = orthographic; 1 = oblique; 2 = perspective
#declare Camera_Diagonal	= cosd(45);
#declare Camera_Vertical	= -22.5;				//45;
#declare Camera_Horizontal	= 60;				//30;
#declare Camera_Scale		= 1;
#declare Camera_Aspect		= image_height/image_width;
#declare Camera_Distance	= 128;
#declare Camera_Translate	= <0,-city_radius,0,>;			//<0,0,-city_size_total.y,>
#declare Camera_Scale		= 128;
#include "gh_camera.inc"


//------------------------------------------------------------------------------Macros

#macro gamma_color_adjust(in_color)
	#if (version < 3.7)
		#local out_gamma = 2.2;
	#else
		#local out_gamma = 1;
	#end
	#local in_color = in_color + <0,0,0,0,0>;
	color rgbft
	<
		pow(in_color.red, out_gamma),
		pow(in_color.green, out_gamma),
		pow(in_color.blue, out_gamma),
		in_color.filter,
		in_color.transmit
	>
#end
#macro gamma_color_adjust_special(in_color)
	#if (version < 3.7)
		#local out_gamma = 1;
	#else
		#local out_gamma = 0.454545;
	#end
	#local in_color = in_color + <0,0,0,0,0>;
	color rgbft
	<
		pow(in_color.red, out_gamma),
		pow(in_color.green, out_gamma),
		pow(in_color.blue, out_gamma),
		in_color.filter,
		in_color.transmit
	>
#end
#macro vstr_def(in_vector)
	vstr(3,in_vector,",",0,-1)
#end
#macro vfloor_def(in_vector)
	<floor(in_vector.x),floor(in_vector.y),floor(in_vector.z)>
#end
#macro vceil_def(in_vector)
	<ceil(in_vector.x),ceil(in_vector.y),ceil(in_vector.z)>
#end
#macro vmod_def(in_vector,in_quot)
	<mod(in_vector.x,in_quot),mod(in_vector.y,in_quot),mod(in_vector.z,in_quot)>
#end
#macro vgreat_def(in_vector_1,in_vector_2)
	((in_vector_1.x>in_vector_2.x)&(in_vector_1.y>in_vector_2.y)&(in_vector_1.z>in_vector_2.z))
#end
#macro str_def(in_value)
	str(in_value,0,-1)
#end
#macro verbose_include(in_file, in_bool)
	#if (in_bool)
	#debug concat("\n======Already included ", in_file, ", skipping\n")
	#else
		#debug concat("\n>>>>>>Starting to include ", in_file, "\n")
		#include in_file
		#debug concat("\n<<<<<<Finished including ", in_file, "\n")
	#end
#end
#macro verbose_parse_string(in_string)
	#debug concat("\nParsing \"", in_string, "\"\n")
	Parse_String(in_string)
#end


//------------------------------------------------------------------------------Textures

#declare sky_pigment_1 = pigment
{
	bozo
	turbulence	0.65
	octaves		6
	omega		0.7
	lambda		2
	color_map
	{
		[0.0	gamma_color_adjust(<0.85,0.85,0.85,>)]
		[0.1	gamma_color_adjust(<0.75,0.75,0.75,>)]
		[0.5	gamma_color_adjust(< 0.5, 0.6, 1.0 >)]
		[1.0	gamma_color_adjust(< 0.5, 0.6, 1.0 >)]
	}
	scale 16
}
#declare sky_pigment_2 = pigment {sky_pigment_1 transmit 1}
#declare sky_pigment_3 = pigment
{
	radial
	pigment_map
	{
		[0/2 sky_pigment_1]
		[1/2 sky_pigment_2]
		[2/2 sky_pigment_1]
	}
	rotate x * 90
}
#local grass_pigment_1 = pigment
{
	image_map {png "olivepink_marble.png"}
	rotate x * 90
}
#local grass_pigment_2 = pigment
{
	gamma_color_adjust(<046,104,058,>/255/2)
}
#local grass_pigment_3 = pigment
{
	average
	pigment_map
	{
		[2 grass_pigment_1]
		[2 grass_pigment_2]
	}
}
#local grass_texture_1 = texture
{
	pigment {grass_pigment_3}
	normal
	{
		wrinkles
//		scale		1/SceneScale
//		scale		<1,16/HeightScale,1,>
	}
}



//------------------------------------------------------------------------------Global settings

default {finish {ambient 0 diffuse 1}}

global_settings
{
	charset utf8
	#if (version < 3.7)
		assumed_gamma	1.0
	#end
	#if (!NoRadiosity)
		verbose_include("rad_def.inc")
		radiosity {Rad_Settings(Radiosity_OutdoorLight, off, off)}
	#end
	#switch (TexQual)
		#case (0)
			max_trace_level 4
		#break
		#case (1/2)
			max_trace_level 16
		#break
		#case (1)
			max_trace_level 64
		#break
	#end
}


//------------------------------------------------------------------------------Lights & Sky

light_source
{
	<-15000, +15000, -15000> * <1/4,1,1/2>
	gamma_color_adjust_special(light_color)
	translate -y * city_radius
	parallel
}

plane
{
	<0,1,0>,1 hollow
	texture
	{
		pigment
		{
			bozo turbulence 0.75
			octaves 6  omega 0.7 lambda 2 
			color_map
			{
				[ 0.0 color  rgb <0.95, 0.95, 0.95> ]
				[0.05 color  rgb <1, 1, 1>*1.25 ]
				[0.15 color  rgb <0.85, 0.85, 0.85> ]
				[0.55 color rgbt <1, 1, 1, 1>*1 ]
				[ 1.0 color rgbt <1, 1, 1, 1>*1 ]
			}
			translate < 3, 0,-1>
			scale <0.3, 0.4, 0.2>*3
		}
		finish {ambient 1 diffuse 0}
	}
	scale 512
}

sky_sphere {pigment {gamma_color_adjust(<223/255,230/255,255/255>)}}


//------------------------------------------------------------------------------City

#if (!NoCity)
	//------------------------------------------------------------------------------Main City

//	verbose_include("CG_UNIQUE_CURVED_MESH.INC", 0)		// not implemented yet
	verbose_include("CG_DEFAULT_CURVED_MESH.INC", 0)
	verbose_include("CG_VEHICLES_CURVED_MESH.INC", 0)
	verbose_include("CG_PAVEMENT_CURVED_MESH.INC", 0)
	verbose_include("CG_SQUARE_CURVED_MESH.INC", 0)
	verbose_include("CG_PARK_CURVED_MESH.INC", 0)
	verbose_include("CG_NORMAL_CURVED_MESH.INC", 0)
//	object
//	{
//		#include "CG_CITY_CURVED_MESH.inc"
//	}
#end


//------------------------------------------------------------------------------Alignment
/*
cylinder
{
	-x*256,+x*256, 1/2
	pigment {color rgb x}
	translate -y * city_radius
}
cylinder
{
	-y*256,+y*256, 1/2
	pigment {color rgb y}
	translate -y * city_radius
}
cylinder
{
	-z*256,+z*256, 1/2
	pigment {color rgb z}
	translate -y * city_radius
}
*/
