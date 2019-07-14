// Desc: Several GearHead mecha battling it out in a city setting.
// Auth: Michael Horvath
// Home Page: http://www.geocities.com/Area51/Quadrant/3864/gearhead.htm
// This file is licensed under the terms of the CC-LGPL.
// Dependencies:
// 1. CITY GENERATOR INCLUDE FILE by Chris Colefax (modified)
// 2. Rune's particle system

// Not sure if turning antialiasing on is worth it since Panosalado does its own antialiasing
//+KFI0 +KFF5 +KC +KI0 +KF0
//+KFI5 +KFF5 +KC
//+K0 +KC

// double the size of buildings
// add letters for each block to the end cap
// make the cylinder narrower, either by increasing its length or decreasing its diameter
// decrease the number of street lanes by half
// improve the appearance of spokes
// shadows against end caps are ugly
// lens flare?
// get rid of cars and replace them woth something else?
// make the end caps slightly curved

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
#declare Included		= 0;				// tells any included files that they are being included.
#declare Width			= 8;				// 64?
#declare Tiles			= 1;

#local NoLights			= 0;
#local NoCity			= 0;
#local NoShell			= 0;
#local NoAtmos			= 0;
#local NoRadiosity		= 0;
#local NoSky			= 0;
#local NoTrees			= 1;
#local NoSmoke			= 1;				// obsolete for the moment
#local NoMechs			= 1;
#local NoMissiles		= 1;
#local NoBullets		= 1;
#local NoLampShade		= 1;
#local NoFakeSky		= 1;
#local MiniCity			= 0;
#local LowTrace			= 0;

#local total_lanes		= 3;
#local nominal_building_width	= Width * 4;
#local nominal_traffic_width	= Width;
#local city_sections		= 4;

#declare Lightsys_Scene_Scale	= 100;
#declare buildings_per_block	= <2,3,0,>;			// re-set elsewhere, 3x4 including roads
#declare city_block_count	= <1,3,0,>;			// re-set elsewhere
#declare city_tileable		= true;
//#declare traffic_spacing	= 16;				// set elsewhere
#declare traffic_width		= nominal_traffic_width/total_lanes;
#declare traffic_lanes		= (total_lanes-1)/2;
#declare pavement_width		= 2;
#declare building_gap		= pavement_width * 2;
#declare building_width		= nominal_building_width - pavement_width * 2;
#declare min_building_height	= 8;
#declare max_building_height	= 32;
#declare building_height_turb	= 1;
#declare city_night		= false;
#declare city_right_hand_drive	= false;
#declare city_default_objects	= false;
#declare car_scale		= 1;

#local block_dist_x		= traffic_width * (traffic_lanes * 2 + 1) + pavement_width * 2 + building_width * buildings_per_block.x + building_gap * (buildings_per_block.x - 1);
#local block_dist_z		= traffic_width * (traffic_lanes * 2 + 1) + pavement_width * 2 + building_width * buildings_per_block.y + building_gap * (buildings_per_block.y - 1);
#local block_size_xz		= <block_dist_x,block_dist_z,0,>;
#local city_center_offset	= nominal_traffic_width/2 * <1,0,1,>;
#local total_length		= block_dist_z * (city_block_count.y + 1) * city_sections;			// float
#local spoke_total		= 5;					// integer
#local slice_total		= 25;					// integer
#local slice_angle		= 360/slice_total;			// float
#local slice_radius		= block_dist_x/2/sind(slice_angle/2);	// float
#local slice_ydist		= cosd(slice_angle/2) * slice_radius;	// float
#local slice_circum		= 2 * pi * slice_radius;		// float
#local green_width		= 64;					// float
#local green_intrvl		= slice_total/spoke_total;			// integer
#local cap_thickness		= 8;					// float
#local trees_per_unit		= 1/32;					// float
#local AirCarPosition		= <-32,+32,+32,>;			// vector
#local KojedoPosition		= +x * block_dist_x;			// vector	
#local MaanjiPosition		= -x * block_dist_x;			// vector
#local KojedoCenter		= <0,4,0,>;				// vector
#local LineVector		= vnormalize(-AirCarPosition + KojedoCenter + KojedoPosition);
#local Burst			= true;					// boolean
#local light_color		= Light_Color(Daylight(5500),2.3);	// vector

