// Desc: Grass patch object. (Might not work.)
// Auth: Michael Horvath
// Home Page: http://www.geocities.com/Area51/Quadrant/3864/gearhead.htm
// This file is licensed under the terms of the CC-LGPL.
// Dependencies:
// 1. "grasspatch.inc" written by Josh English

#ifndef (Included)
	#declare Camera_Position =	<0,0,-4>;
#else
	#declare Camera_Position =	Camera_Location;
#end

#include "grasspatch.inc"

#declare someseed =		seed(2345);
#declare xseed =		seed(422);
#declare zseed =		seed(369);
#declare Patch_Tranlation =	<0,0,0>;
#declare PlotPoints =		false;
#declare Blade_Density =	2;		// per unit length. Square this to know how many will be in each unit squared of landscape
#declare Blade_Tex = texture			// And of course the texture. This is the default:
{
//	pigment { color rgb <0,0.3,0> }
//	pigment { color rgb <64/255,104/255,72/255,> * 4/3 }
	pigment { color rgb <64/255,104/255,72/255,> * 2 }
//	pigment { color rgb <0,0.5,0,> }
//	finish { phong 0.25 ambient 0.2 }
}
#declare Patch_Shape =		0;		// Circular
#declare Spread_Correction =	0.9;
#declare Blade_Height_Minimum =	1/2;		// Blade_Heights are in standard POV units
#declare Blade_Height_Maximum =	1;
#declare Use_Blade_Distance =	true;
#declare Blade_Detail =		10;
#declare Max_Blade_Angle =	0;
#declare Min_Blade_Angle =	0;
#declare Blade_Scale =		0.5;
#declare Blade_Width =		0.1;
#declare Use_Blade_Distance =	true;
#declare Max_Blade_Detail =	20;
#declare Min_Blade_Detail =	5;
#declare Max_Detail_Distance =	1;
#declare Min_Detail_Distance =	10;

#ifndef (Included)
	union
	{
		PlantPatch()
		scale 16
		no_shadow
	}
#end
