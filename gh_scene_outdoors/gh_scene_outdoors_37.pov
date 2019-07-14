// Desc: Several GearHead mecha battling it out in a woodland setting.
// Auth: Michael Horvath
// Home Page: http://www.geocities.com/Area51/Quadrant/3864/gearhead.htm
// This file is licensed under the terms of the CC-LGPL.
// Dependencies:
// 1. "LegoRoad_macro.inc" by Michael Horvath
// 2. Rune's particle system
// 3. "VEG.INC" by Joerg Schrammel
// 4. "grasspatch.inc" by Josh English
// 5. "sphere.inc" by Shuhei Kawachi

#version 3.7

#include "stdinc.inc"
#include "textures.inc"
#include "metals.inc"
#include "glass.inc"

#declare TexQual		= 1;
#declare Tiles			= 16;		// the default size of the scene, measured in tiles. (Use this to zoom in/out.)
#declare Width			= 64;		// the default width of a tile.
#declare Subdivision		= 0;		// turn on/off mesh subdivision. (Requires a special executable available on the Net.)
#declare Included		= 1;		// tells any included files that they are being included.
#declare Seed			= seed(22231);
#declare SceneScale		= pow(Width, 2);
#declare MechScale		= 2;
#declare Meters			= 4;
#declare WaterLevel		= Width;
#declare TreesLevel		= Width + 8;
#declare GrassLevel		= Width;
#declare RocksLevel		= Width;
#declare TreesAngle		= 6;
#declare GrassAngle		= 6;
#declare RocksAngle		= 6;
#declare Included		= 1;		// Informs included files that they are being included.
#declare TreesPatches		= 250;		// The number of tree patches.		(250)
#declare GrassPatches		= 0;		// The number of grass patches.		(0)
#declare RocksPatches		= 100;		// The number of rock patches.		(100)
#declare TreesNumber		= 10;		// The number of trees per patch.	(10)
#declare GrassNumber		= 1;		// The number of grass per patch.	(1)
#declare RocksNumber		= 1;		// The number of rocks per patch.	(1)
#declare RotateExtra		= 0;

#declare NoColors		= 0;
#declare NoGrid			= 1;		//alw
#declare NoText			= 0;		//nev
#declare NoRadiosity		= 1;		//nev
#declare NoSky			= 0;		//alw		(disable if radiosity is used)
#declare NoWater		= 0;		//nev
#declare NoGround		= 0;		//nev
#declare NoRoad			= 0;		//nev		(depends on ground)
#declare NoWall			= 0;		//nev		(depends on ground)
#declare NoTrees		= 0;		//nev		(depends on road & ground)
#declare NoGrass		= 0;		//alw		(obsolete; depends on road & ground)
#declare NoRocks		= 0;		//nev		(depends on road & ground)
#declare NoDome			= 0;		//nev		(depends on ground)
#declare NoMecha		= 0;		//nev		(depends on ground)
#declare NoSmoke		= 0;		//nev		(depends on ground & camera)
#declare NoExplosions		= 0;		//nev		(depends on camera)
#declare NoBullets		= 0;		//nev		(depends on mecha)
#declare NoMissiles		= 0;		//nev		(depends on ground & mecha)
#declare NoExhaust		= 1;		//alw		(depends on mecha)
#declare NoWeapons		= 0;

#declare Camera_Mode		= 3;		// 0 = orthographic; 1 = oblique; 2 = perspective
#declare Camera_Diagonal	= cosd(45);
#declare Camera_Vertical	= 225 + 22.5 + RotateExtra;
#declare Camera_Horizontal	= 30;
#declare Camera_Scale		= 1;
#declare Camera_Location	= vaxis_rotate(<1, 0, 1,>, <-1, 0, 1,>, Camera_Horizontal) * Camera_Diagonal * Tiles * Camera_Scale;
#declare Camera_Location	= vaxis_rotate(Camera_Location, y, Camera_Vertical);
#declare Camera_Location	= Camera_Location + 0;
#declare Camera_LookAt		= 0;
#declare Camera_LookAt		= vaxis_rotate(Camera_LookAt, y, Camera_Vertical);
#declare Camera_LookAt		= Camera_LookAt + 0;
#declare Camera_Aspect		= image_height / image_width;
#declare Camera_Distance	= SceneScale;
#declare Camera_Translate	= <0,0,0>;
#include "gh_camera.inc"