#local Camera_Mode		= 2;				// 0 to 8; 0 = orthographic; 1 = oblique; 2 = perspective
#local Camera_Diagonal		= cosd(45);
#local Camera_Vertical		= 0;				//22.5;
#local Camera_Horizontal	= 0;				//30;
#local Camera_Scale		= 1;
#local Camera_Aspect		= image_height/image_width;
#local Camera_Distance		= 16;
#local Camera_Scale		= 2;
#local Camera_Translate		= <0,-(slice_ydist-Width*4)/Camera_Scale,-total_length/3/Camera_Scale,>;

#local p_start			= 64/image_width;
#local p_end_tune		= 8/image_width;
#local p_end_final		= 4/image_width;


//------------------------------------------------------------------------------Macros

#macro get_traffic_spacing(s_count)
	abs(tand(s_count/slice_total * 180)) * 16 + 4
#end

#macro gamma_color_adjust(in_color)
	#local out_gamma = 2.2;
	#local in_color = in_color + <0,0,0,0,0>;
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
	#if (LowTrace)
		max_trace_level 4
	#else
		max_trace_level 256
	#end
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
			scale		Camera_Scale
		}
		#declare Camera_Location	= Camera_Scale * (Camera_Translate + Camera_Location);
		#declare Camera_LookAt		= Camera_Scale * (Camera_Translate + Camera_LookAt);
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
			scale		Camera_Scale
		}
		#declare Camera_Location	= Camera_Scale * (Camera_Translate + Camera_Location);
		#declare Camera_LookAt		= Camera_Scale * (Camera_Translate + Camera_LookAt);
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
			scale		Camera_Scale
		}
		#declare Camera_Location	= Camera_Scale * (Camera_Translate + vrotate(Camera_Location,Camera_Rotate));
		#declare Camera_LookAt		= Camera_Scale * (Camera_Translate + vrotate(Camera_LookAt,Camera_Rotate));
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
			scale		Camera_Scale
		}
		#declare Camera_Location	= Camera_Scale * (Camera_Translate + vrotate(Camera_Location,Camera_Rotate));
		#declare Camera_LookAt		= Camera_Scale * (Camera_Translate + vrotate(Camera_LookAt,Camera_Rotate));
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
			scale		Camera_Scale
		}
		#declare Camera_Location	= Camera_Scale * (Camera_Translate + Camera_Location);
		#declare Camera_LookAt		= Camera_Scale * (Camera_Translate + Camera_LookAt);
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
			scale		Camera_Scale
		}
		#declare Camera_Location	= Camera_Scale * (Camera_Translate + vrotate(Camera_Location,Camera_Rotate));
		#declare Camera_LookAt		= Camera_Scale * (Camera_Translate + vrotate(Camera_LookAt,Camera_Rotate));
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
			scale		Camera_Scale
		}
		#declare Camera_Location	= Camera_Scale * (Camera_Translate + Camera_Location);
		#declare Camera_LookAt		= Camera_Scale * (Camera_Translate + Camera_LookAt);
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
			scale		Camera_Scale
		}
		#declare Camera_Location	= Camera_Scale * (Camera_Translate + Camera_Location);
		#declare Camera_LookAt		= Camera_Scale * (Camera_Translate + Camera_LookAt);
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
			scale		Camera_Scale
		}
		#declare Camera_Location	= Camera_Scale * (Camera_Translate + vrotate(Camera_Location,Camera_Rotate));
		#declare Camera_LookAt		= Camera_Scale * (Camera_Translate + vrotate(Camera_LookAt,Camera_Rotate));
	#break
#end


