// Title: Minimal citygen test scene
// Authors: Michael Horvath
// Website: http://isometricland.net
// Updated: 2017-04-05
// This file is licensed under the terms of the CC-LGPL.
// http://www.gnu.org/licenses/lgpl-2.1.html
//
// Dependencies:
// 1. CITY GENERATOR INCLUDE FILE by Chris Colefax (heavily modified by myself)
// 2. Rune's particle system
//
// need to migrate all includes to the GearHead directory
// raumschiff needs a bounding box

//+KFI0 +KFF5 +KC +KI0 +KF0
//+KFI5 +KFF5 +KC
//+K0 +KC

#version 3.7;

#include "CIE.inc"		// http://www.ignorancia.org/en/index.php?page=Lightsys
#include "lightsys.inc"		// http://www.ignorancia.org/en/index.php?page=Lightsys
#include "math.inc"
#include "shapes.inc"
#include "finish.inc"
#include "metals.inc"
#include "colors.inc"

// inter-scene variables
#declare pov_version		= 1;				// 0 = 3.6; 1 = 3.7; 3.7 also has gamma adjustments in INI file
#declare Seed			= seed(72464);
#declare Tiles			= 1;				// the default size of the scene, measured in tiles. Use this to zoom in/out.
#declare Sprite_Height		= 128;				// changes the camera's position. 0 for mecha, 1 for walls & terrain.
#declare Width			= 8;				// the default width of a tile.
#declare Subdivision		= 0;				// turn on/off mesh subdivision. This requires a special exe available on the Net.
#declare Included		= 1;				// tells any included files that they are being included.
#declare TexQual		= 2;
#declare Meters			= 1;
#declare city_seed		= 929843;

// toggles
#declare NoColors		= 0;
#declare NoCity			= 0;
#declare NoRadiosity		= 1;
#declare NoLights		= 0;				// not used
#declare NoSky			= 0;				// not used
#declare NoLamp			= 0;
#declare NoStreet		= 0;
#declare NoBuildings		= 0;
#declare NewTrain		= 1;				// boolean, use maglev instead of streetcars
#declare NoCars			= 0;				// boolean
#declare AlwaysReflect		= 0;				// ???
#declare debug_progress		= 1;				// boolean, see CityGen docs
#declare NoStation		= 0;				// boolean
#declare NoStreetDeco		= 0;				// boolean
#declare NoPedestrians		= 0;				// boolean
#declare glass_hollow	= 0;//					// boolean, used by CityGen, does this render faster or slower?
#declare glass_thin	= 1;//					// boolean, used by CityGen, should not be mutually exclusive with glass_hollow, not all buildings' glass has an ior value, need to double check
#declare bound_fit	= 0;//					// boolean, used by CityGen, should bounding boxes be rotated and closer fit but not parallel to coordinate axes? otherwise, bounding boxes are parallel to coordinate axes but larger and less fit
#declare debug_progress	= 0;//					// boolean, used by CityGen, see CityGen docs
#declare GlassColor	= 0;//					// integer, dome glass color, 0 = gold, 1 = clear white. need to deprecate this
#declare NoseMode	= 0;//					// integer, 0 for textured paraboloid, 1 for web of connected cylinders (textured version is slower)
#declare SimpleLamp	= 0;//					// boolean, type of light at center of each habitat section, 0 = area light, 1 = single point light
#declare city_use_mesh	= 0;//					// boolean, replace some basic CSG shapes with meshes? may not work 100% of the time
#declare BothHabitats	= 1;//					// boolean, render both habitats or just one, should normally never be disabled

// citygen variables (mostly)
#declare city_rotate		= 0;					// float, degrees	22.5
#declare city_night		= false;				// boolean, obsolete?
#declare city_right_hand_drive	= false;				// boolean
#declare city_default_objects	= false;				// boolean
#declare city_use_mesh		= false;				// boolean
#declare city_all_mesh		= false;				// boolean
#declare city_tileable		= "dummy text";					// boolean, turning this off has weird side-effects!!
#declare city_storey_height	= Meters * 3.5;				// float, for reference, people are between 1.0 and 2.0 meters tall
#declare city_ped_density	= 1/64/Meters;				// float, so far this is just used for sidewalks along streets, it should be used everywhere there are pedestrians
#declare city_grass_height	= Meters / 4;				// too thin and it gets clipped by the pavement
#declare city_tree_height	= Meters * 12;				// float
#declare city_hide_buildings	= NoBuildings;				// boolean
#declare total_lanes		= (NewTrain ? 2 : 2);			// integer, in both directions, including half lanes for bikes (minimum 2)
#declare nominal_traffic_width	= Meters * (NewTrain ? 8 : 8);		// float
#declare nominal_building_width	= Meters * 64;				// float
#declare traffic_spacing	= Meters * 256;				// float
#declare traffic_width		= nominal_traffic_width/total_lanes;	// float
#declare traffic_lanes		= floor(total_lanes/2);			// integer, in each direction...
#declare pavement_width		= Meters * 4;				// float
#declare building_width		= nominal_building_width - pavement_width * 2;			// float
#declare min_building_height	= city_storey_height * 6;		// float
#declare max_building_height	= city_storey_height * 12;		// float
#declare building_height_turb	= 1;					// float, between 0 and 1
#declare street_height		= 0;					// to do, may conflict with citygen...
#declare street_width		= nominal_traffic_width;		// float
#declare rail_ped_thick		= Meters;				// float, rail pedestal leg
#declare rail_width		= street_width/2;			// float
#declare rail_height		= Meters * 5;				// float
#declare rail_thick		= Meters/2;				// float
#declare rail_plat_thick	= Meters/2;				// float
#declare rail_plat_radius	= street_width;				// float
#declare rail_ramp_width	= Meters * 2;				// float
#declare rail_cars_number	= 3;					// integer, odd values only
#declare rail_cars_height	= Meters * 3;				// float
#declare rail_buffer		= Meters * 22;
#declare big_block_length	= nominal_traffic_width + nominal_building_width * 4;		// float
#declare sml_block_length	= nominal_traffic_width + nominal_building_width * 1;		// float
#declare city_sections		= <2,0,1>;				// vector of integers
#declare city_circum		= (big_block_length * 2 + sml_block_length * 2) * city_sections.x;		// float, the inner circumference of the spinner colony
#declare city_length		= (big_block_length * 1 + sml_block_length * 2 + nominal_traffic_width) * city_sections.z;		// float, the length of the city along the long axis
#declare city_radius		= city_circum/2/pi;			// float, the radius of the spinner colony's ground surface
#declare big_block_angle	= big_block_length/city_circum * 360;
#declare sml_block_angle	= sml_block_length/city_circum * 360;
#declare street_angle		= street_width/city_circum * 360;
#declare streetlamp_number	= 4;					// integer, the number present on each side of a building
#declare trashcan_number	= 3;					// integer, the number present on each side of a building
#declare pottedplant_number	= 5;					// integer, the number present on each side of a building
#declare people_max_height	= Meters * 2;				// float



