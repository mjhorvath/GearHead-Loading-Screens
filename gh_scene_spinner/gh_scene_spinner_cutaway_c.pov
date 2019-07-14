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
//+SR0.5 +SC0.5

//------------------------------------------------------------------------------Variables

#version 3.7				// ommitting this seriously messes up the colors

#include "CIE.inc"			// http://www.ignorancia.org/en/index.php?page=Lightsys
#include "lightsys.inc"			// http://www.ignorancia.org/en/index.php?page=Lightsys
#include "lightsys_constants.inc"	// http://www.ignorancia.org/en/index.php?page=Lightsys
#include "math.inc"
#include "shapes.inc"
#include "shapesq.inc"
#include "finish.inc"
#include "metals.inc"
#include "colors.inc"
#include "glass.inc"

// inter-scene variables
#declare pov_version		= 1;					// 0 = 3.6; 1 = 3.7; 3.7 also has gamma adjustments in INI file
#declare Seed			= seed(8829464);
#declare Tiles			= 1;					// the default size of the scene, measured in tiles. Use this to zoom in/out.
#declare Sprite_Height		= 128;					// changes the camera's position. 0 for mecha, 1 for walls & terrain.
#declare Width			= 8;					// the default width of a tile.
#declare Subdivision		= 0;					// turn on/off mesh subdivision. This requires a special exe available on the Net.
#declare Included		= 1;					// tells any included files that they are being included.
#declare TexQual		= 1;
#declare Minimal		= 1;					// a minimal render with lots turned off

// toggles
#declare NoColors		= 0;
#declare NoAtmos		= 1;					// very slowwwww!!!
#declare NoCity			= 0;
#declare NoShips		= 0;
#declare NoRadiosity		= 1;					// ugly
#declare NoLights		= 0;
#declare NoShell		= 0;					// boolean, toggle outer shell, spokes and endcaps
#declare NoLamp			= 0;
#declare NoCars			= 0;
#declare NoStreet		= 0;
#declare NoDomes		= 0;
#declare NewTrain		= 1;					// boolean, use maglev instead of streetcars
#declare AlwaysReflect		= 0;					// used in citygen mostly
#declare ShowWhole		= 0;					// show the entire outer shell, not finished
#declare glass_hollow		= 0;					// boolean
#declare glass_thin		= 0;					// boolean
#declare bound_fit		= 1;
#declare debug_progress		= 1;					// boolean, see CityGen docs

#if (Minimal)
	#declare NoAtmos		= 1;				// very slowwwww!!!
	#declare NoShips		= 0;
	#declare NoRadiosity		= 1;				// ugly
	#declare NoLights		= 0;
	#declare NoShell		= 0;				// boolean, toggle outer shell, spokes and endcaps
	#declare NoLamp			= 1;
	#declare NoCars			= 1;
	#declare NoStreet		= 1;
	#declare NoDomes		= 1;
	#declare AlwaysReflect		= 0;				// used in citygen mostly
#end

// citygen variables
#declare city_night		= false;
#declare city_right_hand_drive	= false;
#declare city_default_objects	= false;
#declare city_use_mesh		= false;
#declare city_all_mesh		= false;
#declare city_tileable		= true;
#declare city_units		= 1;					// should not be used anywhere directly
#declare city_storey_height	= city_units * 4;			// for reference, people are roughly city_units * 2 units tall
#declare city_ped_density	= 1/64/city_units;			// is this being used?? it should be!
//#declare city_radius		= city_units * 256;
//#declare city_circum		= city_radius * 2 * pi;
#declare city_grass_height	= city_units / 4;			// too thin and it gets clipped by the pavement
#declare city_tree_height	= city_units * 12;
#declare total_lanes		= (NewTrain ? 2 : 3);			// in both directions, including half lanes for bikes (minimum 2)
#declare nominal_traffic_width	= city_units * (NewTrain ? 6 : 12);
#declare nominal_building_width	= city_units * 64;
#declare buildings_per_block	= <4,4>;				// 2D vector of integers
#declare city_block_count	= <2,4>;				// 2D vector of integers
#declare city_sections		= <3,1>;				// 2D vector of integers
#declare traffic_spacing	= city_units * 128;
#declare traffic_width		= nominal_traffic_width/total_lanes;
#declare traffic_lanes		= floor(total_lanes/2);			// in each direction...
#declare pavement_width		= city_units * 4;
#declare building_gap		= pavement_width * 2;
#declare building_width		= nominal_building_width - pavement_width * 2;
#declare min_building_height	= city_storey_height * 8;
#declare max_building_height	= city_storey_height * 16;
#declare building_height_turb	= 1;
#declare street_height		= 0;					// to do, may conflict with citygen...
#declare street_width		= nominal_traffic_width;
#declare rail_ped_thick		= city_units * 2/3;			// rail pedestal leg
#declare rail_width		= street_width/2;
#declare rail_height		= city_units * 4;
#declare rail_thick		= city_units/4;
#declare rail_plat_width	= street_width * 4/3;
#declare rail_cars_number	= 1;					// odd values only
#declare block_dist_x		= nominal_traffic_width + nominal_building_width * buildings_per_block.x;	// float, ignores city_tileable
#declare block_dist_z		= nominal_traffic_width + nominal_building_width * buildings_per_block.y;	// float, ignores city_tileable
#declare city_length		= block_dist_z * city_block_count.y * city_sections.y		// city blocks
				+ 2 * (nominal_traffic_width + nominal_building_width);		// end border grass
#declare city_circum		= block_dist_x * city_block_count.x * city_sections.x;		// float, the circumference of the spinner colony
#declare city_radius		= city_circum/2/pi;			// float, the radius of the spinner colony
#declare city_rotate		= 15;					// float, rotate the inner shell containing the city by this amount

// scene variables (mostly)
#local ring_length		= city_units * 128;
#local ring_gap			= city_units * 8;
#local dock_length		= city_units * 256;
#local habitat_length		= city_length + ring_gap * 2;
#local dock_start		= habitat_length/2 + ring_length;
#local totl_length		= habitat_length + ring_length + dock_length;
#local shell_radius		= city_radius + ring_gap * 2;
#local dock_radius		= shell_radius;
#local dome_radius		= city_units * 96;
#local dome_gap			= city_units * 16;
#local panel_gap		= city_units * 16;
#local panel_width		= city_units * 128;
#local panel_length		= city_units * 256;
#local panel_thick		= city_units/2;
#local panel_distance		= 576;
#local panel_number		= 8;
#local blinky_radius		= city_units * 2;
#local lamp_radius		= city_units * 4;			// float, the radius of the fusion lamp
#local lamp_length		= city_length;
#if (TexQual = 1)
	#local lamp_number = floor(lamp_length/32);
#else
	#local lamp_number = floor(lamp_length/64);
#end
#local spindle_radius		= 0;
#local Lightsys_Scene_Scale	= city_units * 100;			// 1 = 1cm
#local light_lumens		= 2;					// float
#local light_temp		= Daylight(6100);			// float
#local light_color		= Light_Color(light_temp,light_lumens);
#local planet_distance		= 385000000/10000;			// meters
#local planet_radius		=   6371000/10000;			// meters
#local sun_distance		= 149600000/10000;			// kilometers
#local sun_radius		=    695500/10000;			// kilometers


//------------------------------------------------------------------------------Camera

#declare Camera_Mode		= 3;					// 1 to 8; 1 = oblique; 2 = perspective; 3 = orthographic
#declare Camera_Diagonal	= cosd(45);
#declare Camera_Vertical	= 45;					//45;
#declare Camera_Horizontal	= asind(tand(30));			//30;
#declare Camera_Scale		= 1;
#declare Camera_Aspect		= image_height/image_width;
#declare Camera_Distance	= 128;
#declare Camera_Translate	= <0,-city_radius/2*4/4,-city_radius/2*6/4,>;			//<0,0,-city_size_total.y,>
#declare Camera_Scale		= 160;
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
#macro vstr_def(in_vector)
	concat("<", vstr(3,in_vector,",",0,-1), ">")
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
		#debug concat("\n======Already included \"", in_file, "\", skipping.\n")
	#else
		#debug concat("\n>>>>>>Starting to include \"", in_file, "\".\n")
		#include in_file
		#debug concat("\n<<<<<<Finished including \"", in_file, "\".\n")
	#end
