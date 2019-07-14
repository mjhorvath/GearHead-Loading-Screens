/*************************************************************************
CITY GENERATOR APARTMENT BUILDINGS FILE FOR PERSISTENCE OF VISION 3.x

Created by Chris Colefax, 1 February 1999
NOTE: This file is designed for use with City.mcr and City.inc
To use, include the file before including City.inc, with any other
object/building files you want to use.

**************************************************************************/

// INCLUDE DEFAULT OBJECTS FILE IF REQUIRED
#ifndef (building_size) #include "DEFAULT.OBJ" #end

// COMMON TEXTURES AND FINISHES
#local FMetal = finish {specular .2 roughness .1 metallic brilliance 10}
#local FGlass = finish {specular .5 roughness .05 reflection .4}
#local Concrete = texture {pigment {gamma_color_adjust(<1,1,1>*.5)} normal {granite .2 scale .1}}

// APARTMENT BLOCK #1 (Brown concrete)
#declare building_size[building_types] = <200, 50, 200>;
#declare building_options[building_types] = build_texture + build_profile + build_window_levels + build_details + build_base + build_roof;
#declare building_texture[building_types] = texture
{
	pigment {wrinkles color_map {[0 gamma_color_adjust(<.7, .6, .4>)] [1 gamma_color_adjust(<.6, .4, .3>)]} scale <80, 50, 80>}
	normal {wrinkles .3 scale .2}
}
#declare building_profile[building_types] = box {<-15, 0, -100>, <15, 50, 100>}
#declare building_windows[building_types] = box {<-99, 0, -87>, <99, 50, 87>}
#declare building_window_texture[building_types] = texture
{
	window_texture
	(
		texture {pigment {gamma_color_adjust(<1,1,1>*0)} finish {FGlass}},
		texture {pigment {gamma_color_adjust(<1, .9, .5>)} finish {ambient 1}},
		<15, 50, 0>
	)
	translate x * 25
}
#declare building_window_size[building_types] = <15, 50, 0>;
#declare building_details[building_types] = difference
{
	box {<-100, 0, -90>, <100, 50, 90>}
	#local X = 30;
	#while (X <= 90)
		box {<X - 5, 20, -91>, <X + 5, 40, 91>}
		box {<5 - X, 20, -91>, <-5 - X, 40, 91>}
		#local X = X + 15;
	#end
}
#declare building_base[building_types] = union
{
	object {building_details[building_types]}
	box {<-10, 0, -101>, <10, 40, 101> pigment {gamma_color_adjust(<1,1,1>*.4)} finish {FMetal}}
}
#local AirVent = union
{
	cylinder {<0, 0, 0>, <0, 25, 0>, 5}
	sphere {<0, 25, 0>, 6 scale <1.5, 1, 1.5>}
	pigment {gamma_color_adjust(<1,1,1>*.4)}
	finish {specular .4 metallic}
}
#declare building_roof[building_types] = union
{
	difference
	{
		box {<-102, 0, -102>, <102, 10, 102>}
		box {<-99, 5, -99>, <99, 11, 99>}
		pigment {gamma_color_adjust(<1,1,1>*.6)}
		normal {wrinkles .4 scale .2}
	}
	object {AirVent translate <-60, 5, -60>}
	object {AirVent translate <60, 5, -60>}
	object {AirVent translate <60, 5, 60>}
	object {AirVent translate <-60, 5, 60>}
}
#declare building_types = building_types + 1;

// APARTMENT BLOCK #2 (Red brick)
#declare building_options[building_types] = build_fit_texture + build_profile + build_window_levels + build_details + build_base + build_roof;
#declare building_size[building_types] = <20, 5, 20>;
#declare building_texture[building_types] = texture
{
	pigment {brick gamma_color_adjust(<1,1,1>*.5), gamma_color_adjust(<.6, .35, .15>) brick_size <1, .5, 1> mortar .05}
	normal {agate .1 scale .1}
}
#declare building_profile[building_types] = difference
{
	box {<-10, 0, -10>, <10, 5, 10>}
	box {<-6, -.1, -10.1>, <6, 5.1, 0>}
}
#declare building_windows[building_types] = difference
{
	box {<-10.01, 2, -10.01>, <10.01, 4.2, 10.01>}
	box {<-5.99, 1.9, -10.1>, <5.99, 4.3, -.01>}
}
#declare building_window_texture[building_types] = texture
{
	brick
	texture {pigment {gamma_color_adjust(<1,1,1,0,1>)}},
	texture
	{
		window_texture
		(
			texture {pigment {gamma_color_adjust(<1,1,1>*.1)} finish {FGlass reflection .2}},
			texture {pigment {gamma_color_adjust(<1,1,1>*.8)} finish {FGlass ambient 1}},
			<1.5, 0, 1.5>
		)
		translate <-.25, 0, .25>
	}
	brick_size <1.5, 5, 1.5> mortar .5 translate <1, 0, .25>
}
#declare building_window_size[building_types] = <1.5, 0, 1.5>;
#declare building_details[building_types] = union
{
	box {<-6, 0, -2>, <6, .2, 0>}
	box {<-6, .2, -1.8>, <6, 1.5, -1.6>}
	texture {Concrete}
}
#declare building_base[building_types] = union
{
	box
	{
		<-6, 0, -9.8>, <6, .01, 0>
		pigment {wrinkles color_map {[.4 gamma_color_adjust(<.4, .3, .1>)] [.7 gamma_color_adjust(<.4, .4, .2>)]} scale 4}
		normal {bumps .4 scale .1}
	}
	box {<-6, 0, -9.8>, <-1, 3, -9.5>}
	box {<1, 0, -9.8>, <6, 3, -9.5>}
}
#local AirVent = union
{
	box {<-3, 0, -2>, <3, 2, 2>}
	cylinder {<-2, 2, 0>, <-2, 10, 0>, .5 open}
	cylinder {<2, 2, 0>, <2, 6, 0>, .8 open}
	pigment {gamma_color_adjust(<1,1,1>*.4)}
	normal {dents .4}
	scale .5
}
#declare building_roof[building_types] = union
{
	difference
	{
		box {<-10.2, 0, -10.2>, <10.2, .5, 10.2>}
		box {<-5.8, -.1, -10.3>, <5.8, .6, -.2>}
		texture {Concrete}
	}
	object {AirVent translate <-6, .5, 6>}
	object {AirVent rotate -y*90 translate <8, .5, -6>}
}
#declare building_types = building_types + 1;
