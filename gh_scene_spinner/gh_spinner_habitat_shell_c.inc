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


//------------------------------------------------------------------------------Outer Shell

#local bevel_corner_radius = 0.1;
#local outer_shell_1 = cylinder
{
	-z*(hab_section_length/2), +z*(hab_section_length/2), outer_shell_radius1
}
#local outer_shell_2 = cylinder
{
	-z*(hab_section_length/2-metal_thick), +z*(hab_section_length/2-metal_thick), outer_shell_radius2
}
#local outer_shell_3 = cylinder
{
	-z*(Meters*10000), +z*(Meters*10000), outer_shell_radius3
}
#local outer_shell_4 = cylinder
{
	-z*(hab_section_length/2-metal_thick), +z*(hab_section_length/2-metal_thick), outer_shell_radius3
}
#local outer_shell_5 = cylinder
{
	-z*(Meters*10000), +z*(Meters*10000), outer_shell_radius4
}
#local outer_end_bevel = union
{
	difference
	{
		object {cap_hub_r9}
		object {cap_hub_r7    scale 1.0001}
	}
	difference
	{
		object {cap_hub_r2}
		object {cap_hub_r1    scale 1.0001}
	}
}
#local outer_end_glass = difference
{
	object {cap_hub_r7}
	object {cap_hub_r2    scale 1.0001}
	scale +z * 1/16
}
#local outer_end_gear = object
{
	cap_hub_r1
	scale +z * 4
}
#local outer_cutout = union
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
		cylinder {-z*1, +z*1, 7/9}
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
				}
				#local section_cnt = section_cnt + 1;
			#end
		}
	}
	difference
	{
		cylinder {-z*1, +z*1, 0.670360139066595 * 1.001}
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
				}
				#local section_cnt = section_cnt + 1;
			#end
		}
	}
	difference
	{
		cylinder {-z*1, +z*1, 0.306312194490894}
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
				}
				#local section_cnt = section_cnt + 1;
			#end
		}
	}
	scale outer_shell_radius1
	rotate -z * 30
}

#declare outer_shell_group = union
{
	// outermost metal ring
	difference
	{
		union
		{
			difference
			{
				object {outer_shell_1}
				object {outer_shell_2}
			}
			difference
			{
				object {outer_shell_4}
				object {outer_shell_5}
			}
		}
		object {outer_cutout    translate +z * hab_section_length/2}
		object {outer_cutout    translate -z * hab_section_length/2}
		#if (!ShowWhole)
			object {cutaway_object1}
		#end
		texture {white_metal_texture}
	}
	// outermost rock ring
	difference
	{
		object {outer_shell_2}
		object {outer_shell_3}
		#if (!ShowWhole)
			object {cutaway_object1}
		#end
		texture {steel_filling_texture}
	}
	// end cap bevel
	difference
	{
		union
		{
			object
			{
				outer_end_bevel
				rotate +y * 180
				translate -z*(hab_section_length/2+metal_thick/2)
			}
			object
			{
				outer_end_bevel
				translate +z*(hab_section_length/2+metal_thick/2)
			}
		}
		#if (!ShowWhole)
			object {cutaway_object1}
		#end
		texture {white_metal_texture}
	}
	// end cap glass
	difference
	{
		union
		{
			object
			{
				outer_end_glass
				rotate +y * 180
				translate -z*(hab_section_length/2-metal_thick/2)
			}
			object
			{
				outer_end_glass
				translate +z*(hab_section_length/2-metal_thick/2)
			}
		}
		#if (!ShowWhole)
			object {cutaway_object1}
		#end
		texture {dome_texture}
	}
	// end gear
	union
	{
		object
		{
			outer_end_gear
			translate -z*(hab_section_length/2-metal_thick/2)
		}
		object
		{
			outer_end_gear
			translate +z*(hab_section_length/2-metal_thick/2)
		}
		texture {white_metal_texture}
	}
}

//------------------------------------------------------------------------------Inner Shell & End Caps