#declare camera_location	= Camera_Location;
#declare light_source_location	= vrotate(<0,0,-7000>, <+60,-30,+00>);
/*
#macro gamma_color_adjust(in_color)
	#if (version < 3.7)
		#local out_gamma = 2.2;
	#else
		#local out_gamma = 2.2;			// 1.0
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
*/
#macro gamma_color_adjust(in_color)
	color srgbft in_color + <0,0,0,0,0>
#end

//------------------------------------------------------------------------------Global settings
#if (!NoRadiosity)
	global_settings
	{
		assumed_gamma 1
		ambient_light 0.25
		radiosity
		{
			recursion_limit 1
			brightness 0.5
			count 100
			error_bound 0.5
			always_sample off
		}
		max_trace_level 256
	}
#else
	global_settings
	{
		assumed_gamma 1
		ambient_light 0.25
	}
#end

//------------------------------------------------------------------------------Lights
light_source
{
	light_source_location
	gamma_color_adjust(<1,1,1>*1.5)
	parallel
}
default {finish {ambient .4 diffuse .7}}


//------------------------------------------------------------------------------Sky
#if (!NoSky)
	sky_sphere
	{
		pigment
		{
			gradient y
			color_map
			{
				[0.0 gamma_color_adjust(<0.6,0.7,1.0>)]
				[0.7 gamma_color_adjust(<0.0,0.1,0.8>)]
			}
		}
	}
#else
//	background {color gamma_color_adjust(<0.6,0.7,1.0>)}
	background {color gamma_color_adjust(<1,1,1>)}
#end

//------------------------------------------------------------------------------Ground
#if (!NoGround)
	#local Pigment0 = pigment
	{
		gradient y
		color_map
		{
			[0 gamma_color_adjust(<0,0,0>)]
			[1 gamma_color_adjust(<1,1,1>)]
		}
	}
	#local Pigment1 = pigment
	{
		image_map
		{
			png "olivepink_marble_sat.png"
		}
//		rotate x* 90
	}
	#local Pigment2 = pigment
	{
		slope {-y}
		color_map
		{
			[0	gamma_color_adjust(<046/255,104/255,058/255>)]
			[0.25	gamma_color_adjust(<139/255,117/255,102/255>)]
			[0.5	gamma_color_adjust(<1,1,1>/2)]
		}
	}
	#local Pigment3 = pigment
	{
		average
		pigment_map
		{
			[1 Pigment1]
			[1 Pigment2]
		}
	}
	#local Ground_a = height_field
	{
		png "hf_big.png"
		smooth
		texture {pigment {Pigment3}}
		translate <-1/2, 0, -1/2>
		normal
		{
			bozo
			scale y * 16
			scale 1/SceneScale
//			no_bump_scale
		}
		scale y * 1/16
		scale SceneScale
	}
#else
	#declare WaterLevel = -1;
	#declare TreesLevel = -1;
	#declare GrassLevel = -1;
	#declare RocksLevel = -1;
	#local Ground_a = plane {y, 0 pigment {gamma_color_adjust(<1,1,1>/2)}}
#end

//------------------------------------------------------------------------------Water
#if (!NoWater)
	#declare WaterSurface = plane
	{
		y, WaterLevel
		texture
		{
			pigment {gamma_color_adjust(<0,1/4,1/2,0,1>/2)}
			normal {wrinkles scale 8}
			finish {Glossy}
		}
		clipped_by {box {-SceneScale/2, +SceneScale/2}}
	}
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

