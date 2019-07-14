// Desc: Several GearHead mecha battling it out in a city setting.
// Auth: Michael Horvath
// Home Page: http://www.geocities.com/Area51/Quadrant/3864/gearhead.htm
// This file is licensed under the terms of the CC-LGPL.
// Dependencies:
// 1. CITY GENERATOR INCLUDE FILE by Chris Colefax (modified)
// 2. Rune's particle system

// Not sure if turning antialiasing on is worth it since Panosalado does its own antialiasing.
// +KFI0 +KFF5 +KC +KI0 +KF1
// +KFI5 +KFF5 +KC
// +K0 +KC
// +SC0.5 +EC1.0 +SR0.3 +ER0.7
// +SC0.5 +EC1.0 +SR0.25 +ER0.75
// +SC0.5 +EC1.0 +SR0.5 +ER1.0

// make the cylinder narrower, either by increasing its length or decreasing its diameter
// decrease the number of street lanes by half and double the size of buildings
// improve the appearance of spokes
// shadows against end caps are ugly
// lens flare?

#include "colors.inc"
#include "metals.inc"
#include "glass.inc"
#include "transforms.inc"
#include "stars.inc"
#include "skies.inc"
#include "metals.inc"
#include "CIE.inc"
#include "lightsys.inc"
#include "strings.inc"

// inter-scene variables
#declare pov_version		= 0;					// obsolete? 0 = 3.6; 1 = 3.7; 3.7 also has gamma adjustments in INI file
#declare Seed			= seed(8829464);			// integer, needed by mecha & other GearHead objects
#declare Subdivision		= 0;					// boolean, turn on/off mesh subdivision - this requires a special exe available on the Net
#declare Included		= 0;					// boolean, tells any included files that they are being included.
#declare Sprite_Height		= 128;					// float, needed by mecha & other GearHead objects, changes the camera's position. 0 for mecha, 1 for walls & terrain.
#declare Width			= 8;					// float, needed by mecha & other GearHead objects, 64?, messes up the camera
#declare Tiles			= 1;					// integer, needed by mecha & other GearHead objects
#declare TexQual		= 0;					// float, quality of the textures, 0, 0.5, or 1
#declare Meters		= 1;					// float, should not be used anywhere directly

// toggles
#declare NoLens			= 1;					// boolean, lens flare (use photoshop instead?)
#declare NoPlanet		= 1;					// boolean, toggle Jupiter, Sun, whatever
#declare NoCity			= 0;					// boolean, toggle city
#declare MiniCity		= 1;					// boolean, city debug sections only
#declare NoShell		= 1;					// boolean, toggle outer shell, spokes and endcaps
#declare NoLamp			= 0;					// boolean, toggle visible lamp object
#declare NoSky			= 0;					// boolean, toggle starry space texture
#declare NoAtmos		= 1;					// boolean, toggle atmosphere
#declare NoRadiosity		= 1;					// boolean, toggle radiosity
#declare NoLights		= 1;					// boolean, toggle light sources
#declare NoSmoke		= 1;					// boolean, not implemented any more or obsolete
#declare NoMechs		= 1;					// boolean, not implemented any more or obsolete
#declare NoMissiles		= 1;					// boolean, not implemented any more or obsolete
#declare NoBullets		= 1;					// boolean, not implemented any more or obsolete
#declare NoText			= 1;					// boolean, not implemented any more or obsolete
#declare NoLampShade		= 1;					// boolean, not implemented any more or obsolete
#declare NoFakeSky		= 1;					// boolean, not implemented any more or obsolete
#declare NoCars			= 1;
#declare NoStreet		= 1;
#declare NoDomes		= 1;
#declare NewTrain		= 1;					// new train models
#declare FadePower		= 0;					// boolean, realistic lights with fade power?
#declare AlwaysReflect		= 0;
#declare SunInstead		= 1;

