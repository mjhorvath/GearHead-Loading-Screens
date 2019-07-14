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

#include "colors.inc"
#include "metals.inc"
#include "glass.inc"
#include "transforms.inc"
#include "stars.inc"
#include "skies.inc"
#include "metals.inc"
#include "CIE.inc"
#include "lightsys.inc"

#declare pov_version		= 1;				// 0 = 3.6; 1 = 3.7; 3.7 also has gamma adjustments in INI file
#declare Seed			= seed(8829464);
#declare Subdivision		= 0;				// turn on/off mesh subdivision - this requires a special exe available on the Net
#declare Included		= 1;				// tells any included files that they are being included.

#local NoLights			= 0;
#local NoCity			= 0;
#local NoShell			= 0;
#local NoSmoke			= 1;
#local NoMechs			= 1;
#local NoMissiles		= 1;
#local NoBullets		= 1;
#local NoTrees			= 0;
#local NoRadiosity		= 1;
#local NoSky			= 1;
#local LampShade		= 0;

#declare city_tileable		= 1;					// boolean, see CityGen docs
#declare city_night		= 0;					// boolean, see CityGen docs
#declare city_right_hand_drive	= 0;					// boolean, see CityGen docs
#declare city_default_objects	= 0;					// boolean, see CityGen docs
#declare city_use_mesh		= 0;					// boolean, use meshes instead of cylinders, cones, etc.
#declare city_all_mesh		= 0;					// boolean, use meshes for streets and pavement as well?
#declare Lightsys_Scene_Scale	= 100;
#declare buildings_per_block	= <2,3,0,>;			// 3x4 including roads
#declare city_block_count	= <1,3,0,>;
#declare city_tileable		= true;
#declare city_radius		= 1000;			// float, the radius of the spinner colony
#declare traffic_width		= 16/5;
#declare traffic_lanes		= 2;
//#declare traffic_spacing	= 16;				// set elsewhere
#declare pavement_width		= 1;
#declare building_gap		= 2;
#declare building_width		= 16 - pavement_width * 2;
// does not take "city_tilable" into account
#declare block_dist_x		= traffic_width * (traffic_lanes * 2 + 1) + pavement_width * 2 + building_width * buildings_per_block.x + building_gap * (buildings_per_block.x - 1);
#declare block_dist_z		= traffic_width * (traffic_lanes * 2 + 1) + pavement_width * 2 + building_width * buildings_per_block.y + building_gap * (buildings_per_block.y - 1);
#declare block_size_xz		= <block_dist_x,block_dist_z,0,>;
#if (city_tileable)
	#declare city_size_total	= city_block_count * block_size_xz;
#else
	#declare city_size_total	= city_block_count * block_size_xz + <16,16,0,>;
#end
#declare min_building_height	= 8;
#declare max_building_height	= 32;
#declare building_height_turb	= 1;
#declare city_night		= true;
#declare city_right_hand_drive	= false;

#local total_length		= 1024;
#local spoke_max		= 6;
#local temp_max			= 36;
#local temp_angle		= 360/temp_max;
#local temp_radius		= block_dist_x/2/sind(temp_angle/2);
#local temp_circum		= 2 * pi * temp_radius;
#local green_width		= 64;
#local green_intrvl		= temp_max/spoke_max;
#local slice_radius		= cosd(temp_angle/2) * temp_radius;
#local cap_thickness		= 4;
#local trees_per_unit		= 1/16;
#local AirCarPosition		= <-32,+32,+32,>;
#local KojedoPosition		= +x * block_dist_x;
#local MaanjiPosition		= -x * block_dist_x;
#local KojedoCenter		= <0,4,0,>;
#local LineVector		= vnormalize(-AirCarPosition + KojedoCenter + KojedoPosition);
#local Burst			= true;
#local light_color		= Light_Color(Daylight(5500),2.3);

