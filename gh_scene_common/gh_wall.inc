// Desc: Macro for creating the enclosure wall.
// Auth: Michael Horvath
// Home Page: http://www.geocities.com/Area51/Quadrant/3864/gearhead.htm
// This file is licensed under the terms of the CC-LGPL.
// Notes:
// 1. There should maybe be some razor wire on top of the towers, especially the ones without enclosures.

#ifndef (Included)
	#include "stdinc.inc"
	#include "textures.inc"
	#declare Vect1 = <1,1/2,0,> * -512;
	#declare Vect2 = <1,1/2,0,> * +512;
	#declare Seed = seed(22231);
	camera
	{
		//orthographic
		up		+y * 1536
		right		+x * 1526 * image_width/image_height
		location	-z * 1024
		direction	+z * 1024
	}
	sky_sphere
	{
		pigment
		{
			gradient y
			color_map
			{
				[0.0 rgb <0.6,0.7,1.0>]
				[0.7 rgb <0.0,0.1,0.8>]
			}
		}
	}
	light_source
	{
		<3000, 6000, -7000>
		rgb 1
		parallel
	}
	#declare Concrete_Texture = texture
	{
		pigment {rgb 1/2}
		normal {granite 1/20 scale 1/100}
	}
	#declare Glass_Texture = texture
	{
		pigment {color rgbt 1/2}
		finish {specular 1/2 brilliance 1/2}
	}
	#declare Razor_Texture = Polished_Chrome;
#end

// ----------------------------------------
#macro StretchyWall(Point1, Point2, Width, Height, Angle, Guardhouse, Razorwire, Razorbarbs)
	#local Vector = Point1 - Point2;
	#local MainWid = Width/2;
	#local MainHgh = Height;
	#local MainAng = Angle;
	#local TowrWid = Width * 2/3;
	#local TowrHgh = Height * 9/8;
	#local TowrAng = Angle;
	#local GlssWid = MainWid;
	#local GlssHgh = Height/8;
	#local GlssAng = 180 - Angle;
	#local RoofWid = TowrWid;
	#local RoofHgh = Height/32;
	#local RazrWid = VDist(Point1, Point2) - TowrWid * 2;
	#local RazrHgh = MainWid/2;
	#local RazrThk = RazrHgh/4;
	#local RazrFq1 = RazrWid/8;
	#local RazrSt1 = RazrWid/2;
	#local RazrFq2 = 2 * TowrWid/8;
	#local RazrSt2 = 2 * TowrWid/2;
