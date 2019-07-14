// Desc: Several GearHead mecha battling it out in a woodland/pastural setting.
// Auth: Michael Horvath
// Home Page: http://www.geocities.com/Area51/Quadrant/3864/gearhead.htm
// This file is licensed under the terms of the CC-LGPL.
//
// Dependencies:
// 1. "LegoRoad_macro.inc" by Michael Horvath
// 2. Rune's particle system
// x. "VEG.INC" by Joerg Schrammel	(no longer used)
// 4. "grasspatch.inc" by Josh English
// 5. "sphere.inc" by Shuhei Kawachi
// 6. Volumetric clouds from http://www.geocities.com/evilsnack/tut01.htm
// 7. Spruce tree generated using POV-Tree by Gennady Obukhov
//
// To do:
// 1. Flatter clud bases. Maybe some black hole warps.
// 2. Apply both atmospheric media to the same object.
// 3. Sun and lens flare are so far away they are not rendered at all.
// 4. Rocky heightfield bottoms.
// 5. Objects (smoke!) are slightly too light/desaturated now that gamma has been turned on, especially when seen from overhead with atmosphere turned on.
// 6. Maybe add media to the ocean.
// 7. Trees have lighter bits which don't look so great.

//+KFI0 +KFF5 +KC +KI0 +KF0
//+KFI5 +KFF5 +KC
//+K0 +KC

#include "stdinc.inc"
#include "textures.inc"
#include "metals.inc"
#include "glass.inc"

#declare Tiles =	16;		// the default size of the scene, measured in tiles. Use this to zoom in/out.
#declare Width =	64;		// the default width of a tile.
#declare Subdivision =	0;		// turn on/off mesh subdivision. Requires a special executable available on the Net.
#declare Seed =		seed(22231);
#declare pov_version =	0;		// 0 = 3.6; 1 = 3.7. Affects light intensity/radiosity. 3.7 also needs gamma adjustments in INI file.
#declare camera_mode =	6;		// 0 to 8
#declare SceneScale =	Width * Width;
#declare HeightScale =	4;		// Makes the heightfield lower/higher.
#declare MechScale =	2;
#declare Meters =	4;		// 4 units = 1 meter.
#declare EarthRadius =	6375000 * Meters;
#declare CloudMinRad =	   2000 * Meters;
#declare CloudMaxRad =	   3000 * Meters;
#declare AtmosRadius =	  50000 * Meters;
#declare WaterLevel =	Width;
#declare TreesLevel =	Width * 2;
#declare GrassLevel =	Width * 2;
#declare RocksLevel =	Width * 9/8;
#declare TreesAngle =	30;		// 6
#declare GrassAngle =	30;		// 6
#declare RocksAngle =	15;		// 6
#declare StoneAngle =	60;
#declare Included =	1;		// Informs any included files that they are being included by this file.
#declare TreesPatches = 200;		// The number of tree patches.		(250)
#declare GrassPatches = 0;		// The number of grass patches.		(0)
#declare RocksPatches = 200;		// The number of rock patches.		(100)
#declare TreesPerPat =	10;		// The number of trees per patch.	(10)
#declare GrassPerPat =	1;		// The number of grass per patch.	(1)
#declare RocksPerPat =	2;		// The number of rocks per patch.	(1)

#local NoColors =	0;		//0		(can't remember what this is used for)
#local NoGrid =		1;		//1		(for debug purposes)
#local NoText =		1;		//1
#local NoLights =	0;		//0
#local NoLens =		1;		//0
#local NoRadiosity =	1;		//0
#local NoSun =		0;		//0
#local NoAtmos =	1;		//0
#local NoClouds =	0;		//0
#local NoWater =	0;		//0
#local NoGround =	0;		//0
#local NoMecha =	1;		//0		(depends on ground)
#local NoSmoke =	1;		//0		(depends on ground, camera & lights)
#local NoExplosions =	1;		//0		(depends on camera & lights)
#local NoMissiles =	1;		//0		(depends on ground & mecha)
#local NoBullets =	1;		//0		(depends on mecha)
#local NoDome =		1;		//0		(depends on ground)
#local NoRoad =		1;		//0		(depends on ground)
#local NoWall =		1;		//0		(depends on ground)
#local NoTrees =	1;		//0		(depends on road, wall & ground)
#local NoRocks =	1;		//0		(depends on road, wall & ground)
// obsolete
#local NoGrass =	1;		//1		(depends on road, wall & ground)
#local NoExhaust =	1;		//1		(depends on mecha)

