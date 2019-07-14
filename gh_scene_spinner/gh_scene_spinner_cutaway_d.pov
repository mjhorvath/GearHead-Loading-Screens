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
//+SR0.5 +SC0.6 +ER0.9 +EC0.9

//------------------------------------------------------------------------------Variables

#version 3.6				// ommitting this seriously messes up the colors

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
#include "param.inc"

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
#declare NoWeapons		= 1;

// toggles
#declare NoColors		= 0;
#declare NoAtmos		= 1;					// very slowwwww!!!
#declare NoGalaxy		= 0;
#declare NoCity			= 0;
#declare NoShips		= 0;
#declare NoRadiosity		= 1;					// ugly
#declare NoLights		= 0;
#declare NoShell		= 0;					// boolean, toggle outer shell, spokes and endcaps
#declare NoLamp			= 0;
#declare NoLampLight		= 1;					// very slowwwww!!!
#declare NoCars			= 0;
#declare NoStreet		= 0;
#declare NoDomes		= 1;
#declare NoCone			= 1;
#declare NoEngines		= 1;
#declare NoPanels		= 0;
#declare NoComms		= 0;
#declare NewTrain		= 1;					// boolean, use maglev instead of streetcars
#declare AlwaysReflect		= 0;					// used in citygen mostly
#declare ShowWhole		= 0;					// show the entire outer shell, not finished
#declare glass_hollow		= 0;					// boolean
#declare glass_thin		= 0;					// boolean
#declare bound_fit		= 1;
#declare debug_progress		= 1;					// boolean, see CityGen docs

#if (Minimal)
	#declare NoCity			= 1;
	#declare NoAtmos		= 1;				// very slowwwww!!!
	#declare NoGalaxy		= 1;
	#declare NoShips		= 1;
	#declare NoRadiosity		= 1;				// ugly
	#declare NoLights		= 0;
	#declare NoShell		= 0;				// boolean, toggle outer shell, spokes and endcaps
	#declare NoLamp			= 0;
	#declare NoLampLight		= 1;				// very slowwwww!!!
	#declare NoCars			= 1;
	#declare NoStreet		= 1;
	#declare NoDomes		= 1;
	#declare NoPanels		= 0;
	#declare NoComms		= 0;
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
#declare city_block_count	= <3,4>;				// 2D vector of integers
#declare city_sections		= <2,1>;				// 2D vector of integers
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
#declare city_rotate		= 30;					// float, rotate the inner shell containing the city by this amount

// scene variables (mostly)
#local ring_length		= city_units * 128;
#local ring_gap			= city_units * 8;
#local habitat_length		= city_length + ring_gap * 2;
#local inner_shell_radius1	= city_radius + city_units * 16;
#local inner_shell_radius2	= inner_shell_radius1 - city_units * 4;
#local outer_shell_radius1	= inner_shell_radius1 + ring_gap/4 + city_units * 32;
#local outer_shell_radius2	= inner_shell_radius1 + ring_gap/4 + city_units * 8;
#local dock_length		= city_units * 256;
#local dock_start		= habitat_length/2 + ring_length;
#local dock_radius1		= outer_shell_radius1;
#local dock_radius2		= outer_shell_radius1 * 1/3;
#local dock_depth		= city_units * 48;
#local dock_thick		= dock_length/32;
#local total_length		= habitat_length + ring_length + dock_length;
#local dome_radius		= city_units * 64;
#local dome_gap			= city_units * 16;
#local panel_gap		= city_units * 32;
#local panel_width		= city_units * 128;
#local panel_length		= city_units * 256;
#local panel_thick		= city_units/2;
#local panel_distance		= city_units * 576;
#local panel_number		= 8;
#local panel_rotate		= 60;
#local mini_truss_radius	= city_units * 12;
#local mini_truss_sides		= 3;
#local mini_truss_thick		= city_units;
#local mini_truss_section_size	= city_units * 32;
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

#declare Camera_Mode		= 2;					// 1 to 8; 1 = oblique; 2 = perspective; 3 = orthographic
#declare Camera_Diagonal	= cosd(45);				//45;
#declare Camera_Vertical	= 135;					//45;
#declare Camera_Horizontal	= asind(tand(30));			//asind(tand(30));
#declare Camera_Scale		= 1;
#declare Camera_Aspect		= image_height/image_width;
#declare Camera_Distance	= 256;
#declare Camera_Translate	= <0,-city_radius/2*4/4,-city_radius/2*6/4,>;			//<0,0,-city_size_total.y,>
#declare Camera_Scale		= 256;					//160
#include "gh_camera.inc"


//------------------------------------------------------------------------------Macros

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


//------------------------------------------------------------------------------Textures & Common Objects

#default
{
	finish {ambient 1/16 diffuse albedo 0.7 phong 1}
}


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

#declare sky_texture_a = texture
{
	pigment
	{
		cylindrical
		color_map
		{
			[0 gamma_color_adjust(< 0.5, 0.6, 1.0 >)]
			[1 gamma_color_adjust(< 1, 1, 1 >)]
		}
	}
	rotate x * 90
	scale outer_shell_radius1
}

