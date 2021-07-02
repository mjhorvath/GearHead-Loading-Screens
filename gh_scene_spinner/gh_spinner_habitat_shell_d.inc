//------------------------------------------------------------------------------Shell Primitives

// smaller rings in end caps
#local cap_hub_r9_inn = cylinder {-z*metal_thick/2, +z*metal_thick/2, inner_shell_radius2}
#local cap_hub_r9 = cylinder {-z*metal_thick/2, +z*metal_thick/2, outer_shell_radius1*9/9}
#local cap_hub_r8 = cylinder {-z*metal_thick/2, +z*metal_thick/2, outer_shell_radius1*8/9}
#local cap_hub_r7 = cylinder {-z*metal_thick/2, +z*metal_thick/2, outer_shell_radius1*7/9}
#local cap_hub_r6 = cylinder {-z*metal_thick/2, +z*metal_thick/2, outer_shell_radius1*6/9}
#local cap_hub_r3 = cylinder {-z*metal_thick/2, +z*metal_thick/2, outer_shell_radius1*3/9}
#local cap_hub_r2 = cylinder {-z*metal_thick/2, +z*metal_thick/2, outer_shell_radius1*2/9}
#local cap_hub_r1 = cylinder {-z*metal_thick/2, +z*metal_thick/2, outer_shell_radius1*1/9}
#local cap_hub_r1_hlf = cylinder {0, +z*metal_thick*2, outer_shell_radius1*1/9}


//------------------------------------------------------------------------------Outer Shell

#local bevel_corner_radius = 0.1;
#local outer_shell_1 = cylinder {-z*(hab_section_length/2), +z*(hab_section_length/2), outer_shell_radius1}
#local outer_shell_2 = cylinder {-z*(hab_section_length/2-metal_thick), +z*(hab_section_length/2-metal_thick), outer_shell_radius2}
#local outer_shell_3 = cylinder {-z*(Meters*10000), +z*(Meters*10000), outer_shell_radius3}
#local outer_shell_4 = cylinder {-z*(hab_section_length/2), +z*(hab_section_length/2), outer_shell_radius3}
#local outer_shell_5 = cylinder {-z*(Meters*10000), +z*(Meters*10000), outer_shell_radius4}

#local outer_shell_group = union
{
	// outermost metal ring
	difference
	{
		object {outer_shell_1}
		object {outer_shell_2}
		object {outer_shell_3}
		#if (!ShowWhole)
			object {cutaway_object1}
		#end
		bounded_by {outer_shell_1}
		white_metal_texture()
	}
	// outermost rock ring
	difference
	{
		object {outer_shell_2}
		object {outer_shell_3}
		#if (!ShowWhole)
			object {cutaway_object1}
		#end
		bounded_by {outer_shell_2}
		steel_filling_texture()
	}
	// second metal ring
	difference
	{
		object {outer_shell_4}
		object {outer_shell_5}
		#if (!ShowWhole)
			object {cutaway_object1}
		#end
		bounded_by {outer_shell_4}
		white_metal_texture()
	}
}


//------------------------------------------------------------------------------Spiral "ramps"




//------------------------------------------------------------------------------Inner Shell & End Caps