// citygen variables (mostly)
#declare city_tileable		= 1;					// boolean, see CityGen docs
#declare city_night		= 0;					// boolean, see CityGen docs
#declare city_right_hand_drive	= 0;					// boolean, see CityGen docs
#declare city_default_objects	= 0;					// boolean, see CityGen docs
#declare city_use_mesh		= 0;					// boolean, use meshes instead of cylinders, cones, etc.
#declare city_all_mesh		= 0;					// boolean, use meshes for streets and pavement as well?
#declare debug_progress		= 1;					// boolean, see CityGen docs
#declare glass_hollow		= 0;					// boolean, in most cases should be true if TexQual = 1
#declare glass_thin		= 0;					// boolean, in most cases should be true if TexQual = 1
#declare bound_fit		= 1;					// boolean, the type of bounding used for buildings
#declare city_storey_height	= Meters * 2;			// float, how tall are the building storeys?
#declare city_ped_density	= 1/4/Meters;
// centimeters? meters?
#declare Lightsys_Scene_Scale	= Meters * 100;			// float, see lightsys docs
#declare city_grass_height	= Meters / 4;			// float, how tall is the grass?
#declare city_tree_height	= Meters * 6;			// float, how tall are the trees?
#local total_lanes		= 3;					// integer, don't like how citygen handles streets, would rather set the lane width and number of lanes
#local nominal_building_width	= Meters * 32;			// float, building width before subtracting sidewalks, don't like CityGen in this case :(
#local nominal_traffic_width	= 0;					// float, street width before splitting into lanes, don't like CityGen in this case :(
#declare rail_height		= Meters * 8;
#declare buildings_per_block	= <2,3,0,>;				// 2D integer vector, re-set elsewhere, 3x4 including roads
#declare city_block_count	= <1,1,0,>;				// 2D integer vector, re-set elsewhere
#declare traffic_spacing	= Meters * 128;			// float, see CityGen docs
#declare traffic_width		= nominal_traffic_width/total_lanes;	// float, see CityGen docs
#declare traffic_lanes		= (total_lanes-1)/2;			// integer, see CityGen docs
#declare pavement_width		= Meters * 2;			// float, see CityGen docs
#declare building_gap		= pavement_width * 2;			// float, see CityGen docs
#declare building_width		= nominal_building_width - pavement_width * 2;	// float, see CityGen docs
#declare min_building_height	= Meters * 12;			// float, see CityGen docs, 16
#declare max_building_height	= Meters * 24;			// float, see CityGen docs, 32
#declare building_height_turb	= 1;					// float 0 to 1, see CityGen docs
#declare block_dist_x		= nominal_traffic_width + nominal_building_width * buildings_per_block.x;	// float, ignores city_tileable
#declare block_dist_z		= nominal_traffic_width + nominal_building_width * buildings_per_block.y;	// float, ignores city_tileable
#declare city_length		= block_dist_z * city_block_count.y * city_sections.y		// city blocks
				+ 2 * (nominal_traffic_width + nominal_building_width);		// end border grass
#declare city_circum		= block_dist_x * city_block_count.x * city_sections.x;		// float, the circumference of the spinner colony
#declare city_radius		= city_circum/2/pi;			// float, the radius of the spinner colony
#declare city_rotate		= 30;					// float, rotate the inner shell containing the city by this amount in degrees

// scene variables (mostly)
#local city_sections		= 4;					// integer
#local block_dist_x		= nominal_traffic_width + nominal_building_width * buildings_per_block.x;	// float, ignores city_tileable
#local block_dist_z		= nominal_traffic_width + nominal_building_width * buildings_per_block.y;	// float, ignores city_tileable
#local total_length		= block_dist_z * city_block_count.y * city_sections		// city blocks
				+ block_dist_z * 1 * (city_sections - 1)			// middle grass and parks
				+ 2 * (nominal_traffic_width + nominal_building_width);		// end border grass
#debug concat("\ntotal_length = ",str(total_length,0,0),"\n\n")
#local spoke_total		= 5;					// integer, the number of radial city sections
#local spoke_angle		= 360/spoke_total;			// float, the angle separating each section (should be hidden)
#local slice_total		= 25;					// integer, the number of radial city blocks, needs to be divisible by spoke_total
#local slice_angle		= 360/slice_total;			// float, the angle between each block (should be hidden)
#declare city_circum		= block_dist_x * slice_total;		// float, the circumference of the spinner colony
#declare city_radius		= city_circum/2/pi;			// float, the radius of the spinner colony
#local cap_thickness		= Meters * 4;			// float, the thickness of the spinner shell
#local lamp_radius		= Meters * 4;			// float, the radius of the fusion lamp
#local cap_zscale		= 1/2;					// float, makes the endcaps ellipsoidal instead of spherical
#local light_lumens		= 2.3 * 3/2;				// float
#local light_temp		= Daylight(5500);			// float?
#local nominal_slice_total 	= (MiniCity ? slice_total : slice_total);		// integer, can't remember what this was for
#local planet_distance		= 385000000/10000;			// meters
#local planet_radius		=   6371000/10000;			// meters
#local sun_distance		= 149600000/10000;			// kilometers
#local sun_radius		=    695500/10000;			// kilometers
#local lamp_length = total_length + (city_radius - cap_thickness) * 2 * cap_zscale;
#if (TexQual = 1)
	#local lamp_number = floor(lamp_length/32);