#end
#macro verbose_parse_string(in_string)
	#debug concat("\nParsing \"", in_string, "\"\n")
	Parse_String(in_string)
#end


//------------------------------------------------------------------------------Common Textures & Objects

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
#local blinky_material = material
{
	texture {pigment {rgbt 1}}
	interior {media {emission x*10}}
}
#local blinky_sphere = sphere
{
	0, blinky_radius
	material {blinky_material}
	hollow
}
#declare atmos_material = material
{
	texture {pigment {color rgbt 1}}
	interior
	{
		media
		{
			scattering
			{ 
				4, <0.2,0.4,1.0>/10000	// crappy approximaion of TerraPOV value
				extinction	1
			}
			samples	1,1
			density
			{
				cylindrical
				poly_wave	0.25
				density_map
				{
					// should be based on city_units!!!
					[0	rgb 1]
					[1	rgb 0]
				}
				scale	city_radius
				rotate	x * 90
			}
		}
	}
}
// phong looks like crap
#declare white_metal_texture = texture
{
	pigment {gamma_color_adjust(<1,1,1>*8/8)}
	finish {ambient 0 diffuse 1}
//	finish {phong 1}
}
// phong looks like crap
#declare gray_metal_texture = texture
{
	pigment {gamma_color_adjust(<1,1,1>*1/2)}
	finish {ambient 0 diffuse 1}
//	finish {phong 1}
}
#declare yellow_metal_texture = texture
{
	pigment {gamma_color_adjust(<1,1,0>)}
	finish {ambient 0 diffuse 1}
//	finish {phong 1}
}
#declare green_metal_texture = texture
{
	pigment {gamma_color_adjust(<0,1,0>)}
	finish {ambient 0 diffuse 1}
//	finish {phong 1}
}
#declare cutaway_object = union
{
	plane {-y, 0	rotate +z * 15}
	plane {-y, 0	rotate -z * 15}
}
/*
#declare cutaway_object = union
{
	plane {-y, 0}
//	plane {-y, 0	rotate +z * 30}
//	plane {-y, 0	rotate -z * 30}
//	plane {+x, 0	rotate -z * 60}
	translate -y * city_units * 2
}
*/
#declare dome_texture = texture
{
	pigment { gamma_color_adjust(<1.000, 0.875, 0.575, 0.000, 0.500>) }
	finish
	{
		brilliance 2
		diffuse D_GoldA
		ambient A_GoldA
		reflection R_GoldA
		metallic M
		specular 0.20
		roughness 1/20
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
//		verbose_include("rad_def.inc", 0)
//		radiosity {Rad_Settings(Radiosity_OutdoorLight, off, off)}
		radiosity
		{
			pretrace_start 0.08
			pretrace_end 0.02
			count 20
			error_bound 1
			recursion_limit 1
			normal on
			brightness 0.8
			always_sample no
			gray_threshold 0.8
			media on
		}
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

#if (!NoLights)
	light_source
	{
		<-15000, +15000, -15000> * <1/4,1,1/2>
		gamma_color_adjust(light_color)
		translate -y * city_radius
		parallel
	}
#end
#if (NoRadiosity)
	sky_sphere {pigment {gamma_color_adjust(<223/255,230/255,255/255>)}}
#end


//------------------------------------------------------------------------------City

#if (!NoCity)
		union
		{
			//------------------------------------------------------------------------------Central Area
		
//			verbose_include("CG_UNIQUE_CURVED_MESH.INC", 0)		// not implemented yet
			verbose_include("CG_DEFAULT_CURVED_MESH.INC", 0)
			#if (!Minimal)
				verbose_include("CG_VEHICLES_CURVED_MESH.INC", 0)
				verbose_include("CG_PAVEMENT_CURVED_MESH.INC", 0)		// needs to be updated for new maglev system
				verbose_include("CG_PARK_CURVED_MESH.INC", 0)
				verbose_include("CG_SQUARE_CURVED_MESH.INC", 0)
				verbose_include("CG_NORMAL_CURVED_MESH.INC", 0)
			#end
			#local city_object = object {#include "CG_CITY_CURVED_MESH.inc"}
			object {city_object	rotate +z * city_rotate}
		
			//------------------------------------------------------------------------------End Parks
		
			#declare buildings_per_block	= <buildings_per_block.x,1,0,>;
			#declare city_block_count	= <city_block_count.x,1,0,>;
			verbose_include("CG_DEFAULT_CURVED_MESH.INC", 0)
			#if (!Minimal)
				verbose_include("CG_VEHICLES_CURVED_MESH.INC", 0)
				verbose_include("CG_PAVEMENT_CURVED_MESH.INC", 0)		// needs to be updated for new maglev system
				verbose_include("CG_PARK_CURVED_MESH.INC", 0)
			#end
			#local city_object = object {#include "CG_CITY_CURVED_MESH.inc"}
			object {city_object	rotate +z * city_rotate translate +z * (city_length - nominal_building_width - nominal_traffic_width)/2}
		
			#declare buildings_per_block	= <buildings_per_block.x,1,0,>;
			#declare city_block_count	= <city_block_count.x,1,0,>;
			verbose_include("CG_DEFAULT_CURVED_MESH.INC", 0)
			#if (!Minimal)
				verbose_include("CG_VEHICLES_CURVED_MESH.INC", 0)
				verbose_include("CG_PAVEMENT_CURVED_MESH.INC", 0)		// needs to be updated for new maglev system
				verbose_include("CG_PARK_CURVED_MESH.INC", 0)
			#end
			#declare NoCars			= 1;
			#declare NoStreet		= 1;
			#local city_object = object {#include "CG_CITY_CURVED_MESH.inc"}
			object {city_object	rotate +z * city_rotate translate -z * (city_length - nominal_building_width - nominal_traffic_width)/2}
		}
#end


//------------------------------------------------------------------------------Shell

#if (!NoShell)
	difference
	{
		union
		{

			//------------------------------------------------------------------------------Outer Shell & Mid Walls

			// outer shell
			#local shell_a = cylinder
			{
				-z*(habitat_length/2+ring_length), +z*(habitat_length/2), shell_radius
			}
			#local shell_b = cylinder
			{
				-z*(city_length*10), +z*(city_length*10), shell_radius-city_units*4
			}
			// large gray cylinder end cap
			#local cap_1 = cylinder
			{
				-z*city_units, +z*city_units, shell_radius
			}
			// inner lozenge cutout 2
			#local cap_cutout_2 = cylinder
			{
				-z*city_units*3, +z*city_units*3, shell_radius/5
			}
			#local cap_cutout_2b = union
			{
				object {cap_cutout_2	translate -y * shell_radius/2	rotate z * 000}
				object {cap_cutout_2	translate -y * shell_radius/2	rotate z * 060}
				object {cap_cutout_2	translate -y * shell_radius/2	rotate z * 120}
				object {cap_cutout_2	translate -y * shell_radius/2	rotate z * 180}
				object {cap_cutout_2	translate -y * shell_radius/2	rotate z * 240}
				object {cap_cutout_2	translate -y * shell_radius/2	rotate z * 300}
			}
			// inner lozenge glass 2
			#local cap_glass_2 = difference
			{
				sphere
				{
					0, shell_radius/5*0.999
					scale z * 4/8
				}
				sphere
				{
					0, shell_radius/5*0.999
					scale z * 3/8
				}
				plane {-z,0}
			}
			#local cap_glass_2b = union
			{
				object {cap_glass_2	translate -y * shell_radius/2	rotate z * 000}
				object {cap_glass_2	translate -y * shell_radius/2	rotate z * 060}
				object {cap_glass_2	translate -y * shell_radius/2	rotate z * 120}
				object {cap_glass_2	translate -y * shell_radius/2	rotate z * 180}
				object {cap_glass_2	translate -y * shell_radius/2	rotate z * 240}
				object {cap_glass_2	translate -y * shell_radius/2	rotate z * 300}
			}
			// end cap bevel
			#local cap_hub_r8 = cylinder {-z*city_units*2, +z*city_units*2, shell_radius*8/9}
			#local cap_hub_r7 = cylinder {-z*city_units*2, +z*city_units*2, shell_radius*7/9}
			#local cap_hub_r6 = cylinder {-z*city_units*2, +z*city_units*2, shell_radius*6/9}
			#local cap_hub_r3 = cylinder {-z*city_units*2, +z*city_units*2, shell_radius*3/9}
			#local cap_hub_r2 = cylinder {-z*city_units*2, +z*city_units*2, shell_radius*2/9}
			#local cap_hub_r1 = cylinder {-z*city_units*2, +z*city_units*2, shell_radius*1/9}

			#local cap_object_a = union
			{
				difference
				{
					object {cap_1}
					object {cap_cutout_2b}
				}
				difference
				{
					object {cap_hub_r7}
					object {cap_hub_r6	scale 1.0001}
				}
				difference
				{
					object {cap_hub_r3}
					object {cap_hub_r2	scale 1.0001}
				}
				object {cap_hub_r1}
			}
			#local cap_object_b = union
			{
				object {cap_1}
				difference
				{
					object {cap_hub_r7}
					object {cap_hub_r6	scale 1.0001}
				}
				difference
				{
					object {cap_hub_r3}
					object {cap_hub_r2	scale 1.0001}
				}
				object {cap_hub_r1}
			}
			difference
			{
				object {shell_a}
				object {shell_b}
				texture {white_metal_texture}
			}
			union
			{

				object {cap_object_a	translate +z*(dock_start-ring_length)}
				object {cap_object_b	translate -z*(dock_start-ring_length)}
				object {cap_object_b	translate -z*(dock_start)}
				object {cap_object_b	scale <1,1,1> translate -z*(dock_start+dock_length)}	// was <3/4,3/4,1>
				texture {white_metal_texture}
			}

			//------------------------------------------------------------------------------Inner Shell & End Caps

			// this stuff really needs to be double-checked to make sure things line up correctly

			// inner shell
			#local shell_a = cylinder
			{
				-z*(city_length/2-city_units*1), +z*(city_length/2-city_units*1), city_radius + city_units*2
			}
			#local shell_b = cylinder
			{
				-z*(city_length/2-city_units*3), +z*(city_length/2-city_units*3), city_radius + city_units*1
			}
			#local cap_letter_a =	text {ttf "space age.ttf" "A" 1, 0}
			#local cap_letter_b =	text {ttf "space age.ttf" "B" 1, 0}

			union
			{
				difference
				{
					object {shell_a}
					object {shell_b}
					// side a
					object {cap_cutout_2b	translate +z*(city_length/2-city_units*2)}
					object
					{
						cap_letter_a
						Center_Trans(cap_letter_a, x)
						Center_Trans(cap_letter_a, y)
						Center_Trans(cap_letter_a, z)
						scale <shell_radius/6,shell_radius/6,city_units>
						translate -y*shell_radius/2
						translate +z*(city_length/2-city_units*3)
						rotate z * -30
					}
					object
					{
						cap_letter_b
						Center_Trans(cap_letter_b, x)
						Center_Trans(cap_letter_b, y)
						Center_Trans(cap_letter_b, z)
						scale <shell_radius/6,shell_radius/6,city_units>
						translate -y*shell_radius/2
						translate +z*(city_length/2-city_units*3)
						rotate z * +30
					}
					// side b
					object {cap_cutout_2b	translate -z*(dock_start-city_units*2)}
					object
					{
						cap_letter_a
						Center_Trans(cap_letter_a, x)
						Center_Trans(cap_letter_a, y)
						Center_Trans(cap_letter_a, z)
						scale <shell_radius/6,shell_radius/6,city_units>
						translate -y*shell_radius/2
						translate -z*(city_length/2-city_units*3)
						rotate z * -30
					}
					object
					{
						cap_letter_b
						Center_Trans(cap_letter_b, x)
						Center_Trans(cap_letter_b, y)
						Center_Trans(cap_letter_b, z)
						scale <shell_radius/6,shell_radius/6,city_units>
						translate -y*shell_radius/2
						translate -z*(city_length/2-city_units*3)
						rotate z * +30
					}
				}
				union
				{
					// side a
					difference
					{
						object {cap_hub_r8}
						object {cap_hub_r7	scale 1.0001}
						translate +z*(city_length/2-city_units*2)
					}
					difference
					{
						object {cap_hub_r2}
						object {cap_hub_r1	scale 1.0001}
						translate +z*(city_length/2-city_units*2)
					}

					// side b
					difference
					{
						object {cap_hub_r8}
						object {cap_hub_r7	scale 1.0001}
						translate -z*(city_length/2-city_units*2)
					}
					difference
					{
						object {cap_hub_r2}
						object {cap_hub_r1	scale 1.0001}
						translate -z*(city_length/2-city_units*2)
					}
				}
				// side a
				object
				{
					cap_glass_2b
					translate +z*(city_length/2-city_units*2)
					#if (!NoDomes)
						texture {dome_texture}
					#end
				}
/*
				// side b
				object
				{
					cap_glass_2b
					translate -z*(dock_start-city_units*2)
					#if (!NoDomes)
						texture {dome_texture}
					#end
				}
*/
				texture {white_metal_texture}
				rotate +z * city_rotate
			}

			//------------------------------------------------------------------------------Compact Ring

			union
			{
				#local ring_max = 6;
				#local ring_cnt = 0;
				#while (ring_cnt < ring_max)
					difference
					{
						cylinder {-z*(habitat_length/2+ring_gap-city_units),-z*(city_length/2+ring_length+city_units),city_radius-city_storey_height*ring_cnt*10+city_units}
						cylinder {-z*(habitat_length/2+ring_gap+city_units),-z*(city_length/2+ring_length-city_units),city_radius-city_storey_height*ring_cnt*10-city_units}
					}
					#local ring_cnt = ring_cnt + 1;
				#end
				#local ring_max = 50;
				#local ring_cnt = 0;
				#while (ring_cnt < ring_max)
					difference
					{
						cylinder {-z*(habitat_length/2+ring_gap-city_units),-z*(city_length/2+ring_length+city_units),city_radius-city_storey_height*ring_cnt+city_units/4}
						cylinder {-z*(habitat_length/2+ring_gap+city_units),-z*(city_length/2+ring_length-city_units),city_radius-city_storey_height*ring_cnt-city_units/4}
					}
					#local ring_cnt = ring_cnt + 1;
				#end
				texture {white_metal_texture}
			}

			//------------------------------------------------------------------------------Cargo and Shiphold

			#local decal_texture = texture
			{
				gradient x
				texture_map
				{
					[0/2 yellow_metal_texture]
					[1/2 yellow_metal_texture]
					[1/2 pavement_texture]
					[2/2 pavement_texture]
				}
				rotate y * 45
				scale city_units*8
			}
			#local dock_texture = texture
			{
				brick
				texture {decal_texture}
				texture {pavement_texture}
				brick_size dock_length/6
				mortar city_units*2
				translate (+x+z)*city_units*1
				translate (+x)*dock_length/12
//				translate -y*city_units*2
			}

			#local dock_labels = polygon
			{
				4, <0,0>,<0,1>,<1,1>,<1,0>
				scale <dock_length,shell_radius*2,1>
				pigment
				{
					image_map {png "spinner_lot_text.png"}
					scale <dock_length,dock_length*9/6,1>
				}
				rotate x * 90
				rotate y * 90
				translate z * (-dock_start)
				translate x * (-shell_radius)
				translate (-x-z)*city_units*4
			}
			object {dock_labels	translate y * (-dock_radius*1/4+city_units+0.1)}
			object {dock_labels	translate y * (-dock_radius*2/4+city_units+0.1)}
			difference
			{
				cylinder {<0,0,0>, <0,0,-dock_length>, dock_radius-city_units*4}
				box {<-dock_radius*2,+dock_radius*1/4-city_units,-dock_length>,<+dock_radius*2,+dock_radius*0/4+city_units,0>}
				box {<-dock_radius*2,+dock_radius*2/4-city_units,-dock_length>,<+dock_radius*2,+dock_radius*1/4+city_units,0>}
				box {<-dock_radius*2,+dock_radius*3/4-city_units,-dock_length>,<+dock_radius*2,+dock_radius*2/4+city_units,0>}
//				box {<-dock_radius*2,+dock_radius*4/4+city_units,-dock_length>,<+dock_radius*2,+dock_radius*3/4+city_units,0>}
				box {<-dock_radius*2,-dock_radius*1/4+city_units,-dock_length>,<+dock_radius*2,-dock_radius*0/4-city_units,0>}
				box {<-dock_radius*2,-dock_radius*2/4+city_units,-dock_length>,<+dock_radius*2,-dock_radius*1/4-city_units,0>}
				box {<-dock_radius*2,-dock_radius*3/4+city_units,-dock_length>,<+dock_radius*2,-dock_radius*2/4-city_units,0>}
//				box {<-dock_radius*2,-dock_radius*4/4-city_units,-dock_length>,<+dock_radius*2,-dock_radius*3/4-city_units,0>}
				box {<-dock_length/3,-dock_radius*4/4-city_units,-dock_length>,<+dock_length/3,+dock_radius*3/3+city_units,-dock_length*5/6>}
				box {<-dock_length/3,-dock_radius*4/4-city_units,-dock_length*1/6>,<+dock_length/3,+dock_radius*3/3+city_units,0>}
//				texture {dock_texture}
				texture {pavement_texture}
				scale 0.999
				translate -z*dock_start
			}
			difference
			{
				cylinder {<0,0,0>, <0,0,-dock_length>, dock_radius}
				cylinder {<0,+1,0>, <0,0,-dock_length-1>, dock_radius-city_units*4}
				box {<-dock_radius*2,+dock_radius*1/4-city_units,-dock_length>,<+dock_radius*2,+dock_radius*0/4+city_units,0>}
				box {<-dock_radius*2,+dock_radius*2/4-city_units,-dock_length>,<+dock_radius*2,+dock_radius*1/4+city_units,0>}
				box {<-dock_radius*2,+dock_radius*3/4-city_units,-dock_length>,<+dock_radius*2,+dock_radius*2/4+city_units,0>}
//				box {<-dock_radius*2,+dock_radius*4/4+city_units,-dock_length>,<+dock_radius*2,+dock_radius*3/4+city_units,0>}
				box {<-dock_radius*2,-dock_radius*1/4+city_units,-dock_length>,<+dock_radius*2,-dock_radius*0/4-city_units,0>}
				box {<-dock_radius*2,-dock_radius*2/4+city_units,-dock_length>,<+dock_radius*2,-dock_radius*1/4-city_units,0>}
				box {<-dock_radius*2,-dock_radius*3/4+city_units,-dock_length>,<+dock_radius*2,-dock_radius*2/4-city_units,0>}
//				box {<-dock_radius*2,-dock_radius*4/4-city_units,-dock_length>,<+dock_radius*2,-dock_radius*3/4-city_units,0>}
				box {<-dock_length/3,-dock_radius*4/4-city_units,-dock_length>,<+dock_length/3,+dock_radius*3/3+city_units,-dock_length*5/6>}
				box {<-dock_length/3,-dock_radius*4/4-city_units,-dock_length*1/6>,<+dock_length/3,+shell_radius*3/3+city_units,0>}
//				texture {dock_texture}
				texture {white_metal_texture}
				translate -z*dock_start
			}
/*
			object {blinky_sphere	translate <0,-dock_radius*1/3+city_units,-dock_start-dock_length/2>}
			object {blinky_sphere	translate <-dock_length*1/3,-dock_radius*1/4+city_units,-dock_start-dock_length/2>}
			object {blinky_sphere	translate <-dock_length*2/3,-dock_radius*1/4+city_units,-dock_start-dock_length/2>}
			object {blinky_sphere	translate <+dock_length*1/3,-dock_radius*1/4+city_units,-dock_start-dock_length/2>}
			object {blinky_sphere	translate <+dock_length*2/3,-dock_radius*1/4+city_units,-dock_start-dock_length/2>}

			object {blinky_sphere	translate <-dock_length*1/3,-dock_radius*1/4+city_units,-dock_start-dock_length/2+dock_length/6>}
			object {blinky_sphere	translate <-dock_length*2/3,-dock_radius*1/4+city_units,-dock_start-dock_length/2+dock_length/6>}
			object {blinky_sphere	translate <+dock_length*1/3,-dock_radius*1/4+city_units,-dock_start-dock_length/2+dock_length/6>}
			object {blinky_sphere	translate <+dock_length*2/3,-dock_radius*1/4+city_units,-dock_start-dock_length/2+dock_length/6>}

			object {blinky_sphere	translate <-dock_length*1/3,-dock_radius*1/4+city_units,-dock_start-dock_length/2-dock_length/6>}
			object {blinky_sphere	translate <-dock_length*2/3,-dock_radius*1/4+city_units,-dock_start-dock_length/2-dock_length/6>}
			object {blinky_sphere	translate <+dock_length*1/3,-dock_radius*1/4+city_units,-dock_start-dock_length/2-dock_length/6>}
			object {blinky_sphere	translate <+dock_length*2/3,-dock_radius*1/4+city_units,-dock_start-dock_length/2-dock_length/6>}
*/
		}
		#if (!ShowWhole)
			object {cutaway_object}
		#end
//		texture {white_metal_texture}
		pigment {gamma_color_adjust(<1/2,1/2,1/2>)}
	}

	//------------------------------------------------------------------------------Ring Glass

	#local ring_glass_mat = material
	{
		interior {ior 2.5}
		texture
		{
			pigment {gamma_color_adjust(<.5,.5,.5,.0,.7>)}
			normal {bumps .05 scale .1}
			finish {specular .5 roughness .1 reflection <.3, .4, .5>}
		}
		scale city_units
	}
	difference
	{
		cylinder {-z*(habitat_length/2+ring_gap-city_units),-z*(city_length/2+ring_length+city_units),city_radius}
		cylinder {-z*(habitat_length/2+ring_gap-city_units),-z*(city_length/2+ring_length+city_units),city_radius-city_storey_height*50}
		object {cutaway_object}
		scale <0.99,0.99,1>
		material {ring_glass_mat}
	}

	//------------------------------------------------------------------------------Lamp & Spindles

	#if (!NoLamp)
		#local spindle_arm = cylinder
		{
			0, +y*city_radius, city_units*2
		}
		#local spindle_hub = union
		{
			difference
			{
				union
				{
					object {spindle_arm rotate z * 030}
					object {spindle_arm rotate z * 090}
					object {spindle_arm rotate z * 150}
					object {spindle_arm rotate z * 210}
					object {spindle_arm rotate z * 270}
					object {spindle_arm rotate z * 330}
				}
				cylinder {-z*city_radius, +z*city_radius, city_units * 16}
			}
			torus
			{
				city_units * 16, city_units*2
				rotate x * 90
			}
			texture {white_metal_texture}
		}
		object {spindle_hub	translate -z * lamp_length/4}
		object {spindle_hub	translate +z * lamp_length/4}
	#end

	#if (!NoLamp)
		#local lamp_material = material
		{
			texture {pigment {rgbt 1}}
			interior
			{
				media
				{
					emission gamma_color_adjust(Light_Color(light_temp,light_lumens))
					density
					{
						cylindrical
						color_map
						{
							[0 rgb 0]
							[1 rgb 1]
						}
						scale	lamp_radius
						rotate	x * 90
					}
				}
			}
		}

		#local lamp_guard_a = cylinder {-z*city_units*4, +z*city_units*4, lamp_radius * 1.1}
		#local lamp_guard_b = cylinder {0, +z*city_units*4, lamp_radius * 1.1}
		#local lamp_guard_c = cylinder {-z*city_units*4, 0, lamp_radius * 1.1}
		object
		{
			cylinder {z*-(lamp_length/2), z*+(lamp_length/2), lamp_radius}
			material {lamp_material}
			#if (TexQual = 1)	hollow	#end
			scale	0.9999
			no_shadow
		}
		union
		{
			object {lamp_guard_b	translate -z * lamp_length/2}
			object {lamp_guard_a	translate -z * lamp_length/4}
			object {lamp_guard_c	translate +z * lamp_length/2}
			object {lamp_guard_a	translate +z * lamp_length/4}
			pigment {gamma_color_adjust(<1/2,1/2,1/2>)}
		}
	#end

	//------------------------------------------------------------------------------Reactor Core

	union
	{
		#local ball_radius = city_units * 16;
		#local ball_center = habitat_length/2+ring_length/2;
		#local trumpet_length = ring_length/2-ball_radius-ring_gap;
		#include "param.inc"
		#declare Fx = function(u,v) {v}
		#declare Fy = function(u,v) {city_units*16/pow(v+1,0.7)*cos(u)}
		#declare Fz = function(u,v) {city_units*16/pow(v+1,0.7)*sin(u)}
		object
		{
			Parametric(Fx,Fy,Fz,<0,0>,<2*pi,trumpet_length>,30,30,"")
			rotate -y * 90
			translate -z*(ball_center+city_units*2-ball_radius)
		}
		object
		{
			Parametric(Fx,Fy,Fz,<0,0>,<2*pi,trumpet_length>,30,30,"")
			rotate +y * 90
			translate -z*(ball_center-city_units*2+ball_radius)
		}
		sphere
		{
			0, ball_radius*5/4
			translate -z*(ball_center)
		}
//		torus
//		{
//			ball_radius*3, ball_radius*3/4
//			rotate x * 90
//			translate -z*(ball_center)
//		}
		texture
		{
			white_metal_texture
//			finish {reflection 1}
		}
	}


	//------------------------------------------------------------------------------Ships & Bay Contents

	#if (!NoShips)

		// vehicles
		verbose_include("Raumschiff5.inc", 0)
		#local raums_object	= Raumschiff5;
		#local raums_min	= min_extent(raums_object);
		#local raums_max	= max_extent(raums_object);
		#local raums_box	= raums_max - raums_min;
		#local raums_nrm	= vnormalize(raums_box);
		#local raums_object = object
		{
			raums_object
			translate	-raums_min
			scale		1/raums_box
			translate	<-1/2,0,-1/2>
			scale		raums_nrm * 2
			rotate		y * 180
			scale		32
			scale		z * 3/2
			translate	z * 2
			bounded_by {box {<-32,0,-32>, <+32,+32,+32>}}
			#if (!AlwaysReflect)	no_reflection 	#end	// for sanity's sake!!!
			scale 1
		}
		object
		{
			raums_object
			translate -z * (dock_start+dock_length*1/2)
			translate -y * dock_radius*1/4
			translate +y * city_units
			translate -x * dock_length*2/3
		}
	
		verbose_include("ara_kojedo.pov", 0)
		object
		{
			ara_kojedo_
			translate <18.42348,0,-364.0902> * -1
			scale 1/375
			//edit below
			scale 10 * city_units
			translate -z * (dock_start+dock_length*7/12)
			translate -y * dock_radius*1/4
			translate +y * city_units
			translate +x * dock_length*9/12
		}
		verbose_include("btr_maanji.pov", 0)
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
			rotate y * 360 * rand(Seed)
			scale 18 * city_units
			translate -z * (dock_start+dock_length*3/12)
			translate -y * dock_radius*1/4
			translate +y * city_units
			translate +x * dock_length*1/12
		}
		verbose_include("btr_vadel.pov", 0)
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
			rotate y * 360 * rand(Seed)
			scale 16 * city_units
			translate -z * (dock_start+dock_length*3/12)
			translate -y * dock_radius*1/4
			translate +y * city_units
			translate -x * dock_length*5/12
		}

		verbose_include("Horus.inc", 0)
		#local horus_object	= Horus;
		#local horus_min	= min_extent(horus_object);
		#local horus_max	= max_extent(horus_object);
		#local horus_box	= horus_max - horus_min;
		#local horus_nrm	= vnormalize(horus_box);
		#local horus_object = object
		{
			horus_object
			translate	-horus_min
			scale		1/horus_box
			translate	<-1/2,0,-1/2>
			scale		horus_nrm * 2
			rotate		y * 360 * rand(Seed)
			scale		6
			translate	y
			scale		2 * city_units
			bounded_by {box {<-16,0,-16>, <+16,+32,+16>}}
			#if (!AlwaysReflect)	no_reflection 	#end	// for sanity's sake!!!
		}
		object
		{
			horus_object
			translate -z * (dock_start+dock_length*9/12)
			translate -y * dock_radius*1/4
			translate +y * city_units
			translate -x * dock_length*5/12
		}

		// cargo containers
		#local cargo_pigment = pigment
		{
			checker
			gamma_color_adjust(<0,0,0>),
			gamma_color_adjust(<1/2,1/2,1/2>)
			scale city_units
		}
		#local cargo_box = box
		{
			<-city_units,0,-city_units>,
			<+city_units,+city_units*2,+city_units>
			pigment {cargo_pigment}
		}

		#local cargo_max = 8;
		#local cargo_cnt = 0;
		#while (cargo_cnt < cargo_max)
			#local cargo_rand = rand(Seed);
			object
			{
				union
				{
					object {cargo_box		rotate y * (rand(Seed) * 30 - 15)	translate <0,0,+city_units> * 1.2}
					#if (cargo_rand > 1/4)
						object {cargo_box	rotate y * (rand(Seed) * 30 - 15)	translate <-city_units,0,-city_units> * 1.2}
					#end
					#if (cargo_rand > 2/4)
						object {cargo_box	rotate y * (rand(Seed) * 30 - 15)	translate <+city_units,0,-city_units> * 1.2}
					#end
					#if (cargo_rand > 3/4)
						object {cargo_box	rotate y * (rand(Seed) * 30 - 15)	translate <0,city_units*2,0>}
					#end
				}
				rotate y * 360 * rand(Seed)
				translate -z * (dock_start + dock_length/6 + dock_length/3*rand(Seed))
				translate -x * (dock_length/3*rand(Seed))
				translate -y * (dock_radius*1/4)
				translate +y * (city_units)
			}
			#local cargo_cnt = cargo_cnt + 1;
		#end

		// people (not rendering??)
		#local people_max = 8;
		#local people_cnt = 0;
		#while (people_cnt < people_max)
			object
			{
				ped_macro(Seed)
				translate -z * (dock_start + dock_length/6 + dock_length/3*rand(Seed))
				translate -x * (dock_length/3*rand(Seed))
				translate -y * (dock_radius*1/4)
				translate +y * (city_units)
			}
			#local people_cnt = people_cnt + 1;
		#end

		// fuel tanks
		union
		{
			object
			{
				fuel_tank(city_units*8,city_units*4)
				rotate x * 90
				translate +y*city_units*8
				translate -x*(dock_length/3+city_units*16)
				translate -z*(dock_start+city_units*8)
			}
			object
			{
				fuel_tank(city_units*8,city_units*4)
				rotate x * 90
				translate +y*city_units*8
				translate -x*(dock_length/3+city_units*24)
				translate -z*(dock_start+city_units*8)
			}
			object
			{
				fuel_tank(city_units*8,city_units*4)
				rotate x * 90
				translate +y*city_units*8
				translate +x*(dock_length/3+city_units*16)
				translate -z*(dock_start+city_units*8)
			}
			object
			{
				fuel_tank(city_units*8,city_units*4)
				rotate x * 90
				translate +y*city_units*8
				translate +x*(dock_length/3+city_units*24)
				translate -z*(dock_start+city_units*8)
			}
			translate -y*dock_radius*1/4
			texture {yellow_metal_texture}
		}
		union
		{
			object
			{
				fuel_tank(city_units*8,city_units*4)
				rotate x * 90
				translate +y*city_units*8
				translate -x*(dock_length/3+city_units*16)
				translate -z*(dock_start+city_units*8)
			}
			object
			{
				fuel_tank(city_units*8,city_units*4)
				rotate x * 90
				translate +y*city_units*8
				translate -x*(dock_length/3+city_units*24)
				translate -z*(dock_start+city_units*8)
			}
			object
			{
				fuel_tank(city_units*8,city_units*4)
				rotate x * 90
				translate +y*city_units*8
				translate +x*(dock_length/3+city_units*16)
				translate -z*(dock_start+city_units*8)
			}
			object
			{
				fuel_tank(city_units*8,city_units*4)
				rotate x * 90
				translate +y*city_units*8
				translate +x*(dock_length/3+city_units*24)
				translate -z*(dock_start+city_units*8)
			}
			translate -y*dock_radius*2/4
			texture {yellow_metal_texture}
		}

		// robo-arm
		union
		{
			cylinder {0, <0,4,0>, 16}
			cylinder {0, <0,12,0>, 8}
			union
			{
				cylinder {<0,0,0>, <128,0,0>, 8 scale y * 1/2}
				cylinder {<128,-4,0>, <128,12,0>, 8}
				union
				{
					cylinder {<-128,0,0>, <0,0,0>, 8 scale y * 1/2}
					cylinder {<-128,-4,0>, <-128,12,0>, 8}
					cylinder {<-96,-4,0>, <-96,4,0>, 8}
					union
					{
						cone {y*4, 2, y*12, 0 translate z*4 rotate x * 15 rotate y * 000}
						cone {y*4, 2, y*12, 0 translate z*4 rotate x * 15 rotate y * 120}
						cone {y*4, 2, y*12, 0 translate z*4 rotate x * 15 rotate y * 240}
						translate y * 8
						translate x * -128
					}
					translate y * 8
					rotate -y * 15
					translate x * 128
				}
				translate y * 8
				rotate +y * 15
			}
			texture {white_metal_texture}
			rotate -x*90
			scale city_units/2
			translate -y*dock_radius/6
			translate -z*(dock_start+city_units*2)
		}

		// rafters
		#declare rafter_object_a = union
		{
			#declare truss_sides = 3;
			#declare truss_sections = 8;
			#declare truss_radius = city_units*4;
			#declare truss_thickness = city_units/4;
			#declare truss_point1 = -x*city_units*120;
			#declare truss_point2 = +x*city_units*120;
			object
			{
				#include "truss.inc"
				rotate +x * 30
				translate -z*(dock_start+dock_length*1/4)
				translate -y*(lamp_radius*2)
			}
			object
			{
				#include "truss.inc"
				rotate +x * 30
				translate -z*(dock_start+dock_length*2/4)
				translate -y*(lamp_radius*2)
			}
			object
			{
				#include "truss.inc"
				rotate +x * 30
				translate -z*(dock_start+dock_length*3/4)
				translate -y*(lamp_radius*2)
			}
/*
			#declare truss_point1 = -z*dock_length/2;
			#declare truss_point2 = +z*dock_length/2;
			object
			{
				#include "truss.inc"
				rotate +x * 30
				translate -z*(dock_start+dock_length/2)
				translate -y*(lamp_radius*2)
				translate -x*(city_units*160)
			}
*/
			texture {yellow_metal_texture}
		}
		#declare rafter_object_b = union
		{
			#declare truss_sides = 3;
			#declare truss_sections = 16;
			#declare truss_radius = city_units*4;
			#declare truss_thickness = city_units/4;
			#declare truss_point1 = -x*city_units*240;
			#declare truss_point2 = +x*city_units*240;
			object
			{
				#include "truss.inc"
				rotate +x * 30
				translate -z*(dock_start+dock_length*1/4)
				translate -y*(lamp_radius*2)
			}
			object
			{
				#include "truss.inc"
				rotate +x * 30
				translate -z*(dock_start+dock_length*2/4)
				translate -y*(lamp_radius*2)
			}
			object
			{
				#include "truss.inc"
				rotate +x * 30
				translate -z*(dock_start+dock_length*3/4)
				translate -y*(lamp_radius*2)
			}
/*
			#declare truss_point1 = -z*dock_length/2;
			#declare truss_point2 = +z*dock_length/2;
			object
			{
				#include "truss.inc"
				rotate +x * 30
				translate -z*(dock_start+dock_length/2)
				translate -y*(lamp_radius*2)
				translate -x*(city_units*160)
			}
*/
			cylinder
			{
				-z*dock_length*1/8,+z*dock_length*1/8,city_units*1
				translate -z*(dock_start+dock_length*3/8)
				translate -y*(lamp_radius*2+city_units*4)
				translate -x*(city_units*64)
				pigment {color rgb <0,0,0>}
			}
			cylinder
			{
				-z*dock_length*1/8,+z*dock_length*1/8,city_units*1
				translate -z*(dock_start+dock_length*5/8)
				translate -y*(lamp_radius*2+city_units*4)
				translate +x*(city_units*64)
				pigment {color rgb <0,0,0>}
			}
			translate -y*(dock_radius*1/4)
			texture {yellow_metal_texture}
		}
		object {rafter_object_a}
		object {rafter_object_b}

		// gantry
		#declare gantry_object = union
		{
			//y
			box {<-12,+00,-30>, <-10,+36,-28>}
			box {<+12,+00,-30>, <+10,+36,-28>}
			box {<+12,+00,+30>, <+10,+36,+28>}
			box {<-12,+00,+30>, <-10,+36,+28>}
			//top
			box {<-12,+36,+30>, <+12,+34,+28>}
			box {<-12,+36,-30>, <+12,+34,-28>}
			box {<-12,+36,-30>, <-10,+30,+30>}
			box {<+12,+36,-30>, <+10,+30,+30>}
			//bottom
			box {<-12,+02,+30>, <+12,+03,+28>}
			box {<-12,+02,-30>, <+12,+03,-28>}
			box {<-12,+12,+30>, <+12,+13,+28>}
			box {<-12,+12,-30>, <+12,+13,-28>}
			scale 1/30
			scale city_units * 16
		}
		object
		{
			gantry_object
			rotate y*15
			translate -y*(dock_radius*1/4-city_units)
			translate -z*(city_length/2+ring_length+dock_length*1/4)
			translate +x*(dock_radius*3/4)
			texture {yellow_metal_texture}
		}
	#end

	//------------------------------------------------------------------------------Agri Domes & Tanks

	#if (!NoDomes)

		// grass setup
		verbose_include("grasspatch.inc", 0)
		#local someseed			= seed(2345);
		#local xseed			= seed(422);
		#local zseed			= seed(369);
		#local Patch_Tranlation		= <0,0,0>;
		#local PlotPoints		= false;
		#local Blade_Density		= 8;		// per unit length. Square this to know how many will be in each unit squared of landscape
		#local Patch_Shape		= 0;		// Circular
		#local Spread_Correction	= 0.9;
		#local Blade_Height_Minimum	= 1/2;		// Blade_Heights are in standard POV units
		#local Blade_Height_Maximum	= 1;
		#local Use_Blade_Distance	= true;
		#local Blade_Detail		= 4;
		#local Max_Blade_Angle		= 0;
		#local Min_Blade_Angle		= 0;
		#local Blade_Scale		= 0.5;
		#local Blade_Width		= 0.1;
		#local Use_Blade_Distance	= true;
		#local Max_Blade_Detail		= 20;
		#local Min_Blade_Detail		= 5;
		#local Max_Detail_Distance	= 1;
		#local Min_Detail_Distance	= 10;
		#local Blade_Tex = texture			// And of course the texture. This is the default:
		{
			pigment {gamma_color_adjust(<64/255,104/255,72/255,> * 2)}
		}

		// dome setup
		#local N			= 2;
		#local Half			= 1;
		#local Method			= 1;
		#local Disc			= 0;
		#local R_Ten			= 0.01 / N;
		#local R_Hen			= 0.01 / N;
		verbose_include("sphere.inc", 0)
		#local RibTexture		= texture {white_metal_texture}
		#local PaneTexture		= texture {dome_texture}
		#local DirtTexture		= texture
		{
			pigment
			{
				wrinkles
				color_map
				{
					[0 gamma_color_adjust(1/4*<1,1,1>)]
					[1 gamma_color_adjust(0/4*<1,1,1>)]
				}
			}
		}
		#local dome_object = union
		{
			object {Ten		texture {RibTexture}}
			object {Hen		texture {RibTexture}}
			object {Men		texture {PaneTexture}}
			cylinder {-y/16,0,1	texture {RibTexture}}
			cylinder {0,+y/128,1	texture {DirtTexture}}

		}
		#local dome_plants = union
		{
			PlantPatch()
			scale	1/2 * 0.9
			scale	y*2/3
		}

		#local dome_max = 4;
		#local dome_cnt = 0;
		#while (dome_cnt < dome_max)
			#local dome_trans_a = <0,-shell_radius,-dome_radius*3+dome_cnt*(dome_radius*2+dome_gap)>;
			#local dome_trans_b = <0,-shell_radius,-dome_radius*3+dome_cnt*(dome_radius*2+dome_gap)>;
			union
			{
				object {dome_object}
				object {dome_plants	rotate	y * rand(Seed) * 360}
				rotate		-z * 180
				scale		dome_radius
				translate	dome_trans_a
				rotate		-z * 060
			}
			#if (ShowWhole)
				union
				{
					object {dome_object}
					object {dome_plants	rotate	y * rand(Seed) * 360}
					rotate		+z * 180
					scale		dome_radius
					translate	dome_trans_b
					rotate		-z * 180
				}
			#end
			union
			{
				object {dome_object}
				object {dome_plants	rotate	y * rand(Seed) * 360}
				rotate		+z * 180
				scale		dome_radius
				translate	dome_trans_b
				rotate		-z * 300
			}
			#local dome_cnt = dome_cnt + 1;
		#end

		#local dome_tank = object
		{
			fuel_tank(city_length/4,dome_radius/2)
			translate -y*(shell_radius+dome_radius/2)
		}
		union
		{
			object {dome_tank		rotate -z * 030}
			#if (ShowWhole)
				object {dome_tank	rotate -z * 090}
				object {dome_tank	rotate -z * 150}
				object {dome_tank	rotate -z * 210}
				object {dome_tank	rotate -z * 270}
			#end
			object {dome_tank		rotate -z * 330}
			texture {white_metal_texture}
		}
	#end

	//------------------------------------------------------------------------------Solar Panels & Comm Dish

	#local comm_dish = union
	{
		difference
		{
			object {Paraboloid_Z}
			object {Paraboloid_Z	scale 0.999}
			plane {-z,-0.05}
			rotate y * 180
			scale		dock_radius/4
		}
		cylinder {<0,0,0>, <0,0,-city_units*8>, city_units/2}
		scale 2
		translate -z*city_units*16
	}
	#local comm_dome = difference
	{
		sphere {-z*city_units*16, city_units*16}
		plane {-z,0}
	}

	// trusses
	#declare truss_sides = 6;
	#declare truss_sections = 1;
	#declare truss_radius = city_units*16;
	#declare truss_thickness = city_units/2;
	#declare truss_point1 = -z*city_units*16;
	#declare truss_point2 = 0;
	#local comm_truss = object
	{
		#include "truss.inc"
		texture {white_metal_texture}
	}
	#local comm_anten = union
	{
		cylinder {<0,0,0>, <0,0,-city_length/16>, city_units}
		cylinder {<0,0,0>, <0,0,-city_length/4>, city_units/2}
		cylinder {<0,-city_units*32,0>, <0,-city_units*32,-city_length/32>, city_units}
		cylinder {<0,-city_units*32,0>, <0,-city_units*32,-city_length/8>, city_units/2}
		object {blinky_sphere	translate <0,0,-city_length/4-blinky_radius>}
		sphere {blinky_sphere	translate <0,-city_units*32,-city_length/8-blinky_radius>}
	}
	union
	{
		object
		{
			comm_dome
			translate	-y*dock_radius/2
			rotate		+z * 000
		}
		object
		{
			comm_truss
			translate	-y*dock_radius/2
			rotate		+z * 000
		}
		object
		{
			comm_dish
			translate	-y*dock_radius/2
			rotate		+z * 040
		}
		object
		{
			comm_truss
			translate	-y*dock_radius/2
			rotate		+z * 040
		}
		object
		{
			comm_anten
			translate	-y*dock_radius/2
			rotate		+z * 330
		}
		translate	-z*(dock_start+dock_length+city_units*3)
		texture {white_metal_texture}
	}
	#local solar_panel = union
	{
		box
		{
			<-panel_width/2,-panel_thick/2,-panel_length/2>,
			<+panel_width/2,+panel_thick/2,+panel_length/2>
			texture
			{
				pigment
				{
					brick gamma_color_adjust(0/4*<1,1,1>), gamma_color_adjust(1/4*<1,1,1>)
					brick_size city_units * 16
					mortar city_units * 1
				}
				finish {Glossy}
				translate -city_units/4
				translate +z*city_units * 8
			}
		}
		object {blinky_sphere	translate <-panel_width/2,0,-panel_length/2>}
		object {blinky_sphere	translate <-panel_width/2,0,+panel_length/2>}
		object {blinky_sphere	translate <+panel_width/2,0,-panel_length/2>}
		object {blinky_sphere	translate <+panel_width/2,0,+panel_length/2>}
	}
	#macro solar_group(solar_deg_x, solar_deg_z, solar_dis_z)
		union
		{
			#local panels_max = panel_number;
			#local panels_cnt = 0;
			#while (panels_cnt < panels_max)
				union
				{
					object {solar_panel	translate -z*(panel_length/2+panel_gap/2)}
					object {solar_panel	translate +z*(panel_length/2+panel_gap/2)}
					translate x * (shell_radius+panel_width/2+(panel_width + panel_gap)*panels_cnt)
				}
				#local panels_cnt = panels_cnt + 1;
			#end
			object {solar_truss}
			rotate +x * solar_deg_x
			rotate +z * solar_deg_z
			translate -y*shell_radius
			translate +z*solar_dis_z
		}
	#end

	// trusses
	#declare truss_sides = 3;
	#declare truss_sections = 8*panel_number;
	#declare truss_radius = panel_gap/2;
	#declare truss_thickness = city_units/2;
	#declare truss_point1 = 0;
	#declare truss_point2 = +x*(shell_radius+(panel_width + panel_gap)*panel_number);
	#local solar_truss = object
	{
		#include "truss.inc"
		texture {white_metal_texture}
	}
	object {solar_group(+15, 000, -ring_length/2-dock_length/2)}
	object {solar_group(-15, 180, -ring_length/2-dock_length/2)}