#local KojedoPosition	= trace(Ground_a, <-06 * Width, 1024, -05 * Width>, -y);
#local MaanjiPosition	= trace(Ground_a, <+12 * Width, 1024, +05 * Width>, -y);
#local VadelPosition	= trace(Ground_a, <-08 * Width, 1024, +04 * Width>, -y);
#local KtoMVector	= KojedoPosition - MaanjiPosition;
#local VtoMVector	= VadelPosition - MaanjiPosition;

#if (!NoMecha)
	#local MechaUnion = union
	{
		#include "ara_kojedo.pov"
		object
		{
			ara_kojedo_
			translate <18.42348,0,-364.0902> * -1
			scale 1/375
			// edit below
			scale 10 * Meters
			Reorient_Trans(z, <-KtoMVector.x, 0, -KtoMVector.z,>)
			translate KojedoPosition
		}
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
			translate y * -4.65
			scale 1/115
			//edit below
			scale 18 * Meters
			Reorient_Trans(z, <+KtoMVector.x, 0, +KtoMVector.z,>)
			translate MaanjiPosition
		}
		#include "btr_vadel.pov"
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
			scale 16 * Meters
			Reorient_Trans(z, <-VtoMVector.x, 0, -VtoMVector.z,>)
			translate VadelPosition
		}
	}
#end

//------------------------------------------------------------------------------Aircraft exhaust (crappy)
#if (!NoExhaust)
	#local Increment1 = 1/16;
	#local Increment2 = 1/16;
	#local ExhaustPlume = union
	{
		#local Count1 = 1 - Increment1;
		#while (Count1 < 1)
			#local InvCount1 = 1 - Count1;
			#local Count2 = 0;
			#while (Count2 < 1)
				intersection
				{
					cone
					{
						<0,Count2 * -128,0,>, 6 + Count2 * Count1 * 26, <0,(Count2 + Increment2) * -128,0,>, 6 + (Count2 + Increment2) * Count1 * 26
						//open
					}
					material
					{
						texture {pigment {gamma_color_adjust(<1,1,1,0,1>)}}
						interior {ior ((1 - InvCount1 * 0.1) + Count2 * InvCount1 * 0.1)}
					}
				}
				#local Count2 = Count2 + Increment2;
			#end
			#local Count1 = Count1 + Increment1;
		#end
		rotate z * -60
		translate VadelPosition
	}
#end

//------------------------------------------------------------------------------Bullets
#if (!NoBullets)
	#include "gh_bullet.inc"
	#local BulletPath = spline
	{
		linear_spline
		0.00, VadelPosition
		1.00, MaanjiPosition
	}
	#local BulletUnion = union
	{
		object
		{
			bullet
			Reorient_Trans(y, VtoMVector)
			scale 16
			translate BulletPath(0.8)
		}
	}
#end

//------------------------------------------------------------------------------Missiles
#macro Random_MissilePath(TraceObject, SplinePath, SizeScale)
	#declare NewPath = spline
	{
		cubic_spline
		-0.25, SplinePath(0.00) - y * SizeScale/2
		0.00, SplinePath(0.00) + y * SizeScale/2
		0.25, trace(TraceObject, SplinePath(0.25) + y * 1024, -y) + SizeScale * (<rand(Seed),rand(Seed),rand(Seed),> * 2 - 1) + SizeScale * y * 3
		0.50, trace(TraceObject, SplinePath(0.50) + y * 1024, -y) + SizeScale * (<rand(Seed),rand(Seed),rand(Seed),> * 2 - 1) + SizeScale * y * 3
		1.00, SplinePath(1.00) + y * SizeScale/2
		1.25, SplinePath(1.00) - y * SizeScale/2
	}
#end

