// INCLUDE DEFAULT OBJECTS FILE IF REQUIRED
#ifndef (building_size) #include "DEFAULT.OBJ" #end

// OFFICE BUILDING #1
#declare building_size[building_types] = <10, 2, 10>;	//<10, 2, 10>
#declare building_options[building_types] = build_window_profile + build_details + build_roof + build_texture;
#declare building_texture[building_types] = texture
{
	pigment {gamma_color_adjust(<.7, .76, .75>)}
	normal {bumps .3 scale .1}
}
#declare building_windows[building_types] = box
{
	<-4.9, 0, -4.9>, <4.9, 2, 4.9>
	interior {ior 2.5}
}
#local Glass = texture
{
	pigment {gamma_color_adjust(<1, 1, 1, 0, 1/2>)}
	normal {bumps .01 scale <.5, .1, .5>}
	finish {specular .2 roughness .1 reflection .5}
}
set_window_texture
(
	texture {Glass},
	texture {Glass finish {ambient 1}},
	<1, 2, 1>
)
#declare building_details[building_types] = difference
{
	box {<-5, 0, -5>, <5, 2, 5>}
	box {<-4.5, .5, -5.1>, <4.5, 1.8, 5.1>}
	box {<-5.1, .5, -4.5>, <5.1, 1.8, 4.5>}
	box {<-4.8, -.1, -4.8>, <4.8, 2.1, 4.8>}
}
#local AirVent = union
{
	cylinder
	{
		-z, z, 1
		clipped_by
		{
			box {<-1, 0, -1.1>, <1, 1, 1.1>}
		}
		scale <1, 1, 1.5>
		pigment {gamma_color_adjust(<.5, .5, .53>)}
		normal {gradient z bump_size .6 sine_wave scale .5 translate z*2}
	}
	cylinder
	{
		<0, 0, -1.5>, <0, 3, -1.5>, .2
		open
		pigment {gamma_color_adjust(<.5,.5,.5>)}
		finish {metallic}
	}
	translate <-3, .5, 2.5>
}
#declare building_roof[building_types] = union
{
	box {<-5.2, -.2, -5.2>, <5.2, .5, 5.2>}
//      object {AirVent} object {AirVent rotate y * 180}
}
#declare building_types = building_types + 1;

// OFFICE BUILDING #2
#declare building_size[building_types] = <2, .5, 2>;	// <2, .5, 2>
#declare building_options[building_types] = build_texture + build_profile + build_window_profile + build_details + build_roof;
#declare building_texture[building_types] = texture
{
	pigment {gamma_color_adjust(<.4,.4,.4>)}
	finish {metallic}
}
#declare building_profile[building_types] = union
{
	#local C = -.75;
	#while (C < 1) 
		box {<C-.01, 0, -1.01>, <C+.01, .5, 1.01>}
		box {<-1.01, 0, C-.01>, <1.01, .5, C+.01>}
		#local C = C + .25;
	#end
}
#declare building_windows[building_types] = box
{
	<-1, 0, -1>, <1, .5, 1>
}
#local Glass = texture
{
	pigment {gamma_color_adjust(<.5,.5,.5>)}
	normal {bumps .05 scale .6}
	finish {specular .5 roughness .1 reflection <.3, .4, .5>}
}
set_window_texture
(
	texture {Glass},
	texture {Glass finish {ambient 1}},
	<.25, .5, .25>
)
#declare building_details[building_types] = box
{
	<-1.02, 0, -1.02>, <1.02, .03, 1.02>
}
#declare building_roof[building_types] = union
{
	box {<-1.05, 0, -1.05>, <1.05, .05, 1.05>}
	object
	{
		building_windows[building_types]
		texture {building_window_texture[building_types]}
		scale .8
		rotate y*90
		translate y*.05
	}
	object
	{
		building_profile[building_types]
		scale .8
		rotate y*90
		translate y*.05
	}
	box {<-.85, .45, -.85>, <.85, .5, .85>}
}
#declare building_types = building_types + 1;