// section letters
#local cap_letter_a = text {ttf "space age.ttf" "A" 1, 0}
#local cap_letter_b = text {ttf "space age.ttf" "B" 1, 0}
#local cap_letter_c = text {ttf "space age.ttf" "C" 1, 0}
#local cap_letter_d = text {ttf "space age.ttf" "D" 1, 0}
#local cap_letter_e = text {ttf "space age.ttf" "E" 1, 0}
#local cap_letter_f = text {ttf "space age.ttf" "F" 1, 0}
#local letter_cutout_front = union
{
	object
	{
		cap_letter_a
		Center_Trans(cap_letter_a, x)
		Center_Trans(cap_letter_a, y)
		Center_Trans(cap_letter_a, z)
		scale <outer_shell_radius1/10,outer_shell_radius1/10,Meters*10000>
		translate -y*outer_shell_radius1*1.5/9
		rotate z * 060
	}
	object
	{
		cap_letter_b
		Center_Trans(cap_letter_b, x)
		Center_Trans(cap_letter_b, y)
		Center_Trans(cap_letter_b, z)
		scale <outer_shell_radius1/10,outer_shell_radius1/10,Meters*10000>
		translate -y*outer_shell_radius1*1.5/9
		rotate z * 120
	}
	object
	{
		cap_letter_c
		Center_Trans(cap_letter_c, x)
		Center_Trans(cap_letter_c, y)
		Center_Trans(cap_letter_c, z)
		scale <outer_shell_radius1/10,outer_shell_radius1/10,Meters*10000>
		translate -y*outer_shell_radius1*1.5/9
		rotate z * 180
	}
	object
	{
		cap_letter_d
		Center_Trans(cap_letter_d, x)
		Center_Trans(cap_letter_d, y)
		Center_Trans(cap_letter_d, z)
		scale <outer_shell_radius1/10,outer_shell_radius1/10,Meters*10000>
		translate -y*outer_shell_radius1*1.5/9
		rotate z * 240
	}
	object
	{
		cap_letter_e
		Center_Trans(cap_letter_e, x)
		Center_Trans(cap_letter_e, y)
		Center_Trans(cap_letter_e, z)
		scale <outer_shell_radius1/10,outer_shell_radius1/10,Meters*10000>
		translate -y*outer_shell_radius1*1.5/9
		rotate z * 300
	}
	object
	{
		cap_letter_f
		Center_Trans(cap_letter_f, x)
		Center_Trans(cap_letter_f, y)
		Center_Trans(cap_letter_f, z)
		scale <outer_shell_radius1/10,outer_shell_radius1/10,Meters*10000>
		translate -y*outer_shell_radius1*1.5/9
		rotate z * 360
	}
	rotate -z * 90
	rotate +z * hab_cap_nudge_angle
}
#local letter_cutout_back = union
{
	object
	{
		cap_letter_a
		Center_Trans(cap_letter_a, x)
		Center_Trans(cap_letter_a, y)
		Center_Trans(cap_letter_a, z)
		scale <outer_shell_radius1/10,outer_shell_radius1/10,Meters*10000>
		translate -y*outer_shell_radius1*1.5/9
		rotate y * 180
		rotate z * 060
	}
	object
	{
		cap_letter_b
		Center_Trans(cap_letter_b, x)
		Center_Trans(cap_letter_b, y)
		Center_Trans(cap_letter_b, z)
		scale <outer_shell_radius1/10,outer_shell_radius1/10,Meters*10000>
		translate -y*outer_shell_radius1*1.5/9
		rotate y * 180
		rotate z * 120
	}
	object
	{
		cap_letter_c
		Center_Trans(cap_letter_c, x)
		Center_Trans(cap_letter_c, y)
		Center_Trans(cap_letter_c, z)
		scale <outer_shell_radius1/10,outer_shell_radius1/10,Meters*10000>
		translate -y*outer_shell_radius1*1.5/9
		rotate y * 180
		rotate z * 180
	}
	object
	{
		cap_letter_d
		Center_Trans(cap_letter_d, x)
		Center_Trans(cap_letter_d, y)
		Center_Trans(cap_letter_d, z)
		scale <outer_shell_radius1/10,outer_shell_radius1/10,Meters*10000>
		translate -y*outer_shell_radius1*1.5/9
		rotate y * 180
		rotate z * 240
	}
	object
	{
		cap_letter_e
		Center_Trans(cap_letter_e, x)
		Center_Trans(cap_letter_e, y)
		Center_Trans(cap_letter_e, z)
		scale <outer_shell_radius1/10,outer_shell_radius1/10,Meters*10000>
		translate -y*outer_shell_radius1*1.5/9
		rotate y * 180
		rotate z * 300
	}
	object
	{
		cap_letter_f
		Center_Trans(cap_letter_f, x)
		Center_Trans(cap_letter_f, y)
		Center_Trans(cap_letter_f, z)
		scale <outer_shell_radius1/10,outer_shell_radius1/10,Meters*10000>
		translate -y*outer_shell_radius1*1.5/9
		rotate y * 180
		rotate z * 360
	}
	rotate -z * 90
	rotate +z * hab_cap_nudge_angle
}
#local bevel_cutout = union
{
	// corner circles
	#local section_max = 3;
	#local section_cnt = 0;
	#while (section_cnt < section_max)
		union
		{
			cylinder {<-0.1813054868515130, 0.653078124336531, -1>, <-0.1813054868515130, 0.653078124336531, +1>, bevel_corner_radius}
			cylinder {<+0.6562349897570840, 0.169523904709349, -1>, <+0.6562349897570840, 0.169523904709349, +1>, bevel_corner_radius}
			cylinder {<-0.0332338479561477, 0.320503778205273, -1>, <-0.0332338479561477, 0.320503778205273, +1>, bevel_corner_radius}
			cylinder {<+0.2941813379127340, 0.131470532507103, -1>, <+0.2941813379127340, 0.131470532507103, +1>, bevel_corner_radius}
			rotate +z * section_cnt * 360/section_max
		}
		#local section_cnt = section_cnt + 1;
	#end
	difference
	{
		#local out_cyl = cylinder {-z*1, +z*1, 7/9}
		object {out_cyl}
		cylinder {-z*2, +z*2, 0.670360139066595}
		union
		{
			#local section_max = 3;
			#local section_cnt = 0;
			#while (section_cnt < section_max)
				intersection
				{
					plane {+y, 0    rotate +z * 14.4844497413763}
					plane {-y, 0    rotate -z * 14.4844497413763}
					rotate +z * section_cnt * 360/section_max
					bounded_by {out_cyl}
				}
				#local section_cnt = section_cnt + 1;
			#end
		}
		bounded_by {out_cyl}
	}
	difference
	{
		#local out_cyl = cylinder {-z*1, +z*1, 0.670360139066595 * 1.001}
		object {out_cyl}
		cylinder {-z*2, +z*2, 0.306312194490894 * 0.999}
		union
		{
			#local section_max = 3;
			#local section_cnt = 0;
			#while (section_cnt < section_max)
				intersection
				{
					plane {+y, 0    rotate +z * 6}
					plane {-y, 0    rotate -z * 6}
					rotate +z * section_cnt * 360/section_max
					bounded_by {out_cyl}
				}
				#local section_cnt = section_cnt + 1;
			#end
		}
		bounded_by {out_cyl}
	}
	difference
	{
		#local out_cyl = cylinder {-z*1, +z*1, 0.306312194490894}
		object {out_cyl}
		cylinder {-z*2, +z*2, 2/9}
		union
		{
			#local section_max = 3;
			#local section_cnt = 0;
			#while (section_cnt < section_max)
				intersection
				{
					plane {+y, 0    rotate +z * 24.0800126244252}
					plane {-y, 0    rotate -z * 24.0800126244252}
					rotate +z * section_cnt * 360/section_max
					bounded_by {out_cyl}
				}
				#local section_cnt = section_cnt + 1;
			#end
		}
		bounded_by {out_cyl}
	}
	scale outer_shell_radius1
	rotate -z * 90
	rotate +z * hab_cap_nudge_angle
}
#local inner_shell_1 = cylinder {-z*(city_length/2), +z*(city_length/2), inner_shell_radius1}
#local inner_shell_2 = cylinder {-z*(city_length/2+Meters*1000), +z*(city_length/2+Meters*1000), inner_shell_radius2}
#local inner_shell_3 = cylinder {-z*(city_length/2), +z*(city_length/2), inner_shell_radius2}
#local inner_shell_4 = cylinder {-z*(Meters*10000), +z*(Meters*10000), inner_shell_radius3}
#local bevel_shell_1 = Spheroid(+z*(city_length/2), <inner_shell_radius1,inner_shell_radius1,inner_shell_bulge+inner_rock_thick+metal_thick>)
#local bevel_shell_2 = Spheroid(+z*(city_length/2), <inner_shell_radius2,inner_shell_radius2,inner_shell_bulge+inner_rock_thick>)
#local bevel_shell_3 = Spheroid(+z*(city_length/2), <inner_shell_radius3,inner_shell_radius3,inner_shell_bulge>)
#local glass_shell_1 = Spheroid(+z*(city_length/2), <inner_shell_radius2+metal_thick/2,inner_shell_radius2+metal_thick/2,inner_shell_bulge+inner_rock_thick+ext_glass_thick/2>)
#local glass_shell_2 = Spheroid(+z*(city_length/2), <inner_shell_radius2-metal_thick/2,inner_shell_radius2-metal_thick/2,inner_shell_bulge+inner_rock_thick-ext_glass_thick/2>)
#local inner_end_gear = object
{
	cap_hub_r1
	translate +z*metal_thick/2
	scale +z * 2
}
#local inner_shell_group = union
{
	// white metal endcap #1
	difference
	{
		object {bevel_shell_1}
		object {bevel_shell_2}
		plane {+z, (city_length/2)}
		object {bevel_cutout    translate +z * (hab_section_length/2)}
		object {bevel_cutout    translate -z * (hab_section_length/2)}
		#if (!ShowWhole)
			object {cutaway_object1}
		#end
		white_metal_texture()
		bounded_by {bevel_shell_1}
	}
	// blue metal endcap #1
	difference
	{
		object {bevel_shell_2}
		object {bevel_shell_3}
		plane {+z, (city_length/2)}
		object {bevel_cutout    translate +z * (hab_section_length/2)}
		object {bevel_cutout    translate -z * (hab_section_length/2)}
		object {letter_cutout_front	translate +z*(hab_section_length/2)}
//		object {letter_cutout_back	translate -z*(hab_section_length/2)}
		#if (!ShowWhole)
			object {cutaway_object1}
		#end
		sky_texture_a()
		bounded_by {bevel_shell_2}
	}
	// glass endcap #1
	difference
	{
		object {glass_shell_1}
		object {glass_shell_2}
		plane {+z, (city_length/2)}
		object {letter_cutout_front	translate +z*(hab_section_length/2)}
//		object {letter_cutout_back	translate -z*(hab_section_length/2)}
		#if (!ShowWhole)
			object {cutaway_object1}
		#end
		dome_material()
		bounded_by {glass_shell_1}
	}
	// white metal endcap #2
	difference
	{
		object {bevel_shell_1		rotate y * 180}
		object {bevel_shell_2		rotate y * 180}
		plane {-z, (city_length/2)}
		object {bevel_cutout    translate +z * (hab_section_length/2)}
		object {bevel_cutout    translate -z * (hab_section_length/2)}
		#if (!ShowWhole)
			object {cutaway_object1}
		#end
		white_metal_texture()
		bounded_by {bevel_shell_1		rotate y * 180}
	}
	// blue metal endcap #2
	difference
	{
		object {bevel_shell_2		rotate y * 180}
		object {bevel_shell_3		rotate y * 180}
		plane {-z, (city_length/2)}
		object {bevel_cutout    translate +z * (hab_section_length/2)}
		object {bevel_cutout    translate -z * (hab_section_length/2)}
//		object {letter_cutout_front	translate +z*(hab_section_length/2)}
		object {letter_cutout_back	translate -z*(hab_section_length/2)}
		#if (!ShowWhole)
			object {cutaway_object1}
		#end
		sky_texture_a()
		bounded_by {bevel_shell_2		rotate y * 180}
	}
	// glass endcap #2
	difference
	{
		object {glass_shell_1		rotate y * 180}
		object {glass_shell_2		rotate y * 180}
		plane {-z, (city_length/2)}
//		object {letter_cutout_front	translate +z*(hab_section_length/2)}
		object {letter_cutout_back	translate -z*(hab_section_length/2)}
		#if (!ShowWhole)
			object {cutaway_object1}
		#end
		dome_material()
		bounded_by {glass_shell_1		rotate y * 180}
	}
	// inner shell
	difference
	{
		object {inner_shell_1}
		object {inner_shell_2}
		#if (!ShowWhole)
			object {cutaway_object1}
		#end
		white_metal_texture()
		bounded_by {inner_shell_1}
	}
	// inner rock layer
	difference
	{
		object {inner_shell_3}
		object {inner_shell_4}
		#if (!ShowWhole)
			object {cutaway_object1}
		#end
		rock_filling_texture()
		bounded_by {inner_shell_3}
	}
	// end gear
	union
	{
		object
		{
			cap_hub_r1_hlf
			sky_texture_a()
		}
		object
		{
			cap_hub_r1_hlf
			rotate +y * 180
			white_metal_texture()
		}
		translate -z*(city_length/2+inner_shell_bulge+inner_rock_thick)
	}
	union
	{
		object
		{
			cap_hub_r1_hlf
			rotate +y * 180
			sky_texture_a()
		}
		object
		{
			cap_hub_r1_hlf
			white_metal_texture()
		}
		translate +z*(city_length/2+inner_shell_bulge+inner_rock_thick)
	}
}


