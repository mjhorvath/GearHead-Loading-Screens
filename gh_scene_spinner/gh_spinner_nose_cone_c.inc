#local glass_cone = difference
{
	object
	{
		Paraboloid_Z
		scale nose_cone_radius
		translate -z * ext_glass_thick/2
	}
	object
	{
		Paraboloid_Z
		scale nose_cone_radius
		translate +z * ext_glass_thick/2
	}
	bounded_by
	{
		#local x_new = nose_cone_radius/4 * nose_cone_length * 2;
		#local z_new = nose_cone_radius/4 * pow(nose_cone_length, 2);
		cylinder {-z * (ext_glass_thick/2), +z * (z_new + ext_glass_thick/2), (x_new + ext_glass_thick/2)}
	}
}
#local metal_cone = difference
{
	object
	{
		Paraboloid_Z
		scale nose_cone_radius
		translate -z * (nose_wire_radius_thick + metal_thick)
	}
	object
	{
		Paraboloid_Z
		scale nose_cone_radius
		translate -z * (nose_wire_radius_thick)
	}
	bounded_by
	{
		#local x_new = nose_cone_radius/4 * 1/2 * 2;
		#local z_new = nose_cone_radius/4 * pow(1/2, 2);
		cylinder {-z * (nose_wire_radius_thick + metal_thick), +z * (z_new - nose_wire_radius_thick), (x_new + metal_thick/2)}
	}
}


//------------------------------------------------------------------------------solid glass cone

// looks better but is too slow!!
#if ((!NoNoseGrid) & (NoseMode = 0))
	difference
	{
		intersection
		{
			object {glass_cone}
			plane {+z, nose_cone_radius/4 * pow(nose_cone_length, 2)}
			texture {nose_shield_combined_texture scale nose_cone_radius/2}
			rotate +y * 180
		}
		#if (!ShowWhole)
			object {cutaway_object1}
		#end
		texture {white_metal_texture}
		translate +z * (hab_total_length/2 + nose_cone_position)
	}
#end


//------------------------------------------------------------------------------metal mesh cone

#if ((!NoNoseGrid) & (NoseMode = 1))
	difference
	{
		union
		{
/*
			// thick radial tubes
			#local x_old = 0;
			#local z_old = 0;
			#for (i, nose_wire_para_thick, nose_cone_length, nose_wire_para_thick)
				#local x_new = nose_cone_radius/4 * i * 2;
				#local z_new = nose_cone_radius/4 * pow(i, 2);
				#for (j, 1, 24)
					cylinder
					{
						<+x_old,0,z_old>, <+x_new,0,z_new>, nose_wire_radius_thick
						rotate +z * j * 360/24
					}
				#end
				#local x_old = x_new;
				#local z_old = z_new;
			#end
			// thick z axis tubes
			#for (i, nose_wire_para_thick, nose_cone_length, nose_wire_para_thick)
				#local x_new = nose_cone_radius/4 * i * 2;
				#local z_new = nose_cone_radius/4 * pow(i, 2);
				torus
				{
					x_new, nose_wire_radius_thick
					rotate +x * 90
					translate +z * z_new
				}
			#end
*/
			// thin radial tubes
			#local x_old = 0;
			#local z_old = 0;
			#for (i, nose_wire_para_thin, nose_cone_length, nose_wire_para_thin)
				#local x_new = nose_cone_radius/4 * i * 2;
				#local z_new = nose_cone_radius/4 * pow(i, 2);
				#for (j, 1, 24)
					cylinder
					{
						<+x_old,0,z_old>, <+x_new,0,z_new>, nose_wire_radius_thin
						rotate +z * j * 360/24
					}
				#end
				#local x_old = x_new;
				#local z_old = z_new;
			#end
			// thin z axis tubes
			#for (i, nose_wire_para_thin, nose_cone_length, nose_wire_para_thin)
				#local x_new = nose_cone_radius/4 * i * 2;
				#local z_new = nose_cone_radius/4 * pow(i, 2);
				torus
				{
					x_new, nose_wire_radius_thin
					rotate +x * 90
					translate +z * z_new
				}
			#end
			rotate +y * 180
		}
		#if (!ShowWhole)
			object {cutaway_object1}
		#end
		texture {nose_shield_metal_texture}
//		texture {white_metal_texture}
		translate +z * (hab_total_length/2 + nose_cone_position)
	}
#end


//------------------------------------------------------------------------------metal tip

#local i = 1/3;
#local x_new = nose_cone_radius/4 * i * 2;
#local z_new = nose_cone_radius/4 * pow(i, 2);
intersection
{
	object {metal_cone}
	plane {+z, z_new}
	rotate +y * 180
	texture {white_metal_texture}
	translate +z * (hab_total_length/2 + nose_cone_position - metal_thick)
}


//------------------------------------------------------------------------------connector ring and spindle