#local inner_shell_1 = cylinder
{
	-z*(city_length/2+metal_thick*3), +z*(city_length/2+metal_thick*3), inner_shell_radius1
}
#local inner_shell_2 = cylinder
{
	-z*(city_length/2+metal_thick*2), +z*(city_length/2+metal_thick*2), inner_shell_radius2
}
#local inner_shell_3 = cylinder
{
	-z*(city_length/2), +z*(city_length/2), inner_shell_radius2
}
#local inner_shell_4 = cylinder
{
	-z*(Meters*10000), +z*(Meters*10000), inner_shell_radius3
}
// end bevels
#local inner_end_bevel = union
{
	difference
	{
		object {cap_hub_r9_inn}
		object {cap_hub_r7	scale 1.0001}
	}
	difference
	{
		object {cap_hub_r2}
		object {cap_hub_r1	scale 1.0001}
	}
	cylinder
	{
		-z*metal_thick/2,+z*metal_thick/2,inner_shell_radius2
		translate +z * metal_thick
	}
	translate -z * metal_thick/2
}
// inner lozenge cutout 2
#local cap_cutout_2a = cylinder
{
	-z*Meters*10000, +z*Meters*10000, window_radius
	translate -y * outer_shell_radius2/2
}
#local cap_cutout_2b = union
{
	object {cap_cutout_2a    rotate z * 000}
	object {cap_cutout_2a    rotate z * 060}
	object {cap_cutout_2a    rotate z * 120}
	object {cap_cutout_2a    rotate z * 180}
	object {cap_cutout_2a    rotate z * 240}
	object {cap_cutout_2a    rotate z * 300}
}
// inner lozenge glass 2
#local cap_glass_2a = difference
{
	sphere
	{
		0, window_radius*0.999
		scale z * 4/8
	}
	sphere
	{
		0, window_radius*0.999
		scale z * 4/8
		scale 15/16
	}
	plane {-z,0}
	translate -y * outer_shell_radius2/2
}
#local cap_glass_2b = union
{
	object {cap_glass_2a    rotate z * 000}
	object {cap_glass_2a    rotate z * 060}
	object {cap_glass_2a    rotate z * 120}
	object {cap_glass_2a    rotate z * 180}
	object {cap_glass_2a    rotate z * 240}
	object {cap_glass_2a    rotate z * 300}
}

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
		scale <outer_shell_radius1/6,outer_shell_radius1/6,Meters>
		translate -y*outer_shell_radius1*2/3
		rotate z * 330
	}
	object
	{
		cap_letter_b
		Center_Trans(cap_letter_b, x)
		Center_Trans(cap_letter_b, y)
		Center_Trans(cap_letter_b, z)
		scale <outer_shell_radius1/6,outer_shell_radius1/6,Meters>
		translate -y*outer_shell_radius1*2/3
		rotate z * 030
	}
	object
	{
		cap_letter_c
		Center_Trans(cap_letter_c, x)
		Center_Trans(cap_letter_c, y)
		Center_Trans(cap_letter_c, z)
		scale <outer_shell_radius1/6,outer_shell_radius1/6,Meters>
		translate -y*outer_shell_radius1*2/3
		rotate z * 090
	}
	object
	{
		cap_letter_d
		Center_Trans(cap_letter_d, x)
		Center_Trans(cap_letter_d, y)
		Center_Trans(cap_letter_d, z)
		scale <outer_shell_radius1/6,outer_shell_radius1/6,Meters>
		translate -y*outer_shell_radius1*2/3
		rotate z * 150
	}
	object
	{
		cap_letter_e
		Center_Trans(cap_letter_e, x)
		Center_Trans(cap_letter_e, y)
		Center_Trans(cap_letter_e, z)
		scale <outer_shell_radius1/6,outer_shell_radius1/6,Meters>
		translate -y*outer_shell_radius1*2/3
		rotate z * 210
	}
	object
	{
		cap_letter_f
		Center_Trans(cap_letter_f, x)
		Center_Trans(cap_letter_f, y)
		Center_Trans(cap_letter_f, z)
		scale <outer_shell_radius1/6,outer_shell_radius1/6,Meters>
		translate -y*outer_shell_radius1*2/3
		rotate z * 270
	}
}
#local letter_cutout_back = union
{
	object
	{
		cap_letter_a
		Center_Trans(cap_letter_a, x)
		Center_Trans(cap_letter_a, y)
		Center_Trans(cap_letter_a, z)
		scale <outer_shell_radius1/6,outer_shell_radius1/6,Meters>
		translate -y*outer_shell_radius1*2/3
		rotate y * 180
		rotate z * 330
	}
	object
	{
		cap_letter_b
		Center_Trans(cap_letter_b, x)
		Center_Trans(cap_letter_b, y)
		Center_Trans(cap_letter_b, z)
		scale <outer_shell_radius1/6,outer_shell_radius1/6,Meters>
		translate -y*outer_shell_radius1*2/3
		rotate y * 180
		rotate z * 030
	}
	object
	{
		cap_letter_c
		Center_Trans(cap_letter_c, x)
		Center_Trans(cap_letter_c, y)
		Center_Trans(cap_letter_c, z)
		scale <outer_shell_radius1/6,outer_shell_radius1/6,Meters>
		translate -y*outer_shell_radius1*2/3
		rotate y * 180
		rotate z * 090
	}
	object
	{
		cap_letter_d
		Center_Trans(cap_letter_d, x)
		Center_Trans(cap_letter_d, y)
		Center_Trans(cap_letter_d, z)
		scale <outer_shell_radius1/6,outer_shell_radius1/6,Meters>
		translate -y*outer_shell_radius1*2/3
		rotate y * 180
		rotate z * 150
	}
	object
	{
		cap_letter_e
		Center_Trans(cap_letter_e, x)
		Center_Trans(cap_letter_e, y)
		Center_Trans(cap_letter_e, z)
		scale <outer_shell_radius1/6,outer_shell_radius1/6,Meters>
		translate -y*outer_shell_radius1*2/3
		rotate y * 180
		rotate z * 210
	}
	object
	{
		cap_letter_f
		Center_Trans(cap_letter_f, x)
		Center_Trans(cap_letter_f, y)
		Center_Trans(cap_letter_f, z)
		scale <outer_shell_radius1/6,outer_shell_radius1/6,Meters>
		translate -y*outer_shell_radius1*2/3
		rotate y * 180
		rotate z * 270
	}
}