//------------------------------------------------------------------------------Textures/Materials

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
		[0.000 0.270 color rgbt < 0, 0, 0, 1> color rgbt < 0, 0, 0, 1>]
		[0.270 0.280 color rgbt <.5,.5,.4, 0> color rgbt <.8,.8,.4, 0>]
		[0.280 0.470 color rgbt < 0, 0, 0, 1> color rgbt < 0, 0, 0, 1>]
		[0.470 0.480 color rgbt <.4,.4,.5, 0> color rgbt <.4,.4,.8, 0>]
		[0.480 0.680 color rgbt < 0, 0, 0, 1> color rgbt < 0, 0, 0, 1>]
		[0.680 0.690 color rgbt <.5,.4,.4, 0> color rgbt <.8,.4,.4, 0>]
		[0.690 0.880 color rgbt < 0, 0, 0, 1> color rgbt < 0, 0, 0, 1>]
		[0.880 0.890 color rgbt <.5,.5,.5, 0> color rgbt < 1, 1, 1, 0>]
		[0.890 1.000 color rgbt < 0, 0, 0, 1> color rgbt < 0, 0, 0, 1>]
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
	translate	y * -1/2
	translate	x * -1/2
	rotate		x * 90
	scale		<slice_total * block_dist_x,1,slice_total * block_dist_x,>
}
#local grass_pigment_2 = pigment
{
//	color rgb <046,104,058,>/255/4
	color rgb 1.3 * <110,160,8,>/255/4	// oyonale makegrass color
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
	normal
	{
		wrinkles
	}
}
#declare atmos_interior = interior
{
	media
	{
		scattering
		{ 
			4, <0.2,0.4,1.0>/1000	// crappy approximaion of TerraPOV value
			extinction	1
		}
		density
		{
			cylindrical
			poly_wave	0.25
			density_map
			{
				[0	rgb 10.0/100]
				[1	rgb 00.1/100]
			}
			scale	slice_radius
			rotate	x * 90
		} 
	}
}
#local lamp_interior = interior
{
	media
	{
		emission light_color
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
	}
}
#local cap_metal_texture = texture
{
//	T_Chrome_1A		// 1 = dark, 5 = light, A = soft, E = reflective
	pigment {color rgb gamma_color_adjust(<0.20, 0.20, 0.20>)}
	finish
	{
		ambient		0.35
		brilliance	2
		diffuse		0.3
		metallic
		specular	0.80
		roughness	1/20
		reflection	0.1
	}
}
#local cap_glass_material = material
{
	texture
	{
		pigment	{Col_Glass_General}
		finish
		{
			specular	0.8
			roughness	0.001
			ambient		0
			diffuse		0
			reflection
			{
				0.00, 0.1
			}
			conserve_energy
		}
	}
	interior {I_Glass1}
}

//------------------------------------------------------------------------------Lights

#if (!NoLights)
	#local lamp_length = total_length + (slice_radius * 2 - cap_thickness)/2;
	light_source
	{
		0
		light_color
		area_light
		x, z * lamp_length, 1, floor(lamp_length/32)
		adaptive 1
//		jitter
	}
	// lamp
	cylinder
	{
		z*-(lamp_length/2), z*+(lamp_length/2), cap_thickness/2
		hollow
//		pigment {color light_color}
//		finish {ambient 1}
		pigment {rgbf 1}
		interior {lamp_interior}
		scale	0.9999
		no_shadow
	}
	// lamp shade, maybe try a parabolic one?
	#if (!NoLampShade)
		cylinder
		{
			<0,0,-lamp_length/2,>,<0,0,+lamp_length/2,>, cap_thickness/2
			open
			hollow
			pigment {shade_pigment}
			// mirror finish too slow!
//			finish {reflection {1.0} ambient 0 diffuse 0}
			scale	1
			rotate	z * 90
		}
	#end
#end


//------------------------------------------------------------------------------Sky & stars

#if (!NoSky)
	sphere
	{
		0, 10000
		hollow
		texture {Starfield1 scale 1000}
		no_shadow
	}
	#if (!NoFakeSky)
		// fake sky/shade, the reverse side should have lit stars on it
		// stacking them makes the shadows darker than either one alone, so maybe try another method
		// no longer compatible with endcaps
		cylinder
		{
			<0,0,-total_length/2,>,<0,0,+total_length/2,>, slice_radius - 64
			open
			hollow
			pigment {sky_pigment_3}
			scale	0.9999
			rotate	z * 90
		}
		cylinder
		{
			<0,0,-total_length/2,>,<0,0,+total_length/2,>, slice_radius - 64
			open
			hollow
			pigment {star_pigment_3}
			finish {ambient 1}
			scale	1.0000
			rotate	z * 90
		}
	#end
	// atmosphere
	#if (!NoAtmos)
		difference
		{
			merge
			{
				cylinder
				{
					<0,0,-total_length/2,>, <0,0,+total_length/2,>, slice_radius
				}
				sphere
				{
					0, slice_radius - cap_thickness/2
					scale		z/2
					translate	z * -total_length/2
				}
				sphere
				{
					0, slice_radius - cap_thickness/2
					scale		z/2
					translate	z * +total_length/2
				}
				scale	0.9999
			}
			// no reason to make the center a vacuum if the lamp shade is used
			// no longer compatible with endcaps
			#if (!NoLampShade)
				cylinder
				{
					<0,0,-total_length/2,>, <0,0,+total_length/2,>, slice_radius - 64
					scale	1.0001
				}
			#end
			hollow
			pigment {rgbt 1}
			interior {atmos_interior}
		}
	#end
