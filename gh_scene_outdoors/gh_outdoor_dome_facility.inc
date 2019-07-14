// Desc: Facility with four geodesic domes.
// Auth: Michael Horvath
// Home Page: http://www.geocities.com/Area51/Quadrant/3864/gearhead.htm
// This file is licensed under the terms of the CC-LGPL.
// Dependencies:
// 1. "sphere.inc" by Shuhei Kawachi

#include "textures.inc"
#include "glass.inc"

#local N = 2;
#local Half = 1;
#local Method = 1;
#local Disc = 0;
#local R_Ten = 0.01 / N;
#local R_Hen = 0.01 / N;
//#local RibTexture = material {texture {Aluminum};
//#local PaneTexture = material {texture {T_Glass1};
#local RibTexture = material {texture {pigment {gamma_color_adjust(<1,1,1>*3/4)}}}
#local PaneTexture = material {texture{T_Glass3}};		// interior {I_Glass}
#local DirtTexture = material
{
	texture
	{
		pigment {color rgb 1/8}
		normal {wrinkles}
	}
}
#include "sphere.inc"
#include "shapes.inc"

#declare Dome_Section = union
{
	union
	{
		object {Ten material {RibTexture}}
		object {Hen material {RibTexture}}
		object {Men material {PaneTexture}}
		scale		12
		translate	y * 4
	}
	union
	{
		object {Ten material {RibTexture}}
		object {Hen material {RibTexture}}
		object {Men material {PaneTexture}}
		rotate		x * 180
		scale		12
		translate	y * 4
	}
	#if (Disc = 1)
		union
		{
			#include "gh_grass.inc"
			union
			{
				PlantPatch()
				scale	<4,10,4,>
				rotate	y * rand(Seed) * 360
			}
			disc
			{
				0, y, 10
				material {DirtTexture}
			}
		}
	#end
}

#declare Dome_Object = union
{
	union
	{
		object {Dome_Section translate <+20,0,0,>}
		object {Dome_Section translate <-20,0,0,>}
		object {Dome_Section translate <0,0,+20,>}
		object {Dome_Section translate <0,0,-20,>}
//		no_image
//		no_shadow
//		no_reflection
	}
	difference
	{
		union
		{
			cylinder {<-12,+00,+00,>, <+12,+00,+00,>, 3}
			cylinder {<+00,+00,-12,>, <+00,+00,+12,>, 3}
			cylinder {<+00,-04,+00,>, <+00,+04,+00,>, 8}
		}
		union
		{
			cylinder {<-13,+00,+00,>, <+13,+00,+00,>, 2}
			cylinder {<+00,+00,-13,>, <+00,+00,+13,>, 2}
			cylinder {<+00,-03,+00,>, <+00,+03,+00,>, 7}
		}
		bounded_by
		{
			box {<-13,-05,-13,>, <+13,+05,+13,>}
		}
		material {RibTexture}
		translate	y * 4
	}
	union
	{
//		cylinder {<+20,-20,+00,>, <+20,+00,+00,>, 4}
//		cylinder {<-20,-20,+00,>, <-20,+00,+00,>, 4}
//		cylinder {<+00,-20,+20,>, <+00,+00,+20,>, 4}
//		cylinder {<+00,-20,-20,>, <+00,+00,-20,>, 4}
		cylinder {<+00,-20,+00,>, <+00,+00,+00,>, 3}
		material {RibTexture}
//		translate	y * -0.1
	}
	union
	{
		object
		{
			Paraboloid_X
			clipped_by {plane {x, 1}}
		}
		cylinder {0, x * 2, 0.01}
		material {RibTexture}
		scale		<1/2,1,1,>
		scale		4
		rotate		z * 60
		translate	y * 10
	}
	cylinder
	{
		0, y * 2, 1
		translate	y * 8
	}
	translate y * 8
}

