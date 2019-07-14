// Desc: Several GearHead mecha battling it out in a woodland/pastural setting.
// Auth: Michael Horvath
// Home Page: http://isometricland.com
// This file is licensed under the terms of the Creative Commons Attribution-ShareAlike 3.0 Unported License.
//
// Dependencies:
// 1. "LegoRoad_macro.inc" by Michael Horvath
// 2. Rune's particle system
// x. "VEG.INC" by Joerg Schrammel	(no longer used)
// x. "grasspatch.inc" by Josh English
// 5. "sphere.inc" by Shuhei Kawachi
// 6. Volumetric clouds from http://www.geocities.com/evilsnack/tut01.htm
// 7. LegoRoad_macro.inc by Michael Horvath from the POV-Ray Object Collection
//
// To do:
// 1. Flatter cloud bases. Maybe some black hole warps.
// 2. Apply both atmospheric media to the same object.
// 3. Sun and lens flare are so far away they are not rendered at all.
// 4. Rocky features above waterline.
// 5. Objects (smoke!) are slightly too light/desaturated now that gamma has been turned on, especially when seen from overhead with atmosphere turned on.
// 6. Maybe add media to the ocean.
// 7. Trees have lighter bits which don't look so great.

//+KFI0 +KFF5 +KC +KI0 +KF0
//+KFI0 +KFF5 +KC
//+K0 +KC

#version 3.7

#include "stdinc.inc"
#include "textures.inc"
#include "metals.inc"
#include "glass.inc"
#include "shapes.inc"
#include "CIE.inc"			// http://www.ignorancia.org/en/index.php?page=Lightsys
#include "lightsys.inc"			// http://www.ignorancia.org/en/index.php?page=Lightsys
#include "lightsys_constants.inc"	// http://www.ignorancia.org/en/index.php?page=Lightsys

#declare Tiles		= 16;		// the default size of the scene, measured in tiles. Use this to zoom in/out.
#declare Width		= 64;		// the default width of a tile.
#declare Subdivision	= 0;		// turn on/off mesh subdivision. Requires a special executable available on the Net.
#declare Seed		= seed(22231);
#declare Minimal	= 0;

#declare SceneScale	= Width * Width;
#declare HeightScale	= 8;		// Makes the heightfield lower/higher.
#declare MechScale	= 2;
#declare Meters		= 4;		// 4 units = 1 meter.
#declare EarthRadius	= 6.375 * pow(10,06) * Meters;
#declare CloudMinRad	= 2000 * Meters;
#declare CloudMaxRad	= 3000 * Meters;
#declare AtmosRadius	= 50000 * Meters;
#declare Sun_Distance	= 1.496 * pow(10,11) * Meters;
#declare Sun_Radius	= 6.955 * pow(10,08) * Meters;
#declare WaterLevel	= Width/2;
#declare TreesLevel	= Width * 2;
#declare GrassLevel	= Width * 2;
#declare RocksLevel	= Width * 9/8;
#declare TreesAngle	= 45;		// 6
#declare GrassAngle	= 30;		// 6
#declare RocksAngle	= 45;		// 6
#declare StoneAngle	= 52;
#declare Included	= 1;		// Informs any included files that they are being included by this file.
#declare TreesPatches	= 300;		// The number of tree patches.		(250)
#declare GrassPatches	= 0;		// The number of grass patches.		(0)
#declare RocksPatches	= 200;		// The number of rock patches.		(100)
#declare TreesPerPat	= 10;		// The number of trees per patch.	(10)
#declare GrassPerPat	= 1;		// The number of grass per patch.	(1)
#declare RocksPerPat	= 2;		// The number of rocks per patch.	(1)
#declare light_lumens	= 3;					// float
#declare light_temp	= Daylight(6100);			// float
#declare light_color	= Light_Color(light_temp,light_lumens);

#local NoColors		= 0;		//0		(can't remember what this is used for)
#local NoGrid		= 1;		//1		(for debug purposes)
#local NoText		= 1;		//1
#local NoLights		= 0;		//0
#local NoLens		= 1;		//0
#local NoRadiosity	= 0;		//0
#local NoSun		= 0;		//0
#local NoAtmos		= 0;		//0
#local NoClouds		= 0;		//0
#local NoWater		= 0;		//0
#local NoGround		= 0;		//0
#local NoMecha		= 0;		//0		(depends on ground)
#local NoSmoke		= 1;		//0		(depends on ground, camera & lights)
#local NoExplosions	= 1;		//0		(depends on camera & lights)
#local NoMissiles	= 1;		//0		(depends on ground & mecha)
#local NoBullets	= 1;		//0		(depends on mecha)
#local NoDome		= 0;		//0		(depends on ground)
#local NoRoad		= 0;		//0		(depends on ground)
#local NoWall		= 0;		//0		(depends on ground)
#local NoTrees		= 0;		//0		(depends on road, wall & ground)
#local NoRocks		= 0;		//0		(depends on road, wall & ground)
// obsolete
#local NoGrass		= 1;		//1		(depends on road, wall & ground)
#local NoExhaust	= 1;		//1		(depends on mecha)
#local NoColors		= 0;
#local NoWeapons	= 1;

#if (Minimal)
	#local NoLens		= 1;		//0
	#local NoRadiosity	= 1;		//0
	#local NoSun		= 0;		//0
	#local NoAtmos		= 1;		//0
	#local NoClouds		= 1;		//0
	#local NoWater		= 0;		//0
	#local NoGround		= 0;		//0
	#local NoMecha		= 0;		//0		(depends on ground)
	#local NoSmoke		= 1;		//0		(depends on ground, camera & lights)
	#local NoExplosions	= 1;		//0		(depends on camera & lights)
	#local NoMissiles	= 1;		//0		(depends on ground & mecha)
	#local NoBullets	= 1;		//0		(depends on mecha)
	#local NoDome		= 1;		//0		(depends on ground)
	#local NoRoad		= 0;		//0		(depends on ground)
	#local NoWall		= 0;		//0		(depends on ground)
	#local NoTrees		= 1;		//0		(depends on road, wall & ground)
	#local NoRocks		= 1;		//0		(depends on road, wall & ground)
#end

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

//------------------------------------------------------------------------------Global settings

#if (!NoRadiosity)
	global_settings
	{
		radiosity
		{
			recursion_limit	1
			brightness	0.1		//0.5
			count		100
			error_bound	0.5
			always_sample	off
		}
		ambient_light	0.5
		max_trace_level	8
	}
