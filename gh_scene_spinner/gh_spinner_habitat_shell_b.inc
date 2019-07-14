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
	-z*(habitat_length/2), +z*(habitat_length/2), outer_shell_radius1
}
#local outer_shell_2 = cylinder
{
	-z*(habitat_length/2-metal_thick), +z*(habitat_length/2-metal_thick), outer_shell_radius2
}
#local outer_shell_3 = cylinder
{
	-z*(Meters*10000), +z*(Meters*10000), outer_shell_radius3
}
#local outer_shell_4 = cylinder
{
	-z*(habitat_length/2-metal_thick), +z*(habitat_length/2-metal_thick), outer_shell_radius3
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
#local outer_cutout = union
{
	#local section_max = 6;
	#local section_cnt = 0;
	#while (section_cnt < section_max)
		union
		{
			cylinder {<-0.1813054868515130, 0.653078124336531, -1>, <-0.1813054868515130, 0.653078124336531, +1>, bevel_corner_radius}
			cylinder {<+0.1813054868515130, 0.653078124336531, -1>, <+0.1813054868515130, 0.653078124336531, +1>, bevel_corner_radius}
			cylinder {<-0.0332338479561477, 0.320503778205273, -1>, <-0.0332338479561477, 0.320503778205273, +1>, bevel_corner_radius}
			cylinder {<+0.0332338479561477, 0.320503778205273, -1>, <+0.0332338479561477, 0.320503778205273, +1>, bevel_corner_radius}
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
			#local section_max = 6;
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
		cylinder {-z*1, +z*1, 0.670360139066595}
		cylinder {-z*2, +z*2, 0.306312194490894}
		union
		{
			#local section_max = 6;
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
			#local section_max = 6;
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
    translate +z*(habitat_length/2 + Meters * 4)
}

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
	object {outer_cutout}
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
		translate -z * metal_thick
	}
	translate +z * metal_thick/2
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

// inner shell
difference
{
	object {inner_shell_1}
	object {inner_shell_2}
	object {cap_cutout_2b    translate +z*(habitat_length/2)}
	object {cap_cutout_2b    translate -z*(habitat_length/2)}
	#if (!ShowWhole)
		object {cutaway_object1}
	#end
	texture {white_metal_texture}
	rotate +z * city_rotate
}

// end cap bevel
difference
{
	union
	{
		object
		{
			inner_end_bevel
			translate -z*(city_length/2+metal_thick)
		}
		object
		{
			inner_end_bevel
			rotate +y * 180
			translate +z*(city_length/2+metal_thick)
		}
	}
	union
	{
		object
		{
			letter_cutout_front
			translate +z*(city_length/2+Meters*4)
		}
		object
		{
			letter_cutout_back
			translate -z*(city_length/2+Meters*4)
		}
		texture {white_metal_texture}
	}
	object {cap_cutout_2b    translate +z*(habitat_length/2)}
	object {cap_cutout_2b    translate -z*(habitat_length/2)}
	#if (!ShowWhole)
		object {cutaway_object1}
	#end
	texture {sky_texture_a}
	rotate +z * city_rotate
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
	rotate +z * city_rotate
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
	rotate +z * city_rotate
}