#end


//------------------------------------------------------------------------------City

// use while loops to place each section (usually a total of 4)
#if (!NoCity)
	union
	{
		#include "CG_DEFAULT.inc"
		#include "CG_VEHICLES.inc"
		// city buildings - pass 1 - city buildings
		#declare buildings_per_block	= <2,3,0,>;
		#declare city_block_count	= <1,3,0,>;
		#local section_length		= block_dist_z * 4;
		#local z_offset			= section_length/2;
		#include "CG_DEFAULT.inc"
		#include "CG_NORMAL.inc"
		#local slice_count = 0;
		#while (slice_count < slice_total)
			#declare traffic_spacing = get_traffic_spacing(slice_count);
			#debug concat("ts = ", str(traffic_spacing,0,-1), "\n")
			#if (mod(slice_count, green_intrvl) > 0)
				#local city_strip = object
				{
					// need to make sure rotations match the orientation of the shade, i.e. more traffic where light is greatest
					// textures/normals are not scaled to the size of the scene AFAIK, need to fix this in Colefax include file
					#include "CG_CITY.inc"
					translate	city_center_offset
					translate	y * -slice_ydist
					rotate		z * slice_count * 360/slice_total
				}
				// 1
				object
				{
					city_strip
					translate	z * +z_offset
				}
				#if (!MiniCity)
					object
					{
						city_strip
						translate	z * +(z_offset+section_length)
					}
					// 2
					object
					{
						city_strip
						translate	z * -z_offset
					}
					object
					{
						city_strip
						translate	z * -(z_offset+section_length)
					}
				#end
				#end
			#local slice_count = slice_count + 1;
		#end
		// city buildings - pass 2 - long axis wood bands
		#declare buildings_per_block	= <2,3,0,>;
		#declare city_block_count	= <1,3,0,>;
		#include "CG_DEFAULT.inc"
		#include "CG_WOODS.inc"
		#local slice_count		= 0;
		#while (slice_count < slice_total)
			#if (mod(slice_count, green_intrvl) = 0)
				#declare traffic_spacing = get_traffic_spacing(slice_count);
				#local city_strip = object
				{
					// need to make sure rotations match the orientation of the shade, i.e. more traffic where light is greatest
					// textures/normals are not scaled to the size of the scene AFAIK, need to fix this in Colefax include file
					#include "CITY.inc"
					translate	city_center_offset
					translate	y * -slice_ydist
					rotate		z * slice_count * 360/slice_total
				}
				// 1
				object
				{
					city_strip
					translate	z * +z_offset
				}
				#if (!MiniCity)
					object
					{
						city_strip
						translate	z * +(z_offset+section_length)
					}
					// 2
					object
					{
						city_strip
						translate	z * -z_offset
					}
					object
					{
						city_strip
						translate	z * -(z_offset+section_length)
					}
				#end
			#end
			#local slice_count = slice_count + 1;
		#end
		// city buildings - pass 3 - circumference wood bands
		#declare buildings_per_block	= <2,3,0,>;
		#declare city_block_count	= <1,1,0,>;
		#include "CG_DEFAULT.inc"
		#include "CG_WOODS.inc"
		#local slice_count		= 0;
		#while (slice_count < slice_total)
			#if (mod(slice_count, green_intrvl) > 0)
				#declare traffic_spacing = get_traffic_spacing(slice_count);
				#local city_strip = object
				{
					// need to make sure rotations match the orientation of the shade, i.e. more traffic where light is greatest
					// textures/normals are not scaled to the size of the scene AFAIK, need to fix this in Colefax include file
					#include "CITY.inc"
					translate	city_center_offset
					translate	y * -slice_ydist
					rotate		z * slice_count * 360/slice_total
				}
				// 1
				object
				{
					city_strip
				}
				#if (!MiniCity)
					// 2
					object
					{
						city_strip
						translate	z * +section_length
					}
					// 3
					object
					{
						city_strip
						translate	z * -section_length
					}
				#end
			#end
			#local slice_count = slice_count + 1;
		#end
		// city buildings - pass 4 - fountain squares
		#declare buildings_per_block	= <2,3,0,>;
		#declare city_block_count	= <1,1,0,>;
		#include "CG_DEFAULT.inc"
		#include "CG_FOUNT.inc"
		#local slice_count		= 0;
		#while (slice_count < slice_total)
			#declare traffic_spacing = get_traffic_spacing(slice_count);
			#if (mod(slice_count, green_intrvl) = 0)
				#local city_strip = object
				{
					// need to make sure rotations match the orientation of the shade, i.e. more traffic where light is greatest
					// textures/normals are not scaled to the size of the scene AFAIK, need to fix this in Colefax include file
					#include "CITY.inc"
					translate	city_center_offset
					translate	y * -slice_ydist
					rotate		z * slice_count * 360/slice_total
				}
				// 1
				object
				{
					city_strip
				}
				#if (!MiniCity)
					// 2
					object
					{
						city_strip
						translate	z * +section_length
					}
					// 3
					object
					{
						city_strip
						translate	z * -section_length
					}
				#end
			#end
			#local slice_count = slice_count + 1;
		#end
		// city buildings - pass 5 - skinny end woods
		#declare buildings_per_block	= <2,1,0,>;
		#declare city_block_count	= <1,1,0,>;
		#local z_offset			= section_length/16;
		#include "CG_DEFAULT.inc"
		#include "CG_WOODS.inc"
		#local slice_count		= 0;
		#while (slice_count < slice_total)
			#declare traffic_spacing = get_traffic_spacing(slice_count);
			#local city_strip = object
			{
				// need to make sure rotations match the orientation of the shade, i.e. more traffic where light is greatest
				// textures/normals are not scaled to the size of the scene AFAIK, need to fix this in Colefax include file
				#include "CITY.inc"
				translate	city_center_offset
				translate	y * -slice_ydist
				rotate		z * slice_count * 360/slice_total
			}
			// 1
			object
			{
				city_strip
				translate	z * +(total_length/2-z_offset)
			}
			#if (!MiniCity)
				// 2
				object
				{
					city_strip
					translate	z * -(total_length/2-z_offset)
				}
			#end
			#local slice_count = slice_count + 1;
		#end
		scale	0.999
	}