#local ring_thick = metal_thick/2;
#local z_new = nose_cone_position - main_strut_width/2;
#local i = sqrt(4 * z_new/nose_cone_radius);
#local x_new = nose_cone_radius/4 * i * 2;
#local j_max = 3;
#local j_amt = 360/j_max;
difference
{
	union
	{
		torus
		{
			x_new, ring_thick
			rotate +x * 90
		}
		#for (j, 1, j_max)
			cylinder
			{
				+x * outer_shell_radius1, +x * x_new, ring_thick
				rotate +z * j * j_amt
			}
		#end
	}
	#if (!ShowWhole)
		object {cutaway_object1}
	#end
	texture {white_metal_texture}
//	rotate		+z * 360/12
	translate	+z * (hab_total_length/2 + main_strut_width/2)
}

#local z_new = nose_cone_position + hab_total_length/2 + engine_start + engine_length + main_strut_width/2;
//#local z_new = nose_cone_position + hab_total_length/2 + engine_start;
#local i = sqrt(4 * z_new/nose_cone_radius);
#local x_new = nose_cone_radius/4 * i * 2;
#local j_max = 3;
#local j_amt = 360/j_max;
#local x_dif = x_new - outer_shell_radius1;
difference
{
	union
	{
		torus
		{
			x_new, ring_thick
			rotate +x * 90
		}
/*
		torus
		{
			outer_shell_radius1 + x_dif/2, ring_thick
			rotate +x * 90
		}
*/
		#for (j, 1, j_max)
			cylinder
			{
				+x * outer_shell_radius1, +x * x_new, ring_thick
				rotate +z * j * j_amt
			}
		#end
	}
	#if (!ShowWhole)
		object {cutaway_object1}
	#end
	texture {white_metal_texture}
//	rotate		+z * 360/12
	translate	-z * (engine_start + engine_length - main_strut_width/2)
//	translate	-z * (engine_start)
}


//------------------------------------------------------------------------------trumpet attachment to body of ship

#local trumpet_radius = Meters * 32;
#local trumpet_length = nose_cone_position - inner_shell_bulge - metal_thick * 3;
#local nose_Fx2 = function(u,v) {v}
#local nose_Fy2 = function(u,v) {trumpet_radius/pow(v+1,0.5)*cos(u)}
#local nose_Fz2 = function(u,v) {trumpet_radius/pow(v+1,0.5)*sin(u)}
object
{
	Parametric(nose_Fx2,nose_Fy2,nose_Fz2,<0,0>,<2*pi,trumpet_length>,30,30,"")
	rotate -y * 90
	texture {white_metal_texture}
	translate +z * (hab_total_length/2 + inner_shell_bulge + metal_thick * 3)
}


//------------------------------------------------------------------------------comms objects

#declare truss_sides = 6;
#declare truss_sections = 1;
#declare truss_radius = Meters*16;
#declare truss_thickness = Meters/2;
#declare truss_point1 = -z*Meters*16;
#declare truss_point2 = 0;
#local comm_truss = object
{
	verbose_include("truss.inc", 0)
	texture {white_metal_texture}
}
#local comm_dish = union
{
	difference
	{
		object {Paraboloid_Z}
		object {Paraboloid_Z	scale 0.999}
		plane {-z, -0.05}
		rotate y * 180
		scale		Meters * 64
	}
	cylinder {<0,0,0>, <0,0,-Meters*8>, Meters/2}
	scale 2
	translate -z * Meters * 16
}
#local comm_dome = sphere {-z*Meters*16, Meters*16}
#local comm_anten = union
{
	cylinder {<0,0,0>, <0,0,-antenna_length/4>, Meters}
	cylinder {<0,0,0>, <0,0,-antenna_length/1>, Meters/2}
	object {blinky_sphere(blinky_radius) translate <0,0,-antenna_length/1-blinky_radius>}
	cylinder {<0,-antenna_offset,0>, <0,-antenna_offset,-antenna_length/8>, Meters}
	cylinder {<0,-antenna_offset,0>, <0,-antenna_offset,-antenna_length/2>, Meters/2}
	object {blinky_sphere(blinky_radius) translate <0,-antenna_offset,-antenna_length/2-blinky_radius>}
}
union
{
	object
	{
		comm_dome
		translate	-y * antenna_offset
		rotate		+z * 240
	}
	object
	{
		comm_truss
		translate	-y * antenna_offset
		rotate		+z * 240
	}
	object
	{
		comm_dish
		translate	-y * antenna_offset
		rotate		+z * 120
	}
	object
	{
		comm_truss
		translate	-y * antenna_offset
		rotate		+z * 120
	}
	object
	{
		comm_anten
	}
	rotate		+y * 180
	texture {white_metal_texture}
	translate 	+z * (hab_total_length/2 + nose_cone_position - Meters * 8)
}