#declare rock_filling_texture = texture
{
	pigment
	{
		granite
		color_map
		{
			[0 DarkBrown]
			[1 color rgb 0]
		}
	}
	finish {phong 0}
}
#declare steel_filling_texture = texture
{
	pigment
	{
		granite
		color_map
		{
			[0 color rgb 1/2]
			[1 color rgb 0]
		}
	}
	finish {phong 0}
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
					[0	rgb 1]
					[1	rgb 0]
				}
				scale	city_radius
			}
		}
	}
	rotate	x * 90
}
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
// phong looks like crap
#declare white_metal_texture = texture
{
	pigment {gamma_color_adjust(<1,1,1>*8/8)}
}
// phong looks like crap
#declare gray_metal_texture = texture
{
	pigment {gamma_color_adjust(<1,1,1>*1/2)}
}
#declare red_metal_texture = texture
{
	pigment {gamma_color_adjust(<1,0,0>)}
}
#declare yellow_metal_texture = texture
{
	pigment {gamma_color_adjust(<1,1,0>)}
}
#declare green_metal_texture = texture
{
	pigment {gamma_color_adjust(<0,1,0>)}
}
#declare cutaway_object1 = union
{
//	plane {-y, 0	rotate +z * 015}
//	plane {-y, 0	rotate -z * 015}
	plane {-y, 0}
}
/*
#declare cutaway_object1 = union
{
	plane {-y, 0}
//	plane {-y, 0	rotate +z * 30}
//	plane {-y, 0	rotate -z * 30}
//	plane {+x, 0	rotate -z * 60}
	translate -y * city_units * 2
}

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
*/
#declare dome_texture = texture{T_Glass3}

#macro new_random_color()
	#if (NoColors = 0)
		#declare MTX = texture { pigment { gamma_color_adjust(<rand(Seed),rand(Seed),rand(Seed)>) } finish { F_MetalA  } }
		#declare CTX = texture { pigment { gamma_color_adjust(<rand(Seed),rand(Seed),rand(Seed)>) } finish { F_MetalA  } }
		#declare HTX = texture { pigment { gamma_color_adjust(<rand(Seed),rand(Seed),rand(Seed)>) } finish { F_MetalA  } }
	#else
		#declare MTX = texture { pigment { gamma_color_adjust(1) } finish { F_MetalA  } }
		#declare CTX = texture { pigment { gamma_color_adjust(0) } finish { F_MetalA  } }
		#declare HTX = texture { pigment { gamma_color_adjust(1/2) } finish { F_MetalA  } }
	#end
#end

#declare Plain_Gray = texture { pigment { gamma_color_adjust(1/2) } finish { F_MetalA  } }
#declare Plain_LightGray = texture { pigment { gamma_color_adjust(3/4) } finish { F_MetalA  } }
#declare Plain_DarkGray = texture { pigment { gamma_color_adjust(1/4) } finish { F_MetalA  } }

#declare street_texture = texture
{
	pigment
	{
		bozo
		color_map
		{
			[0 gamma_color_adjust(<.2,.2,.2>)]
			[1 gamma_color_adjust(<.4,.4,.4>)]
		}
		scale 10
	}
	scale city_units
}
#declare pavement_texture = texture
{
	pigment
	{
		wrinkles
		color_map
		{
//			[0 gamma_color_adjust(<.5,.5,.5>)]
//			[1 gamma_color_adjust(<.6,.6,.6>)]
			[0 gamma_color_adjust(8/8)]
			[1 gamma_color_adjust(8/8)]

		}
		scale 1.5
	}
	scale city_units
}

#macro fuel_tank(in_len, in_rad)
	union
	{
		sphere {-z*in_len/2, in_rad}
		sphere {+z*in_len/2, in_rad}
		cylinder {-z*in_len/2,+z*in_len/2,in_rad}
	}
#end

//------------------------------------------------------------------------------Global settings

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
			max_trace_level 16
		#break
	#end
}


//------------------------------------------------------------------------------Sun & Sky

#if (NoLampLight)
	light_source
	{
		<-15000, +15000, -15000> * <1/4,1,1/2>
		gamma_color_adjust(light_color)
		rotate y * 090
		translate -y * city_radius
		parallel
	}
#end
//#if (NoRadiosity)
//	sky_sphere {pigment {gamma_color_adjust(<223,230,255>/255)}}
//#end

background {color rgb 0}

// Galaxy variables
#if (!NoGalaxy)
	#declare galaxy_bg = 1;			// on or off
	#declare galaxy_objects = 1;		// on or off
	#declare galaxy_starfield = 1;		// on or off
	#declare galaxy_bgstars = 1;		// type or off, not working?
	#declare galaxy_bgnebula = 1;		// type or off, not working?
	#declare galaxy_nebula_sphere = 0;	// type or off, not working?
	#declare galaxy_distance = 100000;
	#declare galaxy_colouration = 0.2;
	#declare star_type = 3;
	#declare star_scale = 1/4;
	#declare star_count = 10000;
	#include "GALAXY.BG"
	#include "GALAXY.SF"
//	#include "galaxy.inc"
#end


//------------------------------------------------------------------------------City

