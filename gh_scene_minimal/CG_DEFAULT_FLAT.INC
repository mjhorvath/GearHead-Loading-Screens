#include "gh_deciduous_tree.inc"

/*************************************************************************
DEFAULT CITY GENERATOR OBJECTS FILE FOR PERSISTENCE OF VISION 3.x

Created by Chris Colefax, 1 February 1999
NOTE: This file is designed for use with City.mcr and City.inc
Scale is approx. 1 unit = 1 metre, default building width 25 units

*************************************************************************/

// GENERAL OPTIONS AND MACROS
#ifndef (city_default_objects)	#declare city_default_objects	= false;	#end
#ifndef (city_night)		#declare city_night		= false;	#end
#ifndef (traffic_night)		#declare traffic_night		= false;	#end
#ifndef (windows_lit)		#declare windows_lit		= .33;		#end
#ifndef (windows_blend)		#declare windows_blend		= .25;		#end
#if (city_night = false)	#declare windows_lit		= 0;		#end

// For creating lit/unlit window textures
#macro window_texture (UnlitTexture, LitTexture, WindowSize)
	#local WScale = WindowSize + <(WindowSize.x = 0 ? 1 : 0), (WindowSize.y = 0 ? 1 : 0), (WindowSize.z = 0 ? 1 : 0)>;
	#local WV = windows_lit*(1+windows_blend);
	bozo
	texture_map
	{
		[WV - windows_blend LitTexture scale 1/(100*WScale)]
		[WV UnlitTexture scale 1/(100*WScale)]
	}
	scale 100
	#if (WindowSize.x) warp {repeat x offset -x*100} #end
	#if (WindowSize.y) warp {repeat y offset -y*100} #end
	#if (WindowSize.z) warp {repeat z offset -z*100} #end
	scale WScale*1.001
#end

#macro set_window_texture (UnlitTexture, LitTexture, WindowSize)
	#declare building_window_texture[building_types] = texture
	{
		window_texture(UnlitTexture, LitTexture, WindowSize)
	}
	#declare building_window_size[building_types] = WindowSize;
#end

// For creating spotlights without media or light sources: Colour should include filter and/or transmit
#macro spotlight_cone (Point1, Radius1, Point2, Radius2, Colour, Falloff)
	#local D = Point2 - Point1;
	cone
	{
		Point1, Radius1, Point2, Radius2
		open
		hollow
		no_shadow
		pigment
		{
			gradient D
			color_map
			{
				[0 Colour]
				[1 Colour transmit 1]
			}
			poly_wave Falloff
			scale vlength(D)
			translate Point1
		}
		finish {ambient 1 diffuse 0}
	}
#end

// INITIALIZE BUILDING OBJECT ARRAYS
#ifndef (max_building_types)
	#local max_building_types = 100;
#end
#declare building_size			= array[max_building_types];
#declare building_options		= array[max_building_types];
#declare building_profile		= array[max_building_types];
#declare building_details		= array[max_building_types];
#declare building_windows		= array[max_building_types];
#declare building_window_texture	= array[max_building_types];
#declare building_window_size		= array[max_building_types];
#declare building_base			= array[max_building_types];
#declare building_roof			= array[max_building_types];
#declare building_texture		= array[max_building_types];

// BUILDING OPTIONS
#declare build_texture		= 1;
#declare build_fit_texture	= 2;
#declare build_profile		= 4;
#declare build_details		= 8;
#declare build_window_levels	= 16;
#declare build_window_profile	= 32;
#declare build_base		= 64;
#declare build_roof		= 128;
#declare building_types		= 0;

// CITY TEXTURES
#declare street_texture = texture
{
	pigment
	{
		bozo
		color_map
		{
			[0 gamma_color_adjust(<.2,.2,.2>)]
			[1 gamma_color_adjust(<.4,.4,.4>)]
		}
		scale .02
	}
}
#declare pavement_texture = texture
{
	pigment
	{
		wrinkles
		color_map
		{
			[0 gamma_color_adjust(<.5,.5,.5>)]
			[1 gamma_color_adjust(<.6,.6,.6>)]
		}
		scale 1.5
	}
}

// Should measure 2x2 in x-z plane, travelling along the x-axis
#declare street_overlay = texture
{
	pigment
	{
		planar
		pigment_map
		{
			[
				1/2
				gradient y
				pigment_map
				{
					[.02 checker gamma_color_adjust(<1,1,1>), gamma_color_adjust(<1,1,1,0,1>) scale .1]
					[.02 gamma_color_adjust(<1,1,1,0,1>)]
				}
				ramp_wave
			]
			[
				1/2
				gradient y
				color_map
				{
					[.01 gamma_color_adjust(<1,1,1,0,1>)]
					[.01 gamma_color_adjust(<1,1,1>)]
					[.03 gamma_color_adjust(<1,1,1>)]
					[.03 gamma_color_adjust(<1,1,1,0,1>)]
				}
				ramp_wave
			]
		}
		rotate x*90
	}
}