#if (!NoMissiles)
	#local MissilePath = spline
	{
		linear_spline
		0.00, KojedoPosition
		1.00, MaanjiPosition
	}
	#local MissileUnion = union
	{
/*
		#include "gh_projectile_missile.inc"
		object
		{
			Missile
			scale 1/4
//			scale 4
			Reorient_Trans(z, KtoMVector)
			translate MissilePath(0.8)
			translate x * 4
		}
		object
		{
			Missile
			scale 1/4
//			scale 4
			Reorient_Trans(z, KtoMVector)
			translate MissilePath(0.6)
			translate x * 8
		}
		object
		{
			Missile
			scale 1/4
//			scale 4
			Reorient_Trans(z, KtoMVector)
			translate MissilePath(0.4)
		}
*/
		#local iCount = 0;
		#while (iCount < 2)
			Random_MissilePath(Ground_a, MissilePath, Width)
			#local ctr = 0;
			#local startdiam = 0.5;
			#while (ctr < 1)
				cone
				{
					NewPath(ctr), 0.5 + ctr, NewPath(ctr + 0.01), 0.5 + ctr + ctr
					open
					texture
					{
						pigment
						{
							bozo
							color_map
							{
								[0 gamma_color_adjust(<1,1,1,0,ctr>)]
								[1 gamma_color_adjust(<1,1,1,0,1>)]
							}
						}
						scale 4
					}
				}
				#local ctr = ctr + 0.01;
			#end
			#local iCount = iCount + 1;
		#end
	}
#end

//------------------------------------------------------------------------------Geodesic dome
#if (!NoDome)
	#local DomePosition = <-01 * Width, 1024, -11 * Width>;
	#local DomePosition = trace (Ground_a, DomePosition, -y);
	#include "gh_dome.inc"
	#declare Dome_a = object
	{
		Dome_Object
		scale 8
		translate DomePosition
	}
#else
	#declare Dome_a = box {-1, +1}
#end

//------------------------------------------------------------------------------Smoke
#if (!NoSmoke)
	#declare camera_location = Camera_Location;
	#declare light_source_location = <+3000, +6000, -7000>;
	#include "gh_effect_smoke.inc"

	#local Smoke0Position = trace(Ground_a, <Width * +00, 1024, Width * +00,>, -y);
	#local Smoke1Position = trace(Ground_a, <Width * +08, 1024, Width * -01,>, -y);
	#local Smoke2Position = trace(Ground_a, <Width * +13, 1024, Width * +06>, -y);
	#local Smoke3Position = trace(Ground_a, <Width * +13, 1024, Width * +04>, -y);

	#declare SmokeUnion = union
	{
		union
		{
			object {Layer1}
			object {Layer2}
			object {Layer3}
			object {Layer4}
			rotate y * rand(Seed) * 360
			scale 16
			translate Smoke0Position
		}
		union
		{
			object {Layer1}
			object {Layer2}
			object {Layer3}
			object {Layer4}
			rotate y * rand(Seed) * 360
			scale 16
			translate Smoke1Position
		}
		union
		{
			object {Layer1}
			object {Layer2}
			object {Layer3}
			object {Layer4}
			rotate y * rand(Seed) * 360
			scale 4
//			scale 2
			translate Smoke2Position
		}
		union
		{
			object {Layer1}
			object {Layer2}
			object {Layer3}
			object {Layer4}
			rotate y * rand(Seed) * 360
			scale 4
//			scale 2
			translate Smoke3Position
		}
	}
#end

//------------------------------------------------------------------------------Explosions
#if (!NoExplosions)
	#declare camera_location = Camera_Location;
	#declare light_source_location = <+3000, +6000, -7000>;
	#include "gh_explosion_smokey.inc"

	#declare ExplosionUnion = union
	{
		object {Layer1}
		object {Layer2}
		object {Layer3}
		object {Layer4}
		rotate y * rand(Seed) * 360
		scale 16
		translate KojedoPosition
	}

#end

//------------------------------------------------------------------------------Loading text
#if (!NoText)
	#declare TextUnion = union
	{
		text
		{
			ttf "Haettenschweiler.ttf" "Just a minute..." 0.1, 0
			pigment {gamma_color_adjust(<1,1,1>)}
			scale Width * 3/2
			rotate y * -90
			translate <Width * 4, Width * 4, Width * 4>
			rotate y * RotateExtra
		}
	}