#if (!NoCity)
	union
	{
		//------------------------------------------------------------------------------Central Area
	
//		verbose_include("CG_UNIQUE_CURVED_MESH.INC", 0)		// not implemented yet
		verbose_include("CG_DEFAULT_CURVED_MESH.INC", 0)
		#if (!Minimal)
			verbose_include("CG_VEHICLES_CURVED_MESH.INC", 0)
			verbose_include("CG_PAVEMENT_CURVED_MESH.INC", 0)		// needs to be updated for new maglev system
			verbose_include("CG_PARK_CURVED_MESH.INC", 0)
			verbose_include("CG_SQUARE_CURVED_MESH.INC", 0)
			verbose_include("CG_NORMAL_CURVED_MESH.INC", 0)
		#end
		#local city_object = object {#include "CG_CITY_CURVED_MESH.inc"}
		object {city_object}
	
		//------------------------------------------------------------------------------End Parks
	
		#declare buildings_per_block	= <buildings_per_block.x,1>;
		#declare city_block_count	= <city_block_count.x,1>;
		verbose_include("CG_DEFAULT_CURVED_MESH.INC", 0)
		#if (!Minimal)
			verbose_include("CG_VEHICLES_CURVED_MESH.INC", 0)
			verbose_include("CG_PAVEMENT_CURVED_MESH.INC", 0)		// needs to be updated for new maglev system
			verbose_include("CG_PARK_CURVED_MESH.INC", 0)
		#end
		#local city_object = object {#include "CG_CITY_CURVED_MESH.inc"}
		object {city_object translate +z * (city_length - nominal_building_width - nominal_traffic_width)/2}
	
		#declare buildings_per_block	= <buildings_per_block.x,1>;
		#declare city_block_count	= <city_block_count.x,1>;
		verbose_include("CG_DEFAULT_CURVED_MESH.INC", 0)
		#if (!Minimal)
			verbose_include("CG_VEHICLES_CURVED_MESH.INC", 0)
			verbose_include("CG_PAVEMENT_CURVED_MESH.INC", 0)		// needs to be updated for new maglev system
			verbose_include("CG_PARK_CURVED_MESH.INC", 0)
		#end
		#declare NoCars			= 1;
		#declare NoStreet		= 1;
		#local city_object = object {#include "CG_CITY_CURVED_MESH.inc"}
		object {city_object translate -z * (city_length - nominal_building_width - nominal_traffic_width)/2}

		rotate +z * (city_rotate)
	}
#end


//------------------------------------------------------------------------------Shell

