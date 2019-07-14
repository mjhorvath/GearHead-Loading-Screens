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

#declare pov_version		= 1;				// 0 = 3.6; 1 = 3.7; 3.7 also has gamma adjustments in INI file
#declare Seed			= seed(8829464);
#declare Tiles			= 1;				// the default size of the scene, measured in tiles. Use this to zoom in/out.
#declare Sprite_Height		= 128;				// changes the camera's position. 0 for mecha, 1 for walls & terrain.
#declare Width			= 64;				// the default width of a tile.
#declare Subdivision		= 0;				// turn on/off mesh subdivision. This requires a special exe available on the Net.
#declare Included		= 1;				// tells any included files that they are being included.

#declare NoCity			= 0;
#declare NoSmoke		= 1;
#declare NoMechs		= 1;
#declare NoMissiles		= 1;
#declare NoBullets		= 1;
#declare NoRadiosity		= 1;

#declare buildings_per_block	= <2,4,0,>;			// 3x4 including roads
#declare city_block_count	= <1,10,0,>;
#declare city_tileable		= false;
#declare traffic_width		= 16/5;
#declare traffic_lanes		= 2;
#declare traffic_spacing	= 16;
#declare pavement_width		= 1;
#declare building_gap		= 2;
#declare building_width		= 16 - pavement_width * 2;
#declare block_dist_x		= traffic_width * (traffic_lanes * 2 + 1) + pavement_width * 2 + building_width * buildings_per_block.x + building_gap * (buildings_per_block.x - 1);
#declare block_dist_z		= traffic_width * (traffic_lanes * 2 + 1) + pavement_width * 2 + building_width * buildings_per_block.y + building_gap * (buildings_per_block.y - 1);
#declare block_size_xz		= <block_dist_x,block_dist_z,0,>;
#if (city_tileable)
	#declare city_size_total	= city_block_count * block_size_xz;
#else
	#declare city_size_total	= city_block_count * block_size_xz + <16,16,0,>;
#end
#declare min_building_height	= building_width * 1/2;
#declare max_building_height	= building_width * 4/2;
#declare building_height_turb	= 0.5;
#declare city_night		= true;
#declare city_right_hand_drive	= false;

#declare green_width		= (buildings_per_block.y * 2 + 1) * 16;
#declare AirCarPosition		= <-32,+32,+32,>;
#declare KojedoPosition		= +x * block_dist_x;
#declare MaanjiPosition		= -x * block_dist_x;
#declare KojedoCenter		= <0,4,0,>;
#declare LineVector		= vnormalize(-AirCarPosition + KojedoCenter + KojedoPosition);
#declare SceneScale		= pow(Width, 2);
#declare Burst			= true;

#declare Camera_Mode		= 6;				// 0 to 8; 0 = orthographic; 1 = oblique; 2 = perspective
#declare Camera_Diagonal	= cosd(45);
#declare Camera_Vertical	= 0;				//22.5;
#declare Camera_Horizontal	= 0;				//30;
#declare Camera_Scale		= 1;
#declare Camera_Aspect		= image_height/image_width;
#declare Camera_Distance	= 16;
#declare Camera_Translate	= <-32,0,0,>;			//<0,0,-city_size_total.y,>


//------------------------------------------------------------------------------Global settings