//------------------------------------------------------------------------------Atmosphere

// very slowwww!!! hasn't been updated in a long while
/*
#local atmos_material = material
{
	// check TexQual here?
	texture {pigment {gamma_color_adjust(1) transmit 1}}
	interior
	{
		media
		{
			scattering
			{ 
				4, color rgb <0.2,0.4,1.0>/10000	// crappy approximaion of TerraPOV value
				extinction	1
			}
			samples	1,1
			density
			{
				cylindrical
				poly_wave	0.25
				color_map
				{
					[0	srgb 1.0]
					[1	srgb 0.0]
				}
			}
		}
	}
	scale	city_radius
	rotate	x * 90
}
*/

// would be nice if the density were slightly less in the middle too
#macro atmos_material()
	material
	{
		texture {pigment {color rgbt 1}}
		interior
		{
			media
			{
				scattering
				{
					#if (SimpleLamp = true)
						4, rgb <0.2,0.4,1.0>/20000		// works well with single point light
					#else
						4, rgb <0.2,0.4,1.0>/20000000		// needed for when using an area light for whatever reason
					#end
					extinction	1
				}
				samples	10
			}
		}
	}
#end

#local atmos_object = difference
{
	merge
	{
		cylinder {+z*(city_length/2), -z*(city_length/2), city_radius}
		Spheroid(+z*(city_length/2), <inner_shell_radius3,inner_shell_radius3,inner_shell_bulge>)
		Spheroid(-z*(city_length/2), <inner_shell_radius3,inner_shell_radius3,inner_shell_bulge>)
		hollow
	}
	#if (!ShowWhole)
		object {cutaway_object1}
	#end
	hollow
	atmos_material()
	bounded_by {cylinder {+z*(city_length/2+inner_shell_bulge), -z*(city_length/2+inner_shell_bulge), city_radius}}
	scale 1.001
}