//------------------------------------------------------------------------------Global settings
global_settings
{
	#if (!NoRadiosity)
		radiosity
		{
			recursion_limit	1
			brightness	0.5
			count		100
			error_bound	0.5
			always_sample	off
		}
		ambient_light	0
	#end
	assumed_gamma	1
	max_trace_level	256
}
default {finish {ambient 0.1 diffuse 0.6}}

//------------------------------------------------------------------------------Camera
#declare Camera_Diagonal =	cosd(45);
#declare Camera_Vertical =	22.5;
#declare Camera_Horizontal =	30;
#declare Camera_Scale =		3;
#declare Camera_Aspect =	image_height/image_width;
#declare Camera_Distance =	SceneScale;

#switch (camera_mode)
	// orthographic
	#case (0)
		#declare Camera_Up =		y * Camera_Diagonal * Width * Tiles * 2 * Camera_Aspect;
		#declare Camera_Right =		x * Camera_Diagonal * Width * Tiles * 2;
		#declare Camera_Location =	vaxis_rotate(<+1,+0,+1,>, <-1,+0,+1,>, Camera_Horizontal) * Camera_Diagonal * Width * Tiles * Camera_Scale;
		#declare Camera_Location =	vaxis_rotate(Camera_Location, y, Camera_Vertical);
		#declare Camera_Location =	Camera_Location + -x * block_dist_x/2;
		#declare Camera_LookAt =	0;
		#declare Camera_LookAt =	vaxis_rotate(Camera_LookAt, y, Camera_Vertical);
		#declare Camera_LookAt =	Camera_LookAt + -x * block_dist_x/2;
		camera
		{
			orthographic
			up		Camera_Up
			right		Camera_Right
			location	Camera_Location
			look_at		Camera_LookAt
		}
	#break
	// oblique
	#case (1)
		#declare CameraArea =		Tiles * 2 * 64;
		#declare Camera_Aspect =	1/Camera_Aspect;
		#declare CameraDistance =	Camera_Diagonal * Width * Tiles * CameraScale;
		#declare CameraSkewed =		sin(pi/4);
		#declare Camera_Up =		-x * CameraArea;
		#declare Camera_Right =		+z * CameraArea * Camera_Aspect;
		#declare Camera_Location =	vnormalize(<CameraSkewed, 1, CameraSkewed>) * CameraDistance;
		#declare Camera_Direction =	-Camera_Location;
		#declare Camera_Location =	Camera_Location + -x * block_dist_x/2;
		#declare Camera_LookAt =	Camera_Location + Camera_Direction;
		camera
		{
			orthographic
			up		Camera_Up
			right		Camera_Right
			location	Camera_Location
			direction	Camera_Direction
		}
	#break
	// perspective (new)
	#case (2)
		#declare Camera_Up =		+y * Camera_Diagonal * Width * Tiles * 2 * Camera_Aspect;
		#declare Camera_Right =		+x * Camera_Diagonal * Width * Tiles * 2;
		#declare Camera_Location =	-z * Camera_Distance;
		#declare Camera_Direction =	+z * Camera_Distance;
		#declare Camera_LookAt =	Camera_Location + Camera_Direction;
		#declare Camera_Rotate =	<Camera_Horizontal,270 - Camera_Vertical,0,>;
		camera
		{
			up		Camera_Up
			right		Camera_Right
			location	Camera_Location
			direction	Camera_Direction
			rotate		Camera_Rotate
		}
		#declare Camera_Location =	vrotate(Camera_Location,Camera_Rotate);
		#declare Camera_LookAt =	vrotate(Camera_LookAt,Camera_Rotate);
	#break
	// orthographic (new)
	#case (3)
		#declare Camera_Up =		+y * Camera_Diagonal * Width * Tiles * 2 * Camera_Aspect;
		#declare Camera_Right =		+x * Camera_Diagonal * Width * Tiles * 2;
		#declare Camera_Location =	-z * Camera_Distance;
		#declare Camera_Direction =	+z;
		#declare Camera_LookAt =	Camera_Location + Camera_Direction;
		#declare Camera_Rotate =	<Camera_Horizontal,270 - Camera_Vertical,0,>;
		camera
		{
			orthographic
			up		Camera_Up
			right		Camera_Right
			location	Camera_Location
			direction	Camera_Direction
			rotate		Camera_Rotate
		}
		#declare Camera_Location =	vrotate(Camera_Location,Camera_Rotate);
		#declare Camera_LookAt =	vrotate(Camera_LookAt,Camera_Rotate);
	#break
	// not sure...
	#case (4)
		#declare Camera_Up =		<+00.29007132383,+00.94193058802,-00.16919038339,>;
		#declare Camera_Right =		<-00.44470821789,-00.00000000114,-00.76243755686,>;
		#declare Camera_Location =	<-15.70614200000,+06.48226800000,+09.16094800000,>;
		#declare Camera_Direction =	<+00.81364160776,-00.33580762148,-00.47457408905,>;
		#declare Camera_LookAt =	Camera_Location + Camera_Direction;
		#declare Camera_Angle =		50.000;
		camera
		{
			angle		Camera_Angle
			up		Camera_Up
			right		Camera_Right
			location	Camera_Location
			direction	Camera_Direction	
		}
	#break
	// cube map
	#case (5)
		#declare Camera_Up =		+y;
		#declare Camera_Right =		+x;
		#declare Camera_Location =	0;
		#declare Camera_Direction =	+z/2;
		#declare Camera_LookAt =	Camera_Location + Camera_Direction;
		#switch (frame_number)
			#case (0)
				#declare Camera_Rotate = <0,000,0,>;
			#break
			#case (1)
				#declare Camera_Rotate = <0,090,0,>;
			#break
			#case (2)
				#declare Camera_Rotate = <0,180,0,>;
			#break
			#case (3)
				#declare Camera_Rotate = <0,270,0,>;
			#break
			#case (4)
				#declare Camera_Rotate = <270,0,0,>;
			#break
			#case (5)
				#declare Camera_Rotate = <090,0,0,>;
			#break
		#end
		#declare Camera_Translate =	<0,Width * 5,0,>;
		camera
		{
			up		Camera_Up
			right		Camera_Right
			location	Camera_Location
			direction	Camera_Direction
			rotate		Camera_Rotate
			translate	Camera_Translate
		}
		#declare Camera_Location =	vrotate(Camera_Location,Camera_Rotate) + Camera_Translate;
		#declare Camera_LookAt =	vrotate(Camera_LookAt,Camera_Rotate) + Camera_Translate;
	#break
	// spherical
	#case (6)
		#declare Camera_Up =		+y;
		#declare Camera_Right =		+x;
		#declare Camera_Location =	0;
		#declare Camera_Direction =	+z;
		#declare Camera_LookAt =	Camera_Location + Camera_Direction;
		#declare Camera_Translate =	<0,Width * 10,0,>;
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
		#declare Camera_Location =	Camera_Location + Camera_Translate;
		#declare Camera_LookAt =	Camera_LookAt + Camera_Translate;
	#break
	// orthographic (overhead)
	#case (7)
		#declare Camera_Up =		+z * Tiles * Width * 4 * Camera_Aspect;
		#declare Camera_Right =		+x * Tiles * Width * 4;
		#declare Camera_Location =	+y * Camera_Distance * 2;
		#declare Camera_Direction =	-y;
		#declare Camera_LookAt =	Camera_Location + Camera_Direction;
		camera
		{
			orthographic
			up		Camera_Up
			right		Camera_Right
			location	Camera_Location
			direction	Camera_Direction
		}
	#break
	// orthographic (overhead, angled)
	#case (8)
		#declare Camera_Scale =		4;
		#declare Camera_Up =		+z * Camera_Diagonal * Width * Tiles * Camera_Scale * Camera_Aspect;
		#declare Camera_Right =		+x * Camera_Diagonal * Width * Tiles * Camera_Scale;
		#declare Camera_Location =	+y * Camera_Distance * Camera_Scale;
		#declare Camera_Direction =	-Camera_Location;
		#declare Camera_LookAt =	Camera_Location + Camera_Direction;
		#declare Camera_Rotate =	<+60,-45,+00,>;		//<+60,-45,+00,>
		camera
		{
//			orthographic
			up		Camera_Up
			right		Camera_Right
			location	Camera_Location
			direction	Camera_Direction
			rotate		Camera_Rotate
		}
		#declare Camera_Location =	vrotate(Camera_Location,Camera_Rotate);
		#declare Camera_LookAt =	vrotate(Camera_LookAt,Camera_Rotate);
	#break