//	#debug concat("Wall.RazrWid = ", str(RazrWid,0,-1), "\n")
//	#debug concat("Wall.RazrFq1 = ", str(RazrFq1,0,-1), "\n")
	union
	{
		// main wall
		intersection
		{
			plane
			{
				y, 0
				rotate		+x * MainAng
				translate	+z * MainWid
				translate	+y * MainHgh
			}
			plane
			{
				y, 0
				rotate		-x * MainAng
				translate	-z * MainWid
				translate 	+y * MainHgh
			}
			#local BoudWid = tand(90-MainAng) * (Height + MainHgh) + MainWid;
			box {<-1/2,-Height,-BoudWid,>, <+1/2,+MainHgh,+BoudWid,>}
			bounded_by
			{
				box {<-1/2,-Height,-BoudWid,>, <+1/2,+MainHgh,+BoudWid,>}
			}
			texture {Concrete_Texture}
//			pigment {color rgbt <rand(Seed),rand(Seed),rand(Seed),1/2,>}
			scale		<vlength(Vector),1,1,>
			Shear_Trans(x, vrotate(y, <0,0,-90 + VAngleD(Vector,y)>), z)
			rotate		z * (90 - VAngleD(y, Vector))
			rotate		y * VRotationD(x, <Vector.x, 0, Vector.z,>, y)
			translate	(Point1 + Point2) / 2
		}
		// tower wall
		intersection
		{
			plane
			{
				y, 0
				rotate		+x * TowrAng
				translate	+z * TowrWid
				translate 	+y * TowrHgh
			}
			plane
			{
				y, 0
				rotate		-x * TowrAng
				translate	-z * TowrWid
				translate 	+y * TowrHgh
			}
			plane
			{
				y, 0
				rotate		-z * TowrAng
				translate	+x * TowrWid
				translate 	+y * TowrHgh
			}
			plane
			{
				y, 0
				rotate		+z * TowrAng
				translate	-x * TowrWid
				translate 	+y * TowrHgh
			}
			#local BoudWid = tand(90-TowrAng) * (Height + TowrHgh) + TowrWid;
			box {<-BoudWid,-Height,-BoudWid,>, <+BoudWid,+TowrHgh,+BoudWid,>}
			bounded_by
			{
				box {<-BoudWid,-Height,-BoudWid,>, <+BoudWid,+TowrHgh,+BoudWid,>}
			}
			texture {Concrete_Texture}
			rotate		y * VRotationD(x, <Vector.x, 0, Vector.z,>, y)
			translate	Point2
		}
		#if (Razorwire)
			#local RazrRat = RazrThk/RazrHgh;
			#if (Razorbarbs)
				#local ScaleYZ = RazrHgh * RazrHgh / (RazrHgh + RazrThk * 2);
				#local Razor_Blade = mesh
				{
					#local P_1 = <-2,1,0,>;
					#local P_2 = <+2,1,0,>;
					#local P_3 = <-1,0,0,>;
					#local P_4 = <+1,0,0,>;
					triangle {P_1,P_2,P_4}
					triangle {P_4,P_3,P_1}
					rotate		y * +90
					rotate		z * -90
					scale		RazrRat
				}
			#else
				#local ScaleYZ = RazrHgh;
			#end
			// razor wire on walltops
			#local Razor_Coil = union
			{
				#local RazrT1 = 0;
				#local RazrT2 = 0;
				#local iCount = 0;
				#while (iCount < RazrSt1)
					#local RazrT2 = iCount/RazrSt1;
					#local RazrT1 = (iCount + 1)/RazrSt1;
					#local P_1 = <1			* cos(RazrFq1 * RazrT1 * 2 * pi),	RazrT1,		1		* sin(RazrFq1 * RazrT1 * 2 * pi),>;
					#local P_2 = <(1 - RazrRat)	* cos(RazrFq1 * RazrT1 * 2 * pi),	RazrT1,		(1 - RazrRat)	* sin(RazrFq1 * RazrT1 * 2 * pi),>;
					#local P_3 = <1			* cos(RazrFq1 * RazrT2 * 2 * pi),	RazrT2,		1		* sin(RazrFq1 * RazrT2 * 2 * pi),>;
					#local P_4 = <(1 - RazrRat)	* cos(RazrFq1 * RazrT2 * 2 * pi),	RazrT2,		(1 - RazrRat)	* sin(RazrFq1 * RazrT2 * 2 * pi),>;
					mesh		// could be smoothed
					{
						triangle {P_1,P_2,P_4}
						triangle {P_4,P_3,P_1}
					}
					#if (Razorbarbs)
						object
						{
							Razor_Blade
							rotate		-y * degrees(RazrFq1 * RazrT1 * 2 * pi)
							translate	P_1
						}
						object
						{
							Razor_Blade
							rotate		-y * degrees(RazrFq1 * RazrT1 * 2 * pi)
							rotate		+y * 180
							translate	P_2
						}
					#end
					#local iCount = iCount + 1;
				#end
				scale		<ScaleYZ,RazrWid,ScaleYZ,>
				rotate		-z * 90
				translate	+x * TowrWid
				texture {Razor_Texture}
			}
			object
			{
				Razor_Coil
				translate	+z * MainWid/2
				Reorient_Trans(x, Vector)
				translate	+y * (MainHgh + RazrHgh)
				translate	Point2
			}
			object
			{
				Razor_Coil
				translate	-z * MainWid/2
				Reorient_Trans(x, Vector)
				translate	+y * (MainHgh + RazrHgh)
				translate	Point2
			}
/*
			// razor wire on towers
			#local Razor_Coil = union
			{
				#local RazrT1 = 0;
				#local RazrT2 = 0;
				#local iCount = 0;
				#while (iCount < RazrSt2)
					#local RazrT2 = iCount/RazrSt2;
					#local RazrT1 = (iCount + 1)/RazrSt2;
					#local P_1 = <1			* cos(RazrFq2 * RazrT1 * 2 * pi),	RazrT1,		1		* sin(RazrFq2 * RazrT1 * 2 * pi),>;
					#local P_2 = <(1 - RazrRat)	* cos(RazrFq2 * RazrT1 * 2 * pi),	RazrT1,		(1 - RazrRat)	* sin(RazrFq2 * RazrT1 * 2 * pi),>;
					#local P_3 = <1			* cos(RazrFq2 * RazrT2 * 2 * pi),	RazrT2,		1		* sin(RazrFq2 * RazrT2 * 2 * pi),>;
					#local P_4 = <(1 - RazrRat)	* cos(RazrFq2 * RazrT2 * 2 * pi),	RazrT2,		(1 - RazrRat)	* sin(RazrFq2 * RazrT2 * 2 * pi),>;
					mesh		// could be smoothed
					{
						triangle {P_1,P_2,P_4}
						triangle {P_4,P_3,P_1}
					}
					#if (Razorbarbs)
						object
						{
							Razor_Blade
							rotate		-y * degrees(RazrFq2 * RazrT1 * 2 * pi)
							translate	P_1
						}
						object
						{
							Razor_Blade
							rotate		-y * degrees(RazrFq2 * RazrT1 * 2 * pi)
							rotate		+y * 180
							translate	P_2
						}
					#end
					#local iCount = iCount + 1;
				#end
				scale		<ScaleYZ,TowrWid * 2,ScaleYZ,>
				rotate		-z * 90
				translate	-x * TowrWid
				#if (Guardhouse)
					translate	+y * (TowrHgh + GlssHgh + RoofHgh + RazrHgh)
				#else
					translate	+y * (TowrHgh + RazrHgh)
				#end
				texture {Razor_Texture}
			}
			union
			{
				object
				{
					Razor_Coil
					translate	+z * TowrWid/2
				}
				object
				{
					Razor_Coil
					translate	-z * TowrWid/2
				}
				object
				{
					Razor_Coil
					translate	+z * TowrWid/2
					rotate		+y * 90
				}
				object
				{
					Razor_Coil
					translate	-z * TowrWid/2
					rotate		+y * 90
				}
				rotate		y * VRotationD(x, <Vector.x, 0, Vector.z,>, y)
				translate	Point2
			}
*/
//			#debug concat("Wall.ScaleYZ = ", str(ScaleYZ,0,-1), "\n")
		#end
		// tower enclosure
		#if (Guardhouse)
			// tower glass
			intersection
			{
				plane
				{
					y, 0
					rotate		+x * GlssAng
					translate	+z * GlssWid
					translate	+y * (TowrHgh + GlssHgh)
				}
				plane
				{
					y, 0
					rotate		-x * GlssAng
					translate	-z * GlssWid
					translate	+y * (TowrHgh + GlssHgh)
				}
				plane
				{
					y, 0
					rotate		-z * GlssAng
					translate	+x * GlssWid
					translate	+y * (TowrHgh + GlssHgh)
				}
				plane
				{
					y, 0
					rotate		+z * GlssAng
					translate	-x * GlssWid
					translate	+y * (TowrHgh + GlssHgh)
				}
				box {<-GlssWid,+TowrHgh,-GlssWid,>, <+GlssWid,+TowrHgh + GlssHgh,+GlssWid,>}
				bounded_by
				{
					box {<-GlssWid,+TowrHgh,-GlssWid,>, <+GlssWid,+TowrHgh + GlssHgh,+GlssWid,>}
				}
				texture {Glass_Texture}
				rotate		y * VRotationD(x, <Vector.x, 0, Vector.z,>, y)
				translate	Point2
			}
			// tower roof
			box
			{
				<-RoofWid,+TowrHgh + GlssHgh,-RoofWid,>, <+RoofWid,+TowrHgh + GlssHgh + RoofHgh,+RoofWid,>
				texture {Concrete_Texture}
				rotate		y * VRotationD(x, <Vector.x, 0, Vector.z,>, y)
				translate	Point2
			}
		#end
	}
#end

// ----------------------------------------
#ifndef (Included)
	sphere {Vect1, 1 pigment {color Red}}
	sphere {Vect2, 1 pigment {color Red}}
	object {StretchyWall(Vect2, Vect1, 32, 96, 85, 1, 1, 1) texture {pigment {color White}}}
	#declare Axis_Markers = union
	{
		sphere {0, 0.005 pigment{color rgb <0,0,0,>}}
		cylinder {0, x, 0.005 pigment{color rgb <1,0,0,>}}
		cylinder {0, y, 0.005 pigment{color rgb <0,1,0,>}}
		cylinder {0, z, 0.005 pigment{color rgb <0,0,1,>}}
	}
	object {Axis_Markers scale 32}
#end