#else
	global_settings
	{
		ambient_light	0.5
		max_trace_level	8
	}
#end
default {finish {ambient 0.1 diffuse 0.6}}

//------------------------------------------------------------------------------Camera


#declare Camera_Mode		= 6;			// 0 to 8
#declare Camera_Diagonal	= cosd(45);
#declare Camera_Vertical	= -135 + 22.5;		// 135 + 22.5
#declare Camera_Horizontal	= 30;			// 30
#declare Camera_Scale		= 2.5;
#declare Camera_Aspect		= image_height/image_width;
#declare Camera_Distance	= Width * 64;
#declare Camera_Translate	= <0,Width*1,0>;	//<0,Width*3,0>
#include "gh_camera.inc"


//------------------------------------------------------------------------------Lights

#include "sunpos.inc"
//				SunPos(Year,	Month, Day, Hour, Minute, Lstm, LAT, LONG)
#local Sun_CalcPos		= SunPos(2011,	9,     5,   11,   2,      0,    -10, 0);
#local Sun_PointAt		= -y * EarthRadius;
#local Sun_Location		= Sun_PointAt + vnormalize(Sun_CalcPos) * Sun_Distance;

#if (!NoLights)
	#if (!NoSun)
		sphere
		{
			Sun_Location, Sun_Radius
			texture
			{
				pigment {gamma_color_adjust(light_color)}
				finish {ambient 1}
			}
			no_shadow
		}
	#end
	light_source
	{
		Sun_Location
		gamma_color_adjust(light_color)
		parallel
		point_at	Sun_PointAt
	}
/*
	// extra light for testing
	light_source
	{
		Source_Location
		gamma_color_adjust(light_color/2)
		parallel
		rotate		y * 90
	}
*/
#end

//------------------------------------------------------------------------------Lens flare


#if (!NoLens)
	#declare camera_location	= Camera_Location;
	#declare camera_look_at		= Camera_LookAt;
	#declare effect_location	= Sun_Location;
	#include "Lens.inc"
#end

//------------------------------------------------------------------------------Atmosphere

#if (!NoAtmos)
	// Units
	#local m =				Meters;				// A value of 1 makes the sun's distance ouside POV's numerical domain.
	#local km =				1000 * m;
	#local mm =				0.001 * m;
	// Atmosphere parameters
	#local TP_ATMO_BOTTOM =			-1 * m;
	#local TP_RAYLEIGH_FACTOR =		1.0;
	#local TP_RAYLEIGH_DENSITY_MAX =	1;
	#local TP_RAYLEIGH_AMOUNT =		2.3;
	#local TP_ATMO_INTERVALS =		5;				// Necessary for good integration
	#local TP_ATMO_SAMPLES =		2;	//5
	#local TP_ATMO_METHOD =			3;
	#local TP_ATMO_THICKNESS =		AtmosRadius;
	// Atmosphere scattering color
//	#local TP_RAYLEIGH_SCATTERING_COLOR =	gamma_color_adjust(<pow(TP_LAMBDA_BLUE/TP_LAMBDA_RED, 4), pow(TP_LAMBDA_BLUE/TP_LAMBDA_GREEN, 4), 1>);
//	#local TP_RAYLEIGH_SCATTERING_COLOR =	gamma_color_adjust(<0.2061 0.3933,1.0000,>);
	#local TP_RAYLEIGH_SCATTERING_COLOR =	gamma_color_adjust(<0.1350,0.3300,1.0000,>);
	#local TP_BASE_RAYLEIGH_POWER =		6.7;				// Constant

	// Atmosphere: density
	#local _tp_rayleigh_power =		TP_BASE_RAYLEIGH_POWER * TP_RAYLEIGH_FACTOR;
	#local _tp_rayleigh_density = density
	{
		function
		{
			TP_RAYLEIGH_DENSITY_MAX * exp(-_tp_rayleigh_power
			* (sqrt(x * x + y * y + z * z)
			- EarthRadius - TP_ATMO_BOTTOM)/TP_ATMO_THICKNESS)
		}
	}

	// Atmosphere: media
	#local _tp_rayleigh_media = media
	{
		method		TP_ATMO_METHOD
		intervals	TP_ATMO_INTERVALS
		samples		TP_ATMO_SAMPLES
		scattering
		{
			RAYLEIGH_SCATTERING
			color		TP_RAYLEIGH_AMOUNT * TP_RAYLEIGH_SCATTERING_COLOR/TP_ATMO_THICKNESS
			extinction	1				// The only physically accurate value
		}
		density		{_tp_rayleigh_density}
	}

	// Atmosphere: shell
	#local InnerRadius = EarthRadius + TP_ATMO_BOTTOM;
	#local OuterRadius = InnerRadius + TP_ATMO_THICKNESS;
	#local BoundRadius = sin(acos(EarthRadius/OuterRadius)) * OuterRadius;
	#local AtmosObject = difference
	{
		sphere		{0, OuterRadius}
		sphere		{0, InnerRadius}
		bounded_by	{cylinder {<0,EarthRadius,0,>, <0,OuterRadius,0,>, BoundRadius}}
		hollow
		material
		{
			texture
			{
				pigment	{gamma_color_adjust(<1,1,1,0,1>)}
			}
			interior
			{
				media	{_tp_rayleigh_media}
			}
		}
		translate	-y * EarthRadius
	}
#else
	sky_sphere
	{
		pigment
		{
			function {f_ph(x,y,z)/pi}
			color_map
			{
				[0.0 gamma_color_adjust(<0.0,0.1,0.8,>)]
				[0.5 gamma_color_adjust(<0.6,0.7,1.0,>)]
				[1.0 gamma_color_adjust(<0.0,0.1,0.8,>)]
			}
		}
	}
#end

//------------------------------------------------------------------------------Clouds


#if (!NoClouds)
	#local InnerRadius = EarthRadius + CloudMinRad;
	#local OuterRadius = EarthRadius + CloudMaxRad;
	#local BoundRadius = sin(acos(EarthRadius/OuterRadius)) * OuterRadius;
	#local ScaleAmount = Width/2;