#end

//------------------------------------------------------------------------------Lights
#include "sunpos.inc"
//#local Source_Location =	vrotate(y, <+030,+160,+000,>) * Source_Distance - y * EarthRadius;
//				SunPos(Year, Month, Day, Hour, Minute, Lstm, LAT, LONG)
#local Source_Location =	SunPos(2009, 9, 5, 11, 2, 0, -10, 0);
#local Source_PointAt =		-y * EarthRadius;
#local Source_Strength =	1/0.95;		// 2.0
#local Sun_Distance =		1000000;
#local Sun_Location =		vnormalize(Source_Location) * Sun_Distance;
#local Sun_Radius =		tand(4/15) * Sun_Distance;

#if (!NoLights)
	#if (!NoSun)
		sphere
		{
			Sun_Location, Sun_Radius
			texture
			{
				pigment {color rgb <1,1,1/2,>}
				finish {ambient 1}
			}
			no_shadow
		}
	#end
	light_source
	{
		Source_Location
		rgb		Source_Strength
		parallel
		point_at	Source_PointAt
	}
/*
	// extra light for testing
	light_source
	{
		Source_Location
		rgb		Source_Strength/2
		parallel
		rotate		y * 90
	}
*/
#end

//------------------------------------------------------------------------------Lens flare