#end


//------------------------------------------------------------------------------Shell

#if (!NoShell)
	// spokes
	#local spoke_object = union
	{
		#local spoke_count = 0;
		#while (spoke_count < spoke_total)
			cylinder
			{
				<0,0,0,>, <0,-slice_radius,0,>, cap_thickness/2
				rotate	z * 360/spoke_total * spoke_count
				rotate	z * 360/slice_total * 1/2/(buildings_per_block.x+1)	// compensate for off-centered of city tiles, should rotate the whole scene too
			}
			#local spoke_count = spoke_count + 1;
		#end
	}
	#local cap_metal_object = difference
	{
		sphere	{0, slice_radius + cap_thickness/2}
		sphere	{0, slice_radius - cap_thickness/2}
		plane	{+z, 0}
		difference
		{
			cone	{0, 0, z*+(2000), tand(75) * 2000}
			cone	{0, 0, z*+(2001), tand(15/2) * 2001}
		}
		scale	z/2
	}
	#local cap_glass_object = difference
	{
		sphere	{0, slice_radius + cap_thickness/2}
		sphere	{0, slice_radius - cap_thickness/2}
		plane	{+z, 0}
		difference
		{
			plane	{-z, 0}
			cone	{0, 0, z*+(2000), tand(75) * 2000}
		}
		cone	{0, 0, z*+(2001), tand(15/2) * 2001}
		scale	z/2
	}
	// greenery (also the outermost surface)
	// is clipping the city blocks at at least one point for some reason, don't see any cars either
	union
	{
		#local long_max = total_length/block_dist_z;
		#local long_count = 0;
		#while (long_count < long_max)
			#local slice_count = 0;
			#while (slice_count < slice_total)
				polygon
				{
					4,
					<-block_dist_x,0,-block_dist_z,>,
					<-block_dist_x,0,+block_dist_z,>,
					<+block_dist_x,0,+block_dist_z,>,
					<+block_dist_x,0,-block_dist_z,>
					texture
					{
						grass_texture_1
						translate	z * -(long_count * block_dist_z - total_length/2)
						translate	x * -(slice_count * block_dist_x)
					}
					translate	y * -slice_ydist
					translate	z * (long_count * block_dist_z - total_length/2)
					rotate		z * slice_count * 360/slice_total
				}
				#local slice_count = slice_count + 1;
			#end
			#local long_count = long_count + 1;
		#end
		scale	1.001
	}
	// end caps & spokes
	// putting spokes inside the cylinder looks nice, but leaves nasty shadows
	union
	{
		object
		{
			cap_metal_object
			texture {cap_metal_texture}
			rotate		y * 180
			translate	z*-(total_length/2)
		}
		object
		{
			cap_metal_object
			texture {cap_metal_texture}
			translate	z*+(total_length/2)
		}
		object
		{
			cap_glass_object
			material {cap_glass_material}
			rotate		y * 180
			translate	z*-(total_length/2)
		}
		object
		{
			cap_glass_object
			material {cap_glass_material}
			translate	z*+(total_length/2)
		}
//		object {spoke_object	translate z*-(total_length/2-256)}
//		object {spoke_object	translate z*+(total_length/2-256)}
	}