//	object {solar_group(+15, 000, +panel_distance)}
//	object {solar_group(-15, 180, +panel_distance)}
//	object {solar_group(+15, 000, -panel_distance)}
//	object {solar_group(-15, 180, -panel_distance)}

	//------------------------------------------------------------------------------Blinky Lights & Thrusters

	#local thruster = union
	{
		cone {<0, 0, 0>, 0, <0, 0, -2>, 1 open hollow}
		cylinder {<0, 0, 0>, <0, 0, -2*0.4>, 0.4 open hollow}
		scale 1/2
	}
	#local thruster_tank_radius = city_units*8;
	#local thruster_aggregate = union
	{
		sphere {0,1}
		object {thruster	translate <0, 0, -1>}
		object {thruster	translate <0, 0, +1>}
		object {thruster	rotate <0, 090, 0> translate <-1, 0, 0>}
		object {thruster	rotate <0, 270, 0> translate <+1, 0, 0>}
		object {thruster	rotate <270, 0, 0> translate <0, -1, 0>}
		object {fuel_tank(4,1)	rotate y * 000}		// was 90
		scale thruster_tank_radius
	//	rotate <0, 0, 45>
	//	translate <0, 2, 0>
	}
	#local blinky_group = union
	{
		object {blinky_sphere	translate <0,-dock_radius-blinky_radius,-habitat_length/2-ring_length-dock_length>}
		object {blinky_sphere	translate <0,-shell_radius-blinky_radius,-habitat_length/2>}
		object {blinky_sphere	translate <0,-shell_radius-blinky_radius,+habitat_length/2>}
	}
	object {blinky_group	rotate +z * 000}
	#if (ShowWhole)
		object {blinky_group	rotate +z * 090}
		object {blinky_group	rotate +z * 180}
		object {blinky_group	rotate +z * 270}
	#end
	#local thruster_group = union
	{
//		object {thruster_aggregate	translate <0,-dock_radius-thruster_tank_radius,-habitat_length/2-ring_length-dock_length>	rotate +z * 45}
		object {thruster_aggregate	translate <0,-shell_radius-thruster_tank_radius,-habitat_length/2>				rotate +z * 45}
		object {thruster_aggregate	translate <0,-shell_radius-thruster_tank_radius,+habitat_length/2-ring_length>				rotate +z * 45}
		pigment {rgb 1}
	}
	object {thruster_group	rotate +z * 000}
	object {thruster_group	rotate +z * 270}
	#if (ShowWhole)
		object {thruster_group	rotate +z * 180}
		object {thruster_group	rotate +z * 090}
	#end