#else
	#local lamp_number = floor(lamp_length/64);
#end

// legacy stuff from GearHead outdoor scene, may be re-implemented in the future but is currently not used
#local AirCarPosition		= <-32,+32,+32,>;			// float vector
#local KojedoPosition		= +x * block_dist_x;			// float vector	
#local MaanjiPosition		= -x * block_dist_x;			// float vector
#local KojedoCenter		= <0,4,0,>;				// float vector
#local LineVector		= vnormalize(-AirCarPosition + KojedoCenter + KojedoPosition);	// float vector
#local Burst			= true;					// boolean

// camera variables
#declare Camera_Mode		= 2;					// 0 to 8; 0 = orthographic; 1 = oblique; 2 = perspective
#declare Camera_Diagonal	= cosd(45);
#declare Camera_Vertical	= 0;					// 22.5?
#declare Camera_Horizontal	= 0;					// 30?
#declare Camera_Aspect		= image_height/image_width;
#declare Camera_Distance	= Meters * 16;
//#declare Camera_Scale		= (Camera_Mode = 3 ? 64 : 2);
#declare Camera_Scale		= 1;
#declare Camera_Translate	= <0,-(city_radius - Meters * 32)/Camera_Scale,-block_dist_z/Camera_Scale,>;	// slightly down and behind, full render
//#declare Camera_Translate	= <0,0,0,>;										// down the barrel, turn lamp off first
//#declare Camera_Translate	= <0,0,+total_length/2/Camera_Scale,>;							// ortho side view of endcaps, turn camera 90 degrees first

/*
#if (frame_number = 1)
	#debug "\n\nFRAME1FRAME1FRAME1FRAME1FRAME1FRAME1FRAME1FRAME1FRAME1\n\n"
	#declare city_use_mesh		= true;
	#declare city_all_mesh		= true;
#else
	#debug "\n\nFRAME2FRAME2FRAME2FRAME2FRAME2FRAME2FRAME2FRAME2FRAME2\n\n"
	#declare city_use_mesh		= false;
	#declare city_all_mesh		= false;
#end
*/


//------------------------------------------------------------------------------Macros

#macro get_traffic_spacing(s_count)
	abs(tand(s_count/slice_total * 180)) * 16 + 4
#end
#macro gamma_color_adjust(in_color)
	#local out_gamma = 2.2;
	#local in_color = in_color + <0,0,0,0,0>;
	color rgbft
	<
		pow(in_color.red,	out_gamma),
		pow(in_color.green,	out_gamma),
		pow(in_color.blue,	out_gamma),
		in_color.filter,
		in_color.transmit
	>
#end
#macro toChar(n)
	#local astring = "0123456789ABCDEF";
	substr(astring, n + 1, 1)
#end
#macro toHex(d)
	#local r = mod(d, 16);
	#if ((d - r) = 0) 
		#local out = toChar(r);
	#else 
		#local out = concat(toHex((d - r)/16), toChar(r));
	#end
	out
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
	((in_vector_2.x>in_vector_1.x)&(in_vector_2.y>in_vector_1.y)&(in_vector_2.z>in_vector_1.z))
#end
#macro str_def(in_value)
	str(in_value,0,-1)
#end
#macro verbose_include(in_file, in_bool)
	#if (in_bool)
		#debug concat("...Already included ", in_file, ", skipping...\n")
	#else
		#debug concat("Starting to include ", in_file, "...\n")
		#include in_file
		#debug concat("...Finished including ", in_file, "\n\n")
	#end
#end
#macro verbose_parse_string(in_string)
//	#debug concat("Parsing \"", in_string, "\"\n")
	Parse_String(in_string)
#end


//------------------------------------------------------------------------------Global settings

default {finish {ambient 0 diffuse 1}}

global_settings
{
	charset utf8
	#if (version < 3.7)
		assumed_gamma	1.0
	#end
	#if (!NoRadiosity)
		verbose_include("rad_def.inc", defined(Rad_Settings))
		radiosity {Rad_Settings(Radiosity_OutdoorLight, off, off)}
	#end
	#switch (TexQual)
		#case (0)
			max_trace_level 4
		#break
		#case (1/2)
//			max_trace_level 16
			max_trace_level 8
		#break
		#case (1)
			max_trace_level 64
		#break
	#end
}


verbose_include("CG_PRIMITIVES_CURVED_MESH.INC", defined(prim_radial_sections))


