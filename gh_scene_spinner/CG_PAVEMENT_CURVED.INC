// CITY OBJECTS
#local street_lamp = union
{
	object {cyl_macro(0, y*5, .10)}
	object {sph_macro(y*5, .15)}
	object {cyl_macro(y*5, <2, 6, 0>, .1)}
	
	object
	{
		sph_macro(0, .5)
		scale <.6, .2, .3>
		translate <2.2, 6, 0>
	}
	object
	{
		sph_macro(0, .5)
		scale <.58, .2, .28>
		translate <2.2, 5.98, 0>
		texture
		{
			pigment {gamma_color_adjust(<1, .9, .7>)}
			finish {ambient 1.3}
		}
		no_shadow
	}
	#if (traffic_night)
		spotlight_cone(<2.2, 6, 0>, .2, <2.2, 0, 0>, 3, gamma_color_adjust(<2, 1.8, 1.6, 0, .9>), 4)
	#end
	texture {lamp_texture}
	scale Meters
}

#local traffic_light = union
{
	object {cyl_macro(<0, 6, 0>, <4, 6, 0>, .05)}
	object {cyl_macro(<0, 5.6, 0>, <4, 5.6, 0>, .05)}
	difference
	{
		box {<4, 5.3, -.2>, <4.6, 6.3, .2>}
		object {sph_macro(<4.3, 5.5, -.2>, .1)	pigment {gamma_color_adjust(< 0, .6,.2>)}}
		object {sph_macro(<4.3, 5.8, -.2>, .1)	pigment {gamma_color_adjust(<.6, .4, 0>)}}
		object {sph_macro(<4.3, 6.1, -.2>, .1)	pigment {gamma_color_adjust(< 1, .2, 0>)}	finish {ambient 1.5 diffuse .5}}
		bounded_by {box {<4, 5.3, -.2>, <4.6, 6.3, .2>}}
	}
	#if (traffic_night)
		spotlight_cone(<4.3, 6.1, -.1>, .1, <4.3, 6.1, -.6>, .6, gamma_color_adjust(<1.5, .3, .1, 0, .8>), 2)
	#end
	texture {lamp_texture}
	scale Meters
}
#local traffic_union = union
{
	object
	{
		street_lamp
		rotate y * 45
	}
	object {traffic_light}
	object {traffic_light	rotate y * 90}
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
		pigment {gamma_color_adjust(<.7, .7, .7, 0, .3>)}		// missing finish!
	}
	box
	{
		<-1.5, .6, -1.5>, <-1, .65, 1.5>
		pigment {gamma_color_adjust(<.6, .3, .1>)}				// missing finish!
	}
	object
	{
		cyl_macro(0, y*3, .05)
		translate <-1.5, 0, -1.5>
	}
	object
	{
		cyl_macro(0, y*3, .05)
		translate <-1.5, 0, 1.5>
	}
	object
	{
		cyl_macro(0, y*3, .05)
		translate <0, 0, -1.5>
	}
	object
	{
		cyl_macro(0, y*3, .05)
		translate <0, 0, 1.5>
	}
	box
	{
		<-1.7, 3, -1.7>, <.4, 3.1, 1.7>
	}
	#if (traffic_night)
		spotlight_cone(<0, 3, 0>, 0, <0, 0, 0>, 1.5, gamma_color_adjust(<1.5, 1.4, 1.2, 0.0, 0.9>), 1.5)
	#end
	texture {metal_texture}
	scale Meters
}

// this stuff is not used any longer
#if (!NewTrain)
	#declare pavement_object = array[3]
	{
		object {traffic_union	scale 3/4	scale <1,2/3,1>	translate -x * 1/2},
		object {street_lamp	scale 3/4	scale <1,2/3,1>	translate -x * 1/2},
		object {bus_stop	scale 3/4			translate -x * 1/3},
	}
	#declare pavement_object_offset = array[3]
	{
		1/2,20,20
	}
	#declare pavement_object_spacing = array[3]
	{
		00,32,00
	}
	#declare pavement_object_turb = array[3]
	{
		00,00,32
	}
#else
	// streetlamps and pedestrians are now handled in CG_CITY_CURVED.INC instead of here
	#declare pavement_object = array[2]
	{
		"trash_can_macro",
		"potted_plant_macro"
	}
	#declare pavement_object_offset = array[2]
	{
		nominal_building_width/Meters/4+2, nominal_building_width/Meters/3
	}
	#declare pavement_object_spacing = array[2]
	{
		nominal_building_width/Meters, nominal_building_width/Meters
	}
	#declare pavement_object_turb = array[2]
	{
		0, 0
	}
#end