//	object {thruster	scale 32 rotate y * 180	translate <0,0,+dock_start>}
#end

//------------------------------------------------------------------------------Solar Collector

/*
			#local p_radius = shell_radius*1;
			#local p_scale = shell_radius*2;
			#local z_position = pow(p_radius,2)/p_scale;
			
			intersection
			{
				difference
				{
					object
					{
						Paraboloid_Z
						scale p_scale
					}
					object
					{
						Paraboloid_Z
						scale p_scale
						translate z * city_units * 2
					}
				}
				plane {+z,z_position}
				rotate y * 180
				translate +z * z_position
				translate +z * habitat_length/2
				#if (!NoDomes)
					texture {dome_texture}
				#else
					pigment {color rgb 1}
				#end
			}
*/


//------------------------------------------------------------------------------Neighboring Craft

#if (!NoShips)
/*
	// http://skotan.deviantart.com/art/Aquila-Mk-I-spacecraft-185944452
	union
	{
		verbose_include("Aquila-Mk_I.pov", 0)
		scale		32
		translate	+x * shell_radius
		translate	-z * dock_start
	}
*/
	// http://povrayinclude.wytraven.com/links.html
	union
	{
		verbose_include("SPACESHP.POV", 0)
		scale		2
		rotate		-x * 090
		translate	-y * shell_radius/2
		translate	-x * shell_radius * 7/4
		translate	-z * (city_length/2 + ring_length + dock_length * 6/4)
	}

	// http://news.povray.org/povray.binaries.scene-files/thread/%3C4dfdbaad%40news.povray.org%3E/
	union
	{
		verbose_include("Anastasia2bX_.pov", 0)
		scale 1/2
		translate -z*dock_start*5/4
		translate +x*city_radius*5/4
	}
	union
	{
		verbose_include("Anastasia2bX_.pov", 0)
		scale 1/2
		translate -z*dock_start*5/4
		translate +x*city_radius*5/4
		translate -x*city_units*32
		translate +z*city_units*32
	}