//------------------------------------------------------------------------------Lamp

#include "gh_spinner_habitat_lamp_c.inc"


//------------------------------------------------------------------------------Spindles, no longer used

#local spindle_arm = cylinder
{
	0, +y*inner_shell_radius2, Meters*2
}
#local spindle_hub = union
{
	difference
	{
		union
		{
			object {spindle_arm rotate z * 000}
			object {spindle_arm rotate z * 090}
			object {spindle_arm rotate z * 180}
			object {spindle_arm rotate z * 270}
		}
		cylinder {-z*city_radius, +z*city_radius, Meters * 16}
	}
	torus
	{
		Meters * 16, Meters*2
		rotate x * 90
	}
	rotate +z * 045
	white_metal_texture()
}


//------------------------------------------------------------------------------Body Trusses

// cylindrical trusses around habitat
#local outer_shell_truss = difference
{
	#declare truss_sides = 24;
	#declare truss_sections = 8;
	#declare truss_thickness = big_truss_thick;
	#declare truss_radius = outer_shell_radius1 * sqrt(pow(tand(360/2/truss_sides),2) + 1) - truss_thickness;
	#declare truss_point1 = -z*(hab_section_length/2);
	#declare truss_point2 = +z*(hab_section_length/2);
	object {#include "truss.inc"}
	#if (!ShowWhole)
		object {cutaway_object1}
	#end
	white_metal_texture()
	bounded_by {cylinder {-z*(hab_section_length/2 + truss_thickness), +z*(hab_section_length/2 + truss_thickness), outer_shell_radius1 * sqrt(pow(tand(360/2/truss_sides),2) + 1)}}
}


//------------------------------------------------------------------------------Sum total habitat section

#if (BothHabitats)
	union
	{
		object {outer_shell_truss}
		object {outer_shell_group}
		object {inner_shell_group}
		#if (!NoSpindle)
			object {spindle_hub}
		#end
		#if (!NoLampObject)
			object {lamp_object}
		#end
		#if (!NoAtmos)
			object {atmos_object}
		#end
		#if (!NoHabRotate)
			rotate -z * city_rotate
		#end
		translate -z * hab_section_offset
	}
#end

union
{
	object {outer_shell_truss}
	object {outer_shell_group}
	object {inner_shell_group}
	#if (!NoSpindle)
		object {spindle_hub}
	#end
	#if (!NoLampObject)
		object {lamp_object}
	#end
	#if (!NoAtmos)
		object {atmos_object}
	#end
	#if (!NoHabRotate)
		rotate +z * city_rotate
	#end
	translate +z * hab_section_offset
}