#if (!NoLens)
	#declare camera_location =	Camera_Location;
	#declare camera_look_at =	Camera_LookAt;
	#declare effect_location =	Source_Location;
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
//	#local TP_RAYLEIGH_SCATTERING_COLOR =	rgb <pow(TP_LAMBDA_BLUE/TP_LAMBDA_RED, 4), pow(TP_LAMBDA_BLUE/TP_LAMBDA_GREEN, 4), 1>;
//	#local TP_RAYLEIGH_SCATTERING_COLOR =	rgb <0.2061 0.3933,1.0000,>;
	#local TP_RAYLEIGH_SCATTERING_COLOR =	rgb <0.1350,0.3300,1.0000,>;
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
				pigment	{color rgbt 1}
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
				[0.0 rgb <0.0,0.1,0.8,>]
				[0.5 rgb <0.6,0.7,1.0,>]
				[1.0 rgb <0.0,0.1,0.8,>]
			}
		}
	}
#end

//------------------------------------------------------------------------------Clouds

#if (!NoClouds)
	#local InnerRadius = EarthRadius + CloudMinRad;
	#local OuterRadius = InnerRadius + CloudMaxRad;
	#local BoundRadius = sin(acos(EarthRadius/OuterRadius)) * OuterRadius;
	#local ScaleAmount = Width/2;
//	#local testpattern = function {mod(sqrt(Sqr(X) + Sqr(Y) + Sqr(Z)), 1.0)}
	#local CloudPigment = pigment
	{
		average
		pigment_map
		{
//			[2 onion	scale CloudMaxRad/ScaleAmount	phase -mod(OuterRadius,CloudMaxRad)/CloudMaxRad/ScaleAmount]
			[1 granite	scale 32768/ScaleAmount]
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
			density_map {[0.59 rgb 0][0.61 rgb 1]}
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
			texture {pigment {rgbt 1}}
			interior
			{
				media {CloudMedia}
			}
			scale ScaleAmount
		}
		translate -y * EarthRadius
	}
#end

//------------------------------------------------------------------------------Ground
#if (!NoGround)
	#local tx_pigment1 = pigment
	{
		image_map {png "olivepink_marble.png"}
		rotate x * 90
	}
	#local tx_pigment2 = pigment
	{
		slope {-y, 0, 1/2}
		color_map
		{
			[00/90		color rgb <046,104,058,>/255/2]
			[StoneAngle/90	color rgb <139,117,102,>/255/2]
			[StoneAngle/90	color rgb <128,128,128,>/255/2]
			[90/90		color rgb <128,128,128,>/255/2]
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
	#local tx_texture1 = texture
	{
		pigment {tx_pigment3}
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

	#local hf_pigment0 = pigment {color rgb 1}
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
	#local hf_pigment2 = pigment {color rgb 0}

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
//		png		"hf_big.png"
		smooth
		texture		{tx_texture1}
		translate	<-1/2,0,-1/2,>
		scale		<1,HeightScale/16,1,>
		scale		SceneScale
	}
#else
	#local WaterLevel = -1;
	#local TreesLevel = -1;
	#local GrassLevel = -1;
	#local RocksLevel = -1;
	#local Ground_a = plane {y, 0 pigment {color rgb y}}
#end

//------------------------------------------------------------------------------Water
#if (!NoWater)
	#local tx_pigment1 = pigment
	{
		image_map {png "olivepink_marble.png"}
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
			pigment {rgbt <0/4,1/4,2/4,2/4,>}
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
			pigment {tx_pigment3}
//			normal {tx_normal1}		// doesn't work
		}
		translate -y * EarthRadius
	}
#end

//------------------------------------------------------------------------------Mecha
#local KojedoPosition	= trace(Ground_a, <-05,+16,-02,> * Width, -y);
#local MaanjiPosition	= trace(Ground_a, <+06,+16,+05,> * Width, -y);
#local VadelPosition	= trace(Ground_a, <-03,+16,+03,> * Width, -y);
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
					texture {pigment {color rgbt 1}}
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
			scale		16
			translate	BulletPath(0.8)
		}
	}