// CITY OBJECTS
#declare street_lamp = union
{
	cylinder
	{
		0, y*5, .15
	}
	sphere
	{
		y*5, .15
	}
	cylinder
	{
		y*5, <2, 6, 0>, .1
	}
	sphere
	{
		0, .5
		scale <.6, .2, .3>
		translate <2.2, 6, 0>
	}
	sphere
	{
		0, .5
		scale <.58, .2, .28>
		translate <2.2, 5.98, 0>
		pigment {gamma_color_adjust(<1, .9, .7>)}
		finish {ambient 1.3}
		no_shadow
	}
	#if (traffic_night)
		spotlight_cone (<2.2, 6, 0>, .2, <2.2, 0, 0>, 3, gamma_color_adjust(<2, 1.8, 1.6, 0, .9>), 4)
	#end
	pigment {gamma_color_adjust(<.6,.6,.6>)}
	finish {metallic}
	scale 3/4
}

#local traffic_light = union
{
	cylinder {<0, 6, 0>, <4, 6, 0>, .05}
	cylinder {<0, 5.6, 0>, <4, 5.6, 0>, .05}
	difference
	{
		box {<4, 5.3, -.2>, <4.6, 6.3, .2>}
		sphere {<4.3, 5.5, -.2>, .1	pigment {gamma_color_adjust(< 0, .6,.2>)}}
		sphere {<4.3, 5.8, -.2>, .1	pigment {gamma_color_adjust(<.6, .4, 0>)}}
		sphere {<4.3, 6.1, -.2>, .1	pigment {gamma_color_adjust(< 1, .2, 0>)}	finish {ambient 1.5 diffuse .5}}
	}
	#if (traffic_night)
		spotlight_cone (<4.3, 6.1, -.1>, .1, <4.3, 6.1, -.6>, .6, gamma_color_adjust(<1.5, .3, .1, 0, .8>), 2)
	#end
	pigment {gamma_color_adjust(<.6,.6,.6>)}
	finish {metallic}
}
#local traffic_union = union
{
	object
	{
		street_lamp
		scale 1.2
		rotate y*45
	}
	object {traffic_light}
	object {traffic_light	rotate y * 90}
	scale 3/4
}

#local bus_stop = union
{
	box
	{
		<-1.5, 0, -1.5>, <.1, 3.1, 1.5>
		clipped_by
		{
			box {<-1.6, .4, -1.6>, <0, 3, 1.6>}
		}
		pigment {gamma_color_adjust(<.7, .7, .7, 0, .3>)}
	}
	box
	{
		<-1.5, .6, -1.5>, <-1, .65, 1.5>
		pigment {gamma_color_adjust(<.6, .3, .1>)}
	}
	cylinder
	{
		0, y*3, .05
		translate <-1.5, 0, -1.5>
	}
	cylinder
	{
		0, y*3, .05
		translate <-1.5, 0, 1.5>
	}
	cylinder
	{
		0, y*3, .05
		translate <0, 0, -1.5>
	}
	cylinder
	{
		0, y*3, .05
		translate <0, 0, 1.5>
	}
	box
	{
		<-1.7, 3, -1.7>, <.4, 3.1, 1.7>
	}
	#if (traffic_night)
		spotlight_cone (<0, 3, 0>, 0, <0, 0, 0>, 1.5, gamma_color_adjust(<1.5, 1.4, 1.2, 0.0, 0.9>), 1.5)
	#end
	pigment {gamma_color_adjust(<.4,.4,.4>)}
	finish {metallic}
	scale 3/4
}

#local metal_texture = texture
{
	pigment {gamma_color_adjust(<.4,.4,.4>)}
	finish {metallic}
}
#local plant_seed = seed(099032826); 
#local potted_plant = union
{
	object
	{
		TREE
		scale		<2,4,2>
		translate	y*1/8
		rotate		y * rand(plant_seed) * 360
	}
	difference
	{
		sphere {y*1, 8/8}
		sphere {y*1, 7/8}
		plane {-y,-1}
	}
	intersection
	{
		sphere {y*1, 7/8}
		plane {y, 7/8}
		pigment {gamma_color_adjust(<.2,.2,.2>)}
	}
	cylinder {0, y/2, 1/8	translate <-1,0,-1>/2}
	cylinder {0, y/2, 1/8	translate <-1,0,+1>/2}
	cylinder {0, y/2, 1/8	translate <+1,0,+1>/2}
	cylinder {0, y/2, 1/8	translate <+1,0,-1>/2}
	bounded_by {cylinder {0, y*5, 2}}
	texture {metal_texture}
	scale 1/2
	scale 3/4
}

#local trash_can = union
{
	difference
	{
		cone {y/2, 12/16, y*5/2, 16/16}
		cone {y/1, 11/16, y*6/2, 15/16}
	}
	cylinder {0, y*5/2, 1/8	translate <-1,0,0>}
	cylinder {0, y*5/2, 1/8	translate <+1,0,0>}
	cylinder {0, y*5/2, 1/8	translate <0,0,+1>}
	cylinder {0, y*5/2, 1/8	translate <0,0,-1>}
	bounded_by {cylinder {0, y*5/2, 1+1/8}}
	texture {metal_texture}
	scale 1/2
	scale 3/4
}

#declare pavement_object		= array[5]
{
	object {traffic_union	translate -x * 1/2},
	object {street_lamp	translate -x * 1/2},
	object {bus_stop	translate -x * 1/3},
	object {potted_plant	translate -x * 1/2},
	object {trash_can	translate -x * 1/2}
}
#declare pavement_object_offset		= array[5] {1/2, 20, 10, 02, 04}
#declare pavement_object_spacing	= array[5] {00, 32, 00, 32, 32}
#declare pavement_object_turb		= array[5] {00, 00, 32, 32, 32}