#end

//------------------------------------------------------------------------------Roads
#if (!NoRoad)
	#include "legoroad_macro.inc"
	#local scale_ratio =		48/360;		//48/360
	#declare LRoad_RoadSurfaceTexture = texture
	{
		pigment {gamma_color_adjust(<1,1,1>/4)}
	}
	#declare LRoad_InnerStripeTexture = texture
	{
		pigment {gamma_color_adjust(<1,1,0>/2)}
	}
	#declare LRoad_RoadWidth =	array[3] {280 * scale_ratio, 306 * scale_ratio, 360 * scale_ratio,}
	#declare LRoad_StripeInterval =	array[3] { 64 * scale_ratio,  64 * scale_ratio,  64 * scale_ratio,}
	#declare LRoad_EmbankmentTexture = texture
	{
		LRoad_EmbankmentTexture
		normal {granite .05 scale .01}
	}

	#local segments_num = 22;
	#local road_coordinates = array[segments_num]
	{
		trace (Ground_a, <-22 * Width, 1024, -10 * Width>, -y),
		trace (Ground_a, <-18 * Width, 1024, -02 * Width>, -y),
		trace (Ground_a, <-16 * Width, 1024, -03 * Width>, -y),
		trace (Ground_a, <-10 * Width, 1024, +02 * Width>, -y),
		trace (Ground_a, <-11 * Width, 1024, +00 * Width>, -y),
		trace (Ground_a, <-05 * Width, 1024, +02 * Width>, -y),
		trace (Ground_a, <-03 * Width, 1024, +01 * Width>, -y),
		trace (Ground_a, <+04 * Width, 1024, +01 * Width>, -y),
		trace (Ground_a, <+04 * Width, 1024, +00 * Width>, -y),
		trace (Ground_a, <+09 * Width, 1024, -01 * Width>, -y),
		trace (Ground_a, <+10 * Width, 1024, -02 * Width>, -y),
		trace (Ground_a, <+15 * Width, 1024, -05 * Width>, -y),
		trace (Ground_a, <+13 * Width, 1024, -06 * Width>, -y),
		trace (Ground_a, <+15 * Width, 1024, -11 * Width>, -y),
		trace (Ground_a, <+14 * Width, 1024, -10 * Width>, -y),
		trace (Ground_a, <+15 * Width, 1024, -16 * Width>, -y),
		trace (Ground_a, <+16 * Width, 1024, -15 * Width>, -y),
		trace (Ground_a, <+18 * Width, 1024, -20 * Width>, -y),
		trace (Ground_a, <+18 * Width, 1024, -19 * Width>, -y),
		trace (Ground_a, <+20 * Width, 1024, -22 * Width>, -y),
		trace (Ground_a, <+21 * Width, 1024, -23 * Width>, -y),
		trace (Ground_a, <+24 * Width, 1024, -26 * Width>, -y),
	}

	#local iCount = 0;
	#while (iCount < (segments_num / 2 - 1))
		#local this_pt = road_coordinates[iCount * 2];
		#local next_pt = road_coordinates[(iCount + 1) * 2];
		#local dist_pt = VDist(this_pt, next_pt);
		#local high_pt = next_pt.y - this_pt.y;
		#local this_vc = road_coordinates[iCount * 2 + 1];
		#local dist_vc = VDist(this_pt, this_vc);
		#local rato_vc = dist_vc / dist_pt;
		#local high_vc = this_pt.y + high_pt * rato_vc;
		#debug concat("high_vc = ", str(high_vc, 0, -1), "\n")
		#local road_coordinates[iCount * 2 + 1] = <this_vc.x, high_vc, this_vc.z,>;
		#local iCount = iCount + 1;
	#end

	#declare LRoad_SkyVector =	-y;
	#declare LRoad_FloorObject =	plane {LRoad_SkyVector, -Width * Width / 16};
	#declare Road_a =		object {LRoad_Road_Macro(0,0,4,road_coordinates,100,0,100,off,30,1,on)}

	#declare LRoad_SkyVector =	+y;
	#declare LRoad_FloorObject =	plane {LRoad_SkyVector, 0};
	#declare Road_b =		object {LRoad_Road_Macro(0,0,4,road_coordinates,100,0,100,off,30,1,on)}

	#declare Ground_b = difference
	{
		object {Ground_a}
		object {Road_a}
		pigment {gamma_color_adjust(<1,1,1,0,1>)}
	}
