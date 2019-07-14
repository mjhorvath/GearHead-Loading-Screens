// Desc: Several GearHead mecha battling it out in a city setting.
// Auth: Michael Horvath
// Home Page: http://www.geocities.com/Area51/Quadrant/3864/gearhead.htm
// This file is licensed under the terms of the CC-LGPL.
// Dependencies:
// 1. CITY GENERATOR INCLUDE FILE by Chris Colefax
// 2. Rune's particle system

#version 3.7

#include "colors.inc"
#include "metals.inc"
#include "glass.inc"
#include "transforms.inc"
//#include "CIE.inc"			// http://www.ignorancia.org/en/index.php?page=Lightsys
//#include "lightsys.inc"			// http://www.ignorancia.org/en/index.php?page=Lightsys
//#include "lightsys_constants.inc"	// http://www.ignorancia.org/en/index.php?page=Lightsys

#declare Seed			= seed(8829464);
#declare Tiles			= 1;				// the default size of the scene, measured in tiles. Use this to zoom in/out.
#declare Sprite_Height	= 128;				// changes the camera's position. 0 for mecha, 1 for walls & terrain.
#declare Width			= 64;				// the default width of a tile.
#declare Subdivision	= 0;				// turn on/off mesh subdivision. This requires a special exe available on the Net.
#declare Minimal		= 0;
#declare TexQual		= 1;					// -1 = random colors, no finishes, normals or interiors, 0 = no finishes, normals or interiors, 1 = no interiors, 2 = everything
#declare Included		= 1;				// tells any included files that they are being included.
#declare NoRadiosity	= 0;
#declare NoCity			= 0;
#declare NoMechs		= 0;
#declare NoMissiles		= 0;
#declare NoSmoke		= 0;
#declare NoExplosions	= 0;
#declare Burst			= 1;
#declare NoColors		= 0;
#declare NoWeapons		= 0;

#if (Minimal)
	#declare NoRadiosity		= 1;
	#declare NoCity			= 0;
	#declare NoSmoke		= 0;
	#declare NoMechs		= 0;
	#declare NoMissiles		= 0;
	#declare NoExplosions		= 0;
#end

#declare city_block_count	= <8,8,0>;
#declare street_width		= 32;
#declare traffic_width		= 16/5;
#declare traffic_lanes		= 2;
#declare buildings_per_block	= <4,2,0>;
#declare max_building_height	= 8;
#declare pavement_width		= 2;
#declare building_gap		= pavement_width * 2;
#declare building_width		= 16 - pavement_width * 2;
#declare building_height_turb	= 0.5;
#declare city_default_objects	= false;
#declare block_dist_x		= traffic_width * (traffic_lanes * 2 + 1) + pavement_width * 2 + building_width * buildings_per_block.x + building_gap * (buildings_per_block.x - 1);
#declare block_dist_z		= traffic_width * (traffic_lanes * 2 + 1) + pavement_width * 2 + building_width * buildings_per_block.y + building_gap * (buildings_per_block.y - 1);

#declare Camera_Mode		= 2;				// 1 = oblique; 2 = perspective; 3 = orthographic
#declare Camera_Eye			= 1;				// 0 = left, 1 = right, -1 = neither
#declare Camera_Distance	= Width * 4;
#declare Camera_Vertical	= 225+22.5;
#declare Camera_Horizontal	= 30;
#declare Camera_Scale		= 1.1;
#declare Camera_Diagonal	= cosd(45);
#declare Camera_Aspect		= image_height /image_width;
#declare Camera_Translate	= -x * block_dist_x/2;
#include "gh_camera.inc"
#declare camera_location	= Camera_Location;

// *** CIE & LIGHTSYS ***
#include "CIE.inc"
CIE_ColorSystemWhitepoint(sRGB_ColSys,Illuminant_D65)
#include "lightsys.inc"          
#include "rspd_jvp.inc"          // predefined material samples

// *** trace control ***
#declare r_sun=seed(29);
#declare hf_res=800;

// *** sky sphere and sun ***
//#declare Al=90*rand(r_sun);
//#declare Az=360*rand(r_sun);
#declare Al=60;
#declare Az=300;
#declare North=<-1+2*rand(r_sun),0,-1+2*rand(r_sun)>;
#declare Intensity_Mult=1;
#declare Max_Vertices=800;
#include "CIE_Skylight"