#local Camera_Mode		= 6;				// 0 to 8; 0 = orthographic; 1 = oblique; 2 = perspective
#local Camera_Diagonal		= cosd(45);
#local Camera_Vertical		= 0;				//22.5;
#local Camera_Horizontal	= 0;				//30;
#local Camera_Scale		= 1;
#local Camera_Aspect		= image_height/image_width;
#local Camera_Distance		= 16;
#local Camera_Translate		= <-32,+32,-32,>;			//<0,0,-city_size_total.y,>

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
//default {finish {ambient 0.1 diffuse 0.6}}
//default {finish {ambient 0.4 diffuse 0.7}}

global_settings
{
	#if (version < 3.7)
		assumed_gamma	1.0
	#end
	#if (!NoRadiosity)
		ambient_light	0.0
		radiosity
		{
			always_sample	off
			brightness	0.5
			recursion_limit	1
			count		100
			error_bound	0.5
		}
	#end
	max_trace_level 8
}


//------------------------------------------------------------------------------Camera

#switch (Camera_Mode)
	// orthographic
	#case (0)
		#declare Camera_Up		= y * Camera_Diagonal * Width * Tiles * 2 * Camera_Aspect;
		#declare Camera_Right		= x * Camera_Diagonal * Width * Tiles * 2;
		#declare Camera_Location	= vaxis_rotate(<+1,+0,+1,>, <-1,+0,+1,>, Camera_Horizontal) * Camera_Diagonal * Width * Tiles * Camera_Scale;
		#declare Camera_Location	= vaxis_rotate(Camera_Location, y, Camera_Vertical);
		#declare Camera_Location	= Camera_Location + -x * block_dist_x/2;
		#declare Camera_LookAt		= 0;
		#declare Camera_LookAt		= vaxis_rotate(Camera_LookAt, y, Camera_Vertical);
		#declare Camera_LookAt		= Camera_LookAt + -x * block_dist_x/2;
		camera
		{
			orthographic
			up		Camera_Up
			right		Camera_Right
			location	Camera_Location
			look_at		Camera_LookAt
			translate	Camera_Translate
		}
		#declare Camera_Location	= Camera_Translate + Camera_Location;
		#declare Camera_LookAt		= Camera_Translate + Camera_LookAt;
	#break
	// oblique
	#case (1)
		#declare Camera_Area		= Tiles * 2 * 64;
		#declare Camera_Aspect		= 1/Camera_Aspect;
		#declare Camera_Distance	= Camera_Diagonal * Width * Tiles * CameraScale;
		#declare Camera_Skewed		= sin(pi/4);
		#declare Camera_Up		= -x * Camera_Area;
		#declare Camera_Right		= +z * Camera_Area * Camera_Aspect;
		#declare Camera_Location	= vnormalize(<Camera_Skewed, 1, Camera_Skewed>) * Camera_Distance;
		#declare Camera_Direction	= -Camera_Location;
		#declare Camera_Location	= Camera_Location + -x * block_dist_x/2;
		#declare Camera_LookAt		= Camera_Location + Camera_Direction;
		camera
		{
			orthographic
			up		Camera_Up
			right		Camera_Right
			location	Camera_Location
			direction	Camera_Direction
			translate	Camera_Translate
		}
		#declare Camera_Location	= Camera_Translate + Camera_Location;
		#declare Camera_LookAt		= Camera_Translate + Camera_LookAt;
	#break
	// perspective (new)
	#case (2)
		#declare Camera_Up		= +y * Camera_Diagonal * Width * Tiles * 2 * Camera_Aspect;
		#declare Camera_Right		= +x * Camera_Diagonal * Width * Tiles * 2;
		#declare Camera_Location	= -z * Camera_Distance;
		#declare Camera_Direction	= +z * Camera_Distance;
		#declare Camera_LookAt		= Camera_Location + Camera_Direction;
		#declare Camera_Rotate		= <Camera_Horizontal,Camera_Vertical,0,>;
		camera
		{
			up		Camera_Up
			right		Camera_Right
			location	Camera_Location
			direction	Camera_Direction
			rotate		Camera_Rotate
			translate	Camera_Translate
		}
		#declare Camera_Location	= Camera_Translate + vrotate(Camera_Location,Camera_Rotate);
		#declare Camera_LookAt		= Camera_Translate + vrotate(Camera_LookAt,Camera_Rotate);
	#break
	// orthographic (new)
	#case (3)
		#declare Camera_Up		= +y * Camera_Diagonal * Width * Tiles * 2 * Camera_Aspect;
		#declare Camera_Right		= +x * Camera_Diagonal * Width * Tiles * 2;
		#declare Camera_Location	= -z * Camera_Distance;
		#declare Camera_Direction	= +z;
		#declare Camera_LookAt		= Camera_Location + Camera_Direction;
		#declare Camera_Rotate		= <Camera_Horizontal,Camera_Vertical,0,>;
		camera
		{
			orthographic
			up		Camera_Up
			right		Camera_Right
			location	Camera_Location
			direction	Camera_Direction
			rotate		Camera_Rotate
			translate	Camera_Translate
		}
		#declare Camera_Location	= Camera_Translate + vrotate(Camera_Location,Camera_Rotate);
		#declare Camera_LookAt		= Camera_Translate + vrotate(Camera_LookAt,Camera_Rotate);
	#break
	// not sure...
	#case (4)
		#declare Camera_Up		= <+00.29007132383,+00.94193058802,-00.16919038339,>;
		#declare Camera_Right		= <-00.44470821789,-00.00000000114,-00.76243755686,>;
		#declare Camera_Location	= <-15.70614200000,+06.48226800000,+09.16094800000,>;
		#declare Camera_Direction	= <+00.81364160776,-00.33580762148,-00.47457408905,>;
		#declare Camera_LookAt		= Camera_Location + Camera_Direction;
		#declare Camera_Angle		= 50.000;
		camera
		{
			angle		Camera_Angle
			up		Camera_Up
			right		Camera_Right
			location	Camera_Location
			direction	Camera_Direction
			translate	Camera_Translate	
		}
		#declare Camera_Location	= Camera_Translate + Camera_Location;
		#declare Camera_LookAt		= Camera_Translate + Camera_LookAt;
	#break
	// cube map
	#case (5)
		#declare Camera_Up		= +y;
		#declare Camera_Right		= +x;
		#declare Camera_Location	= 0;
		#declare Camera_Direction	= +z/2;
		#declare Camera_LookAt		= Camera_Location + Camera_Direction;
		#switch (frame_number)
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
		camera
		{
			up		Camera_Up
			right		Camera_Right
			location	Camera_Location
			direction	Camera_Direction
			rotate		Camera_Rotate
			translate	Camera_Translate
		}
		#declare Camera_Location	= Camera_Translate + vrotate(Camera_Location,Camera_Rotate);
		#declare Camera_LookAt		= Camera_Translate + vrotate(Camera_LookAt,Camera_Rotate);
	#break
	// spherical
	#case (6)
		#declare Camera_Up		= +y;
		#declare Camera_Right		= +x;
		#declare Camera_Location	= 0;
		#declare Camera_Direction	= +z;
		#declare Camera_LookAt		= Camera_Location + Camera_Direction;
		camera
		{
			spherical
			angle		360 180
			up		Camera_Up
			right		Camera_Right
			location	Camera_Location
			look_at		Camera_LookAt
			translate	Camera_Translate
		}
		#declare Camera_Location	= Camera_Translate + Camera_Location;
		#declare Camera_LookAt		= Camera_Translate + Camera_LookAt;
	#break
	// orthographic (overhead)
	#case (7)
		#declare Camera_Up		= +z * Tiles * Width * 4 * Camera_Aspect;
		#declare Camera_Right		= +x * Tiles * Width * 4;
		#declare Camera_Location	= +y * Camera_Distance * 2;
		#declare Camera_Direction	= -y;
		#declare Camera_LookAt		= Camera_Location + Camera_Direction;
		camera
		{
			orthographic
			up		Camera_Up
			right		Camera_Right
			location	Camera_Location
			direction	Camera_Direction
			translate	Camera_Translate
		}
		#declare Camera_Location	= Camera_Translate + Camera_Location;
		#declare Camera_LookAt		= Camera_Translate + Camera_LookAt;
	#break
	// orthographic (overhead, angled)
	#case (8)
		#declare Camera_Scale		= 4;
		#declare Camera_Up		= +z * Camera_Diagonal * Width * Tiles * Camera_Scale * Camera_Aspect;
		#declare Camera_Right		= +x * Camera_Diagonal * Width * Tiles * Camera_Scale;
		#declare Camera_Location	= +y * Camera_Distance * Camera_Scale;
		#declare Camera_Direction	= -Camera_Location;
		#declare Camera_LookAt		= Camera_Location + Camera_Direction;
		#declare Camera_Rotate		= <+60,-45,+00,>;		//<+60,-45,+00,>
		camera
		{
//			orthographic
			up		Camera_Up
			right		Camera_Right
			location	Camera_Location
			direction	Camera_Direction
			rotate		Camera_Rotate
			translate	Camera_Translate
		}
		#declare Camera_Location	= Camera_Translate + vrotate(Camera_Location,Camera_Rotate);
		#declare Camera_LookAt		= Camera_Translate + vrotate(Camera_LookAt,Camera_Rotate);
	#break