#end

//------------------------------------------------------------------------------Missiles
#if (!NoMissiles)
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
			scale		1/4
//			scale		4
			Reorient_Trans(z, KtoMVector)
			translate	MissilePath(0.8)
			translate	x * 4
		}
		object
		{
			Missile
			scale		1/4
//			scale		4
			Reorient_Trans(z, KtoMVector)
			translate	MissilePath(0.6)
			translate	x * 8
		}
		object
		{
			Missile
			scale		1/4
//			scale		4
			Reorient_Trans(z, KtoMVector)
			translate	MissilePath(0.4)
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
					NewPath(ctr), 0.5 + ctr, NewPath(ctr + 0.01), 0.5 + ctr + 0.01
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
			#local iCount = iCount + 1;
		#end
	}
#end

//------------------------------------------------------------------------------Geodesic dome
#if (!NoDome)
	#local DomePosition = <+03,+16,-05,> * Width;
	#local DomePosition = trace (Ground_a, DomePosition, -y);
	#include "gh_dome.inc"
	#local Dome_a = object
	{
		Dome_Object
		scale		6
		translate	DomePosition
	}
	#local Dome_b = object
	{
		Dome_Object
		scale		12
		translate	DomePosition
	}
#else
	#local Dome_a = box {-1, +1}
	#local Dome_b = box {-1, +1}
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
			pigment {color rgb 1}
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
		pigment {color rgb <0.682353,0.682353,0.682353,>}
		normal {granite .05 scale .01}
	}
	#local LRoad_RoadSurfaceTexture = texture
	{
		pigment {color rgb <0.682353,0.682353,0.682353,>/4}
	}
	#local LRoad_InnerStripeTexture = texture
	{
		pigment {color rgb 1}
	}
	#local LRoad_CenterStripeTexture = texture
	{
		pigment {color rgb <1,0.905882,0.211765,>}
	}
	#local segments_num = 24;
	#local road_coordinates = array[segments_num]
	{
		trace (Ground_a, <-15,+16,-13,> * Width, -y),
		trace (Ground_a, <-21,+16,-02,> * Width, -y),
		trace (Ground_a, <-15,+16,-04,> * Width, -y),
		trace (Ground_a, <-13,+16,+00,> * Width, -y),
		trace (Ground_a, <-11,+16,+00,> * Width, -y),
		trace (Ground_a, <-05,+16,+03,> * Width, -y),
		trace (Ground_a, <-03,+16,+01,> * Width, -y),
		trace (Ground_a, <+04,+16,+01,> * Width, -y),
		trace (Ground_a, <+06,+16,+00,> * Width, -y),
		trace (Ground_a, <+11,+16,-01,> * Width, -y),
		trace (Ground_a, <+11,+16,-02,> * Width, -y),
		trace (Ground_a, <+14,+16,-04,> * Width, -y),
		trace (Ground_a, <+15,+16,-07,> * Width, -y),
		trace (Ground_a, <+17,+16,-14,> * Width, -y),
		trace (Ground_a, <+15,+16,-15,> * Width, -y),
		trace (Ground_a, <+12,+16,-22,> * Width, -y),
		trace (Ground_a, <+11,+16,-20,> * Width, -y),
		trace (Ground_a, <+06,+16,-23,> * Width, -y),
		trace (Ground_a, <+05,+16,-21,> * Width, -y),
		trace (Ground_a, <-04,+16,-21,> * Width, -y),
		trace (Ground_a, <-07,+16,-19,> * Width, -y),
		trace (Ground_a, <-11,+16,-17,> * Width, -y),
		trace (Ground_a, <-15,+16,-13,> * Width, -y),
		trace (Ground_a, <-21,+16,-02,> * Width, -y),
	}

	#if (!NoGrid)
		#local iCount = 0;
		#while (iCount < segments_num)
			sphere
			{
				road_coordinates[iCount],
				Width/8
				#if (mod(iCount,2) = 0)
					pigment {color rgb x + z/2}
				#else
					pigment {color rgb x + z}
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
		object {Ground_a}
		object {Road_b}
		bounded_by
		{
			box {<-SceneScale,0,-SceneScale,>, <+SceneScale,+SceneScale/2,+SceneScale,>}
		}
		pigment {color rgbt 1}
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
		pigment {rgb 1/2}
		normal {granite .05 scale .01}
	}
	#declare Glass_Texture = texture
	{
		pigment {color rgbt <0,0,0,3/4,>}
		finish {specular 1/2 brilliance 1/2}
	}
	#declare Razor_Texture = Polished_Chrome;
	#include "gh_wall.inc"
	#local WallNumber = 29;
	#local WallPoints = array[WallNumber][2]
	{
		{<-02,+16,-23,> * Width,<0,0,0,>,},	// 1
		{<-06,+16,-23,> * Width,<0,0,0,>,},	// 1.5
		{<-11,+16,-22,> * Width,<1,1,1,>,},	// 2
		{<-15,+16,-19,> * Width,<0,0,0,>,},	// 3
		{<-17,+16,-16,> * Width,<0,0,0,>,},	// 3.5
		{<-19,+16,-13,> * Width,<0,0,0,>,},	// 4
		{<-23,+16,-09,> * Width,<1,1,1,>,},	// 5
		{<-24,+16,-03,> * Width,<0,0,0,>,},	// 6
		{<-22,+16,+01,> * Width,<0,0,0,>,},	// 7
		{<-19,+16,+05,> * Width,<1,1,1,>,},	// 8
		{<-13,+16,+06,> * Width,<0,0,0,>,},	// 9
		{<-07,+16,+03,> * Width,<0,0,0,>,},	// 10
		{<-02,+16,+07,> * Width,<0,0,0,>,},	// 11
		{<-01,+16,+10,> * Width,<1,1,1,>,},	// 12
		{<+06,+16,+12,> * Width,<0,0,0,>,},	// 13
		{<+13,+16,+10,> * Width,<1,1,1,>,},	// 14
		{<+15,+16,+09,> * Width,<0,0,0,>,},	// 15
		{<+17,+16,+07,> * Width,<0,0,0,>,},	// 16
		{<+17,+16,+04,> * Width,<0,0,0,>,},	// 17
		{<+16,+16,+02,> * Width,<0,0,0,>,},	// 18
		{<+16,+16,-02,> * Width,<0,0,0,>,},	// 19
//		{<+16,+16,-06,> * Width,<1,1,1,>,},	// 20
		{<+17,+16,-08,> * Width,<0,0,0,>,},	// 21
		{<+17,+16,-13,> * Width,<0,0,0,>,},	// 22
		{<+17,+16,-18,> * Width,<0,0,0,>,},	// 23
		{<+15,+16,-23,> * Width,<1,1,1,>,},	// 24
		{<+10,+16,-26,> * Width,<0,0,0,>,},	// 25
		{<+04,+16,-26,> * Width,<0,0,0,>,},	// 26
		{<+01,+16,-25,> * Width,<0,0,0,>,},	// 26.5
		{<-02,+16,-23,> * Width,<0,0,0,>,},	// 1 (again)
	}

	#if (!NoGrid)
		#local iCount = 0;
		#while (iCount < WallNumber)
			sphere
			{
				WallPoints[iCount][0]
				Width/8
				#if (WallPoints[iCount][1] = 1)
					pigment {color rgb x + y/2}
				#else
					pigment {color rgb x + y}
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
			StretchyWall(Position1, Position2, 32, 96, 85, WallPoints[iCount][1].x, 1, 0)
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
			StretchyWall(Position1, Position2, 96, 96, 85, 0, 0, 0)
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
				#local TreesPosition = trace(Ground_a, TreesPosition, -y, NormGround);
				#local NormalAngle = VAngleD(NormGround, y);
				#if ((NormalAngle < TreesAngle) & (TreesPosition.y > TreesLevel))
					#local NormSum = <0,0,0,>;
					#if (!NoRoad)
						#local NormSum = NormSum + trace(Road_a, TreesPosition + y * 1024, -y, NormRoad);
					#end
					#if (!NoWall)
						#local NormSum = NormSum + trace(Wall_b, TreesPosition + y * 1024, -y, NormWall);
					#end
					#if (!NoDome)
						#local NormSum = NormSum + trace(Dome_b, TreesPosition + y * 1024, -y, NormDome);
					#end
					#if (VEq(NormSum, <0,0,0,>))
						object
						{
//							Grantrae
							TREE
							scale		Width * (rand(Seed) * 1/4 + 3/4)
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
	#local MaxWidth =	SceneScale;
	#local GrassUnion = union
	{
		#local PatchesCount = 0;
		#while (PatchesCount < GrassPatches)
			#local GrassCount = 0;
			#while (GrassCount < GrassPerPat)
				#local GrassPosition = <rand(Seed) * MaxWidth - MaxWidth/2, 1024, rand(Seed) * MaxWidth - MaxWidth/2>;
				#local GrassPosition = trace(Ground_a, GrassPosition, -y, NormGround);
				#local NormalAngle = VAngleD(NormGround, y);
				#if ((NormalAngle < GrassAngle) & (GrassPosition.y > GrassLevel))
					#local NormSum = <0,0,0,>;
					#if (!NoRoad)
						#local NormSum = NormSum + trace(Road_a, GrassPosition + y * 1024, -y, NormRoad);
					#end
					#if (!NoWall)
						#local NormSum = NormSum + trace(Wall_b, GrassPosition + y * 1024, -y, NormWall);
					#end
					#if (!NoDome)
						#local NormSum = NormSum + trace(Dome_b, GrassPosition + y * 1024, -y, NormDome);
					#end
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
	#local MaxWidth =	SceneScale;
	#local RocksUnion = union
	{
		#local PatchesCount = 0;
		#while (PatchesCount < RocksPatches)
			#local RocksCount = 0;
			#while (RocksCount < RocksPerPat)
				#local RocksPosition = <rand(Seed) * MaxWidth - MaxWidth/2, 1024, rand(Seed) * MaxWidth - MaxWidth/2>;
				#local RocksPosition = trace(Ground_a, RocksPosition, -y, NormGround);
				#local NormalAngle = VAngleD(NormGround, y);
				#if ((NormalAngle > RocksAngle) & (RocksPosition.y > RocksLevel))
					#local NormSum = <0,0,0,>;
					#if (!NoRoad)
						#local NormSum = NormSum + trace(Road_a, RocksPosition + y * 1024, -y, NormRoad);
					#end
					#if (!NoWall)
						#local NormSum = NormSum + trace(Wall_b, RocksPosition + y * 1024, -y, NormWall);
					#end
					#if (!NoDome)
						#local NormSum = NormSum + trace(Dome_b, RocksPosition + y * 1024, -y, NormDome);
					#end
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
		sphere		{0,    0.001 pigment{color rgb <0,0,0,>}}
		cylinder	{0, x, 0.001 pigment{color rgb <1,0,0,>}}
		cylinder	{0, y, 0.001 pigment{color rgb <0,1,0,>}}
		cylinder	{0, z, 0.001 pigment{color rgb <0,0,1,>}}
		finish {ambient 1}
		scale		SceneScale
		translate	<0,Width*4,0,>
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
						pigment {color rgb x}
						finish {ambient 1}
					}
				#end
				sphere
				{
					This_coo,
					1/16/Width
					#if (mod(Count_x,8) = 0 & mod(Count_z,8) = 0)
						pigment {color rgb x}
					#else
						pigment {color rgb y}
					#end
				}
				#local Count_z = Count_z + 1;
			#end
			#local Count_x = Count_x + 1;
		#end
		no_shadow
		no_reflection
		scale		SceneScale
		translate	<0,Width*4,0,>
	}
#end

//------------------------------------------------------------------------------Final


#if (!NoClouds)
	object {CloudSphere}
#end
#if (!NoAtmos)
	object {AtmosObject}
#end
#if (!NoTrees)
	object {TreesUnion}
#end
#if (!NoRoad)
	object {Road_a}
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
	object {Dome_a}
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
