// Desc: A bullet and tracer.
// Auth: Michael Horvath
// Home Page: http://www.geocities.com/Area51/Quadrant/3864/gearhead.htm
// This file is licensed under the terms of the CC-LGPL.

#declare Bullet_Material = material
{
	interior
	{
		media
		{
			emission rgbt <1,1/2,0,0,> * 20
			density
			{
				gradient y
				scale 8
				translate - 4
			}
//			intervals 50
		}

	}
	texture {pigment {color rgbt 1}}
}

#declare bullet = merge
{
	cone {<0,-4,0,>, 0, <0,3.9,0,>, 0.1}
	sphere {<0,3.9,0,>, 0.1}
	material {Bullet_Material}
	hollow
}

#ifndef (Included)
	light_source {<3000, 6000, -7000> rgb 1.3 parallel}
	default {finish {ambient .4 diffuse .7}}
	camera
	{
		orthographic
		location 	-z * 20
		direction	+z * 20
		up		y * 20
		right		x * image_width/image_height * 20
		rotate		x * 5
		rotate		y * 45
	}
	global_settings
	{
		radiosity
		{
			recursion_limit 1
			brightness 0.5
			count 100
			error_bound 0.5
			always_sample off
		}
		max_trace_level 24
	}
	sky_sphere
	{
		pigment
		{
			gradient y
			pigment_map
			{
				[0.00 rgb 1]
				[0.10 wrinkles color_map {[0.5 rgb 1] [0.7 rgb <0.4, 0.5, 0.6>]} scale 0.1]
				[0.15 wrinkles color_map {[0.1 rgb 1] [0.4 rgb <0.4, 0.5, 0.6>]} scale 0.1]
				[0.20 rgb <0.4, 0.5, 0.6>]
			}
		}
	}
	plane
	{
		-y, 0.02 hollow
		pigment {color rgbt 1/2}
	}
	object {bullet scale 1/4}
#end
