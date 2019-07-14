#include "glass.inc"
#local Tex_1 = texture
{
	pigment {gamma_color_adjust(<1,1,1>)}
	finish
	{
		ambient 0.0
		diffuse 0.6
		specular 0.1
	}
}
#local Tex_2 = texture
{
	pigment {gamma_color_adjust(<0.8,0.8,1.0,0.0,0.5>)}
	normal {wrinkles}
}
#local Tex_3 = texture
{
	pigment {gamma_color_adjust(<0,0,0>)}
	finish {F_Glass5}
}
#local Int_1 = interior
{
	I_Glass_Dispersion1
}

// FOUNTAIN
#declare building_size[building_types] = <32, 32, 32>;
#declare building_options[building_types] = build_base;
#declare building_base[building_types] = union
{
	difference
	{
		box {<-13,0.0,-13,>, <+13,1.5,+13,>}
		box {<-12,0.5,-12,>, <+12,2.0,+12,>}
		texture {Tex_1}
	}
	box
	{
		<-11.9999,0.5001,-11.9999,>, <+11.9999,1,+11.9999,>
		texture {Tex_2}
//		texture {Tex_3}
//		interior {Int_1}
		hollow
	}
	difference
	{
		box {<-7,1.0,-7,>, <+7,2.5,+7,>}
		box {<-6,1.5,-6,>, <+6,3.0,+6,>}
		texture {Tex_1}
	}
	box
	{
		<-5.9999,1.5001,-5.9999,>, <+5.9999,2,+5.9999,>
		texture {Tex_2}
//		texture {Tex_3}
//		interior {Int_1}
		hollow
	}
	union
	{
		box {<-6,1,-6,>, <-7,6,-7,>}
		box {<-6,1,+6,>, <-7,6,+7,>}
		box {<+6,1,+6,>, <+7,6,+7,>}
		box {<+6,1,-6,>, <+7,6,-7,>}
		texture {Tex_1}
	}
	scale y/2
}
#declare building_types = building_types + 1;

/*
// from radiosity scene, needs a nicer texture
#declare building_size[building_types] = <20, 20, 20>;
#declare building_options[building_types] = build_base;
#local Column_Block = union
{
	#declare Cnt=0;
	#while (Cnt < 8.8)
		cylinder { <4.4, 0.2, 4.4-Cnt>, <4.4, 3.6, 4.4-Cnt>, 0.2 }
		#declare Cnt=Cnt+(8.8/3);
	#end
}
#local Walls = difference
{
	box { <-10, -0.1, -10>, <10,   4, 10> }
	box { < -9,  0.3,  -9>, < 9, 3.5,  9> }
	box { < -8,  0.1,  -8>, < 8,   5,  8> }
	intersection
	{
		merge
		{
			cylinder { <0, 0.3, 0>, <0, 0.3, 12>, 2 }
			cylinder { <0, 0.3, 0>, <0, 0.3, 12>, 2 rotate 180*y }
			cylinder { <0, 0.3, 0>, <0, 0.3, 12>, 2 rotate  90*y }
			cylinder { <0, 0.3, 0>, <0, 0.3, 12>, 2 rotate -90*y }
		}
		plane { y, 0.3 inverse }
	}
}
#local Col_Base = difference
{
	box { <-4.7,    0, -4.7>, <4.7, 3.6, 4.7> }
	box { <-4.1, -0.1, -4.1>, <4.1,   4, 4.1> }
	box { <  -5,  0.5,   -5>, <  5, 3.3,   5> }
}
#declare building_base[building_types] = union
{
	object { Walls }
	object { Column_Block }
	object { Column_Block rotate 180*y }
	object { Column_Block rotate  90*y }
	object { Column_Block rotate -90*y }
	object { Col_Base }
	texture { Tex_1 }
}
#declare building_types = building_types + 1;
*/