#else
	#declare Road_a = box {-1, +1}
	#declare Road_b = box {-1, +1}
	#declare Ground_b = Ground_a;
#end

//------------------------------------------------------------------------------Walls
#if (!NoWall)
	#declare Concrete_Texture = texture
	{
		pigment {gamma_color_adjust(<1,1,1>*2/4)}
		normal {granite .05 scale .01}
	}
	#declare Glass_Texture = texture
	{
		pigment {gamma_color_adjust(<0,0,0,0,3/4>)}
		finish {specular 1/2 brilliance 1/2}
	}
	#declare Razor_Texture = Polished_Chrome;
	#include "gh_wall.inc"
	#local WallNumber = 17;
	#local WallPoints = array[WallNumber][4]
	{
		{+29 * Width, 1024, -10 * Width, 1,},	//WNA
		{+23 * Width, 1024, -10 * Width, 0,},	//WNB
		{+19 * Width, 1024, -08 * Width, 1,},	//WNC
		{+17 * Width, 1024, -04 * Width, 0,},	//WOB
		{+17 * Width, 1024, -00 * Width, 0,},	//WND
		{+17 * Width, 1024, +04 * Width, 1,},	//WOC
		{+17 * Width, 1024, +08 * Width, 0,},	//WOD
		{+15 * Width, 1024, +10 * Width, 1,},	//WNE
		{+13 * Width, 1024, +12 * Width, 0,},	//WNF
		{+08 * Width, 1024, +12 * Width, 1,},	//WOG
		{+04 * Width, 1024, +12 * Width, 0,},	//WOH
		{+00 * Width, 1024, +10 * Width, 0,},	//WOI
		{-04 * Width, 1024, +08 * Width, 1,},	//WNG
		{-08 * Width, 1024, +06 * Width, 0,},	//WNH
		{-12 * Width, 1024, +04 * Width, 0,},	//WOJ
		{-16 * Width, 1024, +02 * Width, 0,},	//WOK
		{-20 * Width, 1024, +00 * Width, 0,},	//WOL
	}
	#declare Wall_a = union
	{
		#local iCount = 0;
		#while (iCount < (WallNumber - 1))
			#local jCount = iCount + 1;
			#local Position1 = trace(Ground_a, <WallPoints[iCount][0],WallPoints[iCount][1],WallPoints[iCount][2],>, -y);
			#local Position2 = trace(Ground_a, <WallPoints[jCount][0],WallPoints[jCount][1],WallPoints[jCount][2],>, -y);
			StretchyWall(Position1, Position2, 48, Width, 85, WallPoints[iCount][3], 1, 1)
			#local iCount = jCount;
		#end
	}
	#declare Wall_b = union
	{
		#local iCount = 0;
		#while (iCount < (WallNumber - 1))
			#local jCount = iCount + 1;
			#local Position1 = trace(Ground_a, <WallPoints[iCount][0],WallPoints[iCount][1],WallPoints[iCount][2],>, -y);
			#local Position2 = trace(Ground_a, <WallPoints[jCount][0],WallPoints[jCount][1],WallPoints[jCount][2],>, -y);
			StretchyWall(Position1, Position2, 24, Width, 85, WallPoints[iCount][3], 1, 1)
			#local iCount = jCount;
		#end
	}
#else
	#declare Wall_a = box {-1, +1}
	#declare Wall_b = box {-1, +1}
#end