// scene variables (mostly)
#declare light_lumens			= 2.3;				// float
#declare light_temp			= Daylight(6500);		// float?
#declare light_color			= Light_Color(Daylight(6500),2.3);

#declare Camera_Mode		= 3;					// 0 to 8; 0 = orthographic; 1 = oblique; 2 = perspective
#declare Camera_Diagonal	= cosd(45);
#declare Camera_Vertical	= 45;					//45;
#declare Camera_Horizontal	= 30;					//30;
//#declare Camera_Vertical	= 00;					//45;
//#declare Camera_Horizontal	= 90;					//30;
#declare Camera_Aspect		= image_height/image_width;
#declare Camera_Distance	= 128;
#declare Camera_Translate	= <0,-city_radius,0,>;			//<0,0,-city_size_total.y,>
#declare Camera_Scale		= 64;					//32 is good for a 4x4 city block
#include "gh_camera.inc"


//------------------------------------------------------------------------------Macros

#macro gamma_color_adjust(in_color)
	color srgbft in_color + <0,0,0,0,0>
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
#macro lowqual_pig(in_seed)
	gamma_color_adjust(<rand(in_seed),rand(in_seed),rand(in_seed),0,0>)
#end


//------------------------------------------------------------------------------Global settings

default {finish {ambient 0 diffuse 1}}

global_settings
{
	charset utf8
	assumed_gamma	1.0
	#if (!NoRadiosity)
		verbose_include("rad_def.inc")
		radiosity {Rad_Settings(Radiosity_OutdoorLight, off, off)}
	#end
	#switch (TexQual)
		#case (-1)
			max_trace_level 0
		#break
		#case (0)
			max_trace_level 4
		#break
		#case (1)
			max_trace_level 16
		#break
		#case (2)
			max_trace_level 64
		#break
	#end
}


//------------------------------------------------------------------------------Textures

#declare city_rail_texture = texture
{
	pigment {gamma_color_adjust(<1,1,1>*8/8)}
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


//------------------------------------------------------------------------------Lights & Sky

light_source
{
	<-15000, +15000, -15000> * <1/4,1,1/2>
	light_color					// don't adjust gamma here
	translate -y * city_radius
	parallel
	point_at 0
//	shadowless
}
/*
light_source
{
	Camera_Location
	light_color/2					// don't adjust gamma here
	parallel
	point_at 0
}
*/

sky_sphere {pigment {gamma_color_adjust(<223/255,230/255,255/255>)}}


//------------------------------------------------------------------------------City

#if (!NoCity)
	//------------------------------------------------------------------------------Main City

	#declare buildings_per_block	= <4,0,4,>;
	#declare blocks_per_section	= <2,0,2,>;
	#declare NoRailX1		= 0;
	#declare NoRailZ1		= 0;
	#declare NoRailX2		= 1;
	#declare NoRailZ2		= 0;
	#declare NoStreetX1		= 0;
	#declare NoStreetZ1		= 0;
	#declare NoStreetX2		= 1;
	#declare NoStreetZ2		= 0;
	#declare NoStation		= 0;
	#declare NoCarsX		= 0;
	#declare NoCarsZ		= 0;
	verbose_include("CG_INIT_CURVED.INC", 0)
	verbose_include("CG_VEHICLES_CURVED.INC", 0)
	verbose_include("CG_PAVEMENT_CURVED.INC", 0)
//	init_building_types()
//	verbose_include("CG_SQUARE_CURVED.INC", 0)
	init_building_types()
	verbose_include("CG_PARK_CURVED.INC", 0)
//	init_building_types()
//	verbose_include("CG_NORMAL_CURVED.INC", 0)
	object
	{
		verbose_include("CG_CITY_CURVED.inc", 0)
	}
#end


//------------------------------------------------------------------------------Alignment

cylinder
{
	0,+x*256, 1/2
	pigment {color rgb x}
	translate -y * city_radius
}
cylinder
{
	0,+y*256, 1/2
	pigment {color rgb y}
	translate -y * city_radius
}
cylinder
{
	0,+z*256, 1/2
	pigment {color rgb z}
	translate -y * city_radius
}