#end


//------------------------------------------------------------------------------Textures

#local sky_pigment_1 = pigment
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
		[0.5	color rgb <0.50,0.60,1.00,>]
		[1.0	color rgb <0.50,0.60,1.00,>]
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
#local star_pigment_1 = pigment
{
	granite
	color_map
	{
		[ 0.000  0.270 color rgbt < 0, 0, 0, 1> color rgbt < 0, 0, 0, 1> ]
		[ 0.270  0.280 color rgbt <.5,.5,.4, 0> color rgbt <.8,.8,.4, 0> ]
		[ 0.280  0.470 color rgbt < 0, 0, 0, 1> color rgbt < 0, 0, 0, 1> ]
		[ 0.470  0.480 color rgbt <.4,.4,.5, 0> color rgbt <.4,.4,.8, 0> ]
		[ 0.480  0.680 color rgbt < 0, 0, 0, 1> color rgbt < 0, 0, 0, 1> ]
		[ 0.680  0.690 color rgbt <.5,.4,.4, 0> color rgbt <.8,.4,.4, 0> ]
		[ 0.690  0.880 color rgbt < 0, 0, 0, 1> color rgbt < 0, 0, 0, 1> ]
		[ 0.880  0.890 color rgbt <.5,.5,.5, 0> color rgbt < 1, 1, 1, 0> ]
		[ 0.890  1.000 color rgbt < 0, 0, 0, 1> color rgbt < 0, 0, 0, 1> ]
	}
	turbulence 1
	sine_wave
	scale 5
}
#local star_pigment_2 = pigment {star_pigment_1 transmit 1}
#local star_pigment_3 = pigment
{
	radial
	pigment_map
	{
		[0/2	star_pigment_1]
		[1/2	star_pigment_2]
		[2/2	star_pigment_1]
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
	image_map {png "olivepink_marble.png"}
	scale	64
	// causes crash? bug?
/*
	#if (version < 3.7)
		warp
		{
			cylindrical
			orientation	z
			dist_exp	temp_radius
		}
	#end
*/
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
		[1	grass_pigment_1]
		[1	grass_pigment_2]
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
#declare atmos_interior = interior
{
	media
	{
		scattering
		{ 
			4, 0.1
			extinction	0.1
		}
/*
		density
		{
			cylindrical
			color_map
			{
				[0 rgb 1/10]
				[1 rgb 0/10]
			}
			scale	temp_radius
			rotate	x * 90
		}
*/
		density
		{
			cylindrical
			poly_wave	0.5
			density_map
			{
				[0 rgb 1.0/100]
				[1 rgb 0.3/100]
			}
			scale	temp_radius
			rotate	x * 90
		} 
	}
}
#local lamp_interior = interior
{
	media
	{
		emission vnormalize(light_color)
/*
		density
		{
			cylindrical
			color_map
			{
				[0 rgb 0]
				[1 rgb 1]
			}
			scale	cap_thickness/2
			rotate	x * 90
		}
*/
	}
}

//------------------------------------------------------------------------------Lights

#if (!NoLights)
	light_source
	{
		0
		light_color
		area_light
		x, z * total_length, 1, floor(total_length/32)
		adaptive 1
//		jitter
	}
	// lamp
	cylinder
	{
		z*-total_length/2, z*+total_length/2, cap_thickness/2
		hollow
//		pigment {color light_color}
//		finish {ambient 1}
		pigment {rgbf 1}
		interior {lamp_interior}
		scale	0.9999
		no_shadow
	}
	// lamp shade
	#if (LampShade)
		cylinder
		{
			<0,0,-total_length/2,>,<0,0,+total_length/2,>, 2.1
			open
			hollow
			pigment {shade_pigment}
			// mirror finish too slow!
//			finish {reflection {1.0} ambient 0 diffuse 0}
			scale	1
		}
	#end
#end


//------------------------------------------------------------------------------Stars

#if (!NoSky)
	sphere
	{
		0, 10000
		hollow
		texture {Starfield1}
	}
	// fake sky/shade, the reverse side should have lit stars on it, stacking them makes the shadows darker than either alone, so maybe try another method
	#if (!LampShade)
		cylinder
		{
			<0,0,-total_length/2,>,<0,0,+total_length/2,>, temp_radius - 64
			open
			hollow
			pigment {sky_pigment_3}
			scale	0.9999
		}
		cylinder
		{
			<0,0,-total_length/2,>,<0,0,+total_length/2,>, temp_radius - 64
			open
			hollow
			pigment {star_pigment_3}
			finish {ambient 1}
			scale	1.0000
		}
	#end
	// atmosphere
	difference
	{
		cylinder
		{
			<0,0,-total_length/2,>, <0,0,+total_length/2,>, temp_radius
			scale	0.9999
		}
		// no reason to make the center a vacuum if the lamp shade is used
		#if (!LampShade)
			cylinder
			{
				<0,0,-total_length/2,>, <0,0,+total_length/2,>, temp_radius - 64
				scale	1.0001
			}
		#end
		hollow
		pigment {rgbt 1}
		interior {atmos_interior}
	}
#end


//------------------------------------------------------------------------------City

#if (!NoCity)
	// city buildings
	#local temp_count = 0;
	#while (temp_count < temp_max)
		#if (mod(temp_count,green_intrvl) > 0)
			// need to make sure rotations match the orientation of the shade, i.e. more traffic where light is greatest
			#declare traffic_spacing = tand(temp_count/temp_max * 180) * 4 + 8;
			#local city_strip = object
			{
				// textures/normals are not scaled to the size of the scene AFAIK, need to fix it in include file
				#include "CG_CITY.inc"
				translate	x * 8
				translate	z * 8
				translate	y * -slice_radius
				rotate		z * -90
				rotate		z * 360/temp_max * temp_count
				rotate		z * -360/temp_max/2
				scale		0.9999
			}
			// 1
			object
			{
				city_strip
				translate	z * +128
			}
/*
			object
			{
				city_strip
				translate	z * -128
			}
			// 2
			object
			{
				city_strip
				translate	z * +384
			}
			object
			{
				city_strip
				translate	z * -384
			}
*/
		#end
		#local temp_count = temp_count + 1;
	#end
#end


//------------------------------------------------------------------------------Shell

#if (!NoShell)
	// spokes
	#local spoke_object = union
	{
		#local spoke_count = 0;
		#while (spoke_count < spoke_max)
			cylinder
			{
				<0,0,0,>, <temp_radius,0,0,>, cap_thickness/2
				rotate	z * 360/spoke_max * spoke_count
			}
			#local spoke_count = spoke_count + 1;
		#end
	}
	#local cap_object = union
	{
		difference
		{
			cylinder
			{
				z*-cap_thickness/2, z*+cap_thickness/2, temp_radius
			}
			cylinder
			{
				z*-cap_thickness/2,z*+cap_thickness/2, temp_radius - 64
				scale	1.0001
			}
		}
		cylinder
		{
			z*-cap_thickness/2, z*+cap_thickness/2, 64
		}
	}
	// greenery (also the outermost surface)
	cylinder
	{
		// must have a larger radius or green will overlap the streets!
		<0,0,-total_length/2,>, <0,0,+total_length/2,>, temp_radius
		open
		hollow
		scale	1.0001
		texture {grass_texture_1}
	}
	// end caps & spokes
	union
	{
		// cap 1
		union
		{
			object {cap_object}
			object {spoke_object}
			translate	z*-(total_length/2+cap_thickness/2)
		}
		// cap 2
		union
		{
			object {cap_object}
			object {spoke_object}
			translate	z*+(total_length/2+cap_thickness/2)
		}
//		pigment {sky_pigment_1}
//		pigment {color rgb <0.6,0.7,1.0>}
		pigment {color rgb 1/2}
//		texture {T_Chrome_1A}
	}
#end


//------------------------------------------------------------------------------Trees

// deciduous trees are better where the angle of the light is near vertical since coniferous trees are adapted to low angles
// there is a lot of sideways light in the middle of the habitat however
// need to check for collisions, otherwise rendering time is wasted
// make sure density is the same for horizontal and vertical
#if (!NoTrees)
	#include "gh_deciduous_tree.inc"
	// vertical
	#local trees_area = temp_circum * green_width * 4;
	#local trees_max = trees_area * trees_per_unit / 2;
	#local trees_count = 0;
	#while (trees_count < trees_max)
		// ideal if curved
		#local tree_transform_1 = transform
		{
			scale		2 * (rand(Seed) * 1/2 + 3/2)
			rotate		y * rand(Seed) * 360 
			translate	y * -temp_radius
			translate	z * rand(Seed) * -green_width/2
			translate	z * floor(rand(Seed) * 2 + 1/2) * +256
			rotate		z * rand(Seed) * 360
		}
		#local tree_transform_2 = transform
		{
			scale		8 * (rand(Seed) * 1/2 + 3/2)
			rotate		y * rand(Seed) * 360
			translate	y * -temp_radius
			translate	z * rand(Seed) * +green_width/2
			translate	z * floor(rand(Seed) * 2 + 1/2) * -256
			rotate		z * rand(Seed) * 360
		}
		object
		{
//			Grantrae
			TREE
			transform	tree_transform_1
		}
		object
		{
//			Grantrae
			TREE
			transform	tree_transform_2
		}
		#local trees_count = trees_count + 1;
		#debug concat("_", str(trees_count,0,0))
	#end
	// horizontal
	#local trees_area = temp_circum/temp_max * total_length * spoke_max;
	#local trees_max = trees_area * trees_per_unit;
	#local trees_count = 0;
	#while (trees_count < trees_max)
		// ideal if curved
		#local tree_transform_1 = transform
		{
			scale		8 * (rand(Seed) * 1/2 + 3/2)
			rotate		y * rand(Seed) * 360
			translate	y * -temp_radius
			translate	z * (rand(Seed) * total_length - total_length/2)
			rotate		z * (rand(Seed) * 360/temp_max - 360/temp_max/2)
			rotate		z * (floor(rand(Seed) * spoke_max + 1/2) * 360/spoke_max - 360/spoke_max/2)
		}
		object
		{
//			Grantrae
			TREE
			transform	tree_transform_1
		}
		#local trees_count = trees_count + 1;
		#debug concat("_", str(trees_count,0,0))
	#end
#end


//------------------------------------------------------------------------------Bullets

#if (!NoBullets)
	#declare BulletPath = spline
	{
		linear_spline
		0.00, KojedoCenter + KojedoPosition
		1.00, AirCarPosition
	}
	#include "gh_bullet.inc"
	object
	{
		bullet
		Reorient_Trans(y, LineVector)
		scale 1/2
		translate BulletPath(0.9)
		translate y * 1
	}
	object
	{
		bullet
		Reorient_Trans(y, LineVector)
		scale 1/2
		translate BulletPath(0.8)
		translate y * 1
	}
	object
	{
		bullet
		Reorient_Trans(y, LineVector)
		scale 1/2
		translate BulletPath(0.7)
		translate y * 1
	}
	object
	{
		bullet
		Reorient_Trans(y, LineVector)
		scale 1/2
		translate BulletPath(0.5)
		translate y * 1
	}
	object
	{
		bullet
		Reorient_Trans(y, LineVector)
		scale 1/2
		translate BulletPath(0.4)
		translate y * 1
	}
	object
	{
		bullet
		Reorient_Trans(y, LineVector)
		scale 1/2
		translate BulletPath(0.3)
		translate y * 1
	}
#end


//------------------------------------------------------------------------------Mechs

#if (!NoMechs)
	#declare NoColors = 0;
	#include "ara_kojedo.pov"
	object
	{
		ara_kojedo_
		translate	<18.42348,0,-364.0902> * -1
		scale		1/10	// was 1/12
		scale		3/4
		rotate		y * -45
		rotate		y * clock * 360
		// edit below
		scale		1/4
		translate	KojedoPosition
	}
	#declare NoColors = 1;
	#include "btr_maanji.pov"
	object
	{
		object01
		matrix <1.000000, 0.000000, 0.000000,
		0.000000, 1.000000, 0.000000,
		0.000000, 0.000000, 1.000000,
		0.000000, 0.000000, 0.000000>
		translate	<0.000000, 0.000000, 0.000000>
		scale		<1.000000, 1.000000, 1.000000>
		scale		1/2
		scale		3/4
		rotate		y * -45
//		rotate		y * clock * 360
		// edit below
		scale		1/4
		rotate		y * 90
		translate	MaanjiPosition
	}
	#declare NoColors = 0;
	#include "aer_aircar.pov"
/*
	#declare Increment1 = 1/16;
	#declare Increment2 = 1/16;
	#declare Exhaust_Plume = union
	{
		#declare Count1 = 1 - Increment1;
		#while (Count1 < 1)
			#declare InvCount1 = 1 - Count1;
			#declare Count2 = 0;
			#while (Count2 < 1)
				intersection
				{
					cone
					{
						<0, Count2 * -128, 0,>,
						6 + Count2 * Count1 * 26,
						<0, (Count2 + Increment2) * -128, 0,>,
						6 + (Count2 + Increment2) * Count1 * 26
						//open
					}
					material
					{
						texture {pigment {color rgbt 1}}
						interior {ior ((1 - InvCount1 * 0.1) + Count2 * InvCount1 * 0.1)}
					}
				}
				#declare Count2 = Count2 + Increment2;
			#end
			#declare Count1 = Count1 + Increment1;
		#end
	}
*/
	union
	{
		object
		{
			Air_Car_
			rotate		x * 90
			rotate		y * -90
			translate	y * -3
			translate	x * 8
		}
/*
		object
		{
			Exhaust_Plume
			translate	z * 39
			rotate		z * -60
		}
		object
		{
			Exhaust_Plume
			translate	z * -39
			rotate		z * -60
		}
*/
		translate	y * 24.37624 + 3
		Reorient_Trans(x, <LineVector.x,0,LineVector.z,>)
		scale		1/10
		scale		3/4
		translate	AirCarPosition
	}
#end


//------------------------------------------------------------------------------Loading text

/*
#if (!NoText)
	text
	{
		ttf "hatten.ttf" "Just a minute..." 0.1, 0
		pigment { White }
		scale 8
		rotate y * -90
		translate <-0,8,24>
	}
#end
*/

//------------------------------------------------------------------------------Smoke

#if (!NoSmoke)
	#declare camera_location = Camera_Location;
	#declare light_source_location = <3000, 6000, -7000>;
	#include "gh_effect_smoke.inc"
	union
	{
		object {Layer1}
		object {Layer2}
		object {Layer3}
		object {Layer4}
		scale 4
		translate <-16,0,-16,>
	}
	union
	{
		object {Layer1}
		object {Layer2}
		object {Layer3}
		object {Layer4}
		scale 4
		translate <16,0,64,>
	}
	union
	{
		object {Layer1}
		object {Layer2}
		object {Layer3}
		object {Layer4}
		scale 4
		translate <-96,0,16,>
	}
#end


//------------------------------------------------------------------------------Missiles

#if (!NoMissiles)
	#include "gh_projectile_missile.inc"
	union
	{
		object {Missile}
		#if (Burst = 1)
			object {Missile translate <4,0,-16,>}
			object {Missile translate <8,0,-32,>}
		#end
		no_shadow
		rotate <0,clock * 360 - 45,0,>
		rotate <0,-45,0,>
		scale 1/4
		translate -x * block_dist_x / 2
	}
#end