//------------------------------------------------------------------------------Trees
#if (!NoTrees)
//	#include "VEG.INC"
//	#include "gh_deciduous_tree.inc"
	#include "gh_tomtree_tree_mesh.inc"
	#local TreesTotal = TreesNumber * TreesPatches;
	#local NormGround = <0,0,0,>;
	#local NormRoad = <0,0,0,>;
	#local NormWall = <0,0,0,>;
	#local NormDome = <0,0,0,>;
	#local MaxWidth = SceneScale/2;
	#declare TreesUnion = union
	{
		#local PatchesCount = 0;
		#while (PatchesCount < TreesPatches)
			#local TreesCount = 0;
			#while (TreesCount < TreesNumber)
				#local Theta = rand(Seed) * 2 * pi;
				#local Radius = rand(Seed) * Width/2;
				#local TreesPosition = <Radius * cos(Theta),0,Radius * sin(Theta),>;
				#local TreesPosition = TreesPosition + <rand(Seed) * MaxWidth - MaxWidth/2, 1024, rand(Seed) * MaxWidth - MaxWidth/2>;
				#local TreesPosition = trace(Ground_a, TreesPosition, -y, NormGround);
				#local NormalAngle = VAngleD(NormGround, y);
				#if ((NormalAngle < TreesAngle) & (TreesPosition.y > TreesLevel))
					#local TraceRoad = trace(Road_a, TreesPosition + y * 1024, -y, NormRoad);
					#local TraceWall = trace(Wall_a, TreesPosition + y * 1024, -y, NormWall);
					#local TraceDome = trace(Dome_a, TreesPosition + y * 1024, -y, NormDome);
					#local NormSum = NormRoad + NormWall + NormDome;
					#if (VEq(NormSum, <0,0,0,>))
						object
						{
//							Grantrae
//							scale		4	//4
							TREE
							scale		48
							scale		1/2 + rand(Seed) * 1/2
							rotate		y * rand(Seed) * 360
							translate	TreesPosition
						}
						#local TreesCount = TreesCount + 1;
						#debug concat("TreeNum = ", str(TreesCount + TreesNumber * PatchesCount, 0, 0), "/", str(TreesTotal, 0, 0), "\n")
					#end
				#end
			#end
			#local PatchesCount = PatchesCount + 1;
		#end
	}
#end

//------------------------------------------------------------------------------Grass (might not work)
#if (!NoGrass)
	#include "gh_grass.inc"
	#local GrassTotal = GrassNumber * GrassPatches;
	#local NormGround = <0,0,0,>;
	#local NormRoad = <0,0,0,>;
	#local NormWall = <0,0,0,>;
	#local NormDome = <0,0,0,>;
	#local MaxWidth = SceneScale/2;
	#declare GrassUnion = union
	{
		#local PatchesCount = 0;
		#while (PatchesCount < GrassPatches)
			#local GrassCount = 0;
			#while (GrassCount < GrassNumber)
				#local GrassPosition = <rand(Seed) * MaxWidth - MaxWidth/2, 1024, rand(Seed) * MaxWidth - MaxWidth/2>;
				#local GrassPosition = trace(Ground_a, GrassPosition, -y, NormGround);
				#local NormalAngle = VAngleD(NormGround, y);
				#if ((NormalAngle < GrassAngle) & (GrassPosition.y > GrassLevel))
					#local TraceRoad = trace(Road_a, TreesPosition + y * 1024, -y, NormRoad);
					#local TraceWall = trace(Wall_a, TreesPosition + y * 1024, -y, NormWall);
					#local TraceDome = trace(Dome_a, TreesPosition + y * 1024, -y, NormDome);
					#local NormSum = NormRoad + NormWall + NormDome;
					#if (VEq(NormSum, <0,0,0,>))
						union
						{
							PlantPatch()
							scale		16
							rotate		y * rand(Seed) * 360
							translate	GrassPosition
							no_shadow
						}
						#local GrassCount = GrassCount + 1;
						#debug concat("GrassNum = ", str(GrassCount + GrassNumber * PatchesCount, 0, 0), "/", str(GrassTotal, 0, 0), "\n")
					#end
				#end
			#end
			#local PatchesCount = PatchesCount + 1;
		#end
	}