//	#local testpattern = function {mod(sqrt(Sqr(X) + Sqr(Y) + Sqr(Z)), 1.0)}
	#local CloudPigment = pigment
	{
		average
		pigment_map
		{
//			[2 onion	scale CloudMaxRad/ScaleAmount	phase -mod(OuterRadius,CloudMaxRad)/CloudMaxRad/ScaleAmount]
			[1 granite	scale 2*32768/ScaleAmount]
		}
	}
	#local CloudMedia = media
	{
		scattering	{1, 0.5 * 1/ScaleAmount / 320}
		method		3
		intervals	1
//		samples		30	//30, 100
		samples		4
		density
		{
			pigment_pattern {CloudPigment}
			density_map {[0.59 gamma_color_adjust(<0,0,0>)][0.61 gamma_color_adjust(<1,1,1>)]}
		}
	}
	#local CloudSphere = difference
	{
		sphere {0, OuterRadius}
		sphere {0, InnerRadius}
		bounded_by {cylinder {<0,EarthRadius,0,>, <0,OuterRadius,0,>, BoundRadius}}
		hollow
		material
		{
			texture {pigment {gamma_color_adjust(<1,1,1,0,1>)}}
			interior
			{
				media {CloudMedia}
			}
			scale ScaleAmount
		}
		translate -y * EarthRadius
	}
#end

//------------------------------------------------------------------------------Water

#if (!NoWater)
	#local tx_pigment1 = pigment
	{
		image_map {png "olivepink_marble.png"}
	}
	#local tx_pigment2 = pigment
	{
		gamma_color_adjust(<238,214,175>/255)
	}
	#local tx_pigment3 = pigment
	{
		average
		pigment_map
		{
			[2 tx_pigment1]
			[2 tx_pigment2]
		}
		warp
		{
			spherical
			orientation z
		}
	}
	#local tx_normal1 = normal
	{
		wrinkles
		warp
		{
			spherical
			orientation y
		}
		rotate x * 90
	}
	#local Water_a = sphere
	{
		0, EarthRadius + WaterLevel
		texture
		{
			pigment {gamma_color_adjust(<0/4,1/4,2/4,0,2/4>/8)}
			normal {wrinkles scale 8}
			finish {Glossy}
		}
		translate -y * EarthRadius
	}
	#local Water_b = sphere
	{
		0, EarthRadius
		texture
		{
			pigment {tx_pigment2}
//			normal {tx_normal1}		// doesn't work
		}
		translate -y * EarthRadius
	}
#end

//------------------------------------------------------------------------------Ground