#declare inner_shell_group = union
{
	// inner shell
	difference
	{
		object {inner_shell_1}
		object {inner_shell_2}
		object {cap_cutout_2b    translate +z*(hab_section_length/2)}
		object {cap_cutout_2b    translate -z*(hab_section_length/2)}
		#if (!ShowWhole)
			object {cutaway_object1}
		#end
		texture {white_metal_texture}
	}
	// end cap bevel
	difference
	{
		union
		{
			object
			{
				inner_end_bevel
				translate +z*(city_length/2+metal_thick)
			}
			object
			{
				inner_end_bevel
				rotate +y * 180
				translate -z*(city_length/2+metal_thick)
			}
		}
		union
		{
			object
			{
				letter_cutout_front
				translate +z*(city_length/2+metal_thick)
			}
			object
			{
				letter_cutout_back
				translate -z*(city_length/2+metal_thick)
			}
			texture {white_metal_texture}
		}
		object {cap_cutout_2b    translate +z*(hab_section_length/2)}
		object {cap_cutout_2b    translate -z*(hab_section_length/2)}
		#if (!ShowWhole)
			object {cutaway_object1}
		#end
		texture {sky_texture_a}
	}
	// inner rock layer
	difference
	{
		object {inner_shell_3}
		object {inner_shell_4}
		#if (!ShowWhole)
			object {cutaway_object1}
		#end
		texture {rock_filling_texture}
	}
	// end glass bubbles
	difference
	{
		union
		{
			object
			{
				cap_glass_2b
				translate +z*(city_length/2+metal_thick)
			}
			object
			{
				cap_glass_2b
				rotate +y * 180
				translate -z*(city_length/2+metal_thick)
			}
		}
		#if (!ShowWhole)
			object {cutaway_object1}
		#end
		texture {dome_texture}
	}
}


//------------------------------------------------------------------------------Lamp

// double check if cylindrical is set up correctly
#local lamp_material = material
{
	#switch (TexQual)
		#case (-1)
			lowqual_tex(Seed)
		#break
		#case (0)
			texture {pigment {gamma_color_adjust(lamp_color)}}
		#break
		#case (1)
		#case (2)
			texture
			{
				pigment {gamma_color_adjust(lamp_color) transmit 1}
                finish
				{
					diffuse 0.1
					reflection 0.2
                    specular 0.8
					roughness 0.0003
					phong 1
					phong_size 400
				}
			}
			interior
			{
				media
				{
					emission gamma_color_adjust(lamp_color)
					density
					{
						cylindrical
						color_map
						{
							[0 srgb 0]
							[1 srgb 2/3]
						}
						scale	lamp_radius
						rotate	x * 90
					}
				}
			}
		#break
	#end
}
#declare lamp_object = object
{
	cylinder {z*-(lamp_length/2), z*+(lamp_length/2), lamp_radius}
	material {lamp_material}
	hollow
	scale	0.9999
	no_shadow
}


//------------------------------------------------------------------------------Spindles

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
	texture {white_metal_texture}
}


//------------------------------------------------------------------------------Sum total habitat section

union
{
	object {outer_shell_group}
	object {inner_shell_group	rotate -z * city_rotate}
	#if (!NoSpindle)
		object {spindle_hub	rotate -z * city_rotate}
	#end
	#if (!NoLampLight)
		light_source
		{
			0, gamma_color_adjust(light_color)
			#if (!NoAreaLight)
				area_light z*lamp_length/2, y, lamp_number, 1
			#end
			#if (!NoLampObject)
				looks_like {lamp_object}
			#end
		}
	#else
		#if (!NoLampObject)
			object {lamp_object}
		#end
	#end
	translate -z * hab_section_offset
}

union
{
	object {outer_shell_group}
	object {inner_shell_group	rotate +z * city_rotate}
	#if (!NoSpindle)
		object {spindle_hub	rotate +z * city_rotate}
	#end
	#if (!NoLampLight)
		light_source
		{
			0, gamma_color_adjust(light_color)
			#if (!NoAreaLight)
				area_light z*lamp_length/2, y, lamp_number, 1
			#end
			#if (!NoLampObject)
				looks_like {lamp_object}
			#end
		}
	#else
		#if (!NoLampObject)
			object {lamp_object}
		#end
	#end
	translate +z * hab_section_offset
}

//------------------------------------------------------------------------------Body Trusses

#if (!NoHabitat)
	difference
	{
		// cylindrical trusses around habitat
		#declare truss_sides = 24;
		#declare truss_sections = 16;
		#declare truss_thickness = big_truss_thick;
		#declare truss_radius = outer_shell_radius1 * sqrt(pow(tand(360/2/truss_sides),2) + 1) - truss_thickness;
		#declare truss_point1 = -z*hab_total_length/2;
		#declare truss_point2 = +z*hab_total_length/2;
		object {#include "truss.inc"}
		#if (!ShowWhole)
			object {cutaway_object1}
		#end
		texture {white_metal_texture}
	}
#end