#if (!NoShell)
	// outer metal shell
	#local shell_a1 = cylinder
	{
		-z*(habitat_length/2+ring_length), +z*(habitat_length/2), outer_shell_radius1
	}
	#local shell_b1 = cylinder
	{
		-z*(city_length*10), +z*(city_length*10), outer_shell_radius2
	}
	// outer rock shell
	#local shell_a2 = cylinder
	{
		-z*(habitat_length/2+ring_length-city_units*4), +z*(habitat_length/2-city_units*4), outer_shell_radius1-city_units*4
	}
	#local shell_b2 = cylinder
	{
		-z*(city_length*10), +z*(city_length*10), outer_shell_radius2+city_units*4
	}
	// inner metal shell
	#local shell_a3 = cylinder
	{
		-z*(city_length/2-city_units*0), +z*(city_length/2-city_units*0), inner_shell_radius1
	}
	#local shell_b3 = cylinder
	{
		-z*(city_length/2-city_units*4), +z*(city_length/2-city_units*4), inner_shell_radius2
	}
	// inner rock shell
	#local shell_a4 = cylinder
	{
		-z*(city_length/2-city_units*4), +z*(city_length/2-city_units*4), inner_shell_radius2
	}
	#local shell_b4 = cylinder
	{
		-z*(city_length/2-city_units*0), +z*(city_length/2-city_units*0), city_radius
	}
	#local cap_letter_a =	text {ttf "space age.ttf" "A" 1, 0}
	#local cap_letter_b =	text {ttf "space age.ttf" "B" 1, 0}
	#local cap_letter_c =	text {ttf "space age.ttf" "C" 1, 0}
	// large gray cylinder end cap
	#local cap_1 = cylinder
	{
		-z*city_units, +z*city_units, outer_shell_radius1
	}
	// inner lozenge cutout 2
	#local cap_cutout_2 = cylinder
	{
		-z*city_units*3, +z*city_units*3, outer_shell_radius2/5
	}
	#local cap_cutout_2b = union
	{
		object {cap_cutout_2	translate -y * outer_shell_radius2/2	rotate z * 000}
		object {cap_cutout_2	translate -y * outer_shell_radius2/2	rotate z * 060}
		object {cap_cutout_2	translate -y * outer_shell_radius2/2	rotate z * 120}
		object {cap_cutout_2	translate -y * outer_shell_radius2/2	rotate z * 180}
		object {cap_cutout_2	translate -y * outer_shell_radius2/2	rotate z * 240}
		object {cap_cutout_2	translate -y * outer_shell_radius2/2	rotate z * 300}
	}
	// inner lozenge glass 2
	#local cap_glass_2 = difference
	{
		sphere
		{
			0, outer_shell_radius2/5*0.999
			scale z * 4/8
		}
		sphere
		{
			0, outer_shell_radius2/5*0.999
			scale z * 4/8
			scale 15/16
		}
		plane {-z,0}
	}
	#local cap_glass_2b = union
	{
		object {cap_glass_2	translate -y * outer_shell_radius2/2	rotate z * 000}
		object {cap_glass_2	translate -y * outer_shell_radius2/2	rotate z * 060}
		object {cap_glass_2	translate -y * outer_shell_radius2/2	rotate z * 120}
		object {cap_glass_2	translate -y * outer_shell_radius2/2	rotate z * 180}
		object {cap_glass_2	translate -y * outer_shell_radius2/2	rotate z * 240}
		object {cap_glass_2	translate -y * outer_shell_radius2/2	rotate z * 300}
	}
	// end cap bevel
	#local cap_hub_r8 = cylinder {-z*city_units*2, +z*city_units*2, outer_shell_radius2*8/8}
	#local cap_hub_r7 = cylinder {-z*city_units*2, +z*city_units*2, outer_shell_radius2*7/8}
	#local cap_hub_r6 = cylinder {-z*city_units*2, +z*city_units*2, outer_shell_radius2*6/8}
	#local cap_hub_r3 = cylinder {-z*city_units*2, +z*city_units*2, outer_shell_radius2*3/8}
	#local cap_hub_r2 = cylinder {-z*city_units*2, +z*city_units*2, outer_shell_radius2*2/8}
	#local cap_hub_r1 = cylinder {-z*city_units*2, +z*city_units*2, outer_shell_radius2*2/8}

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
//		difference
//		{
//			object {cap_hub_r3}
//			object {cap_hub_r2	scale 1.0001}
//		}
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
//		difference
//		{
//			object {cap_hub_r3}
//			object {cap_hub_r2	scale 1.0001}
//		}
		object {cap_hub_r1}
	}
	#local outer_rock_ring = difference
	{
		object {shell_a2}
		object {shell_b2}
	}
	#local inner_rock_ring = difference
	{
		object {shell_a4}
		object {shell_b4}
	}

	//------------------------------------------------------------------------------Outer Shell & Mid Walls

	difference
	{
		union
		{

			difference
			{
				object {shell_a1}
				object {shell_b1}
				object {outer_rock_ring}
			}
			object {cap_object_a	translate +z*(habitat_length/2)}
			object {cap_object_b	translate -z*(dock_start)}
//			object {cap_object_b	translate -z*(dock_start+dock_length)}	// was <3/4,3/4,1>
		}
		#if (!ShowWhole)
			object {cutaway_object1}
		#end
		texture {white_metal_texture}
	}

	difference
	{
		object {outer_rock_ring}
		#if (!ShowWhole)
			object {cutaway_object1}
		#end
		texture {steel_filling_texture}
	}

	//------------------------------------------------------------------------------Inner Shell & End Caps

	// this stuff really needs to be double-checked to make sure things line up correctly

	difference
	{
		union
		{
			difference
			{
				object {shell_a3}
				object {shell_b3				texture {sky_texture_a}}
				// side a
				object {cap_cutout_2b	translate +z*(city_length/2-city_units*2)}
				object
				{
					cap_letter_a
					Center_Trans(cap_letter_a, x)
					Center_Trans(cap_letter_a, y)
					Center_Trans(cap_letter_a, z)
					scale <outer_shell_radius1/6,outer_shell_radius1/6,city_units>
					translate -y*outer_shell_radius1/2
					translate +z*(city_length/2-city_units*4)
					rotate z * -060
				}
				object
				{
					cap_letter_b
					Center_Trans(cap_letter_b, x)
					Center_Trans(cap_letter_b, y)
					Center_Trans(cap_letter_b, z)
					scale <outer_shell_radius1/6,outer_shell_radius1/6,city_units>
					translate -y*outer_shell_radius1/2
					translate +z*(city_length/2-city_units*4)
					rotate z * +000
				}
				object
				{
					cap_letter_c
					Center_Trans(cap_letter_c, x)
					Center_Trans(cap_letter_c, y)
					Center_Trans(cap_letter_c, z)
					scale <outer_shell_radius1/6,outer_shell_radius1/6,city_units>
					translate -y*outer_shell_radius1/2
					translate +z*(city_length/2-city_units*4)
					rotate z * +060
				}
				// side b
				object {cap_cutout_2b	translate -z*(dock_start-city_units*2)}
				object
				{
					cap_letter_a
					Center_Trans(cap_letter_a, x)
					Center_Trans(cap_letter_a, y)
					Center_Trans(cap_letter_a, z)
					rotate y * 180
					scale <outer_shell_radius1/6,outer_shell_radius1/6,city_units>
					translate -y*outer_shell_radius1/2
					translate -z*(city_length/2-city_units*4)
					rotate z * -60
				}
				object
				{
					cap_letter_b
					Center_Trans(cap_letter_b, x)
					Center_Trans(cap_letter_b, y)
					Center_Trans(cap_letter_b, z)
					rotate y * 180
					scale <outer_shell_radius1/6,outer_shell_radius1/6,city_units>
					translate -y*outer_shell_radius1/2
					translate -z*(city_length/2-city_units*4)
					rotate z * +00
				}
				object
				{
					cap_letter_c
					Center_Trans(cap_letter_c, x)
					Center_Trans(cap_letter_c, y)
					Center_Trans(cap_letter_c, z)
					rotate y * 180
					scale <outer_shell_radius1/6,outer_shell_radius1/6,city_units>
					translate -y*outer_shell_radius1/2
					translate -z*(city_length/2-city_units*4)
					rotate z * +60
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
		}
		#if (!ShowWhole)
			object {cutaway_object1}
		#end
		texture {white_metal_texture}
		rotate +z * city_rotate
	}

	difference
	{
		object {inner_rock_ring}
		#if (!ShowWhole)
			object {cutaway_object1}
		#end
		texture {rock_filling_texture}
		rotate +z * city_rotate
	}

	//------------------------------------------------------------------------------Compact Ring

	difference
	{
		union
		{
			#local ring_max = 6;
			#local ring_cnt = 0;
			#while (ring_cnt < ring_max)
				difference
				{
					cylinder {-z*(habitat_length/2-city_units),-z*(city_length/2+ring_length+city_units),inner_shell_radius1-city_storey_height*ring_cnt*10+city_units}
					cylinder {-z*(habitat_length/2+city_units),-z*(city_length/2+ring_length-city_units),inner_shell_radius1-city_storey_height*ring_cnt*10-city_units}
				}
				#local ring_cnt = ring_cnt + 1;
			#end
			#local ring_max = 50;
			#local ring_cnt = 0;
			#while (ring_cnt < ring_max)
				difference
				{
					cylinder {-z*(habitat_length/2-city_units),-z*(city_length/2+ring_length+city_units),inner_shell_radius1-city_storey_height*ring_cnt+city_units/4}
					cylinder {-z*(habitat_length/2+city_units),-z*(city_length/2+ring_length-city_units),inner_shell_radius1-city_storey_height*ring_cnt-city_units/4}
				}
				#local ring_cnt = ring_cnt + 1;
			#end
		}
		#if (!ShowWhole)
			object {cutaway_object1}
		#end
		texture {white_metal_texture}
	}

	difference
	{
		cylinder {-z*(habitat_length/2+city_units),-z*(city_length/2+ring_length-city_units),inner_shell_radius1			scale <0.99,0.99,1>}
		cylinder {-z*(habitat_length/2-city_units),-z*(city_length/2+ring_length+city_units),inner_shell_radius1-city_storey_height*50	scale <0.99,0.99,1>}
		#if (!ShowWhole)
			object {cutaway_object1}
		#end
		#if (!NoDomes)
			material {ring_glass_mat}
		#else
			pigment {color rgb 1}
		#end
	}

	//------------------------------------------------------------------------------Cargo and Shiphold

	difference
	{
		union
		{

			#local dock_labels = polygon
			{
				4, <0,0>,<0,1>,<1,1>,<1,0>
				texture {pigment {color rgb 1/2}}
				texture
				{
					pigment
					{
						image_map {png "spinner_lot_text.png"}
					}
				}
				translate <-1/2,-1/2,0>
				scale <dock_length*7/8,outer_shell_radius1*2,1>
				rotate y * 90
			}

			#local dock_cnt = 0;
			#local dock_max = 3;
			#while (dock_cnt < dock_max)
				difference
				{
					superellipsoid
					{
						<0.001, 0.1>
						scale <dock_depth + dock_thick,dock_radius1*2,dock_length/2>
						translate -z * dock_length/2
						rotate z * (dock_cnt * 60 + 30)
					}
					superellipsoid
					{
						<0.001, 0.1>
						scale <dock_depth,dock_radius1*2,dock_length/2 - dock_thick>
						translate -z * dock_length/2
						rotate z * (dock_cnt * 60 + 30)
					}
					cylinder {<0,0,+1>, <0,0,-dock_length-1>, dock_radius1 inverse}
					cylinder {<0,0,+1>, <0,0,-dock_length-1>, dock_radius2}
					translate -z * (dock_start)
				}
				#local dock_cnt = dock_cnt + 1;
			#end

			difference
			{
				union
				{
					#local dock_cnt = 0;
					#local dock_max = 3;
					#while (dock_cnt < dock_max)
						union
						{
							object
							{
								dock_labels
								translate +x * dock_depth * 0.99
								rotate z * (dock_cnt * 60 + 30)
							}
							object
							{
								dock_labels
								translate -x * dock_depth * 0.99
								rotate z * (dock_cnt * 60 + 30)
							}
						}
						#local dock_cnt = dock_cnt + 1;
					#end
				}
				cylinder {<0,0,-dock_length/2>, <0,0,+dock_length/2>, dock_radius2}
				cylinder {<0,0,-dock_length/2>, <0,0,+dock_length/2>, dock_radius1 inverse}
				translate -z * (dock_start + dock_length/2)
			}
		}
		#if (!ShowWhole)
			object {cutaway_object1}
		#end
		texture {white_metal_texture}
	}

	//------------------------------------------------------------------------------Solar Collector

	difference
	{
		union
		{

			#if (!NoCone)
				#local p_radius = outer_shell_radius2*6/8;
				#local p_scale = outer_shell_radius2*6/8;
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
/*
				#local p_radius = outer_shell_radius1/2;
				#local p_scale = outer_shell_radius1*2;
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
					translate -z * z_position
					translate -z * (habitat_length/2+ring_length+dock_length)
					#if (!NoDomes)
						texture {dome_texture}
					#else
						pigment {color rgb 1}
					#end
				}
*/
			#end
		}
		#if (!ShowWhole)
			object {cutaway_object1}
		#end
		texture {white_metal_texture}
	}

	//------------------------------------------------------------------------------body trusses x-long

	#declare truss_sides = 12;
	#declare truss_sections = 16;
	#declare truss_thickness = city_units*2;
	#declare truss_radius = outer_shell_radius1 * sqrt(pow(tand(360/2/truss_sides),2) + 1) + truss_thickness;
	#declare truss_point1 = -z*(habitat_length/2+ring_length);	//+dock_length
	#declare truss_point2 = +z*habitat_length/2;
	difference
	{
		object {#include "truss.inc"}
		#if (!ShowWhole)
			object {cutaway_object1}
		#end
		texture {white_metal_texture}
	}

	//------------------------------------------------------------------------------Lamp & Spindles

	#if (!NoLampLight)
		light_source
		{
			0, gamma_color_adjust(Light_Color(light_temp,light_lumens))
			area_light z*lamp_length/2, y, 16, 1
		}
		light_source
		{
			+z*city_units*4096, gamma_color_adjust(Light_Color(light_temp,light_lumens))
			parallel
		}
	#end

	#if (!NoLamp)
		object
		{
			cylinder {z*-(lamp_length/2), z*+(lamp_length/2), lamp_radius}
			material {lamp_material}
			#if (TexQual = 1)	hollow	#end
			scale	0.9999
			no_shadow
		}
	#end

	//------------------------------------------------------------------------------Reactor Core

	union
	{
		#local ball_radius = city_units * 16;
		#local ball_center = habitat_length/2+ring_length/2;
		#local trumpet_length = ring_length/2-ball_radius-ring_gap;
		#declare Fx2 = function(u,v) {v}
		#declare Fy2 = function(u,v) {city_units*16/pow(v+1,0.7)*cos(u)}
		#declare Fz2 = function(u,v) {city_units*16/pow(v+1,0.7)*sin(u)}
		object
		{
			Parametric(Fx2,Fy2,Fz2,<0,0>,<2*pi,trumpet_length>,30,30,"")
			rotate -y * 90
			translate -z*(ball_center+city_units*2-ball_radius)
		}
		object
		{
			Parametric(Fx2,Fy2,Fz2,<0,0>,<2*pi,trumpet_length>,30,30,"")
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


	//------------------------------------------------------------------------------Shiphold Contents

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
			translate -y * dock_depth
			translate +y * city_units
			translate -x * dock_length*2/3
		}
		new_random_color()
		verbose_include("ara_kojedo.pov", 0)
		object
		{
			ara_kojedo_
			translate <18.42348,0,-364.0902> * -1
			scale 1/375
			//edit below
			scale 10 * city_units
			translate -z * (dock_start+dock_length*7/12)
			translate -y * dock_depth
			translate +y * city_units
			translate +x * dock_length*9/12
		}
		new_random_color()
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
			translate -y * dock_depth
			translate +y * city_units
			translate +x * dock_radius1*9/12
		}
		new_random_color()
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
			translate -y * dock_depth
			translate +y * city_units
			translate -x * dock_radius1*9/12
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
			translate -y * dock_depth
			translate +y * city_units
			translate -x * dock_radius1*8/12
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
				translate -z * (dock_start + dock_length/6 + dock_length/3 * rand(Seed))
				translate -x * ((dock_radius1 * 3/4 - dock_radius2) * rand(Seed) + dock_radius2)
				translate -y * (dock_depth)
				translate +y * (city_units)
			}
			#local cargo_cnt = cargo_cnt + 1;
		#end
/*
		// people (not rendering??)
		#local people_max = 8;
		#local people_cnt = 0;
		#while (people_cnt < people_max)
			object
			{
				ped_macro(Seed)
				translate -z * (dock_start + dock_length/6 + dock_length/3*rand(Seed))
				translate -x * (dock_length/3*rand(Seed))
				translate -y * (dock_radius1*1/4)
				translate +y * (city_units)
			}
			#local people_cnt = people_cnt + 1;
		#end
*/
		// fuel tanks
		union
		{
			object
			{
				fuel_tank(city_units*8,city_units*4)
				rotate x * 90
				translate +y*city_units*8
				translate -x*(dock_radius1/2+city_units*16)
				translate -z*(dock_start+dock_thick+city_units*8)
			}
			object
			{
				fuel_tank(city_units*8,city_units*4)
				rotate x * 90
				translate +y*city_units*8
				translate -x*(dock_radius1/2+city_units*24)
				translate -z*(dock_start+dock_thick+city_units*8)
			}
			object
			{
				fuel_tank(city_units*8,city_units*4)
				rotate x * 90
				translate +y*city_units*8
				translate +x*(dock_radius1/2+city_units*16)
				translate -z*(dock_start+dock_thick+city_units*8)
			}
			object
			{
				fuel_tank(city_units*8,city_units*4)
				rotate x * 90
				translate +y*city_units*8
				translate +x*(dock_radius1/2+city_units*24)
				translate -z*(dock_start+dock_thick+city_units*8)
			}

			object
			{
				fuel_tank(city_units*8,city_units*4)
				rotate x * 90
				translate +y*city_units*8
				translate -x*(dock_radius1/2+city_units*16)
				translate -z*(dock_start+dock_length-dock_thick-city_units*8)
			}
			object
			{
				fuel_tank(city_units*8,city_units*4)
				rotate x * 90
				translate +y*city_units*8
				translate -x*(dock_radius1/2+city_units*24)
				translate -z*(dock_start+dock_length-dock_thick-city_units*8)
			}
			object
			{
				fuel_tank(city_units*8,city_units*4)
				rotate x * 90
				translate +y*city_units*8
				translate +x*(dock_radius1/2+city_units*16)
				translate -z*(dock_start+dock_length-dock_thick-city_units*8)
			}
			object
			{
				fuel_tank(city_units*8,city_units*4)
				rotate x * 90
				translate +y*city_units*8
				translate +x*(dock_radius1/2+city_units*24)
				translate -z*(dock_start+dock_length-dock_thick-city_units*8)
			}
			translate -y*dock_depth
			texture {yellow_metal_texture}
		}

		// robo arm
		object
		{
			#include "gh_roboarm.inc"
			rotate -x*90
			scale city_units/2
			translate -z*(dock_start+city_units*2)
			texture {white_metal_texture}
		}

		// rafters
		#declare rafter_object_a = union
		{
			#declare truss_sides = 3;
			#declare truss_sections = 8;
			#declare truss_radius = city_units*8;
			#declare truss_thickness = city_units;
			#declare truss_point1 = <dock_radius2-truss_radius-truss_thickness,0,-dock_start - dock_length*15/16>;
			#declare truss_point2 = <dock_radius2-truss_radius-truss_thickness,0,-dock_start - dock_length*01/16>;
			#declare truss_rotate = 180;
			object
			{
				#include "truss.inc"
				rotate -z * 030
			}
			object
			{
				#include "truss.inc"
				rotate -z * 090
			}
			object
			{
				#include "truss.inc"
				rotate -z * 150
			}
			texture {white_metal_texture}
		}
		object {rafter_object_a}

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
			translate -y*(dock_depth-city_units)
			translate -z*(city_length/2+ring_length+dock_length*1/4)
			translate +x*(dock_radius1*3/4)
			texture {yellow_metal_texture}
		}
	#end

	//------------------------------------------------------------------------------Engines

	#if (!NoEngines)
		#local fuel_radius = outer_shell_radius1*1/4;
		#local tank_cnt = 0;
		#local tank_max = 6;
		#while (tank_cnt < tank_max)
			sphere
			{
				-y*(outer_shell_radius1-fuel_radius),
				fuel_radius
				rotate z * tank_cnt * 60
				translate -z * (habitat_length/2+ring_length+dock_length+fuel_radius)
				texture {white_metal_texture}
			}
			#local tank_cnt = tank_cnt + 1;
		#end

		#local p_radius = outer_shell_radius1/2;
		#local p_scale = outer_shell_radius1/2;
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
//				translate -z * z_position
			translate -z * (habitat_length/2+ring_length+dock_length)
			#if (!NoDomes)
				texture {dome_texture}
			#else
				pigment {color rgb 1}
			#end
		}
	#end

	//------------------------------------------------------------------------------Agri Domes

	#if (!NoDomes)
		#include "gh_dome_group.inc"
		#local dome_x = city_units * 768;
		#local dome_z = city_length/4;
		#local dome_y = 0;
		object
		{
			dome_group
			rotate +x * panel_rotate
			translate +x * dome_x
			translate +z * dome_z
			translate -y * dome_y
			translate +y * mini_truss_radius
		}
		object
		{
			dome_group
			rotate +x * panel_rotate
			translate -x * dome_x
			translate +z * dome_z
			translate -y * dome_y
			translate +y * mini_truss_radius
		}

		#declare truss_sides = mini_truss_sides;
		#declare truss_radius = mini_truss_radius;
		#declare truss_thickness = mini_truss_thick;
		#declare truss_point1 = +x * outer_shell_radius1;
		#declare truss_point2 = +x * dome_x;
		#declare truss_sections = VDist(truss_point1, truss_point2) / mini_truss_section_size;
		object
		{
			#include "truss.inc"
			translate +z * dome_z
			translate -y * dome_y
			texture {white_metal_texture}
		}
		#declare truss_sides = mini_truss_sides;
		#declare truss_radius = mini_truss_radius;
		#declare truss_thickness = mini_truss_thick;
		#declare truss_point1 = -x * outer_shell_radius1;
		#declare truss_point2 = -x * dome_x;
		#declare truss_sections = VDist(truss_point1, truss_point2) / mini_truss_section_size;
		object
		{
			#include "truss.inc"
			translate +z * dome_z
			translate -y * dome_y
			texture {white_metal_texture}
		}
	#end

	//------------------------------------------------------------------------------Tanks

	#local tank_radius = city_units * 16;
	#local tank_length = city_units * 128;
	#local tank_object = object
	{
		fuel_tank(tank_length,tank_radius)
		translate -y*(outer_shell_radius1+tank_radius)
	}
	union
	{
		object {tank_object		rotate -z * 030}
		#if (ShowWhole)
			object {tank_object	rotate -z * 090}
			object {tank_object	rotate -z * 150}
			object {tank_object	rotate -z * 210}
			object {tank_object	rotate -z * 270}
		#end
		object {tank_object		rotate -z * 330}
		texture {white_metal_texture}
	}

	//------------------------------------------------------------------------------Comms

	#if (!NoComms)
		#local comm_dish = union
		{
			difference
			{
				object {Paraboloid_Z}
				object {Paraboloid_Z	scale 0.999}
				plane {-z,-0.05}
				rotate y * 180
				scale		dock_radius1/4
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
	
		// comms trusses
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
				translate	-y*dock_radius1 * 5/6
				rotate		+z * 000
			}
			object
			{
				comm_truss
				translate	-y*dock_radius1 * 5/6
				rotate		+z * 000
			}
			object
			{
				comm_dish
				translate	-y*dock_radius1 * 5/6
				rotate		+z * 040
			}
			object
			{
				comm_truss
				translate	-y*dock_radius1 * 5/6
				rotate		+z * 040
			}
			object
			{
				comm_anten
				translate	-y*dock_radius1 * 5/6
				rotate		+z * 330
			}
			translate	-z*(habitat_length/2)
			rotate		y * 180
			texture {white_metal_texture}
		}
	#end

	//------------------------------------------------------------------------------Solar Panels

	#if (!NoPanels)
		#declare truss_sides = mini_truss_sides;
		#declare truss_radius = mini_truss_radius;
		#declare truss_thickness = mini_truss_thick;
		#declare truss_point1 = 0;
		#declare truss_point2 = +x * (panel_width + panel_gap) * (panel_number + 0);
		#declare truss_sections = VDist(truss_point1, truss_point2) / mini_truss_section_size;
		#local solar_truss1 = object
		{
			#include "truss.inc"
			texture {white_metal_texture}
		}
		#declare truss_sides = mini_truss_sides;
		#declare truss_radius = mini_truss_radius;
		#declare truss_thickness = mini_truss_thick;
		#declare truss_point1 = -y * panel_length * 3/2;
		#declare truss_point2 = +y * panel_length * 3/2;
		#declare truss_sections = VDist(truss_point1, truss_point2) / mini_truss_section_size;
		#local solar_truss2 = object
		{
			#include "truss.inc"
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
						translate x * (panel_width/2 + (panel_width + panel_gap) * (panels_cnt + 0))
					}
					#local panels_cnt = panels_cnt + 1;
				#end
				object {solar_truss1}
				rotate +x * solar_deg_x
				translate +x*outer_shell_radius1
				rotate +z * solar_deg_z
				translate +z * solar_dis_z
			}
		#end
		union
		{	
			object {solar_group(-panel_rotate, 180, 0) translate +y * panel_length * 3/2}
			object {solar_group(-panel_rotate, 180, 0) translate -y * panel_length * 3/2}
			object {solar_truss2 translate -x * outer_shell_radius1}
			translate -x * panel_width
		}
		union
		{

			object {solar_group(+panel_rotate, 000, 0) translate +y * panel_length * 3/2}
			object {solar_group(+panel_rotate, 000, 0) translate -y * panel_length * 3/2}
			object {solar_truss2 translate +x * outer_shell_radius1}
			translate +x * panel_width
		}
	#end

	//------------------------------------------------------------------------------Blinky Lights & Thrusters

	#local blinky_group = union
	{
		object {blinky_sphere	translate <0,-dock_radius1-blinky_radius,-habitat_length/2-ring_length-dock_length>}
		object {blinky_sphere	translate <0,-outer_shell_radius1-blinky_radius,-habitat_length/2>}
		object {blinky_sphere	translate <0,-outer_shell_radius1-blinky_radius,+habitat_length/2>}
	}
	object {blinky_group	rotate +z * 030}
		object {blinky_group	rotate +z * 090}
	#if (ShowWhole)
		object {blinky_group	rotate +z * 150}
		object {blinky_group	rotate +z * 210}
	#end
		object {blinky_group	rotate +z * 270}
	object {blinky_group	rotate +z * 330}


	#local thruster = union
	{
		cone {<0, 0, 0>, 0, <0, 0, -2>, 1 open hollow}
		cylinder {<0, 0, 0>, <0, 0, -2*0.4>, 0.4 open hollow}
		scale 1/2
	}
	#local thruster_tank_radius = city_units*12;
	#local thruster_aggregate = union
	{
		sphere {0,1}
		object {thruster	translate <0, 0, -3>}
		object {thruster	rotate <0, 180, 0> translate <0, 0, +3>}
		object {thruster	rotate <0, 090, 0> translate <-1, 0, 0>}
		object {thruster	rotate <0, 270, 0> translate <+1, 0, 0>}
		object {thruster	rotate <270, 0, 0> translate <0, -1, 0>}
		object {fuel_tank(4,1)}
		scale thruster_tank_radius
	}
	#local thruster_group = union
	{
//		object {thruster_aggregate	translate <0,-dock_radius1-thruster_tank_radius,-habitat_length/2-ring_length-dock_length>}
		object {thruster_aggregate	translate <0,-(outer_shell_radius1+thruster_tank_radius*2),-habitat_length/2>}
		object {thruster_aggregate	translate <0,-(outer_shell_radius1+thruster_tank_radius*2),+habitat_length/2-ring_length>}
		pigment {rgb 1}
	}
	object {thruster_group	rotate +z * 300}
	object {thruster_group	rotate +z * 000}
	object {thruster_group	rotate +z * 060}
	#if (ShowWhole)
		object {thruster_group	rotate +z * 120}
		object {thruster_group	rotate +z * 180}
		object {thruster_group	rotate +z * 240}
	#end