//#declare light_lumens		= 4;					// float
//#declare light_temp		= Daylight(6500);			// float
//#declare light_color		= Light_Color(light_temp, light_lumens);
//#declare light_location	= vrotate(<0,0,-7000>, <+60,-30,+00>);

#macro gamma_color_adjust(in_color)
	color srgbft in_color + <0,0,0,0,0>
#end

//------------------------------------------------------------------------------Global settings

#if (!NoRadiosity)
	global_settings
	{
		assumed_gamma	1
		ambient_light	0
		max_trace_level 16
		radiosity
		{
			recursion_limit	1
			brightness		0.8
			count			100
			error_bound		0.5
			always_sample	off
		}
	}
#else
	global_settings
	{
		assumed_gamma	1
		ambient_light	0.5
		max_trace_level 16
	}
#end

//------------------------------------------------------------------------------Lights

light_source{
 SolarPosition
 Light_Color(SunColor,6)
 parallel
}

default {finish {ambient 0.4 diffuse 0.7}}

//------------------------------------------------------------------------------Sky

sky_sphere
{
	pigment
	{
		gradient y
		pigment_map
		{
			[0.00 gamma_color_adjust(<1,1,1>)]
			[0.10 wrinkles color_map {[0.5 gamma_color_adjust(<1,1,1>)] [0.7 gamma_color_adjust(<0.4, 0.5, 0.6>)]} scale 0.1]
			[0.15 wrinkles color_map {[0.1 gamma_color_adjust(<1,1,1>)] [0.4 gamma_color_adjust(<0.4, 0.5, 0.6>)]} scale 0.1]
			[0.20 gamma_color_adjust(<0.4, 0.5, 0.6>)]
		}
	}
}

//------------------------------------------------------------------------------Ground

plane
{
	-y, 0.02 hollow
	pigment {gamma_color_adjust(<1,1,1>*1/2)}
}

//------------------------------------------------------------------------------City

#if (!NoCity)
	#include "CG_DEFAULT_FLAT.INC"
	#if (!Minimal)
		#include "CG_VEHICLES_FLAT.INC"
		#include "CG_FLATS_FLAT.INC"
		#include "CG_HOTELS_FLAT.INC"
		#include "CG_OFFICES_FLAT.INC"
		#include "CG_PARK_FLAT.INC"
//		#include "CG_SQUARE_FLAT.INC"
	#end
	#include "CG_CITY_FLAT.inc"
#end

//------------------------------------------------------------------------------Mecha

#if (!NoColors)
	#declare MTX = texture { pigment { gamma_color_adjust(<rand(Seed),rand(Seed),rand(Seed)>) } finish { F_MetalA } }
	#declare CTX = texture { pigment { gamma_color_adjust(<rand(Seed),rand(Seed),rand(Seed)>) } finish { F_MetalA } }
	#declare HTX = texture { pigment { gamma_color_adjust(<rand(Seed),rand(Seed),rand(Seed)>) } finish { F_MetalA } }
#else
	#declare MTX = texture { pigment { gamma_color_adjust(1) } finish { F_MetalA } }
	#declare CTX = texture { pigment { gamma_color_adjust(0) } finish { F_MetalA } }
	#declare HTX = texture { pigment { gamma_color_adjust(1/2) } finish { F_MetalA } }
#end

#declare Plain_Gray = texture { pigment { gamma_color_adjust(1/2) } finish { F_MetalA  } }
#declare Plain_LightGray = texture { pigment { gamma_color_adjust(3/4) } finish { F_MetalA  } }
#declare Plain_DarkGray = texture { pigment { gamma_color_adjust(1/4) } finish { F_MetalA  } }

#local KojedoPosition	= 0;
#local MaanjiPosition	= -x * block_dist_x;
#local KtoMVector	= KojedoPosition - MaanjiPosition;
#local AirCarPosition	= <-32,+16,+32,>;
#local KojedoCenter	= <+00,+04,+00,>;
#local LineVector	= -AirCarPosition + KojedoCenter;