//------------------------------------------------------------------------------Camera

#include "gh_camera.inc"


//------------------------------------------------------------------------------Textures/materials

#local sky_pigment_1 = pigment
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
		[0.5	gamma_color_adjust(<0.50,0.60,1.00,>)]
		[1.0	gamma_color_adjust(<0.50,0.60,1.00,>)]
	}
	scale 32
}
#local sky_pigment_2 = pigment {sky_pigment_1 transmit 1}
#local sky_pigment_3 = pigment
{
	radial
	pigment_map
	{
		[0/2	sky_pigment_1]
		[1/2	sky_pigment_2]
		[2/2	sky_pigment_1]
	}
	rotate x * 90
}
#local starfield_pigment_0 = pigment
{
	bozo
	color_map
	{
		[0.0 color rgb 3]
		[0.2 color rgb 0]
		[1.0 color rgb 0]
	}
	scale 0.001
}
#local starfield_pigment_1 = pigment
{
	granite
	color_map
	{
		[0.000 0.270 gamma_color_adjust(< 0, 0, 0, 0, 1>) gamma_color_adjust(< 0, 0, 0, 0, 1>)]
		[0.270 0.280 gamma_color_adjust(<.5,.5,.4, 0, 0>) gamma_color_adjust(<.8,.8,.4, 0, 0>)]
		[0.280 0.470 gamma_color_adjust(< 0, 0, 0, 0, 1>) gamma_color_adjust(< 0, 0, 0, 0, 1>)]
		[0.470 0.480 gamma_color_adjust(<.4,.4,.5, 0, 0>) gamma_color_adjust(<.4,.4,.8, 0, 0>)]
		[0.480 0.680 gamma_color_adjust(< 0, 0, 0, 0, 1>) gamma_color_adjust(< 0, 0, 0, 0, 1>)]
		[0.680 0.690 gamma_color_adjust(<.5,.4,.4, 0, 0>) gamma_color_adjust(<.8,.4,.4, 0, 0>)]
		[0.690 0.880 gamma_color_adjust(< 0, 0, 0, 0, 1>) gamma_color_adjust(< 0, 0, 0, 0, 1>)]
		[0.880 0.890 gamma_color_adjust(<.5,.5,.5, 0, 0>) gamma_color_adjust(< 1, 1, 1, 0, 0>)]
		[0.890 1.000 gamma_color_adjust(< 0, 0, 0, 0, 1>) gamma_color_adjust(< 0, 0, 0, 0, 1>)]
	}
	turbulence 1
	sine_wave
	scale 5
}
#local starfield_pigment_2 = pigment {starfield_pigment_1 transmit 1}
#local starfield_pigment_3 = pigment
{
	radial
	pigment_map
	{
		[0/2	starfield_pigment_1]
		[1/2	starfield_pigment_2]
		[2/2	starfield_pigment_1]
	}
	rotate x * 90
}
#local shade_pigment = pigment
{
	radial
	color_map
	{
		[0/2	rgbt <0,0,0,0,>]
		[1/3	rgbt <0,0,0,1,>]
		[2/3	rgbt <0,0,0,1,>]
		[2/2	rgbt <0,0,0,0,>]
	}
	rotate x * 90
}
#local grass_pigment_1 = pigment
{
//	image_map {png "olivepink_marble.png" #if (version >= 3.7) file_gamma srgb #end}
	image_map {png "olivepink_marble.png"}
	translate	y * -1/2
	translate	x * -1/2
	rotate		x * 90
	scale		<slice_total * block_dist_x,1,slice_total * block_dist_x,>
}
#local grass_pigment_2 = pigment
{
//	gamma_color_adjust(<046,104,058,>/255/2)
	gamma_color_adjust(<110,160,008,>/255/2*1.3)	// oyonale makegrass color
}
#local grass_pigment_3 = pigment
{
	average
	pigment_map
	{
		[1	grass_pigment_1]
		[2	grass_pigment_2]
	}
}
#local grass_texture_1 = texture
{
	pigment {grass_pigment_3}
	normal {wrinkles}
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
				4, <0.2,0.4,1.0>/1000000	// crappy approximaion of TerraPOV value
				extinction	1
			}