//	object {thruster	scale 32 rotate y * 180	translate <0,0,+dock_start>}
#end


//------------------------------------------------------------------------------Neighboring Craft

#if (!NoShips)
/*
	// http://skotan.deviantart.com/art/Aquila-Mk-I-spacecraft-185944452
	union
	{
		verbose_include("Aquila-Mk_I.pov", 0)
		scale		32
		translate	+x * outer_shell_radius1
		translate	-z * dock_start
	}
*/
	// http://povrayinclude.wytraven.com/links.html
	union
	{
		verbose_include("SPACESHP.POV", 0)
		scale		2
		rotate		+x * 090
		translate	-y * 0
		translate	+x * (outer_shell_radius1 + city_units * 128)
		translate	-z * (city_length/2 + ring_length)
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
			+z*city_length/2, -z*city_length/2, city_radius
		}
		#if (!ShowWhole)
			object {cutaway_object1}
		#end
		material {atmos_material}
		hollow
		rotate +z * (city_rotate)
	}
#end

//------------------------------------------------------------------------------Text
/*
text
{
//	ttf "impact.ttf" "Just a minute..." 0.1, 0
	ttf "Haettenschweiler.ttf" "www.GearHeadRPG.com" 0.1, 0
	texture {white_metal_texture}
	scale outer_shell_radius1/4
	rotate +x * 30
	rotate +y * 45
	translate <outer_shell_radius1*3/2,0,-outer_shell_radius1*1/4>
}

text
{
//	ttf "impact.ttf" "Just a minute..." 0.1, 0
	ttf "FontdSpaTT.ttf" "Athera" 0.1, 0
	texture {white_metal_texture}
	scale outer_shell_radius1/4
	rotate +x * 30
	rotate +y * 45
	translate <outer_shell_radius1*3/2,0,-outer_shell_radius1*1/4>
}

text
{
//	ttf "impact.ttf" "Just a minute..." 0.1, 0
	ttf "FontdinerSwanky.ttf" "Visit" 0.1, 0
	texture {white_metal_texture}
	scale outer_shell_radius1/4
	rotate +x * 30
	rotate +y * 45
	translate <outer_shell_radius1*3/2,0,-outer_shell_radius1*1/4>
}

text
{
//	ttf "impact.ttf" "Just a minute..." 0.1, 0
	ttf "FontdinerSwanky.ttf" "today!" 0.1, 0
	texture {white_metal_texture}
	scale outer_shell_radius1/4
	rotate +x * 30
	rotate +y * 45
	translate <outer_shell_radius1*3/2,0,-outer_shell_radius1*1/4>
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
	rotate +x * 90
	rotate +y * 90
	translate -x * outer_shell_radius1 * 5/2
	translate +z * outer_shell_radius1 * 5/2
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
#debug concat("total_length = ",str(total_length,0,0),"\n")
#debug concat("city_circum = ",str(city_circum,0,0),"\n")
#debug concat("city_radius = ",str(city_radius,0,0),"\n")
#debug "\n"
