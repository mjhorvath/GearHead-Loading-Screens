// Desc: Several GearHead mecha battling it out in a city setting.
// Auth: Michael Horvath
// Home Page: http://www.geocities.com/Area51/Quadrant/3864/gearhead.htm
// This file is licensed under the terms of the CC-LGPL.
// Dependencies:
// 1. CITY GENERATOR INCLUDE FILE by Chris Colefax
// 2. Rune's particle system

//+KFI0 +KFF5 +KC +KI0 +KF0
//+KFI5 +KFF5 +KC
//+K0 +KC

#include "math.inc"
#include "CIE.inc"
#include "lightsys.inc"

#declare pov_version		= 1;				// 0 = 3.6; 1 = 3.7; 3.7 also has gamma adjustments in INI file
#declare Seed			= seed(8829464);
#declare Tiles			= 1;				// the default size of the scene, measured in tiles. Use this to zoom in/out.
#declare Sprite_Height		= 128;				// changes the camera's position. 0 for mecha, 1 for walls & terrain.
#declare Width			= 8;				// the default width of a tile.
#declare Subdivision		= 0;				// turn on/off mesh subdivision. This requires a special exe available on the Net.
#declare Included		= 1;				// tells any included files that they are being included.

#declare NoCity			= 0;
#declare NoSmoke		= 1;
#declare NoMechs		= 1;
#declare NoMissiles		= 1;
#declare NoBullets		= 1;
#declare NoTrees		= 1;
#declare NoRadiosity		= 1;
#declare NoSky			= 1;
#declare TexQual		= 1;

#local total_lanes		= 3;
#local nominal_building_width	= Width * 4;
#local nominal_traffic_width	= Width;

#declare city_units		= Width;
#declare city_storey_height	= city_units/4;
#declare city_radius		= 100;
#declare city_circum		= pi * city_radius * 2;
#declare car_scale		= 1;
#declare slamp_scale		= 3/4;

#declare buildings_per_block	= <2,2,0,>;			// 3x4 including roads
#declare city_block_count	= <2,2,0,>;
#declare city_tileable		= true;
#declare traffic_spacing	= 16;				// 16
#declare traffic_width		= nominal_traffic_width/total_lanes;
#declare traffic_lanes		= (total_lanes-1)/2;
#declare pavement_width		= 2;
#declare building_gap		= pavement_width * 2;
#declare building_width		= nominal_building_width - pavement_width * 2;
#declare block_dist_x		= traffic_width * (traffic_lanes * 2 + 1) + pavement_width * 2 + building_width * buildings_per_block.x + building_gap * (buildings_per_block.x - 1);
#declare block_dist_z		= traffic_width * (traffic_lanes * 2 + 1) + pavement_width * 2 + building_width * buildings_per_block.y + building_gap * (buildings_per_block.y - 1);
#declare block_size_xz		= <block_dist_x,block_dist_z,0,>;
#if (city_tileable)
	#declare city_size_total	= city_block_count * block_size_xz;
#else
	#declare city_size_total	= city_block_count * block_size_xz + <16,16,0,>;
#end
#declare min_building_height	= 16;
#declare max_building_height	= 32;
#declare building_height_turb	= 1;
#declare city_night		= false;
#declare city_right_hand_drive	= false;
#declare city_default_objects	= true;

#declare green_width		= (buildings_per_block.y * 2 + 1) * 16;
#declare green_intrvl		= 6;
#declare total_length		= city_size_total.y * 2 + green_width;
#declare temp_max		= 36;
#declare temp_length		= block_dist_x * temp_max;
#declare temp_radius		= temp_length/pi/2;
#declare AirCarPosition		= <-32,+32,+32,>;
#declare KojedoPosition		= +x * block_dist_x;
#declare MaanjiPosition		= -x * block_dist_x;
#declare KojedoCenter		= <0,4,0,>;
#declare LineVector		= vnormalize(-AirCarPosition + KojedoCenter + KojedoPosition);
#declare SceneScale		= pow(Width, 2);
#declare Burst			= true;

#declare Camera_Mode		= 3;				// 0 to 8; 0 = orthographic; 1 = oblique; 2 = perspective
#declare Camera_Diagonal	= cosd(45);
#declare Camera_Vertical	= 30;				//22.5;
#declare Camera_Horizontal	= 30;				//30;
#declare Camera_Scale		= 1;
#declare Camera_Aspect		= image_height/image_width;
#declare Camera_Distance	= 64;
#declare Camera_Translate	= <0,0,0,>;			//<0,0,-city_size_total.y,>
#declare Camera_Scale		= 8;
#include "gh_camera.inc"

#declare Lightsys_Scene_Scale	= 100;
#declare light_color		= Light_Color(Daylight(5500),2.3);

#macro gamma_color_adjust(in_color)
	#local out_gamma = 2.2;
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

//------------------------------------------------------------------------------Global settings

default {finish {ambient 0 diffuse 1}}

global_settings
{
	#if (version < 3.7)
		assumed_gamma	1.0
	#end
	#if (!NoRadiosity)
		#include "rad_def.inc"
		radiosity {Rad_Settings(Radiosity_OutdoorLQ, off, off)}
	#end
	#switch (TexQual)
		#case (0)
			max_trace_level 4
		#break
		#case (1)
			max_trace_level 256
		#break
	#end
}

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
		[0.0	color rgb <0.85,0.85,0.85,>]
		[0.1	color rgb <0.75,0.75,0.75,>]
		[0.5	color rgb < 0.5, 0.6, 1.0 >]
		[1.0	color rgb < 0.5, 0.6, 1.0 >]
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
	color rgb <046,104,058,>/255/2
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


//------------------------------------------------------------------------------Lights

light_source
{
	<-15000, +15000, -15000> * <1/4,1,1/2>
	light_color
	translate 0
//	parallel
}


//------------------------------------------------------------------------------Sky


sphere
{
	0, 100000
	hollow
	pigment {color rgb < 0.5, 0.6, 1.0 >}
	no_shadow
}


//------------------------------------------------------------------------------City

#if (!NoCity)
	#declare city_strip = object
	{
		#include "CITY.inc"
		translate	x * 4
		translate	z * 4
	}
	// city buildings
	object
	{
		city_strip
/*
		#declare bend_object	= city_strip;
		#declare object_axis1	= -x * city_size_total.x/2;
		#declare object_axis2	= +x * city_size_total.x/2;
		#declare bend_direction	= +y;
		#declare bend_angle	= 15;
		#include "Bend.inc"
*/
	}
#end

cylinder
{
	-x*256,+x*256, 1/2
	pigment {color rgb x}
}
cylinder
{
	-y*256,+y*256, 1/2
	pigment {color rgb y}
}
cylinder
{
	-z*256,+z*256, 1/2
	pigment {color rgb z}
}