#if (!NoGround)
	#local tx_pigment0 = pigment
	{
		gamma_color_adjust(<238,214,175>/255)
	}
	#local tx_pigment1 = pigment
	{
		image_map {png "olivepink_marble_sat.png"}
		rotate x * 90
	}
	#local tx_pigment2 = pigment
	{
		slope {-y, 0, 1/2}
		color_map
		{
			[00/90		gamma_color_adjust(<046,104,058,>/255/2)]
			[StoneAngle/90	gamma_color_adjust(<046,104,058,>/255/2)]		//<139,117,102,>/255/2)
			[StoneAngle/90	gamma_color_adjust(<128,128,128,>/255/2)]
			[90/90		gamma_color_adjust(<128,128,128,>/255/2)]
		}
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
	#local tx_pigment4 = pigment
	{
		gradient y
		pigment_map
		{
			[0.025 tx_pigment0]
			[0.025 tx_pigment0]
			[0.025 tx_pigment3]
			[0.999 tx_pigment3]
			[0.999 tx_pigment0]
			[1.000 tx_pigment0]
		}
	}
	#local tx_texture1 = texture
	{
		pigment {tx_pigment4}
		normal
		{
			wrinkles
			scale		1/SceneScale
			scale		<1,16/HeightScale,1,>
		}
	}

	#local BetaA = 3;
	#local BetaB = 3;
	#local ThingX = ((BetaA - 1) / (BetaB - 1 + BetaA - 1) - 1/2) * 2;
	#local ThingY = pow(ThingX/2 + 1/2,BetaA - 1) * pow(1 - (ThingX/2 + 1/2),BetaB - 1);

	#local hf_pigment0 = pigment {gamma_color_adjust(<1,1,1>)}
	#local hf_pigment1 = pigment
	{
		image_map
		{
//			png "hf_original.png"
//			png "hf_gray.png"
			png "hf_big.png"
		}
		rotate x * 180		// flipped
	}
	#local hf_pigment2 = pigment {gamma_color_adjust(<0,0,0>)}

	#local hf_function1 = function
	{
		min(max(f_r(x*2-1,y*2-1,z*2),0),1)
	}
	#local hf_function2 = function
	{
		pow(hf_function1(x,y,z)/2 + 1/2,BetaA - 1) * pow(1 - (hf_function1(x,y,z)/2 + 1/2),BetaB - 1) / ThingY
	}
	#local hf_function3 = function
	{
		min(max(hf_function2(x,y,z),0),1)
	}

	#local hf_pigment3 = pigment
	{
		function {hf_function3(x,y,z)}
		pigment_map
		{
			[0 hf_pigment2]
			[1 hf_pigment1]
		}
	}

	#local Ground_a = height_field
	{
		function	1024, 1024 {pigment {hf_pigment3}}
		smooth
		texture		{tx_texture1}
		translate	<-1/2,0,-1/2,>
		scale		<1,HeightScale/16,1,>
		scale		SceneScale
		translate	y * 0.1
	}
	#local Ground_b = difference
	{
		object {Ground_a}
		cylinder
		{
			<+08,+14,+08>*Width, <+08,+100,+08>*Width, 400
			texture
			{
				tx_texture1
				translate	<-1/2,0,-1/2,>
				scale		<1,HeightScale/16,1,>
				scale		SceneScale
			}
		}
		cylinder
		{
			<-07,+15,-07>*Width, <-07,+100,-07>*Width, 600
			texture
			{
				tx_texture1
				translate	<-1/2,0,-1/2,>
				scale		<1,HeightScale/16,1,>
				scale		SceneScale
			}
		}
	}
#else
	#local WaterLevel = -1;
	#local TreesLevel = -1;
	#local GrassLevel = -1;
	#local RocksLevel = -1;
	#local Ground_a = plane {y, 0 pigment {gamma_color_adjust(y)}}
#end

//------------------------------------------------------------------------------Entrance

#local EntrancePt2 = trace (Ground_b, <-04,+16,+14>*Width, -y);
#local EntrancePt1 = <-13,+04,+12>*Width + <0,EntrancePt2.y,0>;
#local EntranceBox = box
{
	EntrancePt1, EntrancePt2
}
//#local Ground_b = difference
//{
//	object {Ground_b}
//	object {EntranceBox}
//}
//object {EntranceBox}

//------------------------------------------------------------------------------Geodesic dome

#if (!NoDome)
	#include "gh_dome.inc"
	#local Dome_Position = <+00,+16,+00,> * Width;
	#local Dome_Position = trace (Ground_a, Dome_Position, -y);
	#local Dome_c = object
	{
		Dome_Section
		scale		36
		translate	Dome_Position
	}

#else
	#local Dome_c = box {-1, +1}
#end

//------------------------------------------------------------------------------Platform

#include "platform_POV_geom.inc" //Geometry
#local Platform_Position = <-19,+16,+06,> * Width;
#local Platform_Position = trace(Ground_b, Platform_Position, -y) - y * Width/4;
object
{
	platform_
	rotate		y * 45
	translate	Platform_Position
}

//------------------------------------------------------------------------------Comm dish

#include "Radar_1_m.inc"
#include "Radar_1_o.inc"
#local radar_position = trace (Ground_b, <+07,+32,+09>*Width, -y);
#local radar_dish = union
{
	object{ P_mat_0 }
	object{ P_mat_1 }
	rotate	x * -90
	clipped_by
	{
		plane {-y,0}
	}
	scale	64
	rotate	y * -45
	translate radar_position
}
object {radar_dish}

//------------------------------------------------------------------------------Turbo laser

#include "spaceshipturret_m.inc"
#include "spaceshipturret_o.inc"
#local laser_position = trace (Ground_b, <-06,+64,-08>*Width, -y);
#local laser_cannon = union
{
	object{ P_Bships_pro }
	object{ P_Bships_pr0 }
	object{ P_Bships_pr1 }
	rotate x * -90
	translate laser_position
}
object {laser_cannon}

//------------------------------------------------------------------------------Dock

#local dock_position = trace (Ground_b, <-02,+16,+21>*Width, -y);
#local dock_width = 16;
#local dock_length = 96;
#local dock_height = 1;
#local pylon_radius = 1/2;
#local pylon_height = 160;
#declare loading_dock = union
{
	box
	{
		<-dock_width/2,0,-pylon_radius>,
		<+dock_width/2,-dock_height,+pylon_radius+dock_length>
	}
	cylinder {<-dock_width/2+pylon_radius,0,dock_length*0/8>,<-dock_width/2+pylon_radius,-pylon_height,dock_length*0/8>,pylon_radius}
	cylinder {<+dock_width/2-pylon_radius,0,dock_length*0/8>,<+dock_width/2-pylon_radius,-pylon_height,dock_length*0/8>,pylon_radius}

	cylinder {<-dock_width/2+pylon_radius,0,dock_length*1/8>,<-dock_width/2+pylon_radius,-pylon_height,dock_length*1/8>,pylon_radius}
	cylinder {<+dock_width/2-pylon_radius,0,dock_length*1/8>,<+dock_width/2-pylon_radius,-pylon_height,dock_length*1/8>,pylon_radius}

	cylinder {<-dock_width/2+pylon_radius,0,dock_length*2/8>,<-dock_width/2+pylon_radius,-pylon_height,dock_length*2/8>,pylon_radius}
	cylinder {<+dock_width/2-pylon_radius,0,dock_length*2/8>,<+dock_width/2-pylon_radius,-pylon_height,dock_length*2/8>,pylon_radius}

	cylinder {<-dock_width/2+pylon_radius,0,dock_length*3/8>,<-dock_width/2+pylon_radius,-pylon_height,dock_length*3/8>,pylon_radius}
	cylinder {<+dock_width/2-pylon_radius,0,dock_length*3/8>,<+dock_width/2-pylon_radius,-pylon_height,dock_length*3/8>,pylon_radius}

	cylinder {<-dock_width/2+pylon_radius,0,dock_length*4/8>,<-dock_width/2+pylon_radius,-pylon_height,dock_length*4/8>,pylon_radius}
	cylinder {<+dock_width/2-pylon_radius,0,dock_length*4/8>,<+dock_width/2-pylon_radius,-pylon_height,dock_length*4/8>,pylon_radius}

	cylinder {<-dock_width/2+pylon_radius,0,dock_length*5/8>,<-dock_width/2+pylon_radius,-pylon_height,dock_length*5/8>,pylon_radius}
	cylinder {<+dock_width/2-pylon_radius,0,dock_length*5/8>,<+dock_width/2-pylon_radius,-pylon_height,dock_length*5/8>,pylon_radius}

	cylinder {<-dock_width/2+pylon_radius,0,dock_length*6/8>,<-dock_width/2+pylon_radius,-pylon_height,dock_length*6/8>,pylon_radius}
	cylinder {<+dock_width/2-pylon_radius,0,dock_length*6/8>,<+dock_width/2-pylon_radius,-pylon_height,dock_length*6/8>,pylon_radius}

	cylinder {<-dock_width/2+pylon_radius,0,dock_length*7/8>,<-dock_width/2+pylon_radius,-pylon_height,dock_length*7/8>,pylon_radius}
	cylinder {<+dock_width/2-pylon_radius,0,dock_length*7/8>,<+dock_width/2-pylon_radius,-pylon_height,dock_length*7/8>,pylon_radius}

	cylinder {<-dock_width/2+pylon_radius,0,dock_length*8/8>,<-dock_width/2+pylon_radius,-pylon_height,dock_length*8/8>,pylon_radius}
	cylinder {<+dock_width/2-pylon_radius,0,dock_length*8/8>,<+dock_width/2-pylon_radius,-pylon_height,dock_length*8/8>,pylon_radius}

	pigment {gamma_color_adjust(<1,1,1>*4/4)}
	scale 4
}
object
{
	loading_dock
	translate dock_position
}

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

//#local MaanjiPosition	= trace(Ground_a, <+07,+16,+05,> * Width, -y);
//#local KojedoPosition	= trace(Ground_a, <-13,+16,-00,> * Width, -y);
//#local VadelPosition	= trace(Ground_a, <-03,+16,-17,> * Width, -y);
#local MaanjiPosition	= Platform_Position + <0,160,0>;
#local KojedoPosition	= Platform_Position + vrotate(<+120,160,0>,y * 45);
#local VadelPosition	= Platform_Position + vrotate(<-120,160,0>,y * 45);
#local KtoMVector	= KojedoPosition - MaanjiPosition;
#local VtoMVector	= VadelPosition - MaanjiPosition;

#if (!NoMecha)
	#include "ara_kojedo.pov"
	#local Mecha_1 = object
	{
		ara_kojedo_
		translate	<18.42348,0,-364.0902> * -1
		scale		1/375
		// edit below
		scale		10 * Meters
		Reorient_Trans(z, <-KtoMVector.x,0,-KtoMVector.z,>)
		translate	KojedoPosition
	}
	#include "btr_maanji.pov"
	#local Mecha_2 = object
	{
		object01
		matrix		<1.000000, 0.000000, 0.000000,
				0.000000, 1.000000, 0.000000,
				0.000000, 0.000000, 1.000000,
				0.000000, 0.000000, 0.000000>
		translate	<0.000000, 0.000000, 0.000000>
		scale		<1.000000, 1.000000, 1.000000>
		translate	y * -4.65
		scale		1/115
		//edit below
		scale		18 * Meters
		Reorient_Trans(z, <+KtoMVector.x,0,+KtoMVector.z,>)
		translate	MaanjiPosition
	}
	#include "btr_vadel.pov"
	#local Mecha_3 = object
	{
		object01
		matrix		<0.707112, 0.000000, -0.707101,
				0.000000, 1.000000, 0.000000,
				0.707101, 0.000000, 0.707112,
				0.000000, 0.000000, 0.000000>
		translate	<0.000000, 0.000000, 0.000000>
		scale		<1.000000, 1.000000, 1.000000>
		rotate		y * -45
		scale		1/75
		//edit below
		scale		16 * Meters
		Reorient_Trans(z, <-VtoMVector.x,0,-VtoMVector.z,>)
		translate	VadelPosition
	}
#end

//------------------------------------------------------------------------------Aircraft exhaust (very crappy)

#if (!NoExhaust)
	#local Increment1 = 1/16;
	#local Increment2 = 1/16;
	#local ExhaustPlume = merge
	{
		#local Count1 = 1 - Increment1;
		#while (Count1 < 1)
			#local InvCount1 = 1 - Count1;
			#local Count2 = 0;
			#while (Count2 < 1)
				cone
				{
					<0,Count2 * -128,0,>, 6 + Count2 * Count1 * 26, <0,(Count2 + Increment2) * -128,0,>, 6 + (Count2 + Increment2) * Count1 * 26
					hollow
				}
				material
				{
					texture {pigment {gamma_color_adjust(<1,1,1,0,1>)}}
					interior {ior ((1 - InvCount1 * 0.1) + Count2 * InvCount1 * 0.1)}
				}
				#local Count2 = Count2 + Increment2;
			#end
			#local Count1 = Count1 + Increment1;
		#end
		rotate z * -60
		translate VadelPosition
	}
#end

//------------------------------------------------------------------------------Smoke

#if (!NoSmoke)
	#declare camera_location = 		Camera_Location;
	#declare light_source_location =	Source_Location;
	#include "gh_effect_smoke.inc"

//	#local Smoke0Position = trace(Ground_a, <+00,+16,+00,> * Width, -y);
	#local Smoke1Position = trace(Ground_a, <+08,+16,-01,> * Width, -y);
	#local Smoke2Position = trace(Ground_a, <+13,+16,+06,> * Width, -y);
	#local Smoke3Position = trace(Ground_a, <+13,+16,+04,> * Width, -y);

	#local SmokeObject = union
	{
		object {Layer1}
		object {Layer2}
		object {Layer3}
		object {Layer4}
	}

	#local SmokeUnion = union
	{
/*
		object
		{
			SmokeObject
			rotate		y * rand(Seed) * 360
			scale		16
			translate	Smoke0Position
		}
*/
		object
		{
			SmokeObject
			rotate		y * rand(Seed) * 360
			scale		32
			translate	Smoke1Position
		}
		object
		{
			SmokeObject
			rotate		y * rand(Seed) * 360
			scale		8
			translate	Smoke2Position
		}
		object
		{
			SmokeObject
			rotate		y * rand(Seed) * 360
			scale		8
			translate	Smoke3Position
		}
	}
#end

//------------------------------------------------------------------------------Explosions

#if (!NoExplosions)
	#declare camera_location =		Camera_Location;
	#declare light_source_location =	Source_Location;
	#include "gh_explosion_smokey.inc"

	#local ExplosionUnion = union
	{
		object {Layer1}
		object {Layer2}
		object {Layer3}
		object {Layer4}
		rotate		y * rand(Seed) * 360
		scale		32
		translate	KojedoPosition
	}

#end

//------------------------------------------------------------------------------Loading text

#if (!NoText)
	#local TextUnion = union
	{
		text
		{
			ttf "hatten.ttf" "Just a minute..." 0.1, 0
			pigment {gamma_color_adjust(<1,1,1>)}
			scale		Width * 3/2
			rotate		y * -90
			translate	Width * 4
		}
	}
#end

//------------------------------------------------------------------------------Roads

#if (!NoRoad)
	#include "LegoRoad_macro.inc"
	#local scale_ratio =		48/360;		//48/360
	#local LRoad_RoadWidth =	array[3] {280 * scale_ratio, 306 * scale_ratio, 360 * scale_ratio,}
	#local LRoad_StripeInterval =	array[3] { 64 * scale_ratio,  64 * scale_ratio,  64 * scale_ratio,}
	#local LRoad_EmbankmentTexture = texture
	{
		pigment {gamma_color_adjust(<1,1,1>*3/4)}
		normal
		{
			wrinkles
		}
	}
	#local LRoad_RoadSurfaceTexture = texture
	{
		pigment {gamma_color_adjust(<1,1,1>*1/8)}
	}
	#local LRoad_InnerStripeTexture = texture
	{
		pigment {gamma_color_adjust(<1,1,1>)}
	}
	#local LRoad_CenterStripeTexture = texture
	{
		pigment {gamma_color_adjust(<1,1,0,>)}
	}
	#local segments_num = 28;
	#local road_coordinates = array[segments_num]
	{
trace (Ground_a, <-23,16,-7> * Width, -y),	//RN01
trace (Ground_a, <-27,16,4> * Width, -y),	//RN02
trace (Ground_a, <-23,16,6> * Width, -y),	//RN03
trace (Ground_a, <-19,16,14> * Width, -y),	//RN04
trace (Ground_a, <-15,16,14> * Width, -y),	//RN05
trace (Ground_a, <-6,16,19> * Width, -y),	//RN06
//trace (Ground_a, <-4,16,18> * Width, -y),	//RN07
//trace (Ground_a, <12,16,21> * Width, -y),	//RN08
trace (Ground_a, <2,16,19> * Width, -y),	//RN09
trace (Ground_a, <16,16,19> * Width, -y),	//RN10
trace (Ground_a, <16,16,16> * Width, -y),	//RN11
trace (Ground_a, <26,16,7> * Width, -y),	//RN12
trace (Ground_a, <17,16,9> * Width, -y),	//RN13
trace (Ground_a, <15,16,4> * Width, -y),	//RN14
trace (Ground_a, <15,16,1> * Width, -y),	//RN15
trace (Ground_a, <13,16,-9> * Width, -y),	//RN16
trace (Ground_a, <15,16,-7> * Width, -y),	//RN17
trace (Ground_a, <18,16,-16> * Width, -y),	//RN18
trace (Ground_a, <16,16,-17> * Width, -y),	//RN19
trace (Ground_a, <16,16,-25> * Width, -y),	//RN20
trace (Ground_a, <14,16,-23> * Width, -y),	//RN21
trace (Ground_a, <9,16,-27> * Width, -y),	//RN22
trace (Ground_a, <5,16,-25> * Width, -y),	//RN23
trace (Ground_a, <-10,16,-25> * Width, -y),	//RN24
trace (Ground_a, <-7,16,-23> * Width, -y),	//RN25
trace (Ground_a, <-15,16,-21> * Width, -y),	//RN26
trace (Ground_a, <-16,16,-18> * Width, -y),	//RN27
trace (Ground_a, <-24,16,-11> * Width, -y),	//RN28
trace (Ground_a, <-23,16,-7> * Width, -y),	//RN01
trace (Ground_a, <-27,16,4> * Width, -y),	//RN02
	}

	#if (!NoGrid)
		#local iCount = 0;
		#while (iCount < segments_num)
			sphere
			{
				road_coordinates[iCount],
				Width/8
				#if (mod(iCount,2) = 0)
					pigment {gamma_color_adjust(x + z/2)}
				#else
					pigment {gamma_color_adjust(x + z)}
				#end
				finish {ambient 1}
				no_shadow
			}
			#local iCount = iCount + 1;
		#end
	#end

	// some sort of smoothing
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

	#local LRoad_SkyVector =	+y;
	#local LRoad_FloorObject =	plane {LRoad_SkyVector, 0};
	#local Road_a =		object {LRoad_Road_Macro(0,0,4,road_coordinates,100,0,100,off,30,1,on)}
	// used for collision testing
//	#local LRoad_WallSlope =	1;
	#local LRoad_SkyVector =	-y;
	#local LRoad_FloorObject =	plane {LRoad_SkyVector, -SceneScale};
	#local Road_b =		object {LRoad_Road_Macro(0,0,4,road_coordinates,100,0,100,off,30,1,on)}

	#local Ground_b = difference
	{
		object {Ground_b}
		object {Road_b}
		bounded_by
		{
			box {<-SceneScale,0,-SceneScale,>, <+SceneScale,+SceneScale/2,+SceneScale,>}
		}
		pigment {gamma_color_adjust(<1,1,1,0,1>)}
	}

	#local segments_num = 8;
	#local road_coordinates = array[segments_num]
	{
		trace (Ground_a, <-15,+16,+14> * Width, -y),
		trace (Ground_a, <-24,+16,+09> * Width, -y),
		trace (Ground_a, <-13,+16,+02> * Width, -y),
		trace (Ground_a, <-05,+16,-03> * Width, -y),
		trace (Ground_a, <+04,+16,+00> * Width, -y),
		trace (Ground_a, <+24,+16,-04> * Width, -y),
		trace (Ground_a, <+15,+16,-07> * Width, -y),
		trace (Ground_a, <+18,+16,-16> * Width, -y),
	}

	#if (!NoGrid)
		#local iCount = 0;
		#while (iCount < segments_num)
			sphere
			{
				road_coordinates[iCount],
				Width/8
				#if (mod(iCount,2) = 0)
					pigment {gamma_color_adjust(x + z/2)}
				#else
					pigment {gamma_color_adjust(x + z)}
				#end
				finish {ambient 1}
				no_shadow
			}
			#local iCount = iCount + 1;
		#end
	#end

	// some sort of smoothing
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

	#local LRoad_SkyVector =	+y;
	#local LRoad_FloorObject =	plane {LRoad_SkyVector, 0};
	#local Road_c =		object {LRoad_Road_Macro(0,0,4,road_coordinates,100,0,100,off,30,1,on)}
	// used for collision testing
//	#local LRoad_WallSlope =	1;
	#local LRoad_SkyVector =	-y;
	#local LRoad_FloorObject =	plane {LRoad_SkyVector, -SceneScale};
	#local Road_d =		object {LRoad_Road_Macro(0,0,4,road_coordinates,100,0,100,off,30,1,on)}

	#local Ground_b = difference
	{
		object {Ground_b}
		object {Road_d}
		bounded_by
		{
			box {<-SceneScale,0,-SceneScale,>, <+SceneScale,+SceneScale/2,+SceneScale,>}
		}
		pigment {gamma_color_adjust(<1,1,1,0,1>)}
	}

#else
	#local Road_a = box {-1, +1}
	#local Road_b = box {-1, +1}
	#local Ground_b = Ground_a;
#end

//------------------------------------------------------------------------------Walls

#if (!NoWall)
	#declare Concrete_Texture = texture
	{
		pigment {gamma_color_adjust(<1,1,1>/2)}
		normal {granite .05 scale .01}
	}
	#declare Glass_Texture = texture
	{
		pigment {gamma_color_adjust(<0,0,0,0,3/4>)}
		finish {specular 1/2 brilliance 1/2}
	}
	#declare Razor_Texture = Polished_Chrome;
	#include "gh_wall.inc"
	#local WallNumber = 27;
	#local WallPoints = array[WallNumber][2]
	{
{<-4,16,-25> * Width,<1,1,1,>,},
{<-11,16,-23> * Width,<1,1,1,>,},
{<-16,16,-20> * Width,<1,1,1,>,},
{<-21,16,-15> * Width,<1,1,1,>,},
{<-24,16,-10> * Width,<1,1,1,>,},
{<-26,16,-3> * Width,<1,1,1,>,},
{<-26,16,2> * Width,<1,1,1,>,},
{<-24,16,7> * Width,<1,1,1,>,},
{<-21,16,11> * Width,<1,1,1,>,},
{<-16,16,15> * Width,<1,1,1,>,},
{<-11,16,18> * Width,<1,1,1,>,},
{<-4,16,20> * Width,<1,1,1,>,},
{<2,16,21> * Width,<1,1,1,>,},
{<8,16,21> * Width,<1,1,1,>,},
{<14,16,19> * Width,<1,1,1,>,},
{<18,16,17> * Width,<1,1,1,>,},
{<20,16,12> * Width,<1,1,1,>,},
{<19,16,7> * Width,<1,1,1,>,},
{<17,16,2> * Width,<1,1,1,>,},
{<17,16,-3> * Width,<1,1,1,>,},
{<17,16,-8> * Width,<1,1,1,>,},
{<18,16,-14> * Width,<1,1,1,>,},
{<17,16,-20> * Width,<1,1,1,>,},
{<15,16,-24> * Width,<1,1,1,>,},
{<10,16,-26> * Width,<1,1,1,>,},
{<3,16,-26> * Width,<1,1,1,>,},
{<-4,16,-25> * Width,<1,1,1,>,},
	}

	#if (!NoGrid)
		#local iCount = 0;
		#while (iCount < WallNumber)
			sphere
			{
				WallPoints[iCount][0]
				Width/8
				#if (WallPoints[iCount][1].x = 1)
					pigment {gamma_color_adjust(x + y/2)}
				#else
					pigment {gamma_color_adjust(x + y)}
				#end
				finish {ambient 1}
				no_shadow
			}
			#local iCount = iCount + 1;
		#end
	#end

	#local Wall_a = union
	{
		#local iCount = 0;
		#while (iCount < (WallNumber - 1))
			#local jCount = iCount + 1;
			#local Position1 = trace(Ground_a, WallPoints[iCount][0], -y);
			#local Position2 = trace(Ground_a, WallPoints[jCount][0], -y);
			StretchyWall(Position1, Position2, 40, 128, 81, WallPoints[iCount][1].x, 1, 0)
			#debug concat("Wall_a (", str(iCount + 1,0,0), "/", str(WallNumber - 1,0,0), ")\n")
			#local iCount = jCount;
		#end
	}
	#local Wall_b = union		// used for collision testing
	{
		#local iCount = 0;
		#while (iCount < (WallNumber - 1))
			#local jCount = iCount + 1;
			#local Position1 = trace(Ground_a, WallPoints[iCount][0], -y);
			#local Position2 = trace(Ground_a, WallPoints[jCount][0], -y);
			StretchyWall(Position1, Position2, 40, 128, 81, 0, 0, 0)
			#debug concat("Wall_b (", str(iCount + 1,0,0), "/", str(WallNumber - 1,0,0), ")\n")
			#local iCount = jCount;
		#end
	}
#else
	#local Wall_a = box {-1, +1}
	#local Wall_b = box {-1, +1}
#end

//------------------------------------------------------------------------------Trees

#if (!NoTrees)
//	#include "VEG.INC"
//	#include "gh_tomtree_tree_invk.inc"
//	#include "TOMTREE-1.5.inc"
	#include "gh_tomtree_tree_mesh.inc"
	#local TreesTotal =	TreesPerPat * TreesPatches;
	#local NormGround =	<0,0,0,>;
	#local NormRoad =	<0,0,0,>;
	#local NormWall =	<0,0,0,>;
	#local NormDome =	<0,0,0,>;
	#local NormLaser =	<0,0,0,>;
	#local NormRadar =	<0,0,0,>;
	#local MaxWidth =	SceneScale;
	#declare TreesUnion = union
	{
		#local PatchesCount = 0;
		#while (PatchesCount < TreesPatches)
			#local TreesCount = 0;
			#while (TreesCount < TreesPerPat)
				#local Theta = rand(Seed) * 2 * pi;
				#local Radius = rand(Seed) * Width/2;
				#local TreesPosition = <Radius * cos(Theta),0,Radius * sin(Theta),>;
				#local TreesPosition = TreesPosition + <rand(Seed) * MaxWidth - MaxWidth/2, 1024, rand(Seed) * MaxWidth - MaxWidth/2>;
				#local TreesPosition = trace(Ground_b, TreesPosition, -y, NormGround);
				#local NormalAngle = VAngleD(NormGround, y);
				#if ((NormalAngle < TreesAngle) & (TreesPosition.y > TreesLevel))
					#local NormSum = <0,0,0,>;
					#if (!NoRoad)
						#local NormSum = NormSum + trace(Road_a, TreesPosition + y * 1024, -y, NormRoad);
						#local NormSum = NormSum + trace(Road_c, TreesPosition + y * 1024, -y, NormRoad);
					#end
					#if (!NoWall)
						#local NormSum = NormSum + trace(Wall_b, TreesPosition + y * 1024, -y, NormWall);
					#end
					#if (!NoDome)
//						#local NormSum = NormSum + trace(Dome_b, TreesPosition + y * 1024, -y, NormDome);
					#end
					#local NormSum = NormSum + trace(radar_dish, TreesPosition + y * 1024, -y, NormRadar);
					#local NormSum = NormSum + trace(laser_cannon, TreesPosition + y * 1024, -y, NormLaser);
					#if (VEq(NormSum, <0,0,0,>))
						object
						{
//							Grantrae
							TREE
							scale		Width * (rand(Seed) * 1/4 + 3/4)
							scale		1/2 + rand(Seed) * 1/2
							rotate		y * rand(Seed) * 360
							translate	TreesPosition
						}
						#local TreesCount = TreesCount + 1;
						#debug concat("Trees (", str(TreesCount + TreesPerPat * PatchesCount, 0, 0), "/", str(TreesTotal, 0, 0), ")\n")
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
	#local GrassTotal =	GrassPerPat * GrassPatches;
	#local NormGround =	<0,0,0,>;
	#local NormRoad =	<0,0,0,>;
	#local NormWall =	<0,0,0,>;
	#local NormDome =	<0,0,0,>;
	#local NormLaser =	<0,0,0,>;
	#local NormRadar =	<0,0,0,>;
	#local MaxWidth =	SceneScale;
	#local GrassUnion = union
	{
		#local PatchesCount = 0;
		#while (PatchesCount < GrassPatches)
			#local GrassCount = 0;
			#while (GrassCount < GrassPerPat)
				#local GrassPosition = <rand(Seed) * MaxWidth - MaxWidth/2, 1024, rand(Seed) * MaxWidth - MaxWidth/2>;
				#local GrassPosition = trace(Ground_b, GrassPosition, -y, NormGround);
				#local NormalAngle = VAngleD(NormGround, y);
				#if ((NormalAngle < GrassAngle) & (GrassPosition.y > GrassLevel))
					#local NormSum = <0,0,0,>;
					#if (!NoRoad)
						#local NormSum = NormSum + trace(Road_a, GrassPosition + y * 1024, -y, NormRoad);
						#local NormSum = NormSum + trace(Road_c, GrassPosition + y * 1024, -y, NormRoad);
					#end
					#if (!NoWall)
						#local NormSum = NormSum + trace(Wall_b, GrassPosition + y * 1024, -y, NormWall);
					#end
					#if (!NoDome)
//						#local NormSum = NormSum + trace(Dome_b, GrassPosition + y * 1024, -y, NormDome);
					#end
					#local NormSum = NormSum + trace(radar_dish, GrassPosition + y * 1024, -y, NormRadar);
					#local NormSum = NormSum + trace(laser_cannon, GrassPosition + y * 1024, -y, NormLaser);
					#if (VEq(NormSum, <0,0,0,>))
						union
						{
							PlantPatch()
							scale		<4,8,4,>
							rotate		y * rand(Seed) * 360
							translate	GrassPosition
							no_shadow
						}
						#local GrassCount = GrassCount + 1;
						#debug concat("Grass (", str(GrassCount + GrassPerPat * PatchesCount, 0, 0), "/", str(GrassTotal, 0, 0), ")\n")
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
	#local RocksTotal =	RocksPerPat * RocksPatches;
	#local NormGround =	<0,0,0,>;
	#local NormRoad =	<0,0,0,>;
	#local NormWall =	<0,0,0,>;
	#local NormDome =	<0,0,0,>;
	#local NormLaser =	<0,0,0,>;
	#local NormRadar =	<0,0,0,>;
	#local MaxWidth =	SceneScale;
	#local RocksUnion = union
	{
		#local PatchesCount = 0;
		#while (PatchesCount < RocksPatches)
			#local RocksCount = 0;
			#while (RocksCount < RocksPerPat)
				#local RocksPosition = <rand(Seed) * MaxWidth - MaxWidth/2, 1024, rand(Seed) * MaxWidth - MaxWidth/2>;
				#local RocksPosition = trace(Ground_b, RocksPosition, -y, NormGround);
				#local NormalAngle = VAngleD(NormGround, y);
				#if ((NormalAngle > RocksAngle) & (RocksPosition.y > RocksLevel))
					#local NormSum = <0,0,0,>;
					#if (!NoRoad)
						#local NormSum = NormSum + trace(Road_a, RocksPosition + y * 1024, -y, NormRoad);
						#local NormSum = NormSum + trace(Road_c, RocksPosition + y * 1024, -y, NormRoad);
					#end
					#if (!NoWall)
						#local NormSum = NormSum + trace(Wall_b, RocksPosition + y * 1024, -y, NormWall);
					#end
					#if (!NoDome)
//						#local NormSum = NormSum + trace(Dome_b, RocksPosition + y * 1024, -y, NormDome);
					#end
					#local NormSum = NormSum + trace(radar_dish, RocksPosition + y * 1024, -y, NormRadar);
					#local NormSum = NormSum + trace(laser_cannon, RocksPosition + y * 1024, -y, NormLaser);
					#if (VEq(NormSum, <0,0,0,>))
						object
						{
							Boulders_Object()
							scale		<2,1,2,>
							translate	RocksPosition
						}
						#local RocksCount = RocksCount + 1;
						#debug concat("Rocks (", str(RocksCount + RocksPerPat * PatchesCount, 0, 0), "/", str(RocksTotal, 0, 0), ")\n")
					#end
				#end
			#end
			#local PatchesCount = PatchesCount + 1;
		#end
	}
#end

//------------------------------------------------------------------------------Axes/Grids

#if (!NoGrid)
	#local Axis_Markers = union
	{
		sphere		{0,    0.001 pigment{gamma_color_adjust(<0,0,0,>)}}
		cylinder	{0, x, 0.001 pigment{gamma_color_adjust(<1,0,0,>)}}
		cylinder	{0, y, 0.001 pigment{gamma_color_adjust(<0,1,0,>)}}
		cylinder	{0, z, 0.001 pigment{gamma_color_adjust(<0,0,1,>)}}
		finish {ambient 1}
		scale		SceneScale
		translate	<0,Width*16,0,>
		no_shadow
		no_reflection
	}
	#local Grid_Markers = union
	{
//		plane {y,0}
		#local Count_max = SceneScale/Width;
		#local Count_x = 0;
		#while (Count_x < Count_max)
			#local Count_z = 0;
			#while (Count_z < Count_max)
				#local This_coo = <-1/2,0,-1/2,> + <Count_x/Count_max,0,Count_z/Count_max,>;
				#if (mod(Count_x,8) = 0 & mod(Count_z,8) = 0)
					text
					{
						ttf "timrom.ttf"
						concat(str(Count_x-Count_max/2,-2,0), ",",str(Count_z-Count_max/2,-2,0))
						1/16, 0
						scale		1/2/Width
						rotate		x * 90
						translate	This_coo
						pigment {gamma_color_adjust(x)}
						finish {ambient 1}
					}
				#end
				sphere
				{
					This_coo,
					1/16/Width
					#if (mod(Count_x,8) = 0 & mod(Count_z,8) = 0)
						pigment {gamma_color_adjust(x)}
					#else
						pigment {gamma_color_adjust(y)}
					#end
				}
				#local Count_z = Count_z + 1;
			#end
			#local Count_x = Count_x + 1;
		#end
		no_shadow
		no_reflection
		scale		SceneScale
		translate	<0,Width*16,0,>
	}
#end

//------------------------------------------------------------------------------Final



#if (!NoClouds)
	object {CloudSphere}
#end
#if (!NoAtmos)
	object {AtmosObject}
#end
light_group
{
	#local BrightFactor = 1/4;
	light_source
	{
		Sun_Location
		gamma_color_adjust(light_color * BrightFactor)
		parallel
		point_at	Sun_PointAt
	}
	#if (!NoTrees)
		object {TreesUnion}
	#end
	global_lights off
}
#if (!NoRoad)
	object {Road_a}
	object {Road_c}
#end
#if (!NoWater)
	object {Water_a}
	object {Water_b}
#end
#if (!NoGround)
	object {Ground_b}
#end
#if (!NoWall)
	object {Wall_a}
#end
#if (!NoDome)
//	object {Dome_a}
	object {Dome_c}
#end
#if (!NoGrass)
	object {GrassUnion}
#end
#if (!NoRocks)
	object {RocksUnion}
#end
#if (!NoMecha)
	object {Mecha_1}
	object {Mecha_2}
	object {Mecha_3}
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
	object {Grid_Markers}
#end


//#debug concat("test = ", str(1e5, 0, 0), "\n")