/*
			density
			{
				cylindrical
				poly_wave	0.25
				density_map
				{
					// should be based on Meters!!!
					[0	rgb 100/5000000]
					[1	rgb 010/5000000]
				}
				scale	city_radius
				rotate	x * 90
			} 
*/
		}
	}
}
/*
#local earth_surface	= pigment {image_map {png "EarthMapAtmos_2500x1250.png"	map_type 1 #if (version >= 3.7) file_gamma srgb #end}}
#local earth_lights	= pigment {image_map {png    "EarthNight_2500x1250.png"	map_type 1 #if (version >= 3.7) file_gamma srgb #end}}
#local earth_clouds	= pigment {image_map {png   "EarthClouds_2500x1250.png"	map_type 1 #if (version >= 3.7) file_gamma srgb #end}}
*/
#switch (TexQual)
	#case (0)
		#local planet_texture		= texture {pigment {gamma_color_adjust(<rand(Seed),rand(Seed),rand(Seed)>)}}
		#local cap_metal_finish		= finish {}
		#local cap_metal_texture	= texture {pigment {gamma_color_adjust(<rand(Seed),rand(Seed),rand(Seed)>)}}
		#local cap_glass_material	= material {texture {pigment {gamma_color_adjust(<rand(Seed),rand(Seed),rand(Seed)>)}}}
		#local lamp_material = material
		{
			texture
			{
				pigment {color Light_Color(light_temp,light_lumens)}
				finish {ambient 1}
			}
		}
	#break
	#case (1/2)
		#local planet_material = material
		{
			texture {pigment {earth_surface	}}
			texture {pigment {earth_lights	}	finish {ambient 1}}
			texture {pigment {earth_clouds	}}
		}
		#local cap_metal_finish = finish
		{
			ambient		0.35
			brilliance	2
			diffuse		0.3
			metallic
			specular	0.80
			roughness	1/20
//			reflection {0.01, 0.1}
			reflection {0.001, 0.01}	// try to tone down reflection
		}
		#local cap_metal_texture = texture
		{
			pigment {gamma_color_adjust(<0.20, 0.20, 0.20>)}
			finish {cap_metal_finish}
		}
		#local cap_glass_material = material
		{
			texture
			{
				pigment	{gamma_color_adjust(<0.97, 0.99, 0.98, 0.00, 0.90>)}
				finish
				{
					specular	0.8
					roughness	0.001
					ambient		0
					diffuse		0
//					reflection {0.01, 0.1}
					reflection {0.001, 0.01}	// try to tone down reflection
					conserve_energy
				}
			}
		}
		#local lamp_material = material
		{
			texture
			{
				pigment {color Light_Color(light_temp,light_lumens)}
				finish {ambient 1}
			}
		}
	#break
	#case (1)
		#local planet_texture = texture
		{
			pigment
			{
				image_map
				{
					png		"jupiter.png" #if (version >= 3.7) file_gamma srgb #end
					map_type	1
				}
			}
		}
		#local cap_metal_finish = finish
		{
			ambient		0.35
			brilliance	2
			diffuse		0.3
			metallic
			specular	0.80
			roughness	1/20
//			reflection {0.01, 0.1}
			reflection {0.001, 0.01}	// try to tone down reflection
		}
		#local cap_metal_texture = texture
		{
			pigment {gamma_color_adjust(<0.20, 0.20, 0.20>)}
			finish {cap_metal_finish}
		}
		#local cap_glass_material = material
		{
			interior {I_Glass1}
			texture
			{
				pigment	{gamma_color_adjust(<0.97, 0.99, 0.98, 0.00, 0.90>)}
				finish
				{
					specular	0.8
					roughness	0.001
					ambient		0
					diffuse		0
//					reflection {0.01, 0.1}
					reflection {0.001, 0.01}	// try to tone down reflection
					conserve_energy
				}
			}
		}
		#local lamp_material = material
		{
			texture {pigment {rgbt 1}}
			interior
			{
				media
				{
					emission Light_Color(light_temp,light_lumens)
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
	#break
#end


//------------------------------------------------------------------------------Sun, planet & sky sphere

// stars
#if (!NoSky)
	sky_sphere {pigment {starfield_pigment_0}}
#end

// sun and/or Jupiter
#if (!NoPlanet)
	#if (!SunInstead)
		#if (FadePower)
			object
			{
				Light(light_temp, light_lumens * 1000000000000, 0, 0, 0, 0, 0)
				translate	z * 1000000000
				rotate		x * -5
				rotate		y * -120
			}
			sphere
			{
				<0,0,0>, planet_radius
				material {planet_material}
				translate	z * planet_distance
			}
		#else
			light_group
			{
				light_source
				{
					0
					gamma_color_adjust(Light_Color(light_temp,light_lumens))
					translate	z * 1000000000
					rotate		x * -5
					rotate		y * -120
				}
				sphere
				{
					<0,0,0>, planet_radius
					material {planet_material}
					translate	z * planet_distance
				}
				global_lights off
			}
		#end
	#else
		#local sun_object = sphere
		{
			0, sun_radius
			texture
			{
				pigment {gamma_color_adjust(Light_Color(light_temp,light_lumens))}
				finish {ambient 1}
			}
		}
		light_source
		{
			0
			gamma_color_adjust(Light_Color(light_temp,light_lumens))
			looks_like {sun_object}
			parallel
			translate	-z * sun_distance
		}
		#if (!NoLens)
			#declare camera_location	= Camera_Location;
			#declare camera_look_at		= Camera_LookAt;
			#declare camera_off		= true;
			#declare effect_location	= -z * sun_distance;
			#declare effect_type		= "Sun";
			#declare effect_scale		= 1/4;
			#include "LENS_MOD.INC"
		#end
	#end
#end


//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------City

// use while loops to place each section (usually a total of 4)
#if (!NoCity)
	union
	{
		#local nominal_spoke_total = 1;
		#local nominal_spoke_total = spoke_total;
		verbose_include("CG_DEFAULT_CURVED_MESH.inc", 0)
		verbose_include("CG_PAVEMENT_CURVED_MESH.INC", 0)
		verbose_include("CG_VEHICLES_CURVED_MESH.inc", 0)
		// city buildings - pass 1 - city buildings
		#declare buildings_per_block	= <2,3,0,>;
		#declare city_block_count	= <slice_total/spoke_total-1,3,0,>;
		#local section_width		= (nominal_building_width * buildings_per_block.x + nominal_traffic_width) * city_block_count.x;
		#local section_length		= (nominal_building_width * buildings_per_block.y + nominal_traffic_width) * city_block_count.y;
//		verbose_include("CG_DEFAULT_CURVED_MESH.inc", 0)
		verbose_include("CG_NORMAL_CURVED_MESH.inc", 0)
		#local spoke_count = 0;
		#while (spoke_count < nominal_spoke_total)
//			#local city_strip = object {verbose_include("CG_CITY.inc", 0)}
			#local city_strip = object {verbose_include("CG_CITY_CURVED_MESH.inc", 0)}
			#local city_strip = object
			{
				city_strip
				rotate		z * spoke_count * spoke_angle
				rotate		z * spoke_angle/2
			}
			// 1
			object {city_strip	translate z * +208}
			#if (!MiniCity)
				object {city_strip	translate z * +624}
				// 2
				object {city_strip	translate z * -208}
				object {city_strip	translate z * -624}
			#end
			#local spoke_count = spoke_count + 1;
		#end
		// city buildings - pass 2 - fountain squares
		#declare buildings_per_block	= <2,3,0,>;
		#declare city_block_count	= <1,1,0,>;
		#local section_width		= (nominal_building_width * buildings_per_block.x + nominal_traffic_width) * city_block_count.x;
		#local section_length		= (nominal_building_width * buildings_per_block.y + nominal_traffic_width) * city_block_count.y;
		verbose_include("CG_DEFAULT_CURVED_MESH.inc", 0)
		verbose_include("CG_SQUARE_CURVED_MESH.inc", 0)
		#local spoke_count		= 0;
		#while (spoke_count < nominal_spoke_total)
			#local city_strip = object {verbose_include("CG_CITY_CURVED_MESH.inc", 0)}
			#local city_strip = object
			{
				city_strip
				rotate		z * spoke_count * spoke_angle
			}
			// 1
			object {city_strip}
			#if (!MiniCity)
				// 2
				object {city_strip	translate z * +416}
				// 3
				object {city_strip	translate z * -416}
			#end
			#local spoke_count = spoke_count + 1;
		#end
		// city buildings - pass 3 - long axis wood bands
		#declare buildings_per_block	= <2,3,0,>;
		#declare city_block_count	= <1,3,0,>;
		#local section_width		= (nominal_building_width * buildings_per_block.x + nominal_traffic_width) * city_block_count.x;
		#local section_length		= (nominal_building_width * buildings_per_block.y + nominal_traffic_width) * city_block_count.y;
		verbose_include("CG_DEFAULT_CURVED_MESH.inc", 0)
		verbose_include("CG_PARK_CURVED_MESH.inc", 0)
		#local spoke_count		= 0;
		#while (spoke_count < nominal_spoke_total)
			#local city_strip = object {verbose_include("CG_CITY_CURVED_MESH.inc", 0)}
			#local city_strip = object
			{
				city_strip
				rotate		z * spoke_count * spoke_angle
			}
			// 1
			object {city_strip	translate z * +208}
			#if (!MiniCity)
				object {city_strip	translate z * +624}
				// 2
				object {city_strip	translate z * -208}
				object {city_strip	translate z * -624}
			#end
			#local spoke_count = spoke_count + 1;
		#end
		// city buildings - pass 4 - circumference wood bands
		#declare buildings_per_block	= <2,3,0,>;
		#declare city_block_count	= <slice_total/spoke_total-1,1,0,>;
		#local section_width		= (nominal_building_width * buildings_per_block.x + nominal_traffic_width) * city_block_count.x;
		#local section_length		= (nominal_building_width * buildings_per_block.y + nominal_traffic_width) * city_block_count.y;
//		verbose_include("CG_DEFAULT_CURVED_MESH.inc", 0)
//		verbose_include("CG_PARK_CURVED_MESH.inc", 0)
		#local spoke_count		= 0;
		#while (spoke_count < nominal_spoke_total)
			#local city_strip = object {verbose_include("CG_CITY_CURVED_MESH.inc", 0)}
			#local city_strip = object
			{
				city_strip
				rotate		z * spoke_count * spoke_angle
				rotate		z * spoke_angle/2
			}
			// 1
			object {city_strip}
			#if (!MiniCity)
				// 2
				object {city_strip	translate z * +416}
				// 3
				object {city_strip	translate z * -416}
			#end
			#local spoke_count = spoke_count + 1;
		#end
		// city buildings - pass 5 - skinny end woods
		#declare buildings_per_block	= <2,1,0,>;
		#declare city_block_count	= <slice_total/spoke_total,1,0,>;
		#local section_width		= (nominal_building_width * buildings_per_block.x + nominal_traffic_width) * city_block_count.x;
		#local section_length		= (nominal_building_width * buildings_per_block.y + nominal_traffic_width) * city_block_count.y;
//		verbose_include("CG_DEFAULT_CURVED_MESH.inc", 0)
//		verbose_include("CG_PARK_CURVED_MESH.inc", 0)
		#local spoke_count		= 0;
		#while (spoke_count < nominal_spoke_total)
			#local city_strip = object {verbose_include("CG_CITY_CURVED_MESH.inc", 0)}
			#local city_strip = object
			{
				city_strip
				rotate		z * spoke_count * spoke_angle
				rotate		z * spoke_angle/2
			}
			// 1
			object {city_strip	translate z * +800}
			#if (!MiniCity)
				// 2
				object {city_strip	translate z * -800}
			#end
			#local spoke_count = spoke_count + 1;
		#end
//		bounded_by {cylinder {<0,0,-total_length/2+0>, <0,0,+total_length/2+0>, city_radius}}
		scale	0.999
	}
#end


//------------------------------------------------------------------------------Shell & atmosphere

#if (!NoShell)
	union
	{
		#local bnd_sphere = sphere	{0, city_radius + cap_thickness	rotate x * 90}
		#local cap_cone_1 = difference
		{
			cone	{0, 0, z*+(2000), 2000 * tand(60)}
			cone	{0, 0, z*+(2001), 2001 * tand(15/2)}
			bounded_by {bnd_sphere}
		}
		#local cap_cone_2 = difference
		{
			cone	{0, 0, z*+(2000), 2000 * tand(75)}
			cone	{0, 0, z*+(2001), 2001 * tand(15/2)}
			bounded_by {bnd_sphere}
		}
		#local cap_cone_3 = difference
		{
			cone	{0, 0, z*+(2000), 2000 * tand(75)}
			cone	{0, 0, z*+(2001), 2001 * tand(60)}
			bounded_by {bnd_sphere}
		}
		#local cap_sphere_1 = difference
		{
			sphere	{0, city_radius + cap_thickness	rotate x * 90}
			sphere	{0, city_radius			rotate x * 90}
			bounded_by {bnd_sphere}
		}
		#local cap_glass_object = intersection
		{
			object {cap_sphere_1}
			object {cap_cone_1}
			#if (glass_hollow)	hollow	#end
			bounded_by {bnd_sphere}
			scale z * cap_zscale
		}
		#local cap_metal_object = difference
		{
			object {cap_sphere_1}
			object {cap_cone_2}
			plane {z,0}
			bounded_by {bnd_sphere}
			scale z * cap_zscale
		}
		#local cap_guide_object = intersection
		{
			object {cap_sphere_1}
			object {cap_cone_3}
			plane {+x, 0	rotate z * +spoke_angle/2}
			plane {-x, 0	rotate z * -spoke_angle/2}
			bounded_by {bnd_sphere}
			scale z * cap_zscale
		}
		object
		{
			cap_metal_object
			texture {cap_metal_texture}
			translate	z * total_length/2
			rotate		y * 180
		}
		object
		{
			cap_metal_object
			texture {cap_metal_texture}
			translate	z * total_length/2
		}
		object
		{
			cap_glass_object
			material {cap_glass_material}
			translate	z * total_length/2
			rotate		y * 180
		}
		object
		{
			cap_glass_object
			material {cap_glass_material}
			translate	z * total_length/2
		}
		#local spoke_count = 0;
		#while (spoke_count < spoke_total)
			object
			{
				cap_guide_object
				rotate		z * spoke_angle/2
				rotate		z * spoke_count * spoke_angle
				translate	z * total_length/2
				texture
				{
					pigment {gamma_color_adjust(CHSL2RGB(<spoke_count/spoke_total*360,1/2,1/4>))}
					finish {cap_metal_finish}
				}
			}
			object
			{
				cap_guide_object
				rotate		z * spoke_angle/2
				rotate		z * spoke_count * spoke_angle
				translate	z * total_length/2
				rotate		y * 180
				texture
				{
					pigment {gamma_color_adjust(CHSL2RGB(<spoke_count/spoke_total*360,1/2,1/4>))}
					finish {cap_metal_finish}
				}
			}
			#local spoke_count = spoke_count + 1;
		#end
		// cylinder macro segments need to be matched up correctly with the city parts
		// does not need to be hollow
		difference
		{
			cylinder {<0,0,-total_length/2+0>, <0,0,+total_length/2+0>, city_radius + cap_thickness}
			cylinder {<0,0,-total_length/2+1>, <0,0,+total_length/2+1>, city_radius + 0}
			texture {cap_metal_texture}
		}
		// atmosphere
		#if (!NoAtmos)
			merge
			{
				object
				{
					cyl_macro(<0,0,-total_length/2,>, <0,0,+total_length/2,>, city_radius)
				}
				object
				{
					sph_macro(0, city_radius)
					rotate		x * 90
					scale		z * cap_zscale
					translate	z * -total_length/2
				}
				object
				{
					sph_macro(0, city_radius)
					rotate		x * 90
					scale		z * cap_zscale
					translate	z * +total_length/2
				}
		//		bounded_by {cylinder {<0,0,-(total_length/2+city_radius*cap_zscale),>, <0,0,+(total_length/2+city_radius*cap_zscale),>, city_radius}}
				scale	0.9999
				hollow
				material {atmos_material}
			}
		#end
//		bounded_by {cylinder {<0,0,-(total_length/2+(city_radius + cap_thickness)*cap_zscale),>, <0,0,+(total_length/2+(city_radius + cap_thickness)*cap_zscale),>, city_radius + cap_thickness}}
		scale 1.001
		#if (!AlwaysReflect)	no_reflection 	#end	// for sanity's sake!!!
		hollow
	}
#end

// lamp
#if (!NoLamp)
	object
	{
		cyl_macro(z*-(lamp_length/2), z*+(lamp_length/2), lamp_radius)
		material {lamp_material}
		#if (TexQual = 1)	hollow	#end
		scale	0.9999
		no_shadow
	}
	// lights
	#if (FadePower)
		// should have many small lights instead of a few large ones
		// that way I can use the "circular" keyword to make the lights' cross sections round
		object
		{
			Light(light_temp, light_lumens/2, x * lamp_radius * cosd(45) * 2, z * lamp_length, 2, lamp_number, 0)	// was 2.3 * 3/4
			translate	y * -lamp_radius * cosd(45)
		}
		object
		{
			Light(light_temp, light_lumens/2, x * lamp_radius * cosd(45) * 2, z * lamp_length, 2, lamp_number, 0)	// was 2.3 * 3/4
			translate	y * +lamp_radius * cosd(45)
		}
	#else
		// darkened an extra 50% since with the sun it's way too bright (not any more)
		light_source
		{
			y * -lamp_radius * cosd(45)
			gamma_color_adjust(Light_Color(light_temp,light_lumens/2))
			area_light	x * lamp_radius * cosd(45) * 2, z * lamp_length, 2, lamp_number
			adaptive	1
//			jitter
		}
		light_source
		{
			y * +lamp_radius * cosd(45)
			gamma_color_adjust(Light_Color(light_temp,light_lumens/2))
			area_light	x * lamp_radius * cosd(45) * 2, z * lamp_length, 2, lamp_number
			adaptive	1
//			jitter
		}
	#end
#end

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------