#end

//------------------------------------------------------------------------------Atmosphere

// very slowwww!!!
#if (!NoAtmos)
	difference
	{
		cylinder
		{
			-z*(dock_start-city_units*3), +z*(dock_start-city_units*3), city_radius + city_units*1
		}
		cutaway_object
		material {atmos_material}
		hollow
	}
#end

//------------------------------------------------------------------------------Text
/*
text
{
//	ttf "impact.ttf" "Just a minute..." 0.1, 0
	ttf "Haettenschweiler.ttf" "www.GearHeadRPG.com" 0.1, 0
	texture {white_metal_texture}
	scale shell_radius/4
	rotate +x * 30
	rotate +y * 45
	translate <shell_radius*3/2,0,-shell_radius*1/4>
}

text
{
//	ttf "impact.ttf" "Just a minute..." 0.1, 0
	ttf "FontdSpaTT.ttf" "Athera" 0.1, 0
	texture {white_metal_texture}
	scale shell_radius/4
	rotate +x * 30
	rotate +y * 45
	translate <shell_radius*3/2,0,-shell_radius*1/4>
}

text
{
//	ttf "impact.ttf" "Just a minute..." 0.1, 0
	ttf "FontdinerSwanky.ttf" "Visit" 0.1, 0
	texture {white_metal_texture}
	scale shell_radius/4
	rotate +x * 30
	rotate +y * 45
	translate <shell_radius*3/2,0,-shell_radius*1/4>
}

text
{
//	ttf "impact.ttf" "Just a minute..." 0.1, 0
	ttf "FontdinerSwanky.ttf" "today!" 0.1, 0
	texture {white_metal_texture}
	scale shell_radius/4
	rotate +x * 30
	rotate +y * 45
	translate <shell_radius*3/2,0,-shell_radius*1/4>
}
*/
polygon
{
	4, <0,0>,<0,1>,<1,1>,<1,0>
	pigment
	{
		image_map {png "spinner_units_distance.png" once}
	}
	scale <city_units*200,city_units*200*268/642,1>
	rotate x * 90
	translate -y * shell_radius
	translate -z * habitat_length
}


//------------------------------------------------------------------------------Alignment
/*
cylinder
{
	-x*256,+x*256, 1/2
	pigment {gamma_color_adjust(x)}
	translate -y * city_radius
}
cylinder
{
	-y*256,+y*256, 1/2
	pigment {gamma_color_adjust(y)}
	translate -y * city_radius
}
cylinder
{
	-z*256,+z*256, 1/2
	pigment {gamma_color_adjust(z)}
	translate -y * city_radius
}
*/

//------------------------------------------------------------------------------Debug

#debug "\n"
#debug concat("city_length = ",str(city_length,0,0),"\n")
#debug concat("totl_length = ",str(totl_length,0,0),"\n")
#debug concat("city_circum = ",str(city_circum,0,0),"\n")
#debug concat("city_radius = ",str(city_radius,0,0),"\n")
#debug "\n"