#if (!NoMechs)
	#declare NoColors = 0;
	#include "ara_kojedo.pov"
	object
	{
		ara_kojedo_
		translate <18.42348,0,-364.0902> * -1
		scale 1/10	// was 1/12
		scale 3/4
		rotate y * -45
		rotate y * clock * 360
		// edit below
		scale 1/4
		translate KojedoPosition
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
		translate <0.000000, 0.000000, 0.000000>
		scale <1.000000, 1.000000, 1.000000>
		scale 1/2
		scale 3/4
		rotate y * -45
		rotate y * clock * 360
		// edit below
		scale 1/4
		rotate y * 90
		translate MaanjiPosition
	}
	
	#include "aer_aircar.pov"
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
						texture {pigment {gamma_color_adjust(<1,1,1,0,1>)}}
						interior {ior ((1 - InvCount1 * 0.1) + Count2 * InvCount1 * 0.1)}
					}
				}
				#declare Count2 = Count2 + Increment2;
			#end
			#declare Count1 = Count1 + Increment1;
		#end
	}
	
	union
	{
		object
		{
			Air_Car_
			rotate x * 90
			rotate y * -90
			translate y * -3
			translate x * 8
		}
/*
		object
		{
			Exhaust_Plume
			translate z * 39
			rotate z * -60
		}
		object
		{
			Exhaust_Plume
			translate z * -39
			rotate z * -60
		}
*/
		translate y * 24.37624 + 3
		Reorient_Trans(x, <LineVector.x,0,LineVector.z,>)
		scale 1/10
		scale 3/4
		translate AirCarPosition
	}
#end

//------------------------------------------------------------------------------Missiles

#macro Random_MissilePath(SplinePath, SizeScale)
	#declare NewPath = spline
	{
		cubic_spline
		-0.25, SplinePath(0.00) - y * SizeScale/2
		 0.00, SplinePath(0.00) + y * SizeScale/2
		 0.25, SplinePath(0.25) + y + SizeScale * (<rand(Seed),rand(Seed),rand(Seed),> * 2 - 1) + SizeScale * y * 3
		 0.50, SplinePath(0.50) + y + SizeScale * (<rand(Seed),rand(Seed),rand(Seed),> * 2 - 1) + SizeScale * y * 3
		 1.00, SplinePath(1.00) + y * SizeScale/2
		 1.25, SplinePath(1.00) - y * SizeScale/2
	}
#end

#if (!NoMissiles)
	#local MissilePath = spline
	{
		linear_spline
		0.00, MaanjiPosition
		1.00, KojedoPosition
	}
	#local MissileUnion = union
	{
		#local iCount = 0;
		#while (iCount < 3)
			Random_MissilePath(MissilePath, 8)
			#switch (iCount)
				#case (0)
					#local missile_t = 0;		// + rand(Seed) * 1/4;
				#break
				#case (1)
					#local missile_t = 1/4;		// + rand(Seed) * 1/4;
				#break
				#case (2)
					#local missile_t = 2/4;		// + rand(Seed) * 1/4;
				#break
			#end
			#local ctr = missile_t;
			#while (ctr < 1)
				cone
				{
					NewPath(ctr), ctr * 2/3, NewPath(ctr + 0.01), ctr * 2/3
					open
					texture
					{
						pigment
						{
							bozo
							color_map
							{
								[0 color rgbt <1,1,1,ctr,>]
								[1 color rgbt <1,1,1,1,>]
							}
						}
						scale 4
					}
				}
				#local ctr = ctr + 0.01;
			#end
			#local missile_location_0 = NewPath(missile_t - 0.01);
			#local missile_location_1 = NewPath(missile_t);
			#local missile_vector = missile_location_0 - missile_location_1;
			#include "gh_projectile_missile_nosmoke.inc"
			object
			{
				Missile
				scale 1/4
				Reorient_Trans(z, missile_vector)
				translate missile_location_1
			}
			#local iCount = iCount + 1;
		#end
	}
	object {MissileUnion}
#end

//------------------------------------------------------------------------------Bullets

#declare BulletPath = spline
{
	linear_spline
	0.00, KojedoCenter
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

//------------------------------------------------------------------------------Explosions

#if (!NoExplosions)
	#include "gh_explosion_smokey.inc"
	#declare ExplosionUnion = union
	{
		object {Layer1}
		object {Layer2}
		object {Layer3}
		object {Layer4}
		rotate y * rand(Seed) * 360
		scale 4
		translate MaanjiPosition
		translate y * 3
	}
	object {ExplosionUnion}
#end

//------------------------------------------------------------------------------Loading text

text
{
	ttf "Haettenschweiler.ttf" "Just a minute..." 0.1, 0
	pigment { White }
	scale 8
	rotate y * -90
	translate <-0,8,24>
}

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
