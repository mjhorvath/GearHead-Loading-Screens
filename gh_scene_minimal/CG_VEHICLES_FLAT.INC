/*************************************************************************
CITY GENERATOR VEHICLE OBJECTS FILE FOR PERSISTENCE OF VISION 3.x

Created by Chris Colefax, 1 February 1999
NOTE: This file is designed for use with City.mcr and City.inc
To use, include the file before including City.inc, with any other
object/building files you want to use.

**************************************************************************/

// INCLUDE DEFAULT OBJECTS FILE IF REQUIRED
#ifndef (city_default_objects)
	#include "DEFAULT.OBJ"
#end

// VEHICLE OPTIONS
#ifndef (city_right_hand_drive)
	#local city_right_hand_drive = false;
#end

// VEHICLE COMPONENTS
// NB: Vehicles should travel along +z axis (LH drive), or -z axis (RH drive)
#local Tires = union
{
	sphere {y,	1	scale <.2, .3, .3>	translate -x}
	sphere {y,	1	scale <.2, .3, .3>	translate x}
	pigment {gamma_color_adjust(<.1, .1, .1>)}
}

#local HeadLights = union
{
	sphere {<-.6, .7, 0>,	.15	scale <1, 1, .3>}
	sphere {<+.6, .7, 0>,	.15	scale <1, 1, .3>}
	#if (city_night)
		union
		{
			spotlight_cone (<-.6, 0, 0>,	.1,	<-.6, -.7, 0>,	1,	gamma_color_adjust(<1.5, 1.4, 1.2, 0.0, 0.8>),	1)
			spotlight_cone (<+.6, 0, 0>,	.1,	<+.6, -.7, 0>,	1,	gamma_color_adjust(<1.5, 1.4, 1.2, 0.0, 0.8>),	1)
			matrix <1, 0, 0, 0, 1, -5, 0, 0, 1, 0, .7, -.1>
		}
		finish {ambient 1.3}
	#end
	pigment {gamma_color_adjust(<1, 1, .9>)}
}

#local BrakeLights = union
{
	sphere {<-.5, .7, 0>,	.15}
	sphere {<+.5, .7, 0>,	.15}
	pigment {gamma_color_adjust(<1, .3, .2>)}
	scale <1, 1, .3>
	#if (city_night)
		finish {ambient 1.3}
	#end
}

#local Car = union
{
	superellipsoid {<.4, .5>	scale < 1, .5,   2>	translate y * .6}
	superellipsoid {<.5, .7>	scale <.8, .5, 1.1>	translate y * 1.3}
	object {Tires	translate +z*1.2}
	object {Tires	translate -z*1.2}
	object {HeadLights	translate +z * 2}
	object {BrakeLights	translate -z * 2}
	#if (city_right_hand_drive)
		rotate y*180
	#end
	finish {phong .6	phong_size 20	metallic}
}

#local Bus = union
{
	superellipsoid {<.2, .3> scale <1.2, 1.3, 2.7>	translate <0, 1.6, -.3>}
	superellipsoid {<.5, .6> scale <1.1,  .7,  .7>	translate <0,   1, 2.3>}
	object {Tires	scale 1.2	translate +z*2}
	object {Tires	scale 1.2	translate -z*2}
	object {HeadLights	scale 1.2	translate +z * 2.95}
	object {BrakeLights	scale 1.2	translate -z * 2.95}
	#if (city_right_hand_drive)
		rotate y*180
	#end
	pigment
	{
		gradient y
		color_map
		{
			[.6 gamma_color_adjust(<.8, .6, .2>)]
			[.6 gamma_color_adjust(<.2, .2, .2>)]
		}
		scale 1.5
		translate y*.8
	}
	finish {phong .3 phong_size 15 metallic}
}

#local Car_1 = object {Car				pigment {gamma_color_adjust(< .9, .9, .9>)}}
#local Car_2 = object {Car scale 1.1			pigment {gamma_color_adjust(<  0, .4, .2>)}}
#local Car_3 = object {Car scale 0.8			pigment {gamma_color_adjust(<  1, .9, .3>)}}
#local Car_4 = object {Car scale <1.0, 0.7, 1.0>	pigment {gamma_color_adjust(< .8, .1, .2>)}}
#local Car_5 = object {Car scale <1.1, 1.0, 1.3>	pigment {gamma_color_adjust(<.25,.25,.25>)}}


// OBJECT ARRAYS FOR CITY.MCR
#declare city_vehicle = array[6]
{
	object {Car_1	scale 3/4},
	object {Car_2	scale 3/4},
	object {Car_3	scale 3/4},
	object {Car_4	scale 3/4},
	object {Car_5	scale 3/4}
	object {Bus	scale 3/4}
}
#declare city_vehicle_spacing = array[6] {4.5, 4.5, 4, 4.5, 6, 7}