#end


//------------------------------------------------------------------------------Trees

// deciduous trees are better where the angle of the light is near vertical since coniferous trees are adapted to low angles
// there is a lot of sideways light in the middle of the habitat however
// need to check for collisions, otherwise rendering time is wasted
// make sure density is the same for horizontal and vertical
#if (!NoTrees)
	#include "gh_deciduous_tree.inc"
	#local green_number = 4;
	#local trees_scale = 3;
	#local trees_total = 0;
	// vertical
	#local trees_area = block_dist_x * green_width/2 * green_number;
	#local trees_max = trees_area * trees_per_unit;
	#local slice_count = 0;
	#while (slice_count < slice_total)
		#local trees_count = 0;
		#while (trees_count < trees_max)
			#local tree_transform_1 = transform
			{
				scale		trees_scale * (rand(Seed) * 1/2 + 3/2)
				rotate		y * rand(Seed) * 360 
				translate	y * -slice_ydist
				translate	x * (rand(Seed) * block_dist_x - block_dist_x/2)
				translate	z * rand(Seed) * -green_width/2
				translate	z * (floor(rand(Seed) * (green_number-1) + 1/2) * +256 - 256)
				rotate		z * (slice_count * 360/slice_total - 360/slice_total/2)
			}
			#local tree_transform_2 = transform
			{
				scale		trees_scale * (rand(Seed) * 1/2 + 3/2)
				rotate		y * rand(Seed) * 360 
				translate	y * -slice_ydist
				translate	x * (rand(Seed) * block_dist_x - block_dist_x/2)
				translate	z * rand(Seed) * +green_width/2
				translate	z * (floor(rand(Seed) * (green_number-1) + 1/2) * -256 + 256)
				rotate		z * (slice_count * 360/slice_total - 360/slice_total/2)
			}
			object {TREE	transform tree_transform_1}
			object {TREE	transform tree_transform_2}
			#local trees_count = trees_count + 1;
			#debug concat("_", str(trees_total,0,0))
			#local trees_total = trees_total + 1;
		#end
		#local slice_count = slice_count + 1;
	#end
/*
	// horizontal
	#local trees_area = block_dist_x * total_length;
	#local trees_max = trees_area * trees_per_unit;
	#local spoke_count = 0;
	#while (spoke_count < spoke_total)
		#local trees_count = 0;
		#while (trees_count < trees_max)
			#local tree_transform_1 = transform
			{
				scale		trees_scale * (rand(Seed) * 1/2 + 3/2)
				rotate		y * rand(Seed) * 360
				translate	y * -slice_ydist
				translate	x * (rand(Seed) * block_dist_x - block_dist_x/2)
				translate	z * (rand(Seed) * total_length - total_length/2)
				rotate		z * (spoke_count * 360/spoke_total - 360/spoke_total/2)
			}
			object {TREE	transform tree_transform_1}
			#local trees_count = trees_count + 1;
			#debug concat("_", str(trees_total,0,0))
			#local trees_total = trees_total + 1;
		#end
		#local spoke_count = spoke_count + 1;
	#end
*/
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