default {finish {ambient 0.1 diffuse 0.6}}
//default {finish {ambient 0.4 diffuse 0.7}}
global_settings
{
	#if (!NoRadiosity)
		#switch (pov_version)
			#case (0)
				ambient_light	0.3
				radiosity
				{
					always_sample	off
					brightness	0.3
				}
			#break
			#case (1)
//				ambient_light	0
//				assumed_gamma	1
				radiosity
				{
					always_sample	off
					brightness	0.5
					recursion_limit	1
					count		100
					error_bound	0.5
				}
			#break
		#end
	#end
	max_trace_level 16
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


//------------------------------------------------------------------------------Sky

sphere
{
	0, 100000
	texture
	{
		Starfield1
	}
}


//------------------------------------------------------------------------------Lights

#switch (pov_version)
	#case (0)
		#local light_color = 1.0;
	#break
	#case (1)
		#local light_color = 1.3;
	#break
#end
#local total_length = city_size_total.y;
light_source
{
	0
	rgb light_color
	area_light
	x, z * total_length, 1, floor(total_length/16)
	adaptive 1
	looks_like
	{
		cylinder
		{
			<0,0,-total_length/2,>,<0,0,+total_length/2,>, 10
			pigment {color rgb light_color}
			finish {ambient 1}
		}
	}
}

difference
{
	cylinder
	{
		<0,0,-total_length/2,>,<0,0,+total_length/2,>, 12
	}
	cylinder
	{
		<0,0,-total_length/2-1,>,<0,0,+total_length/2+1,>, 11
	}
	pigment
	{
		radial
		color_map
		{
			[0/2 rgbt <0,0,0,0,>]
			[1/2 rgbt <0,0,0,1,>]
			[2/2 rgbt <0,0,0,0,>]
		}
		rotate x * 90
	}
	// too slow!
//	finish { reflection {1.0} ambient 0 diffuse 0 }
}


//------------------------------------------------------------------------------Sky

sky_sphere
{
	pigment
	{
		color rgb 1
	}
}


//------------------------------------------------------------------------------City

#if (!NoCity)
	#declare temp_max	= 36;
	#declare temp_length	= block_dist_x * temp_max;
	#declare temp_radius	= temp_length/pi/2;
//	difference
//	{
		union
		{
			#local temp_count = 0;
			#while (temp_count < temp_max)
				#declare traffic_spacing	= sind(temp_count/temp_max * 180) * 16;
				object
				{
					#include "CITY.inc"
					translate	y * -temp_radius
// only if non-tiling?			translate	z * 8
					rotate		z * 360/temp_max * temp_count
				}
				#local temp_count = temp_count + 1;
			#end
			clipped_by
			{
				cylinder
				{
					<0,0,-green_width/2,>, <0,0,+green_width/2,>, temp_radius
				}
			}
		}

//		cylinder
//		{
//			<0,0,-green_width/2,>, <0,0,+green_width/2,>, temp_radius
//		}

//	}
	union
	{
		// end caps
		cylinder
		{
			<0,0,-1,>, <0,0,+1,>, temp_radius/2
			translate	z * -city_size_total.y/2
		}
		cylinder
		{
			<0,0,-1,>, <0,0,+1,>, temp_radius/2
			translate	z * +city_size_total.y/2
		}
		// spokes
		#local spoke_count = 0;
		#while (spoke_count < 9)
			cylinder
			{
				<0,0,0,>, <temp_radius,0,0,>, 2
				rotate		z * 360/9 * spoke_count
				translate	z * +city_size_total.y/2
			}
			cylinder
			{
				<0,0,0,>, <temp_radius,0,0,>, 2
				rotate		z * 360/9 * spoke_count
				translate	z * -city_size_total.y/2
			}
			#local spoke_count = spoke_count + 1;
		#end
		pigment {color rgb <0.6,0.7,1.0>}
	}
	// greenery
	#local tx_pigment1 = pigment
	{
		image_map {png "olivepink_marble.png"}
		rotate x * 90
	}
	#local tx_pigment2 = pigment
	{
		color rgb <046,104,058,>/255/2
	}
	#local tx_pigment3 = pigment
	{
		average
		pigment_map
		{
			[2 tx_pigment1]
			[2 tx_pigment2]
		}
	}
	#local tx_texture1 = texture
	{
		pigment {tx_pigment3}
		normal
		{
			wrinkles
//			scale		1/SceneScale
//			scale		<1,16/HeightScale,1,>
		}
	}
	difference
	{
		cylinder
		{
			<0,0,-green_width/2,>, <0,0,+green_width/2,>, temp_radius
		}
		cylinder
		{
			<0,0,-green_width/2-1,>, <0,0,+green_width/2+1,>, temp_radius - 2
		}
		//texture {tx_texture1}
		pigment {tx_pigment2}
	}
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
text
{
	ttf "hatten.ttf" "Just a minute..." 0.1, 0
	pigment { White }
	scale 8
	rotate y * -90
	translate <-0,8,24>
}
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