#end

//------------------------------------------------------------------------------Boulders
#if (!NoRocks)
	#include "gh_rocks.inc"
	#local RocksTotal = RocksNumber * RocksPatches;
	#local NormGround = <0,0,0,>;
	#local NormRoad = <0,0,0,>;
	#local NormWall = <0,0,0,>;
	#local NormDome = <0,0,0,>;
	#local MaxWidth = SceneScale/2;
	#declare RocksUnion = union
	{
		#local PatchesCount = 0;
		#while (PatchesCount < RocksPatches)
			#local RocksCount = 0;
			#while (RocksCount < RocksNumber)
				#local RocksPosition = <rand(Seed) * MaxWidth - MaxWidth/2, 1024, rand(Seed) * MaxWidth - MaxWidth/2>;
				#local RocksPosition = trace(Ground_a, RocksPosition, -y, NormGround);
				#local NormalAngle = VAngleD(NormGround, y);
				#if ((NormalAngle > RocksAngle) & (RocksPosition.y > RocksLevel))
					#local TraceRoad = trace(Road_a, RocksPosition + y * 1024, -y, NormRoad);
					#local TraceWall = trace(Wall_a, RocksPosition + y * 1024, -y, NormWall);
					#local TraceDome = trace(Dome_a, RocksPosition + y * 1024, -y, NormDome);
					#local NormSum = NormRoad + NormWall + NormDome;
					#if (VEq(NormSum, <0,0,0,>))
						object
						{
							Boulders_Object()
							scale		1	//1
							translate	RocksPosition
						}
						#local RocksCount = RocksCount + 1;
						#debug concat("RocksNum = ", str(RocksCount + RocksNumber * PatchesCount, 0, 0), "/", str(RocksTotal, 0, 0), "\n")
					#end
				#end
			#end
			#local PatchesCount = PatchesCount + 1;
		#end
	}
#end

//------------------------------------------------------------------------------Axes
#if (!NoGrid)
	#declare Axis_Markers = union
	{
		sphere {0, 0.005 pigment{gamma_color_adjust(<0,0,0,>)}}
		cylinder {0, x, 0.005 pigment{gamma_color_adjust(<1,0,0,>)}}
		cylinder {0, y, 0.005 pigment{gamma_color_adjust(<0,1,0,>)}}
		cylinder {0, z, 0.005 pigment{gamma_color_adjust(<0,0,1,>)}}
		scale SceneScale
		translate trace (Ground_a, <0, 1024, 0>, -y)
	}
#end

//------------------------------------------------------------------------------Final

light_group
{
	#local BrightFactor = 1/2;
	light_source
	{
		light_source_location
		gamma_color_adjust(<1,1,1>*1.5 * BrightFactor)
		parallel
	}
	#if (!NoTrees)
		object {TreesUnion}
	#end
	global_lights off
}

#if (!NoRoad)
	object {Road_b}
#end
#if (!NoWater)
	object {WaterSurface}
#end
#if (!NoGround)
	object {Ground_b}
#end
#if (!NoWall)
	object {Wall_b}
#end
#if (!NoDome)
	object {Dome_a}
#end
#if (!NoGrass)
	object {GrassUnion}
#end
#if (!NoRocks)
	object {RocksUnion}
#end
#if (!NoMecha)
	object {MechaUnion}
#end
#if (!NoExhaust)
	object {ExhaustPlume}
#end
#if (!NoBullets)
	object {BulletUnion}
#end
#if (!NoMissiles)
	object {MissileUnion}
#end
#if (!NoExplosions)
	object {ExplosionUnion}
#end
#if (!NoSmoke)
	object {SmokeUnion}
#end
#if (!NoText)
	object {TextUnion}
#end
#if (!NoGrid)
	object {Axis_Markers}
